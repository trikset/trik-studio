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

#pragma once

#include <kitBase/robotModel/portInfo.h>
#include <utils/robotCommunication/robotCommunicator.h>
#include <nxtKit/robotModel/parts/nxtMotor.h>
#include <nxtKit/communication/nxtCommandConstants.h>

namespace nxt {
namespace robotModel {
namespace real {
namespace parts {

class Motor : public nxt::robotModel::parts::NxtMotor
{
	Q_OBJECT

public:
	Motor(const kitBase::robotModel::DeviceInfo &info
			, const kitBase::robotModel::PortInfo &port
			, utils::robotCommunication::RobotCommunicator &robotCommunicator);

	void on(int speed, bool breakMode = true) override;
	void on(int speed, uint64_t degrees, bool breakMode = true) override;
	void stop(bool breakMode = true) override;
	void off() override;
	void resetMotorPosition(bool relative);

private:
	void setOutputState(int speed
			, int mode
			, enums::regulationMode::RegulationModeEnum regulation
			, int turnRatio
			, enums::runState::RunStateEnum runState
			, uint64_t tachoLimit);

	utils::robotCommunication::RobotCommunicator &mRobotCommunicator;
};

}
}
}
}
