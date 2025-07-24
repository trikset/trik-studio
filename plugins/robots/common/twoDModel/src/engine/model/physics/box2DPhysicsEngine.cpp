/* Copyright 2017-2018 Dmitry Mordvinov, Gleb Zakharov, CyberTech Labs Ltd.
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

#include <box2d/box2d.h>
#include <qrutils/graphicsUtils/abstractItem.h>

#include "twoDModel/engine/model/robotModel.h"
#include "twoDModel/engine/model/constants.h"
#include "twoDModel/engine/model/worldModel.h"
#include "src/engine/view/scene/twoDModelScene.h"
#include "src/engine/view/scene/robotItem.h"
#include "src/engine/view/scene/sensorItem.h"
#include "src/engine/items/wallItem.h"
#include "src/engine/items/skittleItem.h"
#include "src/engine/items/ballItem.h"
#include "src/engine/items/startPosition.h"
#include "qrutils/mathUtils/math.h"
#include "parts/box2DWheel.h"
#include "parts/box2DRobot.h"
#include "parts/box2DItem.h"

using namespace twoDModel::model::physics;
using namespace parts;
using namespace mathUtils;

const qreal scaleCoeff = 0.001;

Box2DPhysicsEngine::Box2DPhysicsEngine (const WorldModel &worldModel
		, const QList<RobotModel *> &robots)
	: PhysicsEngineBase(worldModel, robots)
	, mPixelsInCm(worldModel.pixelsInCm() * scaleCoeff)
	, mPrevPosition(b2Vec2{0, 0})
	, mPrevAngle(0)
{
	b2WorldDef worldDef = b2DefaultWorldDef();
	worldDef.gravity = b2Vec2{0, 0};
	mWorldId = b2CreateWorld(&worldDef);
	connect(&worldModel, &model::WorldModel::wallAdded,
			this, [this](const QSharedPointer<QGraphicsItem> &i) {itemAdded(i.data());});
	connect(&worldModel, &model::WorldModel::skittleAdded,
			this, [this](const QSharedPointer<QGraphicsItem> &i) {itemAdded(i.data());});
	connect(&worldModel, &model::WorldModel::ballAdded,
			this, [this](const QSharedPointer<QGraphicsItem> &i) {itemAdded(i.data());});
	connect(&worldModel, &model::WorldModel::itemRemoved,
			this, [this](const QSharedPointer<QGraphicsItem> &i) {itemRemoved(i.data());});
}

Box2DPhysicsEngine::~Box2DPhysicsEngine(){
	qDeleteAll(mBox2DRobots);
	qDeleteAll(mBox2DResizableItems);
	b2DestroyWorld(mWorldId);
	mWorldId = b2_nullWorldId;
}

QVector2D Box2DPhysicsEngine::positionShift(model::RobotModel &robot) const
{
	if (!mBox2DRobots.contains(&robot)) {
		return QVector2D();
	}
	return QVector2D(positionToScene(b2Body_GetPosition(mBox2DRobots[&robot]->getBodyId()) - mPrevPosition));
}

qreal Box2DPhysicsEngine::rotation(model::RobotModel &robot) const
{
	if (!mBox2DRobots.contains(&robot)) {
		return 0;
	}

	auto currentAngle = b2Rot_GetAngle(b2Body_GetRotation(mBox2DRobots[&robot]->getBodyId()));
	qreal deltaAngle = currentAngle - mPrevAngle;

	const qreal epsilon = 1e-6;

	if (deltaAngle > mathUtils::pi + epsilon) {
	    deltaAngle -= 2 * mathUtils::pi;
	} else if (deltaAngle < -mathUtils::pi - epsilon) {
	    deltaAngle += 2 * mathUtils::pi;
	}
	return angleToScene(deltaAngle);
}

void Box2DPhysicsEngine::onPressedReleasedSelectedItems(bool active)
{
	for (auto *item : mScene->selectedItems()) {
		Box2DItem *bItem = mBox2DDynamicItems.value(item, nullptr);
		if (bItem) {
			if (active) {
				b2Body_Enable(bItem->getBodyId());
			} else {
				b2Body_Disable(bItem->getBodyId());
			}
		}
	}
}

bool Box2DPhysicsEngine::itemTracked(QGraphicsItem * const item)
{
	return mBox2DResizableItems.contains(item) || mBox2DDynamicItems.contains(item);
}

void Box2DPhysicsEngine::addRobot(model::RobotModel * const robot)
{
	PhysicsEngineBase::addRobot(robot);
	addRobot(robot, robot->robotCenter(), robot->rotation());

	auto bodyId = mBox2DRobots[robot]->getBodyId();
	mPrevPosition = b2Body_GetPosition(bodyId);
	mPrevAngle = b2Rot_GetAngle(b2Body_GetRotation(bodyId));

	connect(robot, &model::RobotModel::positionChanged, this, [&] (const QPointF &newPos) {
		onRobotStartPositionChanged(newPos, dynamic_cast<model::RobotModel *>(sender()));
	});

	connect(robot, &model::RobotModel::rotationChanged, this, [&] (const qreal newAngle){
		onRobotStartAngleChanged(newAngle, dynamic_cast<model::RobotModel *>(sender()));
	});

	QTimer::singleShot(10, this, [this, robot]() {
		mScene = dynamic_cast<view::TwoDModelScene *>(robot->startPositionMarker()->scene());

		connect(mScene->robot(*robot), &view::RobotItem::mouseInteractionStopped, this, [=]() {
			view::RobotItem *rItem = mScene->robot(*robot);
			if (rItem != nullptr) {
				onMouseReleased(rItem->pos(), rItem->rotation());
			}
		});

		connect(mScene->robot(*robot), &view::RobotItem::mouseInteractionStarted
				, this, &Box2DPhysicsEngine::onMousePressed);

		connect(mScene->robot(*robot), &view::RobotItem::recoverRobotPosition
				, this, &Box2DPhysicsEngine::onRecoverRobotPosition);

		connect(mScene->robot(*robot), &view::RobotItem::sensorAdded, this, [&](twoDModel::view::SensorItem *sensor) {
			auto rItem = dynamic_cast<view::RobotItem *>(sender());
			auto model = &rItem->robotModel();
			mRobotSensors[model].insert(sensor);
			mBox2DRobots[model]->addSensor(sensor);
		});
		connect(mScene->robot(*robot), &view::RobotItem::sensorRemoved, this, [&](twoDModel::view::SensorItem *sensor) {
			auto rItem = dynamic_cast<view::RobotItem *>(sender());
			auto model = &rItem->robotModel();
			mRobotSensors[model].remove(sensor);
			mBox2DRobots[model]->removeSensor(sensor);
		});
		connect(mScene->robot(*robot), &view::RobotItem::sensorUpdated
				, this, [&](twoDModel::view::SensorItem *sensor) {
			auto rItem = dynamic_cast<view::RobotItem *>(sender());
			auto model = &rItem->robotModel();
			mBox2DRobots[model]->reinitSensor(sensor);
		});

		connect(robot, &model::RobotModel::deserialized, this, &Box2DPhysicsEngine::onMouseReleased);
	});
}

void Box2DPhysicsEngine::addRobot(model::RobotModel * const robot, const QPointF &pos, qreal angle)
{
	if (mBox2DRobots.contains(robot)) {
		delete mBox2DRobots[robot];
	}

	mBox2DRobots[robot] = new Box2DRobot(this, robot, positionToBox2D(pos), angleToBox2D(angle));
	mLeftWheels[robot] = mBox2DRobots[robot]->getWheelAt(0);
	mRightWheels[robot] = mBox2DRobots[robot]->getWheelAt(1);
}

void Box2DPhysicsEngine::onRobotStartPositionChanged(const QPointF &newPos, model::RobotModel *robot)
{
	if (!mBox2DRobots.contains(robot)) {
		return;
	}

	QPointF robotCenter(robot->info().size().width() / 2, robot->info().size().height() / 2);
	mBox2DRobots[robot]->moveToPoint(positionToBox2D(newPos + robotCenter));
}

void Box2DPhysicsEngine::onRobotStartAngleChanged(const qreal newAngle, model::RobotModel *robot)
{
	if (!mBox2DRobots.contains(robot)) {
		return;
	}

	mBox2DRobots[robot]->setRotation(angleToBox2D(newAngle));
}

void Box2DPhysicsEngine::onMouseReleased(const QPointF &newPos, qreal newAngle)
{
	Box2DRobot *robot = mBox2DRobots.first();

	robot->finishStopping();
	onRobotStartPositionChanged(newPos, robot->getRobotModel());
	onRobotStartAngleChanged(newAngle, robot->getRobotModel());

	onPressedReleasedSelectedItems(true);
}

void Box2DPhysicsEngine::onMousePressed()
{
	for (Box2DRobot *robot: mBox2DRobots){
		robot->startStopping();
	}

	onPressedReleasedSelectedItems(false);
}

void Box2DPhysicsEngine::onRecoverRobotPosition(const QPointF &pos)
{
	clearForcesAndStop();

	auto stop = [=](b2BodyId bodyId){
		b2Body_SetAngularVelocity(bodyId, 0);
		b2Body_SetLinearVelocity(bodyId, {0, 0});
	};

	stop(mBox2DRobots.first()->getBodyId());
	stop(mBox2DRobots.first()->getWheelAt(0)->getBodyId());
	stop(mBox2DRobots.first()->getWheelAt(1)->getBodyId());

	onMouseReleased(pos, mBox2DRobots.keys().first()->startPositionMarker()->rotation());
}

void Box2DPhysicsEngine::removeRobot(model::RobotModel * const robot)
{
	PhysicsEngineBase::removeRobot(robot);
	delete mBox2DRobots[robot];
	mBox2DRobots.remove(robot);
	mLeftWheels.remove(robot);
	mRightWheels.remove(robot);
}

void Box2DPhysicsEngine::recalculateParameters(qreal timeInterval)
{
	const int subStepCount = 10;

	model::RobotModel * const robot = mRobots.first();
	if (!mBox2DRobots[robot]) {
		return;
	}

	b2BodyId rBodyId = mBox2DRobots[robot]->getBodyId();
	float secondsInterval = timeInterval / 1000.0f;

	if (mBox2DRobots[robot]->isStopping()){
		mBox2DRobots[robot]->stop();
	} else {
		// sAdpt is the speed adaptation coefficient for physics engines
		const int sAdpt = 10;
		const qreal speed1 = pxToM(wheelLinearSpeed(*robot, robot->leftWheel())) / secondsInterval * sAdpt;
		const qreal speed2 = pxToM(wheelLinearSpeed(*robot, robot->rightWheel())) / secondsInterval * sAdpt;

		if (qAbs(speed1) + qAbs(speed2) < FLT_EPSILON) {
			mBox2DRobots[robot]->stop();
			mLeftWheels[robot]->stop();
			mRightWheels[robot]->stop();
		}
		else {
			mLeftWheels[robot]->keepConstantSpeed(speed1);
			mRightWheels[robot]->keepConstantSpeed(speed2);
		}
	}


	mPrevPosition = b2Body_GetPosition(rBodyId);
	mPrevAngle = b2Rot_GetAngle(b2Body_GetRotation(rBodyId));

	b2World_Step(mWorldId, secondsInterval, subStepCount);
	static volatile auto sThisFlagHelpsToAvoidClangError = true;
	if ("If you want debug BOX2D, fix this expression to be false" && sThisFlagHelpsToAvoidClangError) {
		return;
	}

	QPainterPath path;

	for(QGraphicsItem *item : mBox2DDynamicItems.keys()) {
		if (auto solidItem = dynamic_cast<items::SolidItem *>(item)) {
			QPolygonF localCollidingPolygon = solidItem->collidingPolygon();
			qreal lsceneAngle = angleToScene(mBox2DDynamicItems[item]->getRotation());
			QMatrix m;
			m.rotate(lsceneAngle);

			QPointF firstP = localCollidingPolygon.at(0);
			localCollidingPolygon.translate(-firstP.x(), -firstP.y());

			QPainterPath lpath;
			lpath.addPolygon(localCollidingPolygon);
			QPainterPath lpathTR = m.map(lpath);
			lpathTR.translate(firstP.x(), firstP.y());

			path.addPath(lpathTR);
		}
	}

	auto bodyId = mBox2DRobots[robot]->getBodyId();
	auto angle = b2Rot_GetAngle(b2Body_GetRotation(bodyId));
	auto position = b2Body_GetPosition(bodyId);

	qreal angleRobot = angleToScene(angle);
	QPointF posRobot = positionToScene(position);
	QGraphicsRectItem *rect1 = new QGraphicsRectItem(-25, -25, 60, 50);
	QGraphicsRectItem *rect2 = new QGraphicsRectItem(-10, -6, 20, 10);
	QGraphicsRectItem *rect3 = new QGraphicsRectItem(-10, -6, 20, 10);

	rect1->setTransformOriginPoint(0, 0);
	rect1->setRotation(angleRobot);
	rect1->setPos(posRobot);
	rect2->setTransformOriginPoint(0, 0);

	auto wheelBodyId = mBox2DRobots[robot]->getWheelAt(0)->getBodyId();
	auto wheelBodyAngle = b2Rot_GetAngle(b2Body_GetRotation(wheelBodyId));
	auto wheelBodyPosition = b2Body_GetPosition(wheelBodyId);

	auto wheel1BodyId = mBox2DRobots[robot]->getWheelAt(1)->getBodyId();
	auto wheel1BodyAngle = b2Rot_GetAngle(b2Body_GetRotation(wheel1BodyId));
	auto wheel1BodyPosition = b2Body_GetPosition(wheel1BodyId);

	rect2->setRotation(angleToScene(wheelBodyAngle));
	rect2->setPos(positionToScene(wheelBodyPosition));
	rect3->setTransformOriginPoint(0, 0);
	rect3->setRotation(angleToScene(wheel1BodyAngle));
	rect3->setPos(positionToScene(wheel1BodyPosition));
	mScene->addItem(rect1);
	mScene->addItem(rect2);
	mScene->addItem(rect3);
	QTimer::singleShot(20, [this, rect1, rect2, rect3](){
		for (auto &&rect: {rect1, rect2, rect3}) {
			mScene->removeItem(rect);
			delete rect;
		}
	});


//		 uncomment it for watching mutual position of robot and wheels (polygon form)
//		path.addPolygon(mBox2DRobots[robot]->getDebuggingPolygon());
//		path.addPolygon(mBox2DRobots[robot]->getWheelAt(0)->mDebuggingDrawPolygon);
//		path.addPolygon(mBox2DRobots[robot]->getWheelAt(1)->mDebuggingDrawPolygon);

	const QMap<const view::SensorItem *, Box2DItem *> sensors = mBox2DRobots[robot]->getSensors();
	for (Box2DItem * sensor : sensors.values()) {
		const b2Vec2 position = b2Body_GetPosition(sensor->getBodyId());
		QPointF scenePos = positionToScene(position);
		path.addEllipse(scenePos, 10, 10);
	}

	static QGraphicsPathItem *debugPathBox2D = nullptr;
	if (debugPathBox2D) {
		mScene->removeItem(debugPathBox2D);
		delete debugPathBox2D;
	}
	debugPathBox2D = new QGraphicsPathItem(path);
	debugPathBox2D->setBrush(Qt::blue);
	debugPathBox2D->setPen(QPen(QColor(Qt::red)));
	debugPathBox2D->setZValue(101);
	mScene->addItem(debugPathBox2D);
	mScene->update();
}

void Box2DPhysicsEngine::wakeUp()
{
	for (Box2DRobot *robot : mBox2DRobots) {
		onRobotStartPositionChanged(robot->getRobotModel()->position(), robot->getRobotModel());
		onRobotStartAngleChanged(robot->getRobotModel()->rotation(), robot->getRobotModel());
	}
}

void Box2DPhysicsEngine::nextFrame()
{
	for(QGraphicsItem *item : mBox2DDynamicItems.keys()) {
		auto isEnabled = b2Body_IsEnabled(mBox2DDynamicItems[item]->getBodyId());
		if (isEnabled && mBox2DDynamicItems[item]->angleOrPositionChanged()) {
			QPointF scenePos = positionToScene(mBox2DDynamicItems[item]->getPosition());
			item->setPos(scenePos - item->boundingRect().center());
			item->setRotation(angleToScene(mBox2DDynamicItems[item]->getRotation()));
		}
	}
}

void Box2DPhysicsEngine::clearForcesAndStop()
{
	for (auto item : mBox2DDynamicItems) {
		b2BodyId bodyId = item->getBodyId();
		b2Body_SetLinearVelocity(bodyId, {0, 0});
		b2Body_SetAngularVelocity(bodyId, 0);
	}
}

bool Box2DPhysicsEngine::isRobotStuck() const
{
	return false;
}

void Box2DPhysicsEngine::onPixelsInCmChanged(qreal value)
{
	mPixelsInCm = value * scaleCoeff;
}

void Box2DPhysicsEngine::itemAdded(QGraphicsItem *item)
{
	if (auto abstractItem = dynamic_cast<graphicsUtils::AbstractItem*>(item)) {
		auto onItemDraggedLambda = [&] { onItemDragged(dynamic_cast<graphicsUtils::AbstractItem *> (sender())); };

		connect(abstractItem, &graphicsUtils::AbstractItem::x1Changed, this, onItemDraggedLambda);
		connect(abstractItem, &graphicsUtils::AbstractItem::x2Changed, this, onItemDraggedLambda);
		connect(abstractItem, &graphicsUtils::AbstractItem::y1Changed, this, onItemDraggedLambda);
		connect(abstractItem, &graphicsUtils::AbstractItem::y2Changed, this, onItemDraggedLambda);
		connect(abstractItem, &graphicsUtils::AbstractItem::positionChanged, this, onItemDraggedLambda);

		connect(abstractItem, &graphicsUtils::AbstractItem::mouseInteractionStarted, this, [=](){
			onPressedReleasedSelectedItems(false);
		});

		connect(abstractItem, &graphicsUtils::AbstractItem::mouseInteractionStopped, this, [=](){
			onPressedReleasedSelectedItems(true);
		});

		onItemDragged(abstractItem);
	}
}

void Box2DPhysicsEngine::onItemDragged(graphicsUtils::AbstractItem *item)
{
	// for items, that allows resizing/growing/reshaping, we should recreate box2d object
	if (auto wallItem = dynamic_cast<items::WallItem *>(item)) {
		itemRemoved(item);
		QPolygonF collidingPolygon = wallItem->collidingPolygon();
		if (collidingPolygon.boundingRect().isEmpty() || collidingPolygon.size() < 3) {
			return;
		}

		b2Vec2 pos = positionToBox2D(collidingPolygon.boundingRect().center());
		Box2DItem *box2dItem = new Box2DItem(this, wallItem, pos, angleToBox2D(item->rotation()));
		mBox2DResizableItems[item] = box2dItem;
		return;
	} else if (auto solidItem = dynamic_cast<items::SolidItem *>(item)) {
		QPolygonF collidingPolygon = solidItem->collidingPolygon();
		if (itemTracked(item)) {
			if (solidItem->bodyType() == items::SolidItem::DYNAMIC) {
				auto *bItem = mBox2DDynamicItems[item];

				qreal localRotation = item->rotation();
				item->setRotation(0);
				QPointF localScenePos = item->scenePos();
				item->setRotation(localRotation);
				QRectF localBoundingRect = item->boundingRect();
				QPointF localCenter = localBoundingRect.center();
				bItem->setRotation(0);
				bItem->moveToPosition(positionToBox2D(localScenePos + localCenter));
				bItem->setRotation(angleToBox2D(localRotation));
			}
		} else {
			b2Vec2 pos = positionToBox2D(collidingPolygon.boundingRect().center());
			Box2DItem *box2dItem = new Box2DItem(this, solidItem, pos, angleToBox2D(item->rotation()));
			mBox2DResizableItems[item] = box2dItem;
			if (solidItem->bodyType() == items::SolidItem::DYNAMIC) {
				mBox2DDynamicItems[item] = box2dItem;
			}
		}
	} else {
		/* Nothing */
	}
}

