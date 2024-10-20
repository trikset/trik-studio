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

#include "trikKitInterpreterCommon/robotModel/twoD/parts/twoDNetworkCommunicator.h"
#include <qrkernel/settingsManager.h>
#include <trikNetwork/mailboxInterface.h>

using namespace trik::robotModel::twoD::parts;
using namespace kitBase::robotModel;

TwoDNetworkCommunicator::TwoDNetworkCommunicator(const DeviceInfo &info
		, const PortInfo &port
		,trikNetwork::MailboxInterface *mailbox)
	: robotModel::parts::TrikNetworkCommunicator(info, port)
	, mMailbox(mailbox)
{}


TwoDNetworkCommunicator::~TwoDNetworkCommunicator(){
}

void TwoDNetworkCommunicator::send(const QString& message, int hullNumber)
{
	if (mMailbox) {
		mMailbox->send(hullNumber, message);
	}
}

QString TwoDNetworkCommunicator::receive(bool wait)
{
	if (mMailbox) {
		return mMailbox->receive(wait);
	}

	return QString();
}

void TwoDNetworkCommunicator::stopWaiting()
{
	if (mMailbox) {
		mMailbox->stopWaiting();
	}
}

void TwoDNetworkCommunicator::clearQueue()
{
	if (mMailbox) {
		mMailbox->clearQueue();
	}
}

void TwoDNetworkCommunicator::release()
{
	if (mMailbox) {
		mMailbox->stopWaiting();
		mMailbox->clearQueue();
	}
}

void TwoDNetworkCommunicator::joinNetwork(const QString &ip, int port, int hullNumber)
{
	if (mMailbox) {
		mMailbox->joinNetwork(ip, port, hullNumber);
	}
}


