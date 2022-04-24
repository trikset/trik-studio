#include "trajectorySaver.h"
#include <iostream>
#include <fstream>
#include <QFile>
#include <QtGlobal>
#include "connectionToVizualizator.h"

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

	auto state = createState(id.toStdString(), value.str());
	if (!currStates.contains(QJsonValue(state))) {
		//qDebug(qUtf8Printable(id));
		/// to avoid duplicates, it can be because onItemDragged calls when
		/// objects is moved by other object or by user
		currStates.append(state);
	}
}

QJsonObject TrajectorySaver::createState(string id, string stateStr)
{
	QJsonObject state;
	state.insert("id", id.c_str());
	state.insert("state", stateStr.c_str());
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

		try {
			sendTrajectory(data);
		} catch (exception e) {}
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
	if( file.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate ) ) {
		QTextStream iStream( &file );
		iStream.setCodec( "utf-8" );
		iStream << bytes;
		file.close();
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
		if (file.open(QIODevice::ReadOnly)) {
			QString fileData = file.readAll();
			connToVizualizator->write(fileData);
			file.close();
		}
	}
}

void TrajectorySaver::onStopInterpretation()
{
	isPlaying = false;
}
