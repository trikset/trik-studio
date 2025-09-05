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

#include "physicsEngineFactory.h"
#include "simplePhysicsEngine.h"
#include "box2DPhysicsEngine.h"
#include "twoDModel/engine/model/worldModel.h"

using namespace twoDModel::model::physics;

namespace  {

template <typename EngineType>
PhysicsEngineBase* createEngine(
	const twoDModel::model::WorldModel& world,
	const QList<twoDModel::model::RobotModel*>& robots)
{
	return new EngineType(world, robots);
}

}

PhysicsEngineFactory::CreateEngineCallback
	PhysicsEngineFactory::create(bool isRealistic) const {
	if (isRealistic) {
		return std::bind(
		        &createEngine<Box2DPhysicsEngine>,
		        std::placeholders::_1, std::placeholders::_2);
	}

	return std::bind(
	        &createEngine<SimplePhysicsEngine>,
	        std::placeholders::_1, std::placeholders::_2);
}
