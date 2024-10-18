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

#include "trikKit/robotModel/parts/trikNetworkCommunicator.h"
#include <kitBase/blocksBase/common/waitBlock.h>

namespace trik {
namespace blocks {
namespace details {

class WaitForMessageBlock: public kitBase::blocksBase::common::WaitBlock
{
	Q_OBJECT
public:
	explicit WaitForMessageBlock(kitBase::robotModel::RobotModelInterface &robotModel);

private slots:
	void timerTimeout() override;
private:
	void run() override;

	void handle();

	kitBase::robotModel::DeviceInfo device() const override;

	robotModel::parts::TrikNetworkCommunicator *mNetwork {};
	QString mMessage;

};

}
}
}
