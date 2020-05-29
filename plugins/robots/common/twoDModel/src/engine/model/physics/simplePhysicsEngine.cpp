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

#include "simplePhysicsEngine.h"

#include <QtGui/QTransform>

#include <qrutils/mathUtils/math.h>
#include <qrutils/mathUtils/geometry.h>

#include "twoDModel/engine/model/robotModel.h"
#include "twoDModel/engine/model/constants.h"
#include "twoDModel/engine/model/worldModel.h"

using namespace twoDModel::model;
using namespace physics;
using namespace mathUtils;

SimplePhysicsEngine::SimplePhysicsEngine(const WorldModel &worldModel, const QList<RobotModel *> &robots)
	: PhysicsEngineBase(worldModel, robots)
{
}

QVector2D SimplePhysicsEngine::positionShift(RobotModel &robot) const
{
	return mPositionShift[&robot];
}

qreal SimplePhysicsEngine::rotation(RobotModel &robot) const
{
	return mRotation[&robot];
}

void SimplePhysicsEngine::recalculateParameters(qreal timeInterval)
{
	for (RobotModel * const robot : mRobots) {
		recalculateParameters(timeInterval, *robot);
	}
}

bool SimplePhysicsEngine::isRobotStuck() const
{
	return mStuck;
}

void SimplePhysicsEngine::recalculateParameters(qreal timeInterval, RobotModel &robot)
{
	if (mWorldModel.checkCollision(robot.robotBoundingPath())) {
		mPositionShift[&robot] = -mPositionShift[&robot];
		mRotation[&robot] = -mRotation[&robot];
		mStuck = true;
		return;
	}

	mPositionShift[&robot] = QVector2D();
	mRotation[&robot] = 0.0;
	mStuck = false;

	const qreal speed1 = wheelLinearSpeed(robot, robot.leftWheel());
	const qreal speed2 = wheelLinearSpeed(robot, robot.rightWheel());
	const qreal averageSpeed = (speed1 + speed2) / 2;

	if (!Math::eq(speed1, speed2)) {
		const qreal distBtwWheels = qAbs(robot.info().wheelsPosition()[0].y() - robot.info().wheelsPosition()[1].y());
		const auto shiftToCenter = robot.info().rotationCenter() - robot.info().robotCenter();
		const qreal gammaRadians = (speed1 - speed2) * timeInterval / distBtwWheels;
		const qreal gammaDegrees = gammaRadians * 180 / pi;
		qreal angularSpeed = gammaRadians / timeInterval;
		const qreal averageRadius = averageSpeed / angularSpeed;

		QTransform map;
		map.rotate(robot.rotation());
		map.translate(shiftToCenter.x(), shiftToCenter.y());
		map.translate(0, averageRadius);
		map.rotate(gammaDegrees);
		map.translate(0, -averageRadius);
		map.translate(-shiftToCenter.x(), -shiftToCenter.y());

		mPositionShift[&robot] = QVector2D(map.map(QPointF(0, 0)));
		mRotation[&robot] = gammaDegrees;
	} else {
		mPositionShift[&robot] = averageSpeed * timeInterval * Geometry::directionVector(robot.rotation());
	}
}
