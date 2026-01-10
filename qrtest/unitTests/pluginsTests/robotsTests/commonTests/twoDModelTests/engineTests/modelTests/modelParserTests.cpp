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

#include "modelParserTests.h"
#include <twoDModel/robotModel/physicsEngineFactoryMock.h>
#include <kitBase/robotModel/robotModelInterfaceMock.h>
#include <twoDModel/robotModel/twoDRobotModelMock.h>
#include <twoDModel/engine/model/model.h>
#include <twoDModel/engine/model/robotModel.h>
#include <twoDModel/engine/model/twoDModelRobotParameters.h>
#include "src/engine/items/wallItem.h"
#include "src/engine/items/startPosition.h"
#include "src/engine/items/skittleItem.h"
#include "src/engine/items/lineItem.h"
#include "src/engine/items/ballItem.h"
#include "src/engine/items/cubeItem.h"
#include "src/engine/items/commentItem.h"
#include <cmath>
#include <QFile>
#include <qrutils/inFile.h>
#include <QTextStream>

using namespace ::testing;
using namespace qrTest::robotsTests::commonTwoDModelTests;

void ModelParserTests::SetUp()
{
	mModel.reset(new twoDModel::model::Model(new testing::NiceMock<PhysicsEngineFactoryMock>()));
	mRobotModel.reset(new testing::NiceMock<RobotModelInterfaceMock>());
	mTwoDRobotModel.reset(new testing::NiceMock<TwoDRobotModelMock>(*mRobotModel.data()));
	mModel->addRobotModel(*mTwoDRobotModel.data());
}

void ModelParserTests::TearDown()
{
	// We do not initialize TwoDModelScene, which takes ownership
	// of StartPosition in TwoDModelScene::onRobotAdd.
	for (auto &&robotModel: mModel->robotModels()) {
		delete robotModel->startPositionMarker();
	}
}

