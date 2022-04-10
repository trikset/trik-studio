#ifndef TRAJECTORYSAVER_H
#define TRAJECTORYSAVER_H

#include <sstream>
#include <vector>

#include <QFrame>
#include <QPointF>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

#include <qrutils/graphicsUtils/abstractItem.h>
#include "trajectorySender.h"

using namespace std;

class TrajectorySaver : public QObject
{
    Q_OBJECT
public:
    TrajectorySaver(QObject *parent);

private:
    //map<QString, vector<string>> movableObjStream;
    TrajectorySender *trajSender = nullptr;
    //qint32 frameNumber = 0;
    bool sendData = true;
    bool isPlaying = false;
    QJsonArray frames;
    QJsonArray currStates;

    void SendTrajectory(QString data);
    void addState(QString id, QPointF pos, qreal rotation);

    QJsonObject createState(string id, string stateStr);
    QJsonObject SaveFrames();
    QJsonObject SaveFrame();

public slots:

    void SaveItemPosOrAngle(QString id, QPointF pos, qreal rotation);
    void SaveBeepState(QString robotId, int time);
    void SaveMarkerState(QString robotId, QColor color);
    void SaveToFile();
    void SendFrame();

//    void OnStartInterpretation();
    void OnStopInterpretation();

    void OnItemDragged(QString id, QPointF pos, qreal rotation);
};
#endif // TRAJECTORYSAVER_H
