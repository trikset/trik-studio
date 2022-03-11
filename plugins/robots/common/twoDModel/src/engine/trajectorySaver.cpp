#include "trajectorySaver.h"
#include <iostream>
#include <fstream>
#include <QFile>

void TrajectorySaver::SaveBeepState(QString robotId, int time)
{
    robotStreams[robotId] << "beepState=" << time << "\r";
}

void TrajectorySaver::SaveMarkerState(QString robotId, QColor color)
{
    robotStreams[robotId] << "markerState=" << color.red() << " " << color.green() << " " << color.blue() << " " << color.alpha() << "\r";
}

void TrajectorySaver::SaveItemPosOrAngle(graphicsUtils::AbstractItem *item, bool wasMoving)
{
    if (!wasMoving)
    {
        movableObjStream[item->id()] << "still" << "\r";
    }
    QString newId = item->id();
    movableObjStream[item->id()] << "pos=" << item->pos().x() << " " << -item->pos().y() << "\r";
    movableObjStream[item->id()] << "rot=" << item->rotation() << "\r";
}

void TrajectorySaver::SaveRobotPosOrAngle(QString robotId, QPointF pos, qreal rotation)
{
    robotStreams[robotId] << "pos=" << pos.x() << " " << -pos.y() << "\r";
    robotStreams[robotId] << "rot=" << rotation << "\r";
}

void TrajectorySaver::SaveToFile()
{
    std::ofstream outFile("trajectory.txt");
    map<QString, stringstream> :: iterator it = robotStreams.begin();
    for ( ; it != robotStreams.end(); it++)
    {
        outFile << "robotId=" << it->first.toStdString() << "\r";
        outFile << it->second.rdbuf();
        outFile << "newRobot" << "\r";
    }
    outFile << "robotPart" << "\r";

    it = movableObjStream.begin();
    for ( ; it != movableObjStream.end(); it++)
    {
        outFile << "id=" << it->first.toStdString() << "\r";
        outFile << it->second.rdbuf();
        outFile << "newItem" << "\r";
    }
    outFile.close();
    SendTrajectory();
}

void TrajectorySaver::SendTrajectory()
{
//    ConnectionToVizualize *connectionManager = new ConnectionToVizualize();
//    connectionManager->setGamepadIp("192.168.1.7");
//    connectionManager->setGamepadPort(8888);
//    connectionManager->connectToHost(); // 192.168.77.1  4444
//    QFile file("trajectory.txt");
//    if (file.open(QIODevice::ReadOnly))
//    {
//        QString data = file.readAll();
//        connectionManager->write(data);
//        file.close();
//    }
//    connectionManager->reset();
}
