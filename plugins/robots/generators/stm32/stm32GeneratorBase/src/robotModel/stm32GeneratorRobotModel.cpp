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

#include "stm32GeneratorBase/robotModel/stm32GeneratorRobotModel.h"

using namespace stm32::robotModel;

Stm32V62GeneratorRobotModel::Stm32V62GeneratorRobotModel(const QString &kitId
		, const QString &robotId
		, const QString &name
		, const QString &friendlyName
		, int priority)
//	: Stm32RobotModelV62(kitId, robotId)
    : Stm32RobotModelBase(kitId, robotId)
	, mName(name)
	, mFriendlyName(friendlyName)
	, mPriority(priority)
{
}

void Stm32V62GeneratorRobotModel::setErrorReporter(qReal::ErrorReporterInterface &errorReporter)
{
	Q_UNUSED(errorReporter)
}

QString Stm32V62GeneratorRobotModel::name() const
{
	return mName;
}

QString Stm32V62GeneratorRobotModel::friendlyName() const
{
	return mFriendlyName;
}

bool Stm32V62GeneratorRobotModel::needsConnection() const
{
	return false;
}

bool Stm32V62GeneratorRobotModel::interpretedModel() const
{
	return false;
}

int Stm32V62GeneratorRobotModel::priority() const
{
	return mPriority;
}

void Stm32V62GeneratorRobotModel::addDevice(const kitBase::robotModel::PortInfo &port
		, kitBase::robotModel::robotParts::Device *device)
{
	mPreConfiguredDevices[port] = device;
	configureDevice(port, device->deviceInfo());
	applyConfiguration();
}

kitBase::robotModel::robotParts::Device *Stm32V62GeneratorRobotModel::createDevice(
		const kitBase::robotModel::PortInfo &port
		, const kitBase::robotModel::DeviceInfo &deviceInfo)
{
	if (mPreConfiguredDevices.contains(port) && mPreConfiguredDevices[port]->deviceInfo().isA(deviceInfo)) {
		return mPreConfiguredDevices[port];
	}

	return Stm32RobotModelBase::createDevice(port, deviceInfo);
}
