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

#include <kitBase/robotModel/robotParts/vectorSensor.h>

namespace stm32 {
namespace robotModel {
namespace parts {

/// Pad of android gamepad as 2d-sensor reporting current finger coordinates from -100 to 100
/// (-100, -100) is bottom left corner of a pad. (-1, -1) is returned if pad is not pressed.
class Stm32GamepadPad : public kitBase::robotModel::robotParts::VectorSensor
{
	Q_OBJECT
	Q_CLASSINFO("name", "gamepadPad")
	Q_CLASSINFO("friendlyName", tr("Android Gamepad Pad"))

public:
	/// Constructor.
	/// @param info - device info for that device.
	/// @param port - port on which this device is configured.
	Stm32GamepadPad(const kitBase::robotModel::DeviceInfo &info
			, const kitBase::robotModel::PortInfo &port);
};

}
}
}
