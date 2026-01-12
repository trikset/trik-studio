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
	// NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init)
	PhysicsEngineMock(const twoDModel::model::WorldModel &worldModel,
	                  const QList<twoDModel::model::RobotModel *> &robots)
	        : PhysicsEngineBase(worldModel, robots) {};
	// clazy:excludeall=function-args-by-value,returning-void-expression
	MOCK_METHOD(void, addRobot, (twoDModel::model::RobotModel * const), (override));
	MOCK_METHOD(QVector2D, positionShift, (twoDModel::model::RobotModel &), (const, override));
	MOCK_METHOD(qreal, rotation, (twoDModel::model::RobotModel &), (const, override));
	MOCK_METHOD(void, removeRobot, (twoDModel::model::RobotModel * const), (override));
	MOCK_METHOD(void, recalculateParameters, (qreal), (override));
	MOCK_METHOD(bool, isRobotStuck, (), (const, override));
	// clazy:enable
};
}
