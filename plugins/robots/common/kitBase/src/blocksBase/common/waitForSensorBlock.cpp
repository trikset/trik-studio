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

#include "kitBase/blocksBase/common/waitForSensorBlock.h"

#include <utils/abstractTimer.h>

#include "kitBase/robotModel/robotParts/scalarSensor.h"
#include "kitBase/robotModel/robotModelUtils.h"

using namespace kitBase;
using namespace blocksBase::common;
using namespace robotModel;

WaitForSensorBlock::WaitForSensorBlock(RobotModelInterface &robotModel)
	: WaitBlock(robotModel)
{
}

void WaitForSensorBlock::run()
{
	const QString port = this->port();

	mPort = std::move(RobotModelUtils::findPort(mRobotModel, port, input));
	auto const sensor = RobotModelUtils::findDevice<robotParts::AbstractSensor>(mRobotModel, mPort);
	if (sensor) {
		mConnections << connect(sensor, &robotParts::AbstractSensor::newData
								, this, &WaitForSensorBlock::responseSlot, Qt::UniqueConnection);
		mConnections << connect(sensor, &robotParts::AbstractSensor::failure
								, this, &WaitForSensorBlock::failureSlot, Qt::UniqueConnection);
		mActiveWaitingTimer->start();
		sensor->read();
	} else {
		mActiveWaitingTimer->stop();
		error(tr("%1 is not configured on port %2").arg(device().friendlyName(), mPort.userFriendlyName()));
	}
}

void WaitForSensorBlock::timerTimeout()
{
	/// @todo True horror.
	robotParts::Device * const device = mRobotModel.configuration().device(mPort);
	robotParts::ScalarSensor * const sensor = dynamic_cast<robotParts::ScalarSensor *>(device);
	if (sensor) {
		sensor->read();
	}
}

void WaitForSensorBlock::disconnectSensor()
{
	for (auto &&c: mConnections) {
		disconnect(c);
	}
	mConnections.clear();
}

void WaitForSensorBlock::stop()
{
	disconnectSensor();
	WaitBlock::stop();
}

void WaitForSensorBlock::stopActiveTimerInBlock()
{
	disconnectSensor();
	WaitBlock::stopActiveTimerInBlock();
}
