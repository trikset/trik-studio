/* Copyright 2021 CyberTech Labs Ltd.
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

#include "rangeSensorItem.h"

namespace twoDModel {
namespace view {

/// Lidar sensor that can draw its scanning area.
class LidarSensorItem : public RangeSensorItem
{
	Q_OBJECT
	Q_INTERFACES(QGraphicsItem)

public:
	LidarSensorItem(const model::WorldModel &worldModel
			, model::SensorsConfiguration &configuration
			, const kitBase::robotModel::PortInfo &port
			, QPair<qreal, int> physicalParams
			, const QString &pathToImage
			, const QRect &imageSize
			);

protected:
	QPainterPath scanningRegion() const override;
	void customizePainter(QPainter *painter) const override;
};

}
}
