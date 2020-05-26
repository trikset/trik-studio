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

#include "twoDModel/robotModel/parts/colorSensorPassive.h"

#include "twoDModel/engine/twoDModelEngineInterface.h"
#include <QColor>
#include <QtMath>
#include <qrutils/mathUtils/math.h>

using namespace twoDModel::robotModel::parts;
using namespace kitBase::robotModel;

ColorSensorPassive::ColorSensorPassive(const kitBase::robotModel::DeviceInfo &info
		, const kitBase::robotModel::PortInfo &port
		, engine::TwoDModelEngineInterface &engine)
	: kitBase::robotModel::robotParts::ColorSensorPassive(info, port)
	, mEngine(engine)
{
}

void ColorSensorPassive::read()
{
	auto color = mEngine.readColorSensor(port());
	auto bright = (color.redF() * color.redF() + color.greenF() * color.greenF() + color.blueF() * color.blueF()) / 3;
	auto reading = qRound(qSqrt(bright / 3) * 100);
	setLastData(mathUtils::Math::truncateToInterval(0, 100, reading));
}
