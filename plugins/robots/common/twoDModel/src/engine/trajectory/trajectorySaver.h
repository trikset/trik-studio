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
#include "connectionToVizualizator.h"

using namespace std;

/// Main class for saving trajectories of all dynamic objects on scene
class TrajectorySaver : public QObject
{
	Q_OBJECT
public:
	TrajectorySaver(QObject *parent);

private:

	ConnectionToVizualizator *connToVizualizator = nullptr;

	/// TODO: add option to switch this
	bool sendData = true;
	bool isPlaying = false;
	QJsonArray frames;
	QJsonArray currStates;

	/// methods
	void sendTrajectory(QString data);
	void addState(QString id, QPointF pos, qreal rotation);

	QJsonObject createState(string id, string stateStr);
	QJsonObject saveFrame();

public slots:
	// Emitted when user moves robot or ball/skittle on scene
	void onItemDragged(QString id, QPointF pos, qreal rotation);

	// Emitted when item is moving
	void saveItemPosOrAngle(QString id, QPointF pos, qreal rotation);

	// Emitted when robot plays beep sound
	void saveBeepState(QString robotId, int time);

	// Emitted when robot places marker up or down
	void saveMarkerState(QString robotId, QColor color);

	// Emitted when robot stops
	void saveToFile();

	// Emitted when one frame is played. Sends frame to vizualizator
	void sendFrame();

//	void onStartInterpretation();

	// Emitted when user pushes "Stop" button in vizualizator
	void onStopInterpretation();
};
#endif // TRAJECTORYSAVER_H
