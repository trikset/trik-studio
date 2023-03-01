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

#include "lidarSensorItem.h"

using namespace twoDModel::view;
using namespace kitBase::robotModel;

LidarSensorItem::LidarSensorItem(const model::WorldModel &worldModel
		, model::SensorsConfiguration &configuration
		, const PortInfo &port
		, QPair<qreal, int> angleAndRange
		, const QString &pathToImage
		, const QRect &imageSize
		)
	: RangeSensorItem(worldModel, configuration, port, angleAndRange, pathToImage, imageSize)
{
}

QPainterPath LidarSensorItem::scanningRegion() const
{
	auto angle = RangeSensorItem::scanningRegion();
	QTransform rotator;
	rotator.rotate(mAngle/2);
	return rotator.map(angle);
}

void LidarSensorItem::customizePainter(QPainter *painter) const
{
	painter->setOpacity(0.15);
	painter->setBrush(Qt::darkGreen);
}
