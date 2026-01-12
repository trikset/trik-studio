/* Copyright 2025 CyberTech Labs Ltd.
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

#include <twoDModel/robotModel/twoDRobotModel.h>
#include <gmock/gmock.h>

namespace qrTest {

class TwoDRobotModelMock : public twoDModel::robotModel::TwoDRobotModel
{
	Q_OBJECT

public:
	// NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init)
	explicit TwoDRobotModelMock(const RobotModelInterface &realModel):
	        twoDModel::robotModel::TwoDRobotModel(realModel) {};
	// clazy:excludeall=function-args-by-value,returning-void-expression
	MOCK_METHOD(QString, robotId, (),(const, override));
	MOCK_METHOD(QString, name, (), (const, override));
	MOCK_METHOD(QString, friendlyName, (), (const, override));
	MOCK_METHOD(bool, needsConnection, (), (const, override));
	MOCK_METHOD(int, updateIntervalForInterpretation, (), (const, override));
	MOCK_METHOD(utils::TimelineInterface &, timeline, (), (override));
	MOCK_METHOD(QList< kitBase::robotModel::PortInfo>, configurablePorts, (), (const, override));
	MOCK_METHOD(QList< kitBase::robotModel::DeviceInfo>, convertibleBases, (), (const, override));
	MOCK_METHOD(int, priority, (), (const, override));
	MOCK_METHOD(void, rereadSettings, (), (override));
	MOCK_METHOD(QString, robotImage, (), (const, override));
	MOCK_METHOD(kitBase::robotModel::PortInfo, defaultLeftWheelPort, (), (const, override));
	MOCK_METHOD(kitBase::robotModel::PortInfo, defaultRightWheelPort, (), (const, override));
	MOCK_METHOD(twoDModel::engine::TwoDModelDisplayWidget *, displayWidget,(), (const, override));
	MOCK_METHOD(QPolygonF, collidingPolygon, (), (const, override));
	MOCK_METHOD(qreal, mass, (), (const, override));
	MOCK_METHOD(qreal, friction, (), (const, override));
	MOCK_METHOD(QSizeF, size,(), (const, override));
	MOCK_METHOD(QPointF, rotationCenter, (), (const, override));
	MOCK_METHOD(QPointF, robotCenter, (), (const, override));
	MOCK_METHOD(QList<QPointF>, wheelsPosition, (), (const, override));
	MOCK_METHOD(qreal, onePercentAngularVelocity, (), (const, override));
	// clazy:enable
};
}
