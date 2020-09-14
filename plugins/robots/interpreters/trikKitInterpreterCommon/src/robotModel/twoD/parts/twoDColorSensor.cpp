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

#include "trikKitInterpreterCommon/robotModel/twoD/parts/twoDColorSensor.h"
#include <QColor>

using namespace trik::robotModel::twoD::parts;
using namespace kitBase::robotModel;

ColorSensor::ColorSensor(const DeviceInfo &info, const PortInfo &port
		, twoDModel::engine::TwoDModelEngineInterface &engine)
	: robotModel::parts::TrikColorSensor(info, port)
	, mEngine(engine)
{
}

void ColorSensor::init()
{
}

void ColorSensor::read()
{	
	const auto &color = mEngine.readColorSensor(mEngine.videoPort());
	if (!color.isValid()) return;
	setLastData({color.red(), color.green(), color.blue()});
}
