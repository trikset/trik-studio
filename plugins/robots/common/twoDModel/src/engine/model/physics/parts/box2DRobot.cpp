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
#include "box2DRobot.h"

#include <box2d/box2d.h>
#include "src/engine/model/physics/box2DPhysicsEngine.h"
#include "src/engine/view/scene/rangeSensorItem.h"
#include "twoDModel/engine/model/robotModel.h"
#include "twoDModel/engine/model/constants.h"
#include "box2DWheel.h"
#include "box2DItem.h"

using namespace twoDModel::model::physics;
using namespace parts;

Box2DRobot::Box2DRobot(Box2DPhysicsEngine *engine, twoDModel::model::RobotModel * const robotModel
		, b2Vec2 pos, float angle)
	: mModel(robotModel)
	, mEngine(engine)
	, mWorldId(engine->box2DWorldId())
{
	b2BodyDef bodyDef = b2DefaultBodyDef();
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = pos;
	bodyDef.rotation = b2MakeRot(angle);
	mBodyId = b2CreateBody(engine->box2DWorldId(), &bodyDef);
	b2ShapeDef fixtureDef = b2DefaultShapeDef();
	fixtureDef.enableContactEvents = true;
	fixtureDef.material.restitution = 0.6f;
	fixtureDef.material.friction = mModel->info().friction();
	QPolygonF collidingPolygon = mModel->info().collidingPolygon();
	QPointF localCenter = collidingPolygon.boundingRect().center();
	mPolygon.reset(new b2Vec2[collidingPolygon.size()]);
	for (int i = 0; i < collidingPolygon.size(); ++i) {
		mPolygon[i] = engine->positionToBox2D(collidingPolygon.at(i) - localCenter);
	}
	fixtureDef.density = engine->computeDensity(collidingPolygon, mModel->info().mass());
	b2Hull hull = b2ComputeHull(mPolygon.get(), collidingPolygon.size());
	b2Polygon polygon = b2MakePolygon(&hull, 0.0f);
	b2ShapeId polygonShapeId = b2CreatePolygonShape(mBodyId, &fixtureDef, &polygon);
	b2Body_SetUserData(mBodyId, this);
	b2Body_SetAngularDamping(mBodyId, 1.0f);
	b2Body_SetLinearDamping(mBodyId, 1.0f);
	connectWheels();
	auto finalPolygon = b2Shape_GetPolygon(polygonShapeId);

	for (int i = 0; i < finalPolygon.count; ++i) {
		auto position = b2Body_GetPosition(mBodyId);
		mDebuggingDrawPolygon.append(engine->positionToScene(finalPolygon.vertices[i] + position));
	}

	if (!mDebuggingDrawPolygon.isEmpty() && !mDebuggingDrawPolygon.isClosed()) {
		mDebuggingDrawPolygon.append(mDebuggingDrawPolygon.first());
	}
}

Box2DRobot::~Box2DRobot() {
	auto jointCapacity = b2Body_GetJointCount(mBodyId);
	std::vector<b2JointId> joints(jointCapacity);
	auto jointCount = b2Body_GetJoints(mBodyId, joints.data(), jointCapacity);
	for (auto i = 0; i < jointCount; i++) {
		b2DestroyJoint(joints[i]);
	}

	qDeleteAll(mWheels);
	qDeleteAll(mSensors);
	b2DestroyBody(mBodyId);
}

void Box2DRobot::stop()
{
	b2Body_SetLinearVelocity(mBodyId, b2Vec2{0, 0});
	b2Body_SetAngularVelocity(mBodyId, 0);
}

void Box2DRobot::startStopping()
{
	mIsStopping = true;
}

void Box2DRobot::finishStopping()
{
	mIsStopping = false;
}

bool Box2DRobot::isStopping()
{
	return mIsStopping;
}

void Box2DRobot::addSensor(const twoDModel::view::SensorItem *sensor)
{
	// orientation and direction will be set by reinitSensor() method
	mSensors[sensor] = new Box2DItem(mEngine, sensor, {0, 0}, 0);
	reinitSensor(sensor);
}

