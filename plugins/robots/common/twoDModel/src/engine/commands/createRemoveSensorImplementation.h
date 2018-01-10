/* Copyright 2016 CyberTech Labs Ltd.
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

#include <QtCore/QPointF>

#include <kitBase/devicesConfigurationProvider.h>

namespace twoDModel {

namespace model {
class SensorsConfiguration;
}

namespace commands {

class CreateRemoveSensorImplementation : public kitBase::DevicesConfigurationProvider
{
public:
	CreateRemoveSensorImplementation(model::SensorsConfiguration &configurator
			, const QString &robotId
			, const kitBase::robotModel::PortInfo &port
			, const kitBase::robotModel::DeviceInfo &device
			, const QPointF &position
			, const qreal direction);

	void create();
	void remove();

private:
	model::SensorsConfiguration &mConfigurator;
	const QString mRobotId;
	const kitBase::robotModel::PortInfo mPort;
	kitBase::robotModel::DeviceInfo mDevice;
	QPointF mPosition;
	qreal mDirection;
};

}
}
