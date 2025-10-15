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

#include "twoDColorSensorFull.h"
#include "twoDModel/engine/twoDModelEngineInterface.h"
#include "twoDModel/engine/model/constants.h"
#include <QColor>

using namespace ev3::robotModel::twoD::parts;
using namespace kitBase::robotModel;

ColorSensorFull::ColorSensorFull(const kitBase::robotModel::DeviceInfo &info
		, const kitBase::robotModel::PortInfo &port
		, twoDModel::engine::TwoDModelEngineInterface &engine)
	: kitBase::robotModel::robotParts::ColorSensorFull(info, port)
	, mEngine(engine)
{
}

void ColorSensorFull::read()
{
	const auto &color = mEngine.readColorSensor(port());
	Q_UNUSED(color);
	setLastData(0);
	/*
	 * Implement color recognition for ev3 that will take into account brown
	 */
}