void Box2DPhysicsEngine::itemRemoved(QGraphicsItem * const item)
{
	delete mBox2DResizableItems.value(item);
	mBox2DResizableItems.remove(item);
	mBox2DDynamicItems.remove(item);
}

b2WorldId Box2DPhysicsEngine::box2DWorldId()
{
	return mWorldId;
}

float Box2DPhysicsEngine::pxToCm(qreal px) const
{
	return static_cast<float>(px / mPixelsInCm);
}

b2Vec2 Box2DPhysicsEngine::pxToCm(const QPointF &posInPx) const
{
	return b2Vec2{pxToCm(posInPx.x()), pxToCm(posInPx.y())};
}

qreal Box2DPhysicsEngine::cmToPx(float cm) const
{
	return static_cast<qreal>(cm * static_cast<float>(mPixelsInCm));
}

QPointF Box2DPhysicsEngine::cmToPx(const b2Vec2 posInCm) const
{
	return QPointF(cmToPx(posInCm.x), cmToPx(posInCm.y));
}

b2Vec2 Box2DPhysicsEngine::positionToBox2D(const QPointF &sceneCoords) const
{
	return positionToBox2D(sceneCoords.x(), sceneCoords.y());
}

b2Vec2 Box2DPhysicsEngine::positionToBox2D(float x, float y) const
{
	QPointF invertedCoords = QPointF(x, -y);
	return 0.01f * pxToCm(invertedCoords);
}

QPointF Box2DPhysicsEngine::positionToScene(b2Vec2 boxCoords) const
{
	return positionToScene(boxCoords.x, boxCoords.y);
}

QPointF Box2DPhysicsEngine::positionToScene(float x, float y) const
{
	b2Vec2 invertedCoords = b2Vec2{x, -y};
	return cmToPx(100.0f * invertedCoords);
}

float Box2DPhysicsEngine::angleToBox2D(qreal sceneAngle) const
{
	return -sceneAngle * mathUtils::pi / 180;
}

qreal Box2DPhysicsEngine::angleToScene(float boxAngle) const
{
	return -boxAngle / mathUtils::pi * 180;
}

float Box2DPhysicsEngine::pxToM(qreal px) const
{
	return pxToCm(px) / 100.0f;
}

qreal Box2DPhysicsEngine::mToPx(float m) const
{
	return cmToPx(100.0f * m);
}

qreal Box2DPhysicsEngine::computeDensity(const QPolygonF &shape, qreal mass)
{
	return mass / pxToM(pxToM(mathUtils::Geometry::square(shape)));
}

qreal Box2DPhysicsEngine::computeDensity(qreal radius, qreal mass)
{
	return mass / pxToM(pxToM(mathUtils::pi * radius * radius));
}
