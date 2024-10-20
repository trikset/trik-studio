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

#include <trikKit/robotModel/parts/trikNetworkCommunicator.h>
#include <trikNetwork/mailboxFactory.h>
#include <trikControl/brickInterface.h>
#include "trikKitInterpreterCommon/declSpec.h"

namespace trik {
namespace robotModel {
namespace twoD {
namespace parts {

/// Class for implementing 2D-model network communication between robots
class ROBOTS_TRIK_KIT_INTERPRETER_COMMON_EXPORT TwoDNetworkCommunicator
		: public robotModel::parts::TrikNetworkCommunicator
{
	Q_OBJECT

public:
	TwoDNetworkCommunicator(const kitBase::robotModel::DeviceInfo &info
			, const kitBase::robotModel::PortInfo &port
			, trikNetwork::MailboxInterface *mailbox);
	~TwoDNetworkCommunicator();

	/// Send a message to a robot
	void send(const QString& message, int hullNumber) override;

	/// Receive message from robot
	QString receive(bool wait) override;

	/// Send an interrupt to stop waiting for a message
	void stopWaiting() override;

	/// Clean the incoming message queue
	void clearQueue() override;

	/// Join the network with the specified hull number
	void joinNetwork(const QString &ip, int port, int hullNumber) override;

	/// Deinitializing a TRIK network communicator
	void release() override;
private:
	trikNetwork::MailboxInterface *mMailbox {}; // ownership --- TrikKitInterpreterPluginBase

};

}
}
}
}