TEST_F(ModelParserTests, defaultMetricSystemCustomObjectParametersTest)
{
	ON_CALL(*mTwoDRobotModel, robotId()).WillByDefault(Return("mockRobot"));
	EXPECT_CALL(*mTwoDRobotModel, robotId()).Times(AtLeast(1));

	QDomDocument doc;
	const auto xml = utils::InFile::readAll("./data/pixelWorldModel.xml");
	doc.setContent(xml);
	mModel->deserialize(doc);
	const auto &setting = mModel->settings();
	EXPECT_EQ(setting.realisticMotors(), false);
	EXPECT_EQ(setting.realisticPhysics(), false);
	EXPECT_EQ(setting.realisticSensors(), false);
	auto &worldModel = mModel->worldModel();
	const auto walls = worldModel.walls();
	const auto wallItem = walls["{1bd5379e-e8bb-449a-b91d-4da031309bc3}"];
	EXPECT_FLOAT_EQ(wallItem->x1(), -350.0f);
	EXPECT_FLOAT_EQ(wallItem->y1(), -250.0f);
	EXPECT_FLOAT_EQ(wallItem->x2(), 0.0f);
	EXPECT_FLOAT_EQ(wallItem->y2(), -250.0f);
	EXPECT_FLOAT_EQ(wallItem->pen().widthF(), 2.1f);
	const auto wallSolidItem = static_cast<twoDModel::items::SolidItem*>(wallItem.data());
	EXPECT_FLOAT_EQ(wallSolidItem->friction(), 0.5f);
	EXPECT_FLOAT_EQ(wallSolidItem->restitution(), 0.3f);

	const auto skittles = worldModel.skittles();
	const auto skittleItem = skittles["{af2bf97f-90cd-49a2-a201-b3f6e57497bb}"];
	EXPECT_FLOAT_EQ(skittleItem->x(), 50.0f);
	EXPECT_FLOAT_EQ(skittleItem->y(), -250.0f);
	EXPECT_FLOAT_EQ(skittleItem->rotation(), 0.0f);
	skittleItem->returnToStartPosition();
	EXPECT_FLOAT_EQ(skittleItem->x(), 10.0f);
	EXPECT_FLOAT_EQ(skittleItem->y(), -25.0f);
	EXPECT_FLOAT_EQ(skittleItem->rotation(), 10.0f);

	const auto skittleWithBeginItem = skittles["skittle_with_begin"];
	const auto skittleWidth = skittleWithBeginItem->boundingRect().width();
	const auto skittleHeight = skittleWithBeginItem->boundingRect().height();
	EXPECT_FLOAT_EQ(skittleWithBeginItem->x(), 250 + skittleWidth / 2);
	EXPECT_FLOAT_EQ(skittleWithBeginItem->y(), 300 + skittleHeight / 2);

	const auto skittleSolidItem = static_cast<twoDModel::items::SolidItem*>(skittleItem.data());
	EXPECT_FLOAT_EQ(skittleSolidItem->friction(), 0.5f);
	EXPECT_FLOAT_EQ(skittleSolidItem->restitution(), 0.2f);
	EXPECT_FLOAT_EQ(skittleSolidItem->linearDamping(), 4.0f);
	EXPECT_FLOAT_EQ(skittleSolidItem->angularDamping(), 3.0f);
	EXPECT_FLOAT_EQ(skittleSolidItem->mass(), 0.5f);

	const auto balls = worldModel.balls();
	const auto ballItem = balls["{6573d515-983f-439e-a3df-dee6e9ea8e73}"];
	EXPECT_FLOAT_EQ(ballItem->x(), -402.0f);
	EXPECT_FLOAT_EQ(ballItem->y(), -250.0f);
	EXPECT_FLOAT_EQ(ballItem->rotation(), 0.0f);
	ballItem->returnToStartPosition();
	EXPECT_FLOAT_EQ(ballItem->x(), -102.0f);
	EXPECT_FLOAT_EQ(ballItem->y(), -25.0f);
	EXPECT_FLOAT_EQ(ballItem->rotation(), 10.0f);

	const auto ballWithBeginItem = balls["ball_with_begin"];
	const auto ballWidth = ballWithBeginItem->boundingRect().width();
	const auto ballHeight = ballWithBeginItem->boundingRect().height();
	EXPECT_FLOAT_EQ(ballWithBeginItem->x(), 250 + ballWidth / 2);
	EXPECT_FLOAT_EQ(ballWithBeginItem->y(), 300 + ballHeight / 2);

	const auto ballSolidItem = static_cast<twoDModel::items::SolidItem*>(ballItem.data());
	EXPECT_FLOAT_EQ(ballSolidItem->friction(), 0.4f);
	EXPECT_FLOAT_EQ(ballSolidItem->restitution(), 0.7f);
	EXPECT_FLOAT_EQ(ballSolidItem->linearDamping(), 6.0f);
	EXPECT_FLOAT_EQ(ballSolidItem->angularDamping(), 5.0f);
	EXPECT_FLOAT_EQ(ballSolidItem->mass(), 0.6f);

	const auto colorFields = worldModel.colorFields();
	const auto lineItem = colorFields["{b8ef1043-4bf4-42bf-8f61-841217cc3318}"];
	EXPECT_FLOAT_EQ(lineItem->x1(), -202.0f);
	EXPECT_FLOAT_EQ(lineItem->y1(), -101.0f);
	EXPECT_FLOAT_EQ(lineItem->x2(), 250.0f);
	EXPECT_FLOAT_EQ(lineItem->y2(), -99.0f);
	EXPECT_FLOAT_EQ(lineItem->pen().widthF(), 6.5f);
	EXPECT_FLOAT_EQ(lineItem->rotation(), 0.0f);

	const auto cubicBezier = colorFields["{1b4bb76e-1aff-4d9b-aebb-d6f4fc581e28}"];
	EXPECT_FLOAT_EQ(cubicBezier->x1(), 251.0f);
	EXPECT_FLOAT_EQ(cubicBezier->y1(), 102.0f);
	EXPECT_FLOAT_EQ(cubicBezier->x2(), -198.0f);
	EXPECT_FLOAT_EQ(cubicBezier->y2(), 101.0f);
	EXPECT_FLOAT_EQ(cubicBezier->pen().widthF(), 6.0f);
	EXPECT_FLOAT_EQ(cubicBezier->rotation(), 0.0f);

	const auto rectangle = colorFields["{3f73d96c-7f93-4aac-beb2-ab73832ed556}"];
	EXPECT_FLOAT_EQ(rectangle->x1(), -452.0f);
	EXPECT_FLOAT_EQ(rectangle->y1(), -102.0f);
	EXPECT_FLOAT_EQ(rectangle->x2(), -248.0f);
	EXPECT_FLOAT_EQ(rectangle->y2(), 103.0f);
	EXPECT_FLOAT_EQ(rectangle->pen().widthF(), 6.0f);

	auto comments = worldModel.commentItems();
	auto comment = comments["{ad3169f2-7d29-4f44-99a6-91041dc04f06}"];
	EXPECT_FLOAT_EQ(comment->x1(), 212.0f);
	EXPECT_FLOAT_EQ(comment->y1(), -258.0f);
	EXPECT_FLOAT_EQ(comment->x2(), 481.938f);
	EXPECT_FLOAT_EQ(comment->y2(), -207.0f);

	auto cubes = worldModel.cubes();
	const auto cubeWithBeginItem = cubes["cube_with_begin"];
	const auto worldPoint = cubeWithBeginItem->mapToScene({cubeWithBeginItem->x1(), cubeWithBeginItem->y1()});
	EXPECT_FLOAT_EQ(worldPoint.x(), 250);
	EXPECT_FLOAT_EQ(worldPoint.y(), 300);

	auto robotModels = mModel->robotModels();
	EXPECT_EQ(robotModels.size(), 1);
	auto robotModel = robotModels[0];
	auto leftWheelPortInfo = robotModel->getPortInfoOnWheel(
	                        twoDModel::model::RobotModel::WheelEnum::left);
	auto rightWheelPortInfo = robotModel->getPortInfoOnWheel(
	                        twoDModel::model::RobotModel::WheelEnum::right);
	EXPECT_EQ(leftWheelPortInfo.toString(), "M4###output###М4###");
	EXPECT_EQ(rightWheelPortInfo.toString(), "M3###output###М3###");
	EXPECT_FLOAT_EQ(robotModel->position().x(), 10.0f);
	EXPECT_FLOAT_EQ(robotModel->position().y(), 25.0f);
	EXPECT_FLOAT_EQ(robotModel->rotation(), 0.0f);

	const auto parameters = robotModel->parameters();
	EXPECT_FLOAT_EQ(parameters->friction(), 0.3f);
	EXPECT_FLOAT_EQ(parameters->restitution(), 0.5f);
	EXPECT_FLOAT_EQ(parameters->linearDamping(), 3.5f);
	EXPECT_FLOAT_EQ(parameters->angularDamping(), 2.5f);
	EXPECT_FLOAT_EQ(parameters->mass(), 1.2f);
}

