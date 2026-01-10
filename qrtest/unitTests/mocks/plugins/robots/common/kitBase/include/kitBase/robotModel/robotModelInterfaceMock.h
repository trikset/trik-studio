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

#include <kitBase/robotModel/robotModelInterface.h>
#include <kitBase/robotModel/configuration.h>
#include <utils/timelineInterface.h>

#include <gmock/gmock.h>

namespace qrTest {

typedef QHash<QString, int> StringIntHash;

class RobotModelInterfaceMock : public kitBase::robotModel::RobotModelInterface
{
	Q_OBJECT

public:
	// clazy:excludeall=function-args-by-value,returning-void-expression
	MOCK_METHOD(QString, robotId, (), (const, override));
	MOCK_METHOD(QString, name, (), (const, override));
	MOCK_METHOD(QString, friendlyName, (), (const, override));
	MOCK_METHOD(QString, kitId, (), (const, override));
	MOCK_METHOD(int, priority, (), (const, override));
	MOCK_METHOD(bool, interpretedModel, (), (const, override));
	MOCK_METHOD(void, init, (), (override));
	MOCK_METHOD(void, connectToRobot, (), (override));
	MOCK_METHOD(void, stopRobot, (), (override));
	MOCK_METHOD(void, disconnectFromRobot, (), (override));
	MOCK_METHOD(ConnectionState, connectionState, (), (const, override));
	MOCK_METHOD(bool, needsConnection, (), (const, override));
	MOCK_METHOD(void, updateSensorsValues, (), (const, override));
	MOCK_METHOD(int, updateIntervalForInterpretation, (), (const, override));
	MOCK_METHOD(kitBase::robotModel::ConfigurationInterface const &, configuration, (), (const, override));
	MOCK_METHOD(QList<kitBase::robotModel::PortInfo>, availablePorts, (), (const, override));
	MOCK_METHOD(QList<kitBase::robotModel::PortInfo>, getPortsBy, (const QString &), (const, override));
	MOCK_METHOD(StringIntHash, buttonCodes, (), (const, override));
	MOCK_METHOD(QList<kitBase::robotModel::PortInfo>, configurablePorts, (), (const, override));
	MOCK_METHOD(QList<kitBase::robotModel::DeviceInfo>, allowedDevices,
				(kitBase::robotModel::PortInfo const &), (const, override));
	MOCK_METHOD(void, configureDevice, (kitBase::robotModel::PortInfo const &
						, kitBase::robotModel::DeviceInfo const &), (override));
	MOCK_METHOD(void, applyConfiguration, (), (override));
	MOCK_METHOD(QList< kitBase::robotModel::DeviceInfo>, convertibleBases, (), (const, override));
	MOCK_METHOD(utils::TimelineInterface &, timeline, (), (override));
	MOCK_METHOD(void, onInterpretationStarted, (), (override));
	// clazy:enable
};

}
