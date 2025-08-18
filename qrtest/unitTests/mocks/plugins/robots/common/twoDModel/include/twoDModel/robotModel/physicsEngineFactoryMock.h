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

#include <src/engine/model/physics/physicsEngineFactory.h>
#include "physicsEngineMock.h"

namespace qrTest {

class PhysicsEngineFactoryMock : public twoDModel::model::physics::PhysicsEngineFactory
{
	Q_OBJECT

public:
	CreateEngineCallback create(bool isRealistic) const override {
		Q_UNUSED(isRealistic)
		return std::bind([](const twoDModel::model::WorldModel &worldModel,
		                 const QList<twoDModel::model::RobotModel *> &robots){
			return new PhysicsEngineMock(worldModel, robots);
		}, std::placeholders::_1, std::placeholders::_2);
	}
};
}
