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

#include "twoDModel/engine/model/twoDModelRobotParameters.h"
#include "twoDModel/engine/model/constants.h"
#include <cmath>

using namespace twoDModel::model;

TwoDRobotModelParameters::TwoDRobotModelParameters(
		const twoDModel::robotModel::TwoDRobotModel &twoDRobotModel, QObject *parent):
	QObject(parent),
	mRobotModel(twoDRobotModel),
	mWidth(mRobotModel.size().width()),
	mHeight(mRobotModel.size().height()),
	mMass(mRobotModel.mass()),
	mFriction(mRobotModel.friction()),
	mRestitution(mRobotModel.restitution()),
	mLinearDamping(mRobotModel.linearDamping()),
	mAngularDamping(mRobotModel.angularDamping()),
	mWheelRestitution(mRobotModel.wheelRestitution()),
	mWheelFriction(mRobotModel.wheelFriction()),
	mWheelMass(mRobotModel.wheelMass())
{}

void TwoDRobotModelParameters::reinit() {
	mWidth = mRobotModel.size().width();
	mHeight = mRobotModel.size().height();
	mMass = mRobotModel.mass();
	mFriction = mRobotModel.friction();
	mRestitution = mRobotModel.restitution();
	mLinearDamping = mRobotModel.linearDamping();
	mAngularDamping = mRobotModel.angularDamping();
	mWheelRestitution = mRobotModel.wheelRestitution();
	mWheelFriction = mRobotModel.wheelFriction();
	mWheelMass = mRobotModel.wheelMass();
}

namespace {
static bool valueChanged(const qreal defaultValue, const qreal actualValue) {
	constexpr auto precision = 1e-5;
	return std::abs(defaultValue - actualValue) > precision;
}
}

bool TwoDRobotModelParameters::propertyChanged(const char *propertyName) const {
	const auto &defaultPropertyValue = mRobotModel.property(propertyName);
	const auto &propertyValue = property(propertyName);
	if (propertyValue.canConvert<qreal>()
				&& defaultPropertyValue.canConvert<qreal>()) {
		return valueChanged(defaultPropertyValue.toDouble(), propertyValue.toDouble());
	}
	if (propertyValue.canConvert<QSizeF>()
				&& defaultPropertyValue.canConvert<QSizeF>()) {
		const auto &defaultSize = defaultPropertyValue.toSizeF();
		const auto &size = propertyValue.toSizeF();
		return valueChanged(defaultSize.width(), size.width()) ||
				valueChanged(defaultSize.height(), size.height());
	}
	qFatal("Unknown property or unexpected type for TwoDRobotModelParameters property");
}

QPolygonF TwoDRobotModelParameters::collidingPolygon() const {
	const auto &collPolygon = mRobotModel.collidingPolygon();
	QPolygonF scaledPolygon;

	const auto widthScale = mWidth / mRobotModel.size().width();
	const auto heightScale = mHeight / mRobotModel.size().height();

	scaledPolygon.reserve(collPolygon.size());
	for (auto &&point : collPolygon) {
	    scaledPolygon << QPointF{point.x() * widthScale, point.y() * heightScale};
	}
	return scaledPolygon;
}

void TwoDRobotModelParameters::setMass(const qreal mass) {
	mMass = mass;
}

void TwoDRobotModelParameters::setWheelMass(const qreal mass) {
	mWheelMass = mass;
}

qreal TwoDRobotModelParameters::wheelMass() const {
	return mWheelMass;
}

void TwoDRobotModelParameters::setWheelRestitution(const qreal restitution) {
	mWheelRestitution = restitution;
}

qreal TwoDRobotModelParameters::wheelRestitution() const {
	return mWheelRestitution;
}

void TwoDRobotModelParameters::setWheelFriction(const qreal friction) {
	mWheelFriction = friction;
}

qreal TwoDRobotModelParameters::wheelFriction() const {
	return mWheelFriction;
}

void TwoDRobotModelParameters::setSize(QSizeF size) {
	mWidth = size.width();
	mHeight = size.height();
}

void TwoDRobotModelParameters::setFriction(const qreal friction) {
	mFriction = friction;
}

void TwoDRobotModelParameters::setRestitution(const qreal restitution) {
	mRestitution = restitution;
}

void TwoDRobotModelParameters::setLinearDamping(const qreal linearDamping) {
	mLinearDamping = linearDamping;
}

void TwoDRobotModelParameters::setAngularDamping(const qreal angularDamping) {
	mAngularDamping = angularDamping;
}

qreal TwoDRobotModelParameters::mass() const
{
	return mMass;
}

qreal TwoDRobotModelParameters::friction() const
{
	return mFriction;
}

qreal TwoDRobotModelParameters::restitution() const
{
	return mRestitution;
}

qreal TwoDRobotModelParameters::angularDamping() const
{
	return mAngularDamping;
}

qreal TwoDRobotModelParameters::linearDamping() const
{
	return mLinearDamping;
}

QSizeF TwoDRobotModelParameters::size() const
{
	return QSizeF{mWidth, mHeight};
}

qreal TwoDRobotModelParameters::wheelDiameter() const
{
	return robotWheelDiameterInPx / robotWidth  * mWidth;
}

QPointF TwoDRobotModelParameters::robotCenter() const
{
	return QPointF(mWidth / 2, mHeight / 2);
}

qreal TwoDRobotModelParameters::onePercentAngularVelocity() const
{
	return mRobotModel.onePercentAngularVelocity();
}

QList<QPointF> TwoDRobotModelParameters::wheelsPosition() const
{
	const auto &defaultWheelPosition = mRobotModel.wheelsPosition();
	const auto widthScale = mWidth / mRobotModel.size().width();
	const auto heightScale = mHeight / mRobotModel.size().height();

	QList<QPointF> list;
	list.reserve(defaultWheelPosition.size());
	for (auto &&point : defaultWheelPosition) {
	    list << QPointF{point.x() * widthScale, point.y() * heightScale};
	}
	return list;
}

QPointF TwoDRobotModelParameters::rotationCenter() const
{
	const auto &wheelsPos = wheelsPosition();
	if (wheelsPos.size() < 2) {
		return robotCenter();
	}

	return (wheelsPos[0] + wheelsPos[1]) / 2;
}

qreal TwoDRobotModelParameters::robotTrack() const {
	const auto &wheelsPos = wheelsPosition();
	if (wheelsPos.size() < 2) {
		return mWidth;
	}
	return qAbs(wheelsPos[0].y() - wheelsPos[1].y());
}
