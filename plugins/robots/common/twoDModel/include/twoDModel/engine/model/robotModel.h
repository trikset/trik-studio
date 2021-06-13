/* Copyright 2007-2015 QReal Research Group
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

#include <QtGui/QPainterPath>

#include <utils/circularQueue.h>

#include <QPointer>

#include "twoDModel/robotModel/twoDRobotModel.h"
#include "sensorsConfiguration.h"

#include "twoDModel/twoDModelDeclSpec.h"

class QGraphicsItem;

namespace twoDModel {

namespace items {
class StartPosition;
class MovableItem;
}

namespace model {

class Settings;
namespace physics {
class PhysicsEngineBase;
}

class WorldModel;
class Timeline;

class TWO_D_MODEL_EXPORT RobotModel : public QObject
{
	Q_OBJECT

	Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
	Q_PROPERTY(qreal x READ x)
	Q_PROPERTY(qreal y READ y)

public:
	enum ATime {
		DoInf,
		DoByLimit,
		End
	};

	enum WheelEnum {
		left
		, right
	};

	struct Wheel
	{
		int radius;
		int speed;
		int spoiledSpeed;
		int degrees;
		ATime activeTimeType;
		bool isUsed;
		bool breakMode;
	};

	RobotModel(twoDModel::robotModel::TwoDRobotModel &robotModel
			, const Settings &settings, QObject *parent = nullptr);

	~RobotModel();

	void reinit();

	void clear();
	void stopRobot();
	void playSound(int timeInMs);
	QPointF alignToGrid(QPointF pos) const;

	Q_INVOKABLE void setNewMotor(int speed, uint degrees, const kitBase::robotModel::PortInfo &port, bool breakMode);

	SensorsConfiguration &configuration();

	/// Returns information about the robot`s left wheel state (its size, speed, encoder value, etc).
	const Wheel &leftWheel() const;

	/// Returns information about the robot`s right wheel state (its size, speed, encoder value, etc).
	const Wheel &rightWheel() const;

	/// Returns a reference to external robot description.
	robotModel::TwoDRobotModel &info() const;

	Q_INVOKABLE int readEncoder(const kitBase::robotModel::PortInfo &port) const;
	Q_INVOKABLE void resetEncoder(const kitBase::robotModel::PortInfo &port);

	QPointF position() const;
	void setPosition(const QPointF &newPos);

	qreal rotation() const;
	void setRotation(qreal angle);

	qreal x() const;
	qreal y() const;

	/// Returns false if robot item is dragged by user at the moment.
	bool onTheGround() const;

	QDomElement serialize(QDomElement &parent) const;
	void deserialize(const QDomElement &robotElement);

	void onRobotLiftedFromGround();
	void onRobotReturnedOnGround();

	void setMotorPortOnWheel(WheelEnum wheel, const kitBase::robotModel::PortInfo &port);

	QRectF sensorRect(const kitBase::robotModel::PortInfo &port, const QPointF sensorPos) const;
	QPainterPath sensorBoundingPath(const kitBase::robotModel::PortInfo &port) const;
	QTransform robotsTransform() const;

	/// Returns the color of the trace that robot should draw. Transparent color may also be returned
	/// (then it is highly recommended not to draw trace at all in preformance thoughts).
	QColor markerColor() const;

	/// Moves the marker of the 2D model robot down to the floor.
	/// The robot will draw its trace on the floor after that.
	/// If the marker of another color is already drawing at the moment it will be replaced.
	void markerDown(const QColor &color);

	/// Lifts the marker of the 2D model robot up.
	/// The robot stops drawing its trace on the floor after that.
	void markerUp();

	/// Returns a position of the center of the robot in scene coordinates.
	QPointF robotCenter() const;

	/// Returns the item whose scene position will determine robot`s start position.
	items::StartPosition *startPositionMarker();

	/// Returns accelerometer sensor data.
	Q_INVOKABLE QVector<int> accelerometerReading() const;

	/// Returns gyroscope sensor data:
	/// data[0] -- angular velocity over Z axis (millidegrees per second)
	/// data[1] -- tilt around Z axis (millidegrees)
	Q_INVOKABLE QVector<int> gyroscopeReading() const;

	Q_INVOKABLE QVector<int> gyroscopeCalibrate();

	/// Returns a bounding path of robot and its sensors in scene coordinates.
	QPainterPath robotBoundingPath(const bool withSensors = true) const;

	/// Sets a physical engine. Robot recalculates its position using this engine.
	void setPhysicalEngine(physics::PhysicsEngineBase &engine);

	void setWorldModel(WorldModel &worldModel);
public slots:
	void recalculateParams();
	void nextFragment();

signals:
	void positionChanged(const QPointF &newPosition);
	void rotationChanged(qreal newRotation);

	void deserialized(QPointF newPosition, qreal newRotation);

	/// Emitted when robot rided himself (moved on motors force, not dragged by user or smth) from one point to other.
	void robotRided(const QPointF &newPosition, const qreal newRotation);

	/// Same as robotRided(), but emitted each timeline tick (robotRided() emitted each frame).
	void positionRecalculated(const QPointF &newPosition, const qreal newRotation);

	/// Emitted with parameter 'true' when robot starts playing sound and 'false' if playing sound complete.
	void playingSoundChanged(bool playing);

	/// Emitted when left or right wheel was reconnected to another port.
	void wheelOnPortChanged(WheelEnum wheel, const kitBase::robotModel::PortInfo &port);

private slots:
	void moveCell(int n);
	void turnOn(qreal angle);

private:
	QVector2D robotDirectionVector() const;

	Wheel *initMotor(int radius, int speed, uint64_t degrees, const kitBase::robotModel::PortInfo &port, bool isUsed);

	void countNewForces();
	void countBeep();
	void countSpeedAndAcceleration();

	void countMotorTurnover();

	void synchronizePositions();

	void nextStep();
	QRectF aheadRect() const;
	qreal roundPos(qreal pos) const;
	int varySpeed(const int speed) const;

	void serializeWheels(QDomElement &robotElement) const;
	void deserializeWheels(const QDomElement &robotElement);

	QPointF averageAcceleration() const;

	/// Simulated robot motors.
	/// Has ownership.
	QHash<kitBase::robotModel::PortInfo, QSharedPointer<Wheel>> mMotors;
	/// Stores how many degrees the motor rotated on.
	QHash<kitBase::robotModel::PortInfo, qreal> mTurnoverEngines;
	/// Describes which wheel is driven by which motor.
	QHash<WheelEnum, kitBase::robotModel::PortInfo> mWheelsToMotorPortsMap;
	QHash<kitBase::robotModel::PortInfo, kitBase::robotModel::PortInfo> mMotorToEncoderPortMap;

	const Settings &mSettings;
	twoDModel::robotModel::TwoDRobotModel &mRobotModel;
	SensorsConfiguration mSensorsConfiguration;

	QPointF mPos { 0, 0 };
	qreal mAngle { 0 };
	qreal mGyroAngle { 0 };
	qreal mDeltaDegreesOfAngle { 0 };
	int mBeepTime { 0 };
	bool mIsOnTheGround { true };
	QPointF mWaitPos;
	QPointF mLiftedPos;
	bool mIsCollide { false };
	bool mIsRiding { false };
	QColor mMarker;
	QPointF mAcceleration { 0, 0 };
	utils::CircularQueue<QPointF> mPosStamps;
	bool mIsFirstAngleStamp { true };
	qreal mAngleStampPrevious { 0 };

	physics::PhysicsEngineBase *mPhysicsEngine {};  // Does not take ownership
	WorldModel *mWorldModel{};  // Does not take ownership

	QPointer<items::StartPosition> mStartPositionMarker;
};

}
}
