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
