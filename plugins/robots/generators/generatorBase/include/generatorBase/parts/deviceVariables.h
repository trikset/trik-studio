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

#include <kitBase/robotModel/deviceInfo.h>
#include <kitBase/robotModel/portInfo.h>

#include "generatorBase/robotsGeneratorDeclSpec.h"

namespace generatorBase {
namespace parts {

/// Base class that allows customization of device related code generation. Supposed to be subclassed in generator kit
/// plugins.
class ROBOTS_GENERATOR_EXPORT DeviceVariables
{
	Q_DISABLE_COPY(DeviceVariables)
public:
	DeviceVariables() = default;
	virtual ~DeviceVariables();

	/// Allows to customize path to device expression template based on device info and port info.
	virtual QString variableTemplatePath(const kitBase::robotModel::DeviceInfo &device
			, const kitBase::robotModel::PortInfo &port) const;
};

}
}
