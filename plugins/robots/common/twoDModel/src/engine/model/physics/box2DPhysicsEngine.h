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
#pragma once

#include "physicsEngineBase.h"

#include <box2d/box2d.h>
#include <qrutils/mathUtils/geometry.h>

#include "twoDModel/engine/model/worldModel.h"

class b2World;
class b2Body;

namespace graphicsUtils {
	class AbstractItem;
}

namespace twoDModel {
	namespace view {
		class TwoDModelScene;
		class RobotItem;
		class SensorItem;
	}

	namespace trajectory {
	class TrajectorySaver;
	}

	namespace model {
	namespace physics {
	namespace parts {
		class Box2DRobot;
		class Box2DWheel;
		class Box2DItem;
	}

class Box2DPhysicsEngine : public PhysicsEngineBase
{
	Q_OBJECT
public:
	Box2DPhysicsEngine(const WorldModel &worldModel, const QList<RobotModel *> &robots);
	~Box2DPhysicsEngine();
	QVector2D positionShift(RobotModel &robot) const override;
	qreal rotation(RobotModel &robot) const override;
	void addRobot(RobotModel * const robot) override;
	void addRobot(RobotModel * const robot, const QPointF &pos, qreal angle);
	void removeRobot(RobotModel * const robot) override;
	void recalculateParameters(qreal timeInterval) override;
	void wakeUp() override;
	void nextFrame() override;
	void clearForcesAndStop() override;
	bool isRobotStuck() const override;

	float pxToCm(qreal px) const;
	b2Vec2 pxToCm(const QPointF &posInPx) const;
	qreal cmToPx(float cm) const;
	QPointF cmToPx(const b2Vec2 posInCm) const;
	float pxToM(qreal px) const;
	qreal mToPx(float m) const;

	b2Vec2 positionToBox2D(const QPointF &sceneCoords) const;
	b2Vec2 positionToBox2D(float x, float y) const;
	QPointF positionToScene(b2Vec2 boxCoords) const;
	QPointF positionToScene(float x, float y) const;
	float angleToBox2D(qreal sceneAngle) const;
	qreal angleToScene(float boxAngle) const;
	qreal computeDensity(const QPolygonF &shape, qreal mass);
	qreal computeDensity(qreal radius, qreal mass);

	b2World &box2DWorld();

public slots:
	void onItemDragged(graphicsUtils::AbstractItem *item);
	void onRobotStartPositionChanged(const QPointF &newPos, twoDModel::model::RobotModel *robot);
	void onRobotStartAngleChanged(const qreal newAngle, twoDModel::model::RobotModel *robot);
	void onMouseReleased(const QPointF &newPos, qreal newAngle);
	void onMousePressed();
	void onRecoverRobotPosition(const QPointF &pos);

	signals:
	void trajectoryPosChanged(const QString &id, const QPointF &pos);
	void trajectoryRotChanged(const QString &id, const qreal &rotation);
	void trajectoryItemDragged();
	void trajectorySave();
	void sendNextFrame();

protected:
	void onPixelsInCmChanged(qreal value) override;
	void itemAdded(QGraphicsItem *item) override;
	void itemRemoved(QGraphicsItem * const item) override;

private:
	void onPressedReleasedSelectedItems(bool active);

	bool itemTracked(QGraphicsItem * const item);

	twoDModel::view::TwoDModelScene *mScene {}; // Doesn't take ownership
	qreal mPixelsInCm;
	QScopedPointer<b2World> mWorld;

	QMap<RobotModel *, parts::Box2DRobot *> mBox2DRobots;  // Takes ownership on b2Body instances
	QMap<RobotModel *, parts::Box2DWheel *> mLeftWheels;  // Does not take ownership
	QMap<RobotModel *, parts::Box2DWheel *> mRightWheels;  // Does not take ownership
	QMap<QGraphicsItem *, parts::Box2DItem *> mBox2DResizableItems;  // Takes ownership on b2Body instances
	QMap<QGraphicsItem *, parts::Box2DItem *> mBox2DDynamicItems;  // Doesn't take ownership
	QMap<RobotModel *, QSet<twoDModel::view::SensorItem *>> mRobotSensors; // Doesn't take ownership
	QList<parts::Box2DItem *> inMoveItems;

	b2Vec2 mPrevPosition;
	float mPrevAngle;
	QScopedPointer<trajectory::TrajectorySaver> mTrajSaver {}; // Takes ownership
};

}
}
}
