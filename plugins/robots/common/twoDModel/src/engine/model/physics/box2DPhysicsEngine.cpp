/* Copyright 2017 Gleb Zakharov, QReal Research Group
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
#include "box2DPhysicsEngine.h"

#include <QDebug>
#include <Box2D/Box2D.h>

#include "twoDModel/engine/model/robotModel.h"
#include "twoDModel/engine/model/constants.h"
#include "twoDModel/engine/model/worldModel.h"
#include "src/engine/view/scene/twoDModelScene.h"
#include "src/engine/view/scene/robotItem.h"
#include "src/engine/items/wallItem.h"
#include "qrutils/mathUtils/math.h"
#include "parts/box2DWheel.h"
#include "parts/box2DRobot.h"
#include "parts/box2DWall.h"


using namespace twoDModel::model::physics;
using namespace parts;
using namespace mathUtils;

box2DPhysicsEngine::box2DPhysicsEngine (const WorldModel &worldModel
		, const QList<RobotModel *> robots)
	: PhysicsEngineBase(worldModel, robots)
	, mPixelsInCm(worldModel.pixelsInCm())
	, mWorld(new b2World(b2Vec2(0, 0)))
	, mPrevPosition(b2Vec2(0, 0))
	, mPrevAngle(0)
{
	connect(&worldModel, &model::WorldModel::wallAdded, this, &itemAdded);
	connect(&worldModel, &model::WorldModel::itemRemoved, this, &itemRemoved);
}

box2DPhysicsEngine::~box2DPhysicsEngine(){
	for (box2DRobot *robot : mBox2DRobots.values())
		delete robot;
	mBox2DRobots.clear();
	mRightWheels.clear();
	mLeftWheels.clear();
	mBox2DWalls.clear();
}

QVector2D box2DPhysicsEngine::positionShift(model::RobotModel &robot) const
{
	if (!mBox2DRobots.contains(&robot))
		return QVector2D();
	return QVector2D(positionToScene(mBox2DRobots[&robot]->body->GetPosition() - mPrevPosition));
}

qreal box2DPhysicsEngine::rotation(model::RobotModel &robot) const
{
	if (!mBox2DRobots.contains(&robot))
		return 0;
	return angleToScene(mBox2DRobots[&robot]->body->GetAngle() - mPrevAngle);
}

void box2DPhysicsEngine::createDebugRobot(model::RobotModel* const robot)
{
	//robot
	b2AABB aabb;
	mBox2DRobots[robot]->body->GetFixtureList()->GetShape()->ComputeAABB(
		&aabb, b2Transform(mBox2DRobots[robot]->body->GetPosition(), b2Rot(0)), 0);
	robotItem = new QGraphicsRectItem(-25, -25
		, mToPx(aabb.upperBound.x - aabb.lowerBound.x)
		, mToPx(aabb.upperBound.y - aabb.lowerBound.y));
	robotItem->setBrush(QBrush(Qt::red));

	//leftWheel
	mLeftWheels[robot]->body->GetFixtureList()->GetShape()->ComputeAABB(
				&aabb, b2Transform(mLeftWheels[robot]->body->GetPosition(), b2Rot(0)), 0);
	wheel1Item = new QGraphicsRectItem(-10, -6
			, mToPx(aabb.upperBound.x - aabb.lowerBound.x)
			, mToPx(aabb.upperBound.y - aabb.lowerBound.y));
	wheel1Item->setBrush(QBrush(Qt::green));

	//rightWheel
	mRightWheels[robot]->body->GetFixtureList()->GetShape()->ComputeAABB(
				&aabb, b2Transform(mRightWheels[robot]->body->GetPosition(), b2Rot(0)), 0);
	wheel2Item = new QGraphicsRectItem(-10, -6
			, mToPx(aabb.upperBound.x - aabb.lowerBound.x)
			, mToPx(aabb.upperBound.y - aabb.lowerBound.y));
	wheel2Item->setBrush(QBrush(Qt::blue));

	mScene = dynamic_cast<view::TwoDModelScene *>(robot->startPositionMarker()->scene());
	mScene->addItem(robotItem);
	mScene->addItem(wheel1Item);
	mScene->addItem(wheel2Item);
}

void box2DPhysicsEngine::addRobot(model::RobotModel * const robot)
{
	PhysicsEngineBase::addRobot(robot);
	addRobot(robot, robot->rotationCenter(), robot->rotation());

	mPrevPosition = mBox2DRobots[robot]->body->GetPosition();
	mPrevAngle = mBox2DRobots[robot]->body->GetAngle();

	auto funcPos = [&] (const QPointF &newPos) {
		onRobotStartPositionChanged(newPos, dynamic_cast<model::RobotModel *>(sender()));
	};

	auto funcAngle = [&] (const qreal newAngle){
		onRobotStartAngleChanged(newAngle, dynamic_cast<model::RobotModel *>(sender()));
	};

	connect(robot, &model::RobotModel::positionChanged, this, funcPos);
	connect(robot, &model::RobotModel::rotationChanged, this, funcAngle);

	QTimer::singleShot(10, [=] {
		createDebugRobot(robot);
		auto funcRelease = [=] {
			view::RobotItem *rItem = mScene->robot(*robot);
			if (rItem != nullptr)
				onMouseReleased(rItem->pos(), rItem->rotation());
		};
		connect(mScene, &view::TwoDModelScene::mouseReleased, this, funcRelease);
		connect(mScene, &view::TwoDModelScene::mousePressed, this, &onMousePressed);
		connect(mScene->robot(*robot), &view::RobotItem::recoverRobotPosition, this, &onRecoverRobotPosition);

		connect(robot, &model::RobotModel::deserialized, this, &onMouseReleased);
		//add connect to stop robot here
		drawDebugRobot(robot);
	});
}

void box2DPhysicsEngine::addRobot(model::RobotModel * const robot, QPointF pos, qreal angle)
{
	if (mBox2DRobots.contains(robot))
		delete mBox2DRobots[robot];
	mBox2DRobots[robot] = new box2DRobot(this, robot, positionToBox2D(pos), angleToBox2D(angle));
	mLeftWheels[robot] = mBox2DRobots[robot]->wheels.at(0);
	mRightWheels[robot] = mBox2DRobots[robot]->wheels.at(1);
}

void box2DPhysicsEngine::onRobotStartPositionChanged(const QPointF &newPos, model::RobotModel *robot)
{
	if (!mBox2DRobots.contains(robot))
		return;
	bool newPosIsZero = Math::eq(newPos.x(), 0) && Math::eq(newPos.y(), 0);
	if (newPosIsZero || firstSetPos || mMouseJustReleased){
		firstSetPos = false;
		float angle = mBox2DRobots[robot]->body->GetAngle();
		QPointF newPosShift = newPos + QPointF(robot->info().size().width() / 2, robot->info().size().height() / 2);
		addRobot(robot, newPosShift, angleToScene(angle));
		drawDebugRobot(robot);
	}
}

void box2DPhysicsEngine::onRobotStartAngleChanged(const qreal newAngle, model::RobotModel *robot)
{
	if (!mBox2DRobots.contains(robot))
		return;
	const qreal oldAngle = angleToScene(mBox2DRobots[robot]->body->GetAngle());
	if (Math::eq(oldAngle, 0) || Math::eq(newAngle, 0) || mMouseJustReleased){
		b2Vec2 pos = mBox2DRobots[robot]->body->GetPosition();
		addRobot(robot, positionToScene(pos), newAngle);
		drawDebugRobot(robot);
	}
}

void box2DPhysicsEngine::onMouseReleased(QPointF newPos, qreal newAngle)
{
	mMouseJustReleased = true;
	box2DRobot *robot = mBox2DRobots.first();

	robot->FinishStopping();
	onRobotStartAngleChanged(newAngle, robot->model);
	onRobotStartPositionChanged(newPos, robot->model);
	mMouseJustReleased = false;
}

void box2DPhysicsEngine::onMousePressed()
{
	for (box2DRobot *robot: mBox2DRobots){
		robot->StartStopping();
	}
}

void box2DPhysicsEngine::onRecoverRobotPosition(QPointF pos)
{
	onMouseReleased(pos, angleToScene(mBox2DRobots.first()->body->GetAngle()));
}

void box2DPhysicsEngine::removeRobot(model::RobotModel * const robot)
{
	PhysicsEngineBase::removeRobot(robot);
	delete mBox2DRobots[robot];
	mBox2DRobots.remove(robot);
	mLeftWheels.remove(robot);
	mRightWheels.remove(robot);
}

void box2DPhysicsEngine::recalculateParameters(qreal timeInterval)
{	
	const int velocityIterations = 4;
	const int positionIterations = 3;

	model::RobotModel * const robot = mRobots.first();
	b2Body *rBody = mBox2DRobots[robot]->body;
	float32 secondsInterval = timeInterval / 1000.0f;

	if (mBox2DRobots[robot]->IsStopping()){
		mBox2DRobots[robot]->Stop();
	} else {

		mPrevPosition = rBody->GetPosition();
		mPrevAngle = rBody->GetAngle();

		const qreal speed1 = pxToM(wheelLinearSpeed(*robot, robot->leftWheel())) / secondsInterval * 10;
		const qreal speed2 = pxToM(wheelLinearSpeed(*robot, robot->rightWheel())) / secondsInterval * 10;

		mLeftWheels[robot]->keepConstantSpeed(speed1, secondsInterval);
		mRightWheels[robot]->keepConstantSpeed(speed2, secondsInterval);
	}

	mWorld->Step(secondsInterval, velocityIterations, positionIterations);
	drawDebugRobot(robot);
}

void box2DPhysicsEngine::onPixelsInCmChanged(qreal value)
{
	mPixelsInCm = value;
}

void box2DPhysicsEngine::itemAdded(items::SolidItem * const item)
{
	if (dynamic_cast<items::WallItem *>(item)) {
		mCurrentWall = dynamic_cast<items::WallItem *>(item);
		auto func = [&] {
			onWallDragged(dynamic_cast<items::WallItem *> (sender()));
		};
		connect(mCurrentWall, &items::WallItem::x1Changed, this, func);
		connect(mCurrentWall, &items::WallItem::x2Changed, this, func);
		connect(mCurrentWall, &items::WallItem::y1Changed, this, func);
		connect(mCurrentWall, &items::WallItem::y2Changed, this, func);
		onWallResize();
	}
}

void box2DPhysicsEngine::onWallResize(){
	if (!mCurrentWall)
		return;
	box2DWall *wall = new box2DWall(this, *mCurrentWall);
	mBox2DWalls[mCurrentWall] = wall;

	//test
	float32 length = QVector2D(mCurrentWall->end() - mCurrentWall->begin()).length();
	QPointF wallSize = QPointF(length + mCurrentWall->width(), mCurrentWall->width());
	QGraphicsRectItem *wallRect = new QGraphicsRectItem(-wallSize.x() / 2, -wallSize.y() / 2
			, wallSize.x() + 10, wallSize.y() + 10);
	wallRect->setBrush(QBrush(Qt::black));
	mScene->addItem(wallRect);
	wallRect->setPos(positionToScene(wall->body->GetPosition()));
	wallRect->setRotation(angleToScene(wall->body->GetAngle()));
	mBlackWallsItems[mBox2DWalls[mCurrentWall]] = wallRect;
	//

	mCurrentWall = nullptr;
}

void box2DPhysicsEngine::onWallDragged(items::WallItem *wall){
	itemRemoved(wall);
	mCurrentWall = wall;
	onWallResize();
}

void box2DPhysicsEngine::itemRemoved(QGraphicsItem * const item)
{
	if (mBox2DWalls.contains(item)) {
		//test
		mScene->removeItem(mBlackWallsItems[mBox2DWalls[item]]);
		//
		delete mBox2DWalls[item];
		mBox2DWalls.remove(item);
	}
}

void box2DPhysicsEngine::drawDebugRobot(model::RobotModel* const robot)
{
	robotItem->setPos(positionToScene(mBox2DRobots[robot]->body->GetPosition()));
	robotItem->setRotation(angleToScene(mBox2DRobots[robot]->body->GetAngle()));
	wheel1Item->setPos(positionToScene(mLeftWheels[robot]->body->GetPosition()));
	wheel1Item->setRotation(angleToScene(mLeftWheels[robot]->body->GetAngle()));
	wheel2Item->setPos(positionToScene(mRightWheels[robot]->body->GetPosition()));
	wheel2Item->setRotation(angleToScene(mRightWheels[robot]->body->GetAngle()));
}

float32 box2DPhysicsEngine::pxToCm(qreal px) const
{
	return static_cast<float32>(px / mPixelsInCm);
}

b2Vec2 box2DPhysicsEngine::pxToCm(const QPointF posInPx) const
{
	return b2Vec2(pxToCm(posInPx.x()), pxToCm(posInPx.y()));
}

qreal box2DPhysicsEngine::cmToPx(float cm) const
{
	return static_cast<qreal>(cm * static_cast<float>(mPixelsInCm));
}

QPointF box2DPhysicsEngine::cmToPx(const b2Vec2 posInCm) const
{
	return QPointF(cmToPx(posInCm.x), cmToPx(posInCm.y));
}

b2Vec2 box2DPhysicsEngine::positionToBox2D(QPointF sceneCoords) const
{
	return positionToBox2D(sceneCoords.x(), sceneCoords.y());
}

b2Vec2 box2DPhysicsEngine::positionToBox2D(float32 x, float32 y) const
{
	QPointF invertedCoords = QPointF(x, -y);
	return 0.01f * pxToCm(invertedCoords);
}

QPointF box2DPhysicsEngine::positionToScene(b2Vec2 boxCoords) const
{
	return positionToScene(boxCoords.x, boxCoords.y);
}

QPointF box2DPhysicsEngine::positionToScene(float32 x, float32 y) const
{
	b2Vec2 invertedCoords = b2Vec2(x, -y);
	return cmToPx(100.0f * invertedCoords);
}

float32 box2DPhysicsEngine::angleToBox2D(qreal sceneAngle) const
{
	return -sceneAngle * mathUtils::pi / 180;
}

qreal box2DPhysicsEngine::angleToScene(float32 boxAngle) const
{
	return -boxAngle / mathUtils::pi * 180;
}

float32 box2DPhysicsEngine::pxToM(qreal px) const
{
	return pxToCm(px) / 100.0f;
}

qreal box2DPhysicsEngine::mToPx(float32 m) const
{
	return cmToPx(100.0f * m);
}
