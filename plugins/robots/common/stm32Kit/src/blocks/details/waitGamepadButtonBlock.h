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

#include <kitBase/blocksBase/common/waitBlock.h>

#include "stm32Kit/robotModel/parts/stm32GamepadButton.h"

namespace stm32 {
namespace blocks {
namespace details {

/// Implementation of 'Stm32WaitGamepadButton' for interpreter, uses robot telemetry to wait for button press
/// on a computer.
class WaitGamepadButtonBlock : public kitBase::blocksBase::common::WaitBlock
{
	Q_OBJECT

public:
	explicit WaitGamepadButtonBlock(kitBase::robotModel::RobotModelInterface &robotModel);

private slots:
	/// Called when new data about button state is received.
	void responseSlot(int isPressed);

	void timerTimeout() override;

private:
	void run() override;

	kitBase::robotModel::DeviceInfo device() const override;

	const QString mPort;
	robotModel::parts::Stm32GamepadButton *mButton;  // Does not have ownership.
};

}
}
}
