#ifndef TRAJECTORYSAVER_H
#define TRAJECTORYSAVER_H

#include <QFrame>
#include <QPointF>
#include <sstream>

#include <qrutils/graphicsUtils/abstractItem.h>
#include "thirdparty/gamepad/gamepad/connectionToVizualize.h"

using namespace std;

class TrajectorySaver : public QObject
{
    Q_OBJECT
public:
    TrajectorySaver(QObject *parent) : QObject(parent) {}

private:
    map<QString, stringstream> robotStreams;
    map<QString, stringstream> movableObjStream;

    void SaveToTrajectory();
    void SendTrajectory();
public slots:
    ///void SaveItemPosOrAngle(graphicsUtils::AbstractItem *item);
    void SaveItemPosOrAngle(graphicsUtils::AbstractItem *item, bool wasMoving);

    void SaveRobotPosOrAngle(QString robotId, QPointF pos, qreal rotation);
    void SaveBeepState(QString robotId, int time);
    void SaveMarkerState(QString robotId, QColor color);
    void SaveToFile();
};
#endif // TRAJECTORYSAVER_H
