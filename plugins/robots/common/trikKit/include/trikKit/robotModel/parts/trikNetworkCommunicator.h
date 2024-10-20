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

#pragma once
#include <kitBase/robotModel/robotParts/communicator.h>

namespace trik {
namespace robotModel {
namespace parts {

/// Class for TRIK robot network communication.
class TrikNetworkCommunicator : public kitBase::robotModel::robotParts::Communicator
{
	Q_OBJECT

public:
	TrikNetworkCommunicator(const kitBase::robotModel::DeviceInfo &info
				, const kitBase::robotModel::PortInfo &port);


	/// Send a message to a robot
	virtual void send(const QString& message, int hullNumber) = 0;

	/// Receive message from robot
	virtual QString receive(bool wait) = 0;

	/// Join the network with the specified hull number
	virtual void joinNetwork(const QString &ip, int port, int hullNumber) = 0;

	/// Send an interrupt to stop waiting for a message
	virtual void stopWaiting() = 0;

	/// Clean the incoming message queue
	virtual void clearQueue() = 0;
};

}
}
}
