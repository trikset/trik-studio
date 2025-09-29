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
		const auto itemAngularDamping = angularDamping();
		if (propertyChanged(itemAngularDamping, angularDamping(true))) {
			element.setAttribute("angularDamping", QString::number(itemAngularDamping));
		}
		const auto itemLinearDamping = linearDamping();
		if (propertyChanged(itemLinearDamping, linearDamping(true))) {
			element.setAttribute("linearDamping", QString::number(itemLinearDamping));
		}
		const auto itemMass = mass();
		if (propertyChanged(itemMass, mass(true))) {
			element.setAttribute("mass", QString::number(itemMass));
		}
	}
	const auto itemFriction = friction();
	if (propertyChanged(itemFriction, friction(true))) {
		element.setAttribute("friction", QString::number(itemFriction));
	}
	const auto itemRestitution = restitution();
	if (propertyChanged(itemRestitution, restitution(true))) {
		element.setAttribute("restitution", QString::number(itemRestitution));
	}
}

bool SolidItem::isCircle() const
{
	return false;
}

qreal SolidItem::angularDamping(bool getDefault) const
{
	Q_UNUSED(getDefault)
	return 0.0;
}

qreal SolidItem::linearDamping(bool getDefault) const
{
	Q_UNUSED(getDefault)
	return 0.0;
}