void Box2DRobot::removeSensor(const twoDModel::view::SensorItem *sensor)
{
	b2BodyId bodyId = mSensors[sensor]->getBodyId();
	std::vector<b2JointId> joints(1);
	auto count = b2Body_GetJoints(bodyId, joints.data(), 1);
	if (count == 1) {
		b2DestroyJoint(joints[0]);
	}
	delete mSensors[sensor];
	mSensors.remove(sensor);
}

void Box2DRobot::moveToPoint(const b2Vec2 &destination)
{
	// it is just a parallel transport, there is no need to reinit joints and etc
	const b2Vec2 oldPosition = b2Body_GetPosition(mBodyId);
	if (oldPosition == destination) {
		return;
	}

	auto rotation = b2Body_GetRotation(mBodyId);
	b2Body_SetTransform(mBodyId, destination, rotation);
	const b2Vec2 shift = destination - oldPosition;

	for (auto wheel : mWheels) {
		b2BodyId wheelBodyID = wheel->getBodyId();
		auto position = b2Body_GetPosition(wheelBodyID);
		auto wheelRotation = b2Body_GetRotation(wheelBodyID);
		b2Body_SetTransform(wheelBodyID, position + shift, wheelRotation);
	}

	for (auto sensor: mSensors) {
		b2BodyId sensorBody = sensor->getBodyId();
		b2Body_SetTransform(sensorBody, b2Body_GetPosition(sensorBody) + shift,
					 b2Body_GetRotation(sensorBody));
	}
}

void Box2DRobot::setRotation(float angle)
{
	auto rotation = b2MakeRot(angle);
	b2Body_SetTransform(mBodyId, b2Body_GetPosition(mBodyId), rotation);

	for (auto wheel : mWheels) {
		b2BodyId wheelBodyId = wheel->getBodyId();
		std::vector<b2JointId> joints(1);
		b2Body_GetJoints(wheelBodyId, joints.data(), 1);
		auto position = b2Joint_GetLocalFrameB(joints[0]);
		b2Body_SetTransform(wheelBodyId, position.p, rotation);
	}

	reinitSensors();
}

void Box2DRobot::reinitSensor(const twoDModel::view::SensorItem *sensor)
{
	// box2d doesn't rotate or shift elements, which are connected to main robot body via joints in case
	// when we manually use method SetTransform.
	// So we need to handle elements such as sensors by hand.
	// We use this method in case when user shifts or rotates sensor(s).

	auto box2dSensor = mSensors[sensor];
	auto bodyId = box2dSensor->getBodyId();
	b2Body_SetLinearVelocity(bodyId, {0, 0});
	b2Body_SetAngularVelocity(bodyId, 0);

	auto jointCapacity = b2Body_GetJointCount(bodyId);
	std::vector<b2JointId> joints(jointCapacity);
	auto jointCount = b2Body_GetJoints(bodyId, joints.data(), jointCapacity);
	for (auto i = 0; i < jointCount; i++) {
		mJoints.removeAll(joints[i].index1);
		b2DestroyJoint(joints[i]);
	}

	QPolygonF collidingPolygon = sensor->collidingPolygon();
	QPointF localCenter = collidingPolygon.boundingRect().center();

	QPointF deltaToCenter = mModel->robotCenter() - mModel->position();
	QPointF localPos = sensor->pos() - deltaToCenter;
	QTransform transform;
	QPointF dif = mModel->robotCenter();
	transform.translate(-dif.x(), -dif.y());
	transform.rotate(mModel->rotation());
	localPos = transform.map(localPos);
	transform.reset();
	transform.translate(dif.x(), dif.y());
	localPos = transform.map(localPos);

	const b2Vec2 pos = mEngine->positionToBox2D(localPos - localCenter + mModel->robotCenter());
	// IMPORTANT: we connect every sensor with box2d circle item.
	// So rotation of sensor doesn't matter, we set rotation corresponding to robot.
	// if in future it will be changed, you'll see some strange behavior, because of joints. See connectSensor method.
	auto angle = b2Body_GetRotation(mBodyId);
	b2Body_SetTransform(bodyId, pos, angle);
	connectSensor(*mSensors[sensor]);
}

