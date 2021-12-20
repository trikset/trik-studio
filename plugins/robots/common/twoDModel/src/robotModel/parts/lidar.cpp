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

#include "twoDModel/robotModel/parts/lidar.h"

#include "twoDModel/engine/twoDModelEngineInterface.h"

using namespace twoDModel::robotModel::parts;
using namespace kitBase::robotModel;

Lidar::Lidar(const DeviceInfo &info, const PortInfo &port
		, engine::TwoDModelEngineInterface &engine, QPair<qreal, int> angleAndRange)
	: robotParts::LidarSensor(info, port)
	, mEngine(engine)
	, mAngle(angleAndRange.first)
	, mRange(angleAndRange.second)
{
	setLastData(QVector<int>(360, 0));
}

void Lidar::read()
{
	setLastData(mEngine.readLidarSensor(port(), mRange, mAngle));
}
