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
#include "connectionToVisualizer.h"
#include <iostream>
#include <fstream>
#include <QFile>
#include <QtGlobal>
#include <QsLog.h>

using namespace twoDModel::trajectory;

TrajectorySaver::TrajectorySaver(QObject *parent)
	: QObject(parent)
	, mConnToVisualizer(new ConnectionToVisualizer(this))
{
	mConnToVisualizer->setPort(8080);
	mConnToVisualizer->init();
}

TrajectorySaver::~TrajectorySaver()
{
	mConnToVisualizer->disconnectFromHost();
}

void TrajectorySaver::saveBeepState(const QString &robotId, const qreal &time)
{
	stringstream value;
	value << "beepState=" << time;
	currStates.append(createState(robotId, value.str().c_str()));
}

void TrajectorySaver::saveMarkerState(const QString &robotId, const QColor &color)
{
	stringstream value;
	value << "markerState=" << color.red() << " " << color.green() << " " << color.blue() << " " << color.alpha();
	currStates.append(createState(robotId, value.str().c_str()));
}

void TrajectorySaver::saveItemPosition(const QString &id, const QPointF &pos)
{
	stringstream value;
	value << "pos=" << pos.x() << " " << -pos.y();
	addState(id, value.str().c_str());
	isPlaying = true;
}

void TrajectorySaver::saveItemRotation(const QString &id, const qreal &rotation)
{
	stringstream value;
	value << "rot=" << rotation;
	addState(id, value.str().c_str());
	isPlaying = true;
}

void TrajectorySaver::onItemDragged()
{
	if (!isPlaying) {
		sendFrame();
	}
}

/// Syntactic sugar for onItemDragged and saveItemPosOrState
void TrajectorySaver::addState(const QString &id, const QString &value)
{
	auto state = createState(id, value);
	if (!currStates.contains(QJsonValue(state))) {
		//qDebug(qUtf8Printable(id));
		/// to avoid duplicates, it can be because onItemDragged calls when
		/// objects is moved by other object or by user
		currStates.append(state);
	}
}

QJsonObject TrajectorySaver::createState(const QString &id, const QString &stateStr)
{
	QJsonObject state;
	state.insert("id", id);
	state.insert("state", stateStr);
	return state;
}

void TrajectorySaver::sendFrame()
{
	auto frame = saveFrame();
	QJsonDocument doc;
	doc.setObject(frame);
	QString data (doc.toJson( QJsonDocument::Compact));
	if (mConnToVisualizer->isSendingData())
	{
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
	if (mConnToVisualizer == nullptr) {
//		mConnToVisualizer = new ConnectionToVisualizer();
		mConnToVisualizer->setPort(8080);
		mConnToVisualizer->init();
	}
	mConnToVisualizer->connectToHost();
//	qDebug(qPrintable(mConnToVisualizer->getIp()));
}

void TrajectorySaver::sendTrajectory(const QString &data = nullptr)
{
	if (mConnToVisualizer == nullptr || !mConnToVisualizer->isConnected()) {
		reinitConnection();
	}

//	qDebug(qPrintable(data));
	if (data != nullptr) {
		mConnToVisualizer->write(data);
	} else {
		QFile file("trajectory.json");
		try {
			file.open(QIODevice::ReadOnly);
			QString fileData = file.readAll();
			mConnToVisualizer->write(fileData);
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

void TrajectorySaver::onCleanRobotTrace(const QString &robotId)
{
	saveMarkerState(robotId, Qt::GlobalColor::transparent);
}
