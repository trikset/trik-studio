/* Copyright 2017-2018 Dmitry Mordvinov, Gleb Zakharov, CyberTech Labs Ltd.
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

#include "src/engine/model/physics/box2DPhysicsEngine.h"

class b2World;
class b2Joint;
class b2Body;

namespace twoDModel {
namespace view {
	class SensorItem;
}

namespace model {
	class RobotModel;
namespace physics {
namespace parts {

class Box2DWheel;
class Box2DItem;


class Box2DRobot
{
public:
	Box2DRobot(twoDModel::model::physics::Box2DPhysicsEngine *mEngine
			, twoDModel::model::RobotModel * const robotModel
			, b2Vec2 pos
			, float angle);
	~Box2DRobot();

	void stop();
	void startStopping();
	void finishStopping();
	bool isStopping();

	void addSensor(const view::SensorItem &sensor);
	void removeSensor(const view::SensorItem &sensor);

	void moveToPoint(const b2Vec2 &destination);
	void setRotation(float angle);

	void reinitSensor(const view::SensorItem &sensor);
	void reinitSensors();

	void applyForceToCenter(const b2Vec2 &force, bool wake);

	b2Body *getBody();
	twoDModel::model::RobotModel *getRobotModel() const;
	Box2DWheel *getWheelAt(int i) const;

	// For debugging purpose
	const QPolygonF & getDebuggingPolygon() const;
	const QMap<const view::SensorItem *, Box2DItem *> &getSensors() const;

private:
	void connectWheels();
	void connectWheel(Box2DWheel &wheel);
	void connectSensor(const Box2DItem &sensor);

	b2Body *mBody; // Takes ownership
	QList<Box2DWheel *> mWheels; // Takes ownership
	QList<b2Joint *> mJoints; // Takes ownership
	QMap<const twoDModel::view::SensorItem *, parts::Box2DItem *> mSensors;  // Takes ownership on b2Sensor instances
	twoDModel::model::RobotModel * const mModel; // Doesn't take ownership
	twoDModel::model::physics::Box2DPhysicsEngine *mEngine; // Doesn't take ownership
	b2World &mWorld; // Doesn't take ownership

	b2Vec2 *mPolygon; // Takes ownership

	bool mIsStopping = false;

	QPolygonF mDebuggingDrawPolygon;
};

}
}
}
}
