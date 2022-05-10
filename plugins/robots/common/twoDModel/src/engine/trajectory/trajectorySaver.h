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

#pragma once

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

/// Main class for saving trajectories of all dynamic objects on scene (robot, ball, skittle)
/// Saves trajectory as a sequence of frames. Frame is a scene state in particular moment.
/// Every frame consists of states. State describes status of a single object
class TrajectorySaver : public QObject
{
	Q_OBJECT
public:
	TrajectorySaver(QObject *parent);

private:
	ConnectionToVizualizator *connToVizualizator = nullptr;

	bool isPlaying = false;
	QJsonArray frames;
	QJsonArray currStates;

	void sendTrajectory(const QString &data);
	void addState(const QString &id, const QPointF &pos, const qreal &rotation);

	QJsonObject createState(const QString &id, const QString &stateStr);
	QJsonObject saveFrame();

	void reinitConnection();

public slots:
	/// Emitted when robot/ball/skittle is moved by user. It can happen while playing or not.
	void onItemDragged(const QString &id, const QPointF &pos, const qreal &rotation);

	/// Saves position and angle of robot. Emitted when nextFragment is playing,
	/// saves position and angle of balls/skittles. Emitted when nextFrame is playing
	void saveItemPosOrAngle(const QString &id, const QPointF &pos, const qreal &rotation);

	/// Emitted when robot plays beep sound, saves beeping time in ms
	void saveBeepState(const QString &robotId, int time);

	/// Emitted when robot places marker up or down, saves marker color:
	/// if marker is down, color is equal to marker color, if marker is ip,
	/// color is transparent
	void saveMarkerState(const QString &robotId, const QColor &color);

	/// Emitted when robot stops
	void saveToFile();

	/// Emitted when one frame is played, sends frame/set of frames
	/// (depends on perfomance) to server in Json Compact format
	void sendFrame();

	/// Emitted when user presses "Stop" button in vizualizator
	void onStopInterpretation();
};
