/* Copyright 2022 Lada Egorova
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

#include "trajectorySaver.h"
#include <iostream>
#include <fstream>
#include <QFile>
#include <QtGlobal>
#include <QsLog.h>

TrajectorySaver::TrajectorySaver(QObject *parent)
	: QObject(parent)
{
	connToVizualizator = new ConnectionToVizualizator();
	connToVizualizator->setPort(8080);
	connToVizualizator->init();
}

void TrajectorySaver::saveBeepState(QString robotId, int time)
{
	stringstream value;
	value << "beepState=" << time;
	currStates.append(createState(robotId, value.str().c_str()));
}

void TrajectorySaver::saveMarkerState(QString robotId, QColor color)
{
	stringstream value;
	value << "markerState=" << color.red() << " " << color.green() << " " << color.blue() << " " << color.alpha();
	currStates.append(createState(robotId, value.str().c_str()));
}

void TrajectorySaver::saveItemPosOrAngle(QString id, QPointF pos, qreal rotation)
{
	addState(id, pos, rotation);
	isPlaying = true;
}

void TrajectorySaver::onItemDragged(QString id, QPointF pos, qreal rotation)
{
	addState(id, pos, rotation);
	if (!isPlaying) {
		sendFrame();
	}
}

/// Syntactic sugar for onItemDragged and saveItemPosOrState
void TrajectorySaver::addState(QString id, QPointF pos, qreal rotation)
{
	stringstream value;
	value << "pos=" << pos.x() << " " << -pos.y();
	value << "|rot=" << rotation;

	auto state = createState(id, value.str().c_str());
	if (!currStates.contains(QJsonValue(state))) {
		//qDebug(qUtf8Printable(id));
		/// to avoid duplicates, it can be because onItemDragged calls when
		/// objects is moved by other object or by user
		currStates.append(state);
	}
}

QJsonObject TrajectorySaver::createState(QString id, QString stateStr)
{
	QJsonObject state;
	state.insert("id", id);
	state.insert("state", stateStr);
	return state;
}

void TrajectorySaver::sendFrame()
{
	if (connToVizualizator->isSendingData())
	{
		auto frame = saveFrame();
		QJsonDocument doc;
		doc.setObject(frame);
		QString data (doc.toJson( QJsonDocument::Compact));

		sendTrajectory(data);
	}
}

/// Appends current frame to all frames
QJsonObject TrajectorySaver::saveFrame()
{
	QJsonObject frame;
	frame.insert("frame", currStates);
	frames.append(frame);
	/// updating current states every frame
	currStates = *new QJsonArray();
	return frame;
}

void TrajectorySaver::saveToFile()
{
	sendFrame();

	/// creating json document
	QJsonDocument doc;
	QJsonObject root;
	root.insert("frames", frames);
	doc.setObject(root);
	QByteArray bytes = doc.toJson( QJsonDocument::Compact );

	/// saving it to file
	QFile file("trajectory.json");
	try {
		file.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate );
		QTextStream iStream( &file );
		iStream.setCodec( "utf-8" );
		iStream << bytes;
		file.close();
	}
	catch (const ofstream::failure& e){
		QLOG_ERROR() << "Exception occured when opening/writing to file"
		<< e.what();
	}
}

void TrajectorySaver::reinitConnection()
{
	if (connToVizualizator == nullptr) {
		connToVizualizator = new ConnectionToVizualizator();
		connToVizualizator->setPort(8080);
		connToVizualizator->init();
	}
	connToVizualizator->connectToHost();
//	qDebug(qPrintable(connToVizualizator->getIp()));
}

void TrajectorySaver::sendTrajectory(QString data = nullptr)
{
	if (connToVizualizator == nullptr || !connToVizualizator->isConnected()) {
		reinitConnection();
	}

//	qDebug(qPrintable(data));
	if (data != nullptr) {
		connToVizualizator->write(data);
	} else {
		QFile file("trajectory.json");
		try {
			file.open(QIODevice::ReadOnly);
			QString fileData = file.readAll();
			connToVizualizator->write(fileData);
			file.close();
		} catch (const ofstream::failure& e){
			QLOG_ERROR() << "Exception occured when opening/writing to file"
			<< e.what();
		}
	}
}

void TrajectorySaver::onStopInterpretation()
{
	isPlaying = false;
}
