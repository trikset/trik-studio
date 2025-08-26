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
#include "src/engine/items/wallItem.h"
#include "src/engine/items/startPosition.h"
#include "src/engine/items/skittleItem.h"
#include "src/engine/items/lineItem.h"
#include "src/engine/items/ballItem.h"
#include "src/engine/items/commentItem.h"
#include <cmath>
#include <QFile>
#include <QTextStream>

using namespace ::testing;
using namespace qrTest::robotsTests::commonTwoDModelTests;

namespace {

static QString readAll(const QString &fileName) {
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		return QString();
	}

	QTextStream input;
	input.setDevice(&file);
	input.setCodec("UTF-8");
	const QString text = input.readAll();
	return text;
}
}

void ModelParserTests::SetUp()
{
	mModel.reset(
	        new twoDModel::model::Model(new PhysicsEngineFactoryMock()));
	mRobotModel.reset(new RobotModelInterfaceMock());
	mTwoDRobotModel.reset(new TwoDRobotModelMock(*mRobotModel.data()));
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

TEST_F(ModelParserTests, defaultConfugurationTest)
{
	ON_CALL(*mTwoDRobotModel, robotId()).WillByDefault(Return("mockRobot"));
	EXPECT_CALL(*mTwoDRobotModel, robotId()).Times(AtLeast(1));

	QDomDocument doc;
	const auto xml = readAll("./data/pixelWorldModel.xml");
	doc.setContent(xml);
	mModel->deserialize(doc);
	const auto &setting = mModel->settings();
	EXPECT_EQ(setting.realisticMotors(), false);
	EXPECT_EQ(setting.realisticPhysics(), false);
	EXPECT_EQ(setting.realisticSensors(), false);
	auto &worldModel = mModel->worldModel();
	const auto walls = worldModel.walls();
	const auto wallItem = walls["{1bd5379e-e8bb-449a-b91d-4da031309bc3}"];
	EXPECT_EQ(wallItem->x1(), -350);
	EXPECT_EQ(wallItem->y1(), -250);
	EXPECT_EQ(wallItem->x2(), 0);
	EXPECT_EQ(wallItem->y2(), -250);
	EXPECT_EQ(wallItem->pen().widthF(), 2.1);

	const auto skittles = worldModel.skittles();
	const auto skittleItem = skittles["{af2bf97f-90cd-49a2-a201-b3f6e57497bb}"];
	EXPECT_EQ(skittleItem->x(), 50);
	EXPECT_EQ(skittleItem->y(), -250);
	EXPECT_EQ(skittleItem->rotation(), 0);
	skittleItem->returnToStartPosition();
	EXPECT_EQ(skittleItem->x(), 10);
	EXPECT_EQ(skittleItem->y(), -25);
	EXPECT_EQ(skittleItem->rotation(), 10);

	const auto balls = worldModel.balls();
	const auto ballItem = balls["{6573d515-983f-439e-a3df-dee6e9ea8e73}"];
	EXPECT_EQ(ballItem->x(), -402);
	EXPECT_EQ(ballItem->y(), -250);
	EXPECT_EQ(ballItem->rotation(), 0);
	ballItem->returnToStartPosition();
	EXPECT_EQ(ballItem->x(), -102);
	EXPECT_EQ(ballItem->y(), -25);
	EXPECT_EQ(ballItem->rotation(), 10);

	const auto colorFields = worldModel.colorFields();
	const auto lineItem = colorFields["{b8ef1043-4bf4-42bf-8f61-841217cc3318}"];
	EXPECT_EQ(lineItem->x1(), -202);
	EXPECT_EQ(lineItem->y1(), -101);
	EXPECT_EQ(lineItem->x2(), 250);
	EXPECT_EQ(lineItem->y2(), -99);
	EXPECT_EQ(lineItem->pen().widthF(), 6.5);
	EXPECT_EQ(lineItem->rotation(), 0);

	const auto cubicBezier = colorFields["{1b4bb76e-1aff-4d9b-aebb-d6f4fc581e28}"];
	EXPECT_EQ(cubicBezier->x1(), 251);
	EXPECT_EQ(cubicBezier->y1(), 102);
	EXPECT_EQ(cubicBezier->x2(), -198);
	EXPECT_EQ(cubicBezier->y2(), 101);
	EXPECT_EQ(cubicBezier->pen().widthF(), 6);
	EXPECT_EQ(cubicBezier->rotation(), 0);

	const auto rectangle = colorFields["{3f73d96c-7f93-4aac-beb2-ab73832ed556}"];
	EXPECT_EQ(rectangle->x1(), -452);
	EXPECT_EQ(rectangle->y1(), -102);
	EXPECT_EQ(rectangle->x2(), -248);
	EXPECT_EQ(rectangle->y2(), 103);
	EXPECT_EQ(rectangle->pen().widthF(), 6);

	auto comments = worldModel.commentItems();
	auto comment = comments["{ad3169f2-7d29-4f44-99a6-91041dc04f06}"];
	EXPECT_EQ(comment->x1(), 212);
	EXPECT_EQ(comment->y1(), -258);
	EXPECT_EQ(comment->x2(), 481.938);
	EXPECT_EQ(comment->y2(), -207);

	auto robotModels = mModel->robotModels();
	EXPECT_EQ(robotModels.size(), 1);
	auto robotModel = robotModels[0];
	auto leftWheelPortInfo = robotModel->getPortInfoOnWheel(
	                        twoDModel::model::RobotModel::WheelEnum::left);
	auto rightWheelPortInfo = robotModel->getPortInfoOnWheel(
	                        twoDModel::model::RobotModel::WheelEnum::right);
	EXPECT_EQ(leftWheelPortInfo.toString(), "M4###output###М4###");
	EXPECT_EQ(rightWheelPortInfo.toString(), "M3###output###М3###");
	EXPECT_EQ(robotModel->position().x(), 10);
	EXPECT_EQ(robotModel->position().y(), 25);
	EXPECT_EQ(robotModel->rotation(), 0);
}

static const auto epsilon = 0.0001f;
static const auto pixelsInCm = 16.0f / 5.6f;

#define EXPECT_LT_ABS(X, Y) \
	EXPECT_LT(std::abs(X - (Y * pixelsInCm)), epsilon)

TEST_F(ModelParserTests, cmConfugurationTest)
{
	ON_CALL(*mTwoDRobotModel, robotId()).WillByDefault(Return("mockRobot"));
	EXPECT_CALL(*mTwoDRobotModel, robotId()).Times(AtLeast(1));

	QDomDocument doc;
	const auto xml = readAll("./data/cmWorldModel.xml");
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

	EXPECT_LT_ABS(wallItem->x1(), -350);
	EXPECT_LT_ABS(wallItem->y1(), -250);
	EXPECT_LT_ABS(wallItem->x2(), 0);
	EXPECT_LT_ABS(wallItem->y2(), -250);
	EXPECT_LT_ABS(wallItem->pen().widthF(), 2.1);

	const auto skittles = worldModel.skittles();
	const auto skittleItem = skittles["{af2bf97f-90cd-49a2-a201-b3f6e57497bb}"];
	EXPECT_LT_ABS(skittleItem->x(), 50);
	EXPECT_LT_ABS(skittleItem->y(), -250);
	EXPECT_LT_ABS(skittleItem->rotation(), 0);
	skittleItem->returnToStartPosition();
	EXPECT_LT_ABS(skittleItem->x(), 10);
	EXPECT_LT_ABS(skittleItem->y(), -25);
	EXPECT_EQ(skittleItem->rotation(), 10);

	const auto balls = worldModel.balls();
	const auto ballItem = balls["{6573d515-983f-439e-a3df-dee6e9ea8e73}"];
	EXPECT_LT_ABS(ballItem->x(), -402);
	EXPECT_LT_ABS(ballItem->y(), -250);
	EXPECT_LT_ABS(ballItem->rotation(), 0);
	ballItem->returnToStartPosition();
	EXPECT_LT_ABS(ballItem->x(), -102);
	EXPECT_LT_ABS(ballItem->y(), -25);
	EXPECT_EQ(ballItem->rotation(), 10);

	const auto colorFields = worldModel.colorFields();
	const auto lineItem = colorFields["{b8ef1043-4bf4-42bf-8f61-841217cc3318}"];
	EXPECT_LT_ABS(lineItem->x1(), -202);
	EXPECT_LT_ABS(lineItem->y1(), -101);
	EXPECT_LT_ABS(lineItem->x2(), 250);
	EXPECT_LT_ABS(lineItem->y2(), -99);
	EXPECT_LT_ABS(lineItem->pen().widthF(), 6.5);
	EXPECT_EQ(lineItem->rotation(), 0);

	const auto cubicBezier = colorFields["{1b4bb76e-1aff-4d9b-aebb-d6f4fc581e28}"];
	EXPECT_LT_ABS(cubicBezier->x1(), 251);
	EXPECT_LT_ABS(cubicBezier->y1(), 102);
	EXPECT_LT_ABS(cubicBezier->x2(), -198);
	EXPECT_LT_ABS(cubicBezier->y2(), 101);
	EXPECT_LT_ABS(cubicBezier->pen().widthF(), 6);
	EXPECT_EQ(cubicBezier->rotation(), 0);

	const auto rectangle = colorFields["{3f73d96c-7f93-4aac-beb2-ab73832ed556}"];
	EXPECT_LT_ABS(rectangle->x1(), -452);
	EXPECT_LT_ABS(rectangle->y1(), -102);
	EXPECT_LT_ABS(rectangle->x2(), -248);
	EXPECT_LT_ABS(rectangle->y2(), 103);
	EXPECT_LT_ABS(rectangle->pen().widthF(), 6);

	auto comments = worldModel.commentItems();
	auto comment = comments["{ad3169f2-7d29-4f44-99a6-91041dc04f06}"];
	EXPECT_LT_ABS(comment->x1(), 212);
	EXPECT_LT_ABS(comment->y1(), -258);
	EXPECT_LT_ABS(comment->x2(), 481.938);
	EXPECT_LT_ABS(comment->y2(), -207);

	auto robotModels = mModel->robotModels();
	EXPECT_EQ(robotModels.size(), 1);
	auto robotModel = robotModels[0];
	auto leftWheelPortInfo = robotModel->getPortInfoOnWheel(
	                        twoDModel::model::RobotModel::WheelEnum::left);
	auto rightWheelPortInfo = robotModel->getPortInfoOnWheel(
	                        twoDModel::model::RobotModel::WheelEnum::right);
	EXPECT_EQ(leftWheelPortInfo.toString(), "M4###output###М4###");
	EXPECT_EQ(rightWheelPortInfo.toString(), "M3###output###М3###");
	EXPECT_LT_ABS(robotModel->position().x(), 10);
	EXPECT_LT_ABS(robotModel->position().y(), 25);
	EXPECT_EQ(robotModel->rotation(), 0);
}
