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

// For best understanding see http://www.iforce2d.net/b2dtut/top-down-car

#include "box2DWheel.h"

#include <qrutils/mathUtils/math.h>
#include <box2d/box2d.h>
#include "twoDModel/engine/model/constants.h"
#include "twoDModel/engine/model/twoDModelRobotParameters.h"
#include "box2DRobot.h"

using namespace twoDModel::model::physics::parts;

Box2DWheel::Box2DWheel(twoDModel::model::RobotModel * const robotModel,
		Box2DPhysicsEngine *engine
		, b2Vec2 positionBox2D, b2Rot rotationBox2D, Box2DRobot &robot)
	: mBodyId(b2_nullBodyId)
	, mRobot(robot)
	, mEngine(engine)
	, mWheelHeightM(engine->pxToM(robotModel->parameters()->wheelDiameter() / 2))
	, mWheelWidthM(engine->pxToM(robotModel->parameters()->wheelDiameter()))
	, mPolygon(new b2Vec2[8])
{
	auto bodyDef = b2DefaultBodyDef();
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = positionBox2D;
	bodyDef.rotation = rotationBox2D;
	mBodyId = b2CreateBody(engine->box2DWorldId(), &bodyDef);

	auto fixtureDef = b2DefaultShapeDef();
	fixtureDef.material.restitution = static_cast<float>(robotModel->parameters()->wheelRestitution());
	fixtureDef.material.friction = static_cast<float>(robotModel->parameters()->wheelFriction());
	fixtureDef.density = static_cast<float>(engine->computeDensity(
			QPolygonF(QRectF(0, 0, robotModel->parameters()->wheelDiameter() / 2,
						robotModel->parameters()->wheelDiameter()))
			, robotModel->parameters()->wheelMass()));

	const auto &center = b2Vec2{0.5f * mWheelWidthM, 0.5f * mWheelHeightM};
	mPolygon[0] = b2Vec2{0.2f * mWheelWidthM, mWheelHeightM} - center;
	mPolygon[1] = b2Vec2{0.8f * mWheelWidthM, mWheelHeightM} - center;
	mPolygon[2] = b2Vec2{mWheelWidthM, 0.6f * mWheelHeightM} - center;
	mPolygon[3] = b2Vec2{mWheelWidthM, 0.4f * mWheelHeightM} - center;
	mPolygon[4] = b2Vec2{0.8f * mWheelWidthM, 0.0f} - center;
	mPolygon[5] = b2Vec2{0.2f * mWheelWidthM, 0.0f} - center;
	mPolygon[6] = b2Vec2{0.0f, 0.4f * mWheelHeightM} - center;
	mPolygon[7] = b2Vec2{0.0f, 0.6f * mWheelHeightM} - center;

	const auto &hull = b2ComputeHull(mPolygon, 8);
	const auto &polygon = b2MakePolygon(&hull, 0.0f);
	const auto &polygonShapeId = b2CreatePolygonShape(mBodyId, &fixtureDef, &polygon);
	b2Body_SetUserData(mBodyId, this);

	const auto &finalPolygon = b2Shape_GetPolygon(polygonShapeId);
	for (int i = 0; i < finalPolygon.count; ++i) {
		auto position = b2Body_GetPosition(mBodyId);
		mDebuggingDrawPolygon.append(mEngine->positionToScene(finalPolygon.vertices[i] + position));
	}

	if (!mDebuggingDrawPolygon.isEmpty() && !mDebuggingDrawPolygon.isClosed()) {
		mDebuggingDrawPolygon.append(mDebuggingDrawPolygon.first());
	}
}

Box2DWheel::~Box2DWheel() {
	b2DestroyBody(mBodyId);
	mBodyId = b2_nullBodyId;
	delete[] mPolygon;
}

b2BodyId Box2DWheel::getBodyId() {
	return mBodyId;
}

b2Vec2 Box2DWheel::getLateralVelocity() const {
	const auto &currentRightNormal = b2Body_GetWorldVector(mBodyId, {0, 1});
	return b2Dot(currentRightNormal, b2Body_GetLinearVelocity(mBodyId)) * currentRightNormal;
}

b2Vec2 Box2DWheel::getForwardVelocity() const {
	const auto &currentForwardNormal = b2Body_GetWorldVector(mBodyId, {1, 0});
	return b2Dot(currentForwardNormal, b2Body_GetLinearVelocity(mBodyId)) * currentForwardNormal;
}

void Box2DWheel::keepConstantSpeed(float speed) {
	if (qAbs(prevSpeed - speed) > FLT_EPSILON){
		mRobot.applyForceToCenter(
			b2Body_GetWorldVector(mBodyId, b2Vec2{0.1f *
						static_cast<float>(mathUtils::Math::sign(speed)), 0}), true);
		prevSpeed = speed;
	}

	const auto &lateralImpulse = b2Body_GetMass(mBodyId) * -getLateralVelocity();
	b2Body_ApplyLinearImpulseToCenter(mBodyId, lateralImpulse, true);

	auto currentForwardSpeed =
	    b2Dot(b2Body_GetLinearVelocity(mBodyId),
		  b2Body_GetWorldVector(mBodyId, {1, 0}));

	if (mathUtils::Math::eq(currentForwardSpeed, speed)) {
		return;
	}

	auto speedDiff = speed - currentForwardSpeed;

	if (qAbs(speedDiff) < FLT_EPSILON) {
		stop();
		return;
	}

	const auto &forwardNormal = b2Body_GetWorldVector(mBodyId, {1, 0});
	const auto &linearImpulse = speedDiff * b2Body_GetMass(mBodyId) * forwardNormal;

	b2Body_ApplyLinearImpulseToCenter(mBodyId, linearImpulse, true);
}

void Box2DWheel::stop() {
	b2Body_SetLinearVelocity(mBodyId, {0, 0});
	b2Body_SetAngularVelocity(mBodyId, 0);
}