void Box2DRobot::reinitSensors()
{
	for (auto *sensor : mSensors.keys()) {
		reinitSensor(sensor);
	}
}

void Box2DRobot::applyForceToCenter(const b2Vec2 &force, bool wake)
{
	b2Body_ApplyForceToCenter(mBodyId, force, wake);
}

b2BodyId Box2DRobot::getBodyId()
{
	return mBodyId;
}

twoDModel::model::RobotModel *Box2DRobot::getRobotModel() const
{
	return mModel;
}

Box2DWheel *Box2DRobot::getWheelAt(int i) const
{
	return mWheels.at(i);
}

const QPolygonF &Box2DRobot::getDebuggingPolygon() const
{
	return mDebuggingDrawPolygon;
}

const QMap<const twoDModel::view::SensorItem *, Box2DItem *> &Box2DRobot::getSensors() const
{
	return mSensors;
}

void Box2DRobot::connectWheels() {
	QPointF leftUpCorner = QPointF(-mModel->info().size().width() / 2, -mModel->info().size().height() / 2);
	///@todo: adapt it for more than 2 wheels
	QPointF posLeftWheelFromRobot = mModel->info().wheelsPosition().first();
	QPointF posRightWheelFromRobot = mModel->info().wheelsPosition().last();
	b2Vec2 posLeftWheel = b2Body_GetWorldPoint(mBodyId, mEngine->positionToBox2D(posLeftWheelFromRobot + leftUpCorner));
	b2Vec2 posRightWheel =  b2Body_GetWorldPoint(mBodyId, mEngine->positionToBox2D(posRightWheelFromRobot + leftUpCorner));
	auto angle = b2Rot_GetAngle(b2Body_GetRotation(mBodyId));
	Box2DWheel *leftWheel = new Box2DWheel(mEngine, posLeftWheel, angle, *this);
	Box2DWheel *rightWheel = new Box2DWheel(mEngine, posRightWheel, angle, *this);
	mWheels.append(leftWheel);
	mWheels.append(rightWheel);
	connectWheel(*leftWheel);
	connectWheel(*rightWheel);
}

void Box2DRobot::connectWheel(Box2DWheel &wheel){
	b2RevoluteJointDef revDef = b2DefaultRevoluteJointDef();
	revDef.base.bodyIdA = wheel.getBodyId();
	revDef.base.bodyIdB = mBodyId;
	revDef.base.collideConnected = false;
	revDef.base.localFrameA.p = b2Body_GetLocalCenterOfMass(wheel.getBodyId());
	auto referenceAngle = 0.0f;
	revDef.base.localFrameA.q = b2MakeRot(referenceAngle);
	revDef.base.localFrameB.p = b2Body_GetLocalPoint(mBodyId, b2Body_GetWorldCenterOfMass(wheel.getBodyId()));
	revDef.enableLimit = true;
	revDef.lowerAngle = 0;
	revDef.upperAngle = 0;

	b2JointId jointId = b2CreateRevoluteJoint(mWorldId, &revDef);
	mJoints.append(jointId.index1);
}

void Box2DRobot::connectSensor(const Box2DItem &sensor)
{
	b2WeldJointDef jointDef = b2DefaultWeldJointDef();
	jointDef.base.bodyIdA = mBodyId;
	jointDef.base.bodyIdB = sensor.getBodyId();
	jointDef.base.localFrameA.p = b2Body_GetLocalCenterOfMass(mBodyId);
	auto referenceAngle = 0.0f;
	jointDef.base.localFrameA.q = b2MakeRot(referenceAngle);
	jointDef.base.localFrameB.p =
			b2Body_GetLocalPoint(sensor.getBodyId(),
					     b2Body_GetWorldCenterOfMass(mBodyId));
	jointDef.linearDampingRatio = 1.0f;
	jointDef.angularDampingRatio = 1.0f;

	b2JointId jointId = b2CreateWeldJoint(mWorldId, &jointDef);
	mJoints.append(jointId.index1);
}
