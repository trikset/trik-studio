/* Copyright 2007-2015 QReal Research Group
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

#include "twoDModel/robotModel/parts/colorSensorFull.h"
#include "twoDModel/engine/model/colorDetector.h"
#include "twoDModel/engine/twoDModelEngineInterface.h"
#include <QColor>

using namespace twoDModel::robotModel::parts;
using namespace kitBase::robotModel;

ColorSensorFull::ColorSensorFull(const kitBase::robotModel::DeviceInfo &info
		, const kitBase::robotModel::PortInfo &port
		, engine::TwoDModelEngineInterface &engine)
	: kitBase::robotModel::robotParts::ColorSensorFull(info, port)
	, mEngine(engine)
{
}

void ColorSensorFull::read()
{
	const auto color = mEngine.readColorSensor(port());
	const auto hue = color.hue();
	const auto saturation = color.saturation();
	const auto value= color.value();
	setLastData(static_cast<int>(twoDModel::model::ColorDetector::detect(hue, saturation, value)));
}
