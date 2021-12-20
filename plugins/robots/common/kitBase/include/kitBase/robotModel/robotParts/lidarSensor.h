/* Copyright 2021 CyberTech Labs Ltd.
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

#include "vectorSensor.h"
#include "kitBase/kitBaseDeclSpec.h"

namespace kitBase {
namespace robotModel {
namespace robotParts {

/// Base class for lidar sensors.
class ROBOTS_KIT_BASE_EXPORT LidarSensor : public VectorSensor
{
	Q_OBJECT
	Q_CLASSINFO("name", "lidar")
	Q_CLASSINFO("friendlyName", tr("Lidar"))
	Q_CLASSINFO("simulated", "true")

public:
	/// Constructor, takes device type info and port on which this sensor is configured.
	LidarSensor(const DeviceInfo &info, const PortInfo &port);
};

}
}
}
