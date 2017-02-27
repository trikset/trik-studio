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

#include "waitForMotionBlock.h"

#include "stm32Kit/robotModel/parts/stm32MotionSensor.h"

using namespace stm32::blocks::details;

WaitForMotionBlock::WaitForMotionBlock(kitBase::robotModel::RobotModelInterface &robotModel)
	: WaitForSensorBlock(robotModel)
{
}

void WaitForMotionBlock::responseSlot(int reading)
{
	if (reading > 0) {
		stop();
	}
}

QString WaitForMotionBlock::port()
{
	return "F1";
}

kitBase::robotModel::DeviceInfo WaitForMotionBlock::device() const
{
	return kitBase::robotModel::DeviceInfo::create<robotModel::parts::Stm32MotionSensor>();
}
