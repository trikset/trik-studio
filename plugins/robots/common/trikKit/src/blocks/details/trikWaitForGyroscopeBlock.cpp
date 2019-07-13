/* Copyright 2013-2019 CyberTech Labs Ltd.
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

#include "trikWaitForGyroscopeBlock.h"

using namespace trik::blocks::details;

TrikWaitForGyroscopeBlock::TrikWaitForGyroscopeBlock(kitBase::robotModel::RobotModelInterface &robotModel)
	: kitBase::blocksBase::common::WaitForGyroscopeSensorBlock(robotModel)
{
}

int TrikWaitForGyroscopeBlock::converter(QVector<int> reading)
{
	if (reading.size() < 3)
		return WaitForGyroscopeSensorBlock::converter(reading);
	return reading[2];
}

QString TrikWaitForGyroscopeBlock::port()
{
	return "GyroscopePort";
}
