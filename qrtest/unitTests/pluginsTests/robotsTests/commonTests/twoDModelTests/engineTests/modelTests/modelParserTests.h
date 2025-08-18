#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QtCore/QScopedPointer>

namespace twoDModel {
namespace model {
class Model;
}
}

namespace qrTest {

class TwoDRobotModelMock;
class RobotModelInterfaceMock;

namespace robotsTests {
namespace commonTwoDModelTests {

/// Tests for ConstraintsParser.
class ModelParserTests : public testing::Test
{
public:
	ModelParserTests() = default;

protected:
	void SetUp() override;
	void TearDown() override;
	QScopedPointer<twoDModel::model::Model> mModel;
	QScopedPointer<RobotModelInterfaceMock> mRobotModel;
	QScopedPointer<TwoDRobotModelMock> mTwoDRobotModel;
};

}
}
}
