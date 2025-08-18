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
