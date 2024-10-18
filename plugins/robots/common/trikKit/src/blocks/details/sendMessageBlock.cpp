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

#include "sendMessageBlock.h"

using namespace trik;
using namespace blocks::details;

SendMessageBlock::SendMessageBlock(kitBase::robotModel::RobotModelInterface &robotModel):
	kitBase::blocksBase::common::DeviceBlock<robotModel::parts::TrikNetworkCommunicator>(robotModel)
{}

void SendMessageBlock::doJob(robotModel::parts::TrikNetworkCommunicator &network)
{
	auto message = stringProperty("Message");
	auto hullNumber = intProperty("HullNumber");
	network.send(message, hullNumber);
	emit done(mNextBlockId);
}
