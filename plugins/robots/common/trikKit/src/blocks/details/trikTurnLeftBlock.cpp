/* Copyright 2013-2016 CyberTech Labs Ltd., Grigorii Zimin
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

#include "trikTurnLeftBlock.h"
#include <utils/abstractTimer.h>
#include "utils/timelineInterface.h"

using namespace trik::blocks::details;
using namespace kitBase::robotModel::robotParts;

TurnLeftBlock::TurnLeftBlock(kitBase::robotModel::RobotModelInterface &robotModel)
	: mRobotModel(robotModel)
{
}

void TurnLeftBlock::run()
{
	emit mRobotModel.turnManuallyOn(-90);
	auto timer = mRobotModel.timeline().produceTimer();
	timer->setSingleShot(true);
	connect(timer, &utils::AbstractTimer::timeout, this, [this](){
		emit done(mNextBlockId);
	});
	timer->start(500);
}
