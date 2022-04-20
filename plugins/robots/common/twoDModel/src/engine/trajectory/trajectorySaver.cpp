#include "trajectorySaver.h"
#include <iostream>
#include <fstream>
#include <QFile>
#include <QtGlobal>
#include "connectionToVizualizator.h"

/// Saves trajectory like sequence of frames

TrajectorySaver::TrajectorySaver(QObject *parent)
	: QObject(parent) {}

void TrajectorySaver::saveBeepState(QString robotId, int time)
{
	stringstream value;
	value << "beepState=" << time;
	currStates.append(createState(robotId.toStdString(), value.str()));
}

void TrajectorySaver::saveMarkerState(QString robotId, QColor color)
{
	stringstream value;
	value << "markerState=" << color.red() << " " << color.green() << " " << color.blue() << " " << color.alpha();
	currStates.append(createState(robotId.toStdString(), value.str()));
}

void TrajectorySaver::saveItemPosOrAngle(QString id, QPointF pos, qreal rotation)
{
	addState(id, pos, rotation);
	isPlaying = true;
}

QJsonObject TrajectorySaver::createState(string id, string stateStr)
{
	QJsonObject state;
	state.insert("id", id.c_str());
	state.insert("state", stateStr.c_str());
	return state;
}

void TrajectorySaver::onItemDragged(QString id, QPointF pos, qreal rotation)
{
	addState(id, pos, rotation);
	if (!isPlaying) {
		sendFrame();
	}
}

void TrajectorySaver::addState(QString id, QPointF pos, qreal rotation)
{
	stringstream value;
	value << "pos=" << pos.x() << " " << -pos.y();
	value << "|rot=" << rotation;

	auto state = createState(id.toStdString(), value.str());
	if (!currStates.contains(QJsonValue(state))) {
		//qDebug(qUtf8Printable(id));
		/// to avoid duplicates, it can be because onItemDragged calls when
		/// objects is moved by other object or by user
		currStates.append(state);
	}
}

void TrajectorySaver::sendFrame()
{
	if (sendData) {
		auto frame = saveFrame();
		QJsonDocument doc;
		doc.setObject(frame);
		QString data (doc.toJson( QJsonDocument::Compact));
		try {
			//qDebug(qPrintable(doc.toJson()));
			sendTrajectory(data);
		} catch (exception e) {
			}
	}
}

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
	if( file.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate ) ) {
		QTextStream iStream( &file );
		iStream.setCodec( "utf-8" );
		iStream << bytes;
		file.close();
	}
}

void TrajectorySaver::sendTrajectory(QString data = nullptr)
{
	if (connToVizualizator == nullptr) {
		connToVizualizator = new ConnectionToVizualizator();
		connToVizualizator->init();
		connToVizualizator->setPort(8080);
		connToVizualizator->connectToHost();
	} else if (!connToVizualizator->isConnected()) {
		connToVizualizator->connectToHost();
	}

	if (data != nullptr) {
		connToVizualizator->write(data);
	} else {
		QFile file("trajectory.json");
		if (file.open(QIODevice::ReadOnly)) {
			QString fileData = file.readAll();
			connToVizualizator->write(fileData);
			file.close();
		}
		//connToVizualizator->reset();
	}
}

void TrajectorySaver::onStopInterpretation()
{
	isPlaying = false;
}
