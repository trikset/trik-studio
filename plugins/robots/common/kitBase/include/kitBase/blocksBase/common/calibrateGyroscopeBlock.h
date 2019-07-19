/* Copyright 2007-2019 QReal Research Group
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

#include <kitBase/blocksBase/common/deviceBlock.h>
#include "kitBase/robotModel/robotParts/gyroscopeSensor.h"

namespace kitBase {

namespace robotModel {
namespace robotParts {
class GyroscopeSensor;
}
}

namespace blocksBase {
namespace common {

/// Interpreter implementation for "Calibrate gyroscope" block.
class ROBOTS_KIT_BASE_EXPORT CalibrateGyroscopeBlock :
		public kitBase::blocksBase::common::DeviceBlock<kitBase::robotModel::robotParts::GyroscopeSensor>
{
public:
	CalibrateGyroscopeBlock(kitBase::robotModel::RobotModelInterface &robotModel);

protected:
	virtual void doJob(kitBase::robotModel::robotParts::GyroscopeSensor &gyro);
};

}
}
}
