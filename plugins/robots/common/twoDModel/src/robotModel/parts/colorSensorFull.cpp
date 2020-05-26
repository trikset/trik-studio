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

#include "twoDModel/engine/twoDModelEngineInterface.h"
#include "twoDModel/engine/model/constants.h"
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
	auto color = mEngine.readColorSensor(port());
	uint resColor = 0xFF000000;
	uint clearRed = red - black;
	uint clearGreen = green - black;
	uint clearBlue = blue - black;
	if (color.red() > 200) {
		resColor += clearRed;
	} else if (color.red() > 100) {
		resColor += clearRed / 2;
	}
	if (color.green() > 200) {
		resColor += clearGreen;
	} else if (color.green() > 100) {
		resColor += clearGreen / 2;
	}
	if (color.blue() > 200) {
		resColor += clearBlue;
	} else if (color.blue() > 100) {
		resColor += clearBlue / 2;
	}
	int reading;
	switch (resColor) {
	case (black):
		reading = 1;
		break;
	case (red):
		reading = 5;
		break;
	case (green):
		reading = 3;
		break;
	case (blue) :
		reading = 2;
		break;
	case (yellow):
		reading = 4;
		break;
	case (white):
		reading = 6;
		break;
	case (cyan):
		reading = 7;
		break;
	case (magenta):
		reading = 8;
		break;
	default:
		reading = 0;
	}

	setLastData(reading);
}
