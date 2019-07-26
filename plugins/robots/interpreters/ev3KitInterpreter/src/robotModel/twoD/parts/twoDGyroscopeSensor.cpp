/* Copyright 2007-2019 CyberTech Labs Ltd.
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

#include "twoDGyroscopeSensor.h"
#include "twoDModel/engine/twoDModelEngineInterface.h"

#define FULL_ANGLE 360000

using namespace ev3::robotModel::twoD::parts;

GyroscopeSensor::GyroscopeSensor(const kitBase::robotModel::DeviceInfo &info
		, const kitBase::robotModel::PortInfo &port
		, twoDModel::engine::TwoDModelEngineInterface &engine)
	: twoDModel::robotModel::parts::Gyroscope(info, port, engine)
{
}

QVector<int> GyroscopeSensor::convert(const QVector<int> &data) const
{
	int tmp = (data[1] + FULL_ANGLE/2) % FULL_ANGLE;
	if (tmp < 0) {
		tmp += FULL_ANGLE;
	}
	return {(tmp - FULL_ANGLE/2) / 1000};
}
