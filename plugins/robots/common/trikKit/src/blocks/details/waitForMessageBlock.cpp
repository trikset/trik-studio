/* Copyright 2024 CyberTech Labs Ltd.
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

#include "waitForMessageBlock.h"
#include "trikKit/robotModel/parts/trikNetworkCommunicator.h"
#include <utils/abstractTimer.h>
#include <qrutils/stringUtils.h>
#include <kitBase/robotModel/robotModelInterface.h>
#include <kitBase/robotModel/robotModelUtils.h>

using namespace trik;
using namespace blocks::details;
using namespace kitBase::robotModel;

WaitForMessageBlock::WaitForMessageBlock(kitBase::robotModel::RobotModelInterface &robotModel):
	WaitBlock(robotModel)
{
	mActiveWaitingTimer->setSingleShot(true);
	mActiveWaitingTimer->setInterval(100);
}

void WaitForMessageBlock::handle()
{
	evalCode(stringProperty("Variable") + " = " + mMessage);
	stop();
	Q_EMIT done(mNextBlockId);
	return;
}

void WaitForMessageBlock::run()
{
	mNetwork = RobotModelUtils::findDevice<robotModel::parts::TrikNetworkCommunicator>(mRobotModel, "CommunicatorPort");

	if (!mNetwork) {
		error(tr("Device not found for port name CommunicatorPort"));
		return;
	}

	auto wait = boolProperty("Synchronized");

	if (!wait) {
		mMessage = utils::StringUtils::wrap(utils::StringUtils::dequote(mNetwork->receive(wait)));
		handle();
		return;
	}

	mActiveWaitingTimer->start();
}

void WaitForMessageBlock::timerTimeout()
{
	auto message = mNetwork->receive(false);
	if (message != QString()) {
		mMessage = utils::StringUtils::wrap(utils::StringUtils::dequote(message));
		handle();
		return;
	}

	mActiveWaitingTimer->start();
}

DeviceInfo WaitForMessageBlock::device() const
{
	return DeviceInfo::create<robotModel::parts::TrikNetworkCommunicator>();
}
