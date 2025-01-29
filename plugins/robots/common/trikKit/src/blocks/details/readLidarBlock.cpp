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

#include "readLidarBlock.h"

using namespace trik::blocks::details;
using namespace kitBase::robotModel;

ReadLidarBlock::ReadLidarBlock(RobotModelInterface &robotModel)
	: kitBase::blocksBase::common::DeviceBlock<robotParts::LidarSensor>(robotModel)
{
}

void ReadLidarBlock::doJob(robotParts::LidarSensor &lidar)
{
	Q_UNUSED(lidar)
	evalCode(stringProperty("variable") + " = lidar");
	if (!errorsOccured()) {
		emit done(mNextBlockId);
	}
}
