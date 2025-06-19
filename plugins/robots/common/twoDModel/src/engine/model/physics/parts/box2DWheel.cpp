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
#include "box2DRobot.h"

using namespace twoDModel::model::physics::parts;

Box2DWheel::Box2DWheel(Box2DPhysicsEngine *engine
		, const b2Vec2 &positionBox2D, const b2Rot &rotationBox2D, Box2DRobot &robot)
	: mRobot(robot)
	, mEngine(engine)
	, mWheelHeightM(engine->pxToM(twoDModel::robotWheelDiameterInPx / 2))
	, mWheelWidthM(engine->pxToM(twoDModel::robotWheelDiameterInPx))
	, mPolygon(new b2Vec2[8])
{
	b2BodyDef bodyDef = b2DefaultBodyDef();
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = positionBox2D;
	bodyDef.rotation = rotationBox2D;
	mBodyId = b2CreateBody(engine->box2DWorldId(), &bodyDef);

	b2ShapeDef fixtureDef = b2DefaultShapeDef();
	fixtureDef.material.restitution = 0.5;
	fixtureDef.material.friction = mWheelFriction;
	fixtureDef.density = engine->computeDensity(
			QPolygonF(QRectF(0, 0, twoDModel::robotWheelDiameterInPx / 2, twoDModel::robotWheelDiameterInPx))
			, mWheelMass);

	b2Vec2 center = b2Vec2{0.5f * mWheelWidthM, 0.5f * mWheelHeightM};
	mPolygon[0] = b2Vec2{0.2f * mWheelWidthM, mWheelHeightM} - center;
	mPolygon[1] = b2Vec2{0.8f * mWheelWidthM, mWheelHeightM} - center;
	mPolygon[2] = b2Vec2{mWheelWidthM, 0.6f * mWheelHeightM} - center;
	mPolygon[3] = b2Vec2{mWheelWidthM, 0.4f * mWheelHeightM} - center;
	mPolygon[4] = b2Vec2{0.8f * mWheelWidthM, 0.0f} - center;
	mPolygon[5] = b2Vec2{0.2f * mWheelWidthM, 0.0f} - center;
	mPolygon[6] = b2Vec2{0.0f, 0.4f * mWheelHeightM} - center;
	mPolygon[7] = b2Vec2{0.0f, 0.6f * mWheelHeightM} - center;

	b2Hull hull = b2ComputeHull(mPolygon, 8);
	b2Polygon polygon = b2MakePolygon(&hull, 0.0f);
	b2ShapeId polygonShapeId = b2CreatePolygonShape(mBodyId, &fixtureDef, &polygon);
	b2Body_SetUserData(mBodyId, this);

	auto finalPolygon = b2Shape_GetPolygon(polygonShapeId);
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
	b2Vec2 currentRightNormal = b2Body_GetWorldVector(mBodyId, {0, 1});
	return b2Dot(currentRightNormal, b2Body_GetLinearVelocity(mBodyId)) * currentRightNormal;
}

b2Vec2 Box2DWheel::getForwardVelocity() const {
	b2Vec2 currentForwardNormal = b2Body_GetWorldVector(mBodyId, {1, 0});
	return b2Dot(currentForwardNormal, b2Body_GetLinearVelocity(mBodyId)) * currentForwardNormal;
}

void Box2DWheel::keepConstantSpeed(float speed) {
	const int acceleration = 1;//20;
	if (qAbs(prevSpeed - speed) > FLT_EPSILON){
		mRobot.applyForceToCenter(
			b2Body_GetWorldVector(mBodyId, b2Vec2{0.1f * mathUtils::Math::sign(speed), 0}), true);
		prevSpeed = speed;
	}

	// clears lateral velocity
	b2Vec2 lateralImpulse = b2Body_GetMass(mBodyId) * -getLateralVelocity();
	auto center = b2Body_GetWorldCenterOfMass(mBodyId);
	b2Body_ApplyLinearImpulse(mBodyId, lateralImpulse, center, true);

	b2Vec2 forwardVelocity = getForwardVelocity();
	float scalar = b2Dot(forwardVelocity,
		b2Body_GetWorldVector(mBodyId, {1, 0})) < 0 ? -1 : 1;

	float currentForwardSpeed = b2Length(forwardVelocity) * scalar;

	if (mathUtils::Math::eq(currentForwardSpeed, speed)) {
		return;
	}

	float speedDelta = qAbs(speed) / acceleration * (currentForwardSpeed < speed ? 1 : -1);
	float desiredSpeed = currentForwardSpeed + speedDelta;

	float speedDiff = desiredSpeed - currentForwardSpeed;
	b2Vec2 forwardNormal = b2Body_GetWorldVector(mBodyId, {1, 0});
	b2Vec2 linearImpulse = speedDiff * b2Body_GetMass(mBodyId) * forwardNormal;

	//break stop
	if (qAbs(speedDiff) < FLT_EPSILON) {
		stop();
		return;
	}

	center = b2Body_GetWorldCenterOfMass(mBodyId);
	b2Body_ApplyLinearImpulse(mBodyId, linearImpulse, center, true);
}


void Box2DWheel::stop() {
	b2Body_SetLinearVelocity(mBodyId, {0, 0});
	b2Body_SetAngularVelocity(mBodyId, 0);
}
