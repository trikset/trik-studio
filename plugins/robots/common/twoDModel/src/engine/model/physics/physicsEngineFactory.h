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
