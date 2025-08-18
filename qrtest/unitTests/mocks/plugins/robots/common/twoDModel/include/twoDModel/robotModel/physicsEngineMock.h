/* Copyright 2025 CyberTech Labs Ltd.
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

#include <src/engine/model/physics/physicsEngineBase.h>
#include "twoDModel/engine/model/robotModel.h"
#include <gmock/gmock.h>

namespace qrTest {

class PhysicsEngineMock : public twoDModel::model::physics::PhysicsEngineBase
{
	Q_OBJECT

public:
	PhysicsEngineMock(const twoDModel::model::WorldModel &worldModel,
	                  const QList<twoDModel::model::RobotModel *> &robots)
	        : PhysicsEngineBase(worldModel, robots) {};
	MOCK_CONST_METHOD1(positionShift, QVector2D(twoDModel::model::RobotModel &));
	MOCK_CONST_METHOD1(rotation, qreal(twoDModel::model::RobotModel &));
	MOCK_METHOD1(addRobot, void(twoDModel::model::RobotModel * const));
	MOCK_METHOD1(removeRobot, void(twoDModel::model::RobotModel * const));
	MOCK_METHOD1(recalculateParameters, void(qreal));
	MOCK_CONST_METHOD0(isRobotStuck, bool());
	MOCK_METHOD0(wakeUp, void());
	MOCK_METHOD0(clearForcesAndStop, void());
	MOCK_METHOD0(nextFrame, void());
};
}
