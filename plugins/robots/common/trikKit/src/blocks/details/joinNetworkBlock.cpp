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


#include "joinNetworkBlock.h"

using namespace trik;
using namespace blocks::details;

JoinNetworkBlock::JoinNetworkBlock(kitBase::robotModel::RobotModelInterface &robotModel):
	kitBase::blocksBase::common::DeviceBlock<robotModel::parts::TrikNetworkCommunicator>(robotModel)
{}

void JoinNetworkBlock::doJob(robotModel::parts::TrikNetworkCommunicator &network)
{
	auto address = stringProperty("Address");
	auto port = intProperty("IPPort");
	auto hullNumber = intProperty("HullNumber");
	network.joinNetwork(address, port, hullNumber);
	Q_EMIT done(mNextBlockId);
}
