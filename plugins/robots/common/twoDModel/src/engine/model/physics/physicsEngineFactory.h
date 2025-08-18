#pragma once

#include <QtGui/QVector2D>
#include <QtGui/QPainterPath>

namespace twoDModel {

namespace model {

class WorldModel;
class RobotModel;
namespace physics {

class PhysicsEngineBase;

/// A factory for creating physics engine objects
class PhysicsEngineFactory : public QObject
{
	Q_OBJECT

public:
	PhysicsEngineFactory() = default;

	using CreateEngineCallback = std::function<PhysicsEngineBase *(
	        const twoDModel::model::WorldModel &,
	        const QList<twoDModel::model::RobotModel *> &)>;

	virtual CreateEngineCallback create(bool isRealistic) const;
};

}
}
}
