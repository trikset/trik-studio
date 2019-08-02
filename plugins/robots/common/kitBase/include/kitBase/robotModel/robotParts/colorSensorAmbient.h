/* Copyright 2019 Cybertech Labs Ltd
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

#include "colorSensor.h"

#include "kitBase/kitBaseDeclSpec.h"

namespace kitBase {
namespace robotModel {
namespace robotParts {

class ROBOTS_KIT_BASE_EXPORT ColorSensorAmbient : public ColorSensor
{
	Q_OBJECT
	Q_CLASSINFO("name", "colorAmbient")
	Q_CLASSINFO("friendlyName", tr("EV3 color sensor (ambient)"))
	Q_CLASSINFO("simulated", "true")

public:
	ColorSensorAmbient(const DeviceInfo &info, const PortInfo &port);
};

}
}
}