constexpr auto epsilon = 1e-4;
constexpr auto pixelsInCm = 16.0 / 5.6;

#define EXPECT_LT_ABS(X, Y) \
	EXPECT_NEAR(X, (Y) * pixelsInCm, epsilon)

TEST_F(ModelParserTests, cmConfugurationDefaultParametersTest)
{
	ON_CALL(*mTwoDRobotModel, robotId()).WillByDefault(Return("mockRobot"));
	ON_CALL(*mTwoDRobotModel, mass()).WillByDefault(Return(1.05f));
	ON_CALL(*mTwoDRobotModel, friction()).WillByDefault(Return(0.3f));
	EXPECT_CALL(*mTwoDRobotModel, robotId()).Times(AtLeast(1));

	QDomDocument doc;
	const auto xml = utils::InFile::readAll("./data/cmWorldModel.xml");
	doc.setContent(xml);
	mModel->deserialize(doc);
	const auto &setting = mModel->settings();

	EXPECT_EQ(setting.realisticMotors(), false);
	EXPECT_EQ(setting.realisticPhysics(), false);
	EXPECT_EQ(setting.realisticSensors(), false);
	EXPECT_LT_ABS(setting.pixelsInCm(), 1);
	auto &worldModel = mModel->worldModel();
	const auto walls = worldModel.walls();
	const auto wallItem = walls["{1bd5379e-e8bb-449a-b91d-4da031309bc3}"];

	EXPECT_LT_ABS(wallItem->x1(), -350.0f);
	EXPECT_LT_ABS(wallItem->y1(), -250.0f);
	EXPECT_LT_ABS(wallItem->x2(), 0.0f);
	EXPECT_LT_ABS(wallItem->y2(), -250.0f);
	EXPECT_LT_ABS(wallItem->pen().widthF(), 2.1f);
	const auto wallSolidItem = static_cast<twoDModel::items::SolidItem*>(wallItem.data());
	EXPECT_FLOAT_EQ(wallSolidItem->friction(), 1.0f);
	EXPECT_FLOAT_EQ(wallSolidItem->restitution(), 0.8f);

	const auto skittles = worldModel.skittles();
	const auto skittleItem = skittles["{af2bf97f-90cd-49a2-a201-b3f6e57497bb}"];
	EXPECT_LT_ABS(skittleItem->x(), 50.0f);
	EXPECT_LT_ABS(skittleItem->y(), -250.0f);
	EXPECT_FLOAT_EQ(skittleItem->rotation(), 0.0f);
	skittleItem->returnToStartPosition();
	EXPECT_LT_ABS(skittleItem->x(), 10.0f);
	EXPECT_LT_ABS(skittleItem->y(), -25.0f);
	EXPECT_FLOAT_EQ(skittleItem->rotation(), 10.0f);

	const auto skittleSolidItem = static_cast<twoDModel::items::SolidItem*>(skittleItem.data());
	EXPECT_FLOAT_EQ(skittleSolidItem->friction(), 0.2f);
	EXPECT_FLOAT_EQ(skittleSolidItem->restitution(), 0.8f);
	EXPECT_FLOAT_EQ(skittleSolidItem->linearDamping(), 6.0f);
	EXPECT_FLOAT_EQ(skittleSolidItem->angularDamping(), 6.0f);
	EXPECT_FLOAT_EQ(skittleSolidItem->mass(), 0.05f);

	const auto balls = worldModel.balls();
	const auto ballItem = balls["{6573d515-983f-439e-a3df-dee6e9ea8e73}"];
	EXPECT_LT_ABS(ballItem->x(), -402.0f);
	EXPECT_LT_ABS(ballItem->y(), -250.0f);
	EXPECT_FLOAT_EQ(ballItem->rotation(), 0.0f);
	ballItem->returnToStartPosition();
	EXPECT_LT_ABS(ballItem->x(), -102.0f);
	EXPECT_LT_ABS(ballItem->y(), -25.0f);
	EXPECT_FLOAT_EQ(ballItem->rotation(), 10.0f);

	const auto ballSolidItem = static_cast<twoDModel::items::SolidItem*>(ballItem.data());
	EXPECT_FLOAT_EQ(ballSolidItem->friction(), 1.0f);
	EXPECT_FLOAT_EQ(ballSolidItem->restitution(), 0.8f);
	EXPECT_FLOAT_EQ(ballSolidItem->linearDamping(), 0.09f);
	EXPECT_FLOAT_EQ(ballSolidItem->angularDamping(), 0.09f);
	EXPECT_FLOAT_EQ(ballSolidItem->mass(), 0.015f);

	const auto colorFields = worldModel.colorFields();
	const auto lineItem = colorFields["{b8ef1043-4bf4-42bf-8f61-841217cc3318}"];
	EXPECT_LT_ABS(lineItem->x1(), -202.0f);
	EXPECT_LT_ABS(lineItem->y1(), -101.0f);
	EXPECT_LT_ABS(lineItem->x2(), 250.0f);
	EXPECT_LT_ABS(lineItem->y2(), -99.0f);
	EXPECT_LT_ABS(lineItem->pen().widthF(), 6.5f);
	EXPECT_FLOAT_EQ(lineItem->rotation(), 0.0f);

	const auto cubicBezier = colorFields["{1b4bb76e-1aff-4d9b-aebb-d6f4fc581e28}"];
	EXPECT_LT_ABS(cubicBezier->x1(), 251.0f);
	EXPECT_LT_ABS(cubicBezier->y1(), 102.0f);
	EXPECT_LT_ABS(cubicBezier->x2(), -198.0f);
	EXPECT_LT_ABS(cubicBezier->y2(), 101.0f);
	EXPECT_LT_ABS(cubicBezier->pen().widthF(), 6.0f);
	EXPECT_FLOAT_EQ(cubicBezier->rotation(), 0.0f);

	const auto rectangle = colorFields["{3f73d96c-7f93-4aac-beb2-ab73832ed556}"];
	EXPECT_LT_ABS(rectangle->x1(), -452.0f);
	EXPECT_LT_ABS(rectangle->y1(), -102.0f);
	EXPECT_LT_ABS(rectangle->x2(), -248.0f);
	EXPECT_LT_ABS(rectangle->y2(), 103.0f);
	EXPECT_LT_ABS(rectangle->pen().widthF(), 6.0f);

	auto comments = worldModel.commentItems();
	auto comment = comments["{ad3169f2-7d29-4f44-99a6-91041dc04f06}"];
	EXPECT_LT_ABS(comment->x1(), 212.0f);
	EXPECT_LT_ABS(comment->y1(), -258.0f);
	EXPECT_LT_ABS(comment->x2(), 481.938f);
	EXPECT_LT_ABS(comment->y2(), -207.0f);

	auto robotModels = mModel->robotModels();
	EXPECT_EQ(robotModels.size(), 1);
	auto robotModel = robotModels[0];
	auto leftWheelPortInfo = robotModel->getPortInfoOnWheel(
	                        twoDModel::model::RobotModel::WheelEnum::left);
	auto rightWheelPortInfo = robotModel->getPortInfoOnWheel(
	                        twoDModel::model::RobotModel::WheelEnum::right);
	EXPECT_EQ(leftWheelPortInfo.toString(), "M4###output###М4###");
	EXPECT_EQ(rightWheelPortInfo.toString(), "M3###output###М3###");
	EXPECT_LT_ABS(robotModel->position().x(), 10.0f);
	EXPECT_LT_ABS(robotModel->position().y(), 25.0f);
	EXPECT_FLOAT_EQ(robotModel->rotation(), 0.0f);

	const auto parameters = robotModel->parameters();
	EXPECT_FLOAT_EQ(parameters->friction(), 0.3f);
	EXPECT_FLOAT_EQ(parameters->restitution(), 0.6f);
	EXPECT_FLOAT_EQ(parameters->linearDamping(), 1.0f);
	EXPECT_FLOAT_EQ(parameters->angularDamping(), 1.0f);
	EXPECT_FLOAT_EQ(parameters->mass(), 1.05f);
}
