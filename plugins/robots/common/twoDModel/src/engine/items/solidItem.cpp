/* Copyright 2015 Dmitry Mordvinov
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

#include "solidItem.h"

using namespace twoDModel::items;

void SolidItem::serialize(QDomElement &element) const
{
	if (bodyType() == BodyType::DYNAMIC) {
		if (mAngularDamping.wasChanged()) {
			element.setAttribute(mAngularDamping.name(), QString::number(mAngularDamping));
		}
		if (mLinearDamping.wasChanged()) {
			element.setAttribute(mLinearDamping.name(), QString::number(mLinearDamping));
		}
		if (mMass.wasChanged()) {
			element.setAttribute(mMass.name(), QString::number(mMass));
		}
	}
	if (mFriction.wasChanged()) {
		element.setAttribute(mFriction.name(), QString::number(mFriction));
	}
	if (mRestitution.wasChanged()) {
		element.setAttribute(mRestitution.name(), QString::number(mRestitution));
	}
}

void SolidItem::deserialize(const QDomElement &element)
{
	if (element.hasAttribute("mass")) {
		mMass.changeValue(element.attribute("mass").toDouble());
	}
	if (element.hasAttribute("friction")) {
		mFriction.changeValue(element.attribute("friction").toDouble());
	}
	if (element.hasAttribute("restitution")) {
		mRestitution.changeValue(element.attribute("restitution").toDouble());
	}
	if (element.hasAttribute("angularDamping")) {
		mAngularDamping.changeValue(element.attribute("angularDamping").toDouble());
	}
	if (element.hasAttribute("linearDamping")) {
		mLinearDamping.changeValue(element.attribute("linearDamping").toDouble());
	}
}


bool SolidItem::isCircle() const
{
	return false;
}
