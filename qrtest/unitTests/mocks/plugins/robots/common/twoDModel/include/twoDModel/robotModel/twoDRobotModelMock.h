#pragma once

#include <twoDModel/robotModel/twoDRobotModel.h>
#include <gmock/gmock.h>

namespace qrTest {

class TwoDRobotModelMock : public twoDModel::robotModel::TwoDRobotModel
{
	Q_OBJECT

public:
	TwoDRobotModelMock(const RobotModelInterface &realModel):
	        twoDModel::robotModel::TwoDRobotModel(realModel) {};
	MOCK_CONST_METHOD0(robotId, QString());
	MOCK_CONST_METHOD0(name, QString());
	MOCK_CONST_METHOD0(friendlyName, QString());
	MOCK_CONST_METHOD0(needsConnection, bool());
	MOCK_CONST_METHOD0(updateIntervalForInterpretation, int());
	MOCK_METHOD0(timeline, utils::TimelineInterface &());
	MOCK_CONST_METHOD0(configurablePorts, QList< kitBase::robotModel::PortInfo>());
	MOCK_CONST_METHOD0(convertibleBases, QList< kitBase::robotModel::DeviceInfo>());
	MOCK_CONST_METHOD0(priority, int());
	MOCK_METHOD0(rereadSettings, void());
	MOCK_METHOD1(setEngine, void(twoDModel::engine::TwoDModelEngineInterface &));
	MOCK_CONST_METHOD0(robotImage, QString());
	MOCK_CONST_METHOD0(defaultLeftWheelPort, kitBase::robotModel::PortInfo());
	MOCK_CONST_METHOD0(defaultRightWheelPort, kitBase::robotModel::PortInfo());
	MOCK_CONST_METHOD0(displayWidget, twoDModel::engine::TwoDModelDisplayWidget *());
	MOCK_CONST_METHOD0(collidingPolygon, QPolygonF());
	MOCK_CONST_METHOD0(mass, qreal());
	MOCK_CONST_METHOD0(friction, qreal());
	MOCK_CONST_METHOD0(size, QSizeF());
	MOCK_CONST_METHOD0(rotationCenter, QPointF());
	MOCK_CONST_METHOD0(robotCenter, QPointF());
	MOCK_CONST_METHOD0(wheelsPosition, QList<QPointF>());
	MOCK_CONST_METHOD0(onePercentAngularVelocity, qreal());
};
}
