#include "trajectorySaver.h"
#include <iostream>
#include <fstream>
#include <QFile>
#include "plugins/robots/thirdparty/trikRuntime/trikRuntime/trikNetwork/include/trikNetwork/connection.h"

TrajectorySaver::TrajectorySaver(QObject *parent)
    : QObject(parent) {}

QJsonObject TrajectorySaver::createState(string id, string stateStr)
{
    QJsonObject state;
    state.insert("id", id.c_str());
    state.insert("state", stateStr.c_str());
    return state;
}

void TrajectorySaver::SaveBeepState(QString robotId, int time)
{
    stringstream value;
    value << "beepState=" << time;
    currStates.append(createState(robotId.toStdString(), value.str()));
}

void TrajectorySaver::SaveMarkerState(QString robotId, QColor color)
{
    stringstream value;
    value << "markerState=" << color.red() << " " << color.green() << " " << color.blue() << " " << color.alpha();
//    movableObjStream[robotId].back().append(value.str());
    currStates.append(createState(robotId.toStdString(), value.str()));
}

void TrajectorySaver::SaveItemPosOrAngle(QString id, QPointF pos, qreal rotation)
{
    addState(id, pos, rotation);
    isPlaying = true;
}

void TrajectorySaver::OnItemDragged(QString id, QPointF pos, qreal rotation)
{
    addState(id, pos, rotation);
    if (!isPlaying)
    {
        SendFrame();
    }
}

void TrajectorySaver::addState(QString id, QPointF pos, qreal rotation)
{
    stringstream value;
    value << "pos=" << pos.x() << " " << -pos.y();
    value << "|rot=" << rotation;
    auto state = createState(id.toStdString(), value.str());
    if (!currStates.contains(state)) {
        currStates.append(state);
    }
}

void TrajectorySaver::SendFrame()
{
    if (sendData) {
        auto frame = SaveFrame();
        QJsonDocument doc;
        doc.setObject(frame);
        QString data (doc.toJson( QJsonDocument::Indented));
        SendTrajectory(data);
    }
}

QJsonObject TrajectorySaver::SaveFrame()
{
    QJsonObject frame;
    frame.insert("frame", currStates);
    frames.append(frame);
    currStates = *new QJsonArray();
    return frame;
}

QJsonObject TrajectorySaver::SaveFrames()
{
    QJsonObject root;
//    QJsonArray frames_array;
    //auto it = movableObjStream.begin();
    //int len = it->second.size();
//    for (qreal i = 0; i < len; ++i) {
//        auto frame = SaveFrame();
//        frames_array.append(frame);
//        it = movableObjStream.begin();
//    }
    root.insert("frames", frames);
    return root;
}

//frame1: { "ball1: ".."
//}

void TrajectorySaver::SaveToFile()
{
    QJsonDocument doc;

    auto frames = SaveFrames();
    doc.setObject(frames);
    QByteArray bytes = doc.toJson( QJsonDocument::Indented );
    QFile file("trajectory.json");
    if( file.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate ) ) {
        QTextStream iStream( &file );
        iStream.setCodec( "utf-8" );
        iStream << bytes;
        file.close();
    }
}

void TrajectorySaver::SendTrajectory(QString data = nullptr)
{
    if (trajSender == nullptr) {
        trajSender = new TrajectorySender();
        trajSender->init();
        trajSender->setIp("10.0.5.2");
        trajSender->setPort(8080);
        trajSender->connectToHost();
    } else if (!trajSender->isConnected()) {
        trajSender->connectToHost();
    }

    if (data != nullptr) {
        trajSender->write(data);
    } else {
        QFile file("trajectory.json"); // 192.168.1.7 192.168.56.1 10.0.2.2:9000 10.10.10.72 192.168.56.105
        if (file.open(QIODevice::ReadOnly)) {
            QString fileData = file.readAll();
            trajSender->write(fileData);
            file.close();
        }
        trajSender->reset();
    }
}

//void TrajectorySaver::OnStartInterpretation()
//{
//    isPlaying = true;
//}

void TrajectorySaver::OnStopInterpretation()
{
    isPlaying = false;
}
