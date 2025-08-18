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
