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

#pragma once

#include <QDomElement>
#include <QtGui/QPolygonF>
#include <QtCore/qglobal.h>
#include "details/itemProperty.h"

namespace twoDModel {
namespace items {

/// Provides information for physics such as friction, mass, form, etc.
class SolidItem
{
	Q_GADGET
	Q_DISABLE_COPY(SolidItem)
	Q_PROPERTY(qreal mass READ mass)
	Q_PROPERTY(qreal friction READ friction)
	Q_PROPERTY(qreal restitution READ restitution)
	Q_PROPERTY(qreal linearDamping READ linearDamping)
	Q_PROPERTY(qreal angularDamping READ angularDamping)
public:
	/// static: zero mass, zero velocity, may be manually moved
	/// kinematic: zero mass, non-zero velocity set by user
	/// dynamic: positive mass, non-zero velocity determined by forces
	enum class BodyType
	{
		DYNAMIC,
		STATIC,
		KINEMATIC
	};

	SolidItem() = default;

	virtual ~SolidItem() = default;

	/// Returns body form as polygon.
	virtual QPolygonF collidingPolygon() const = 0;

	/// Returns true if body form is circle, in such case, radius is a half of collidingPolygon() bounding rect size
	virtual bool isCircle() const;

	void serialize(QDomElement &element) const;

	void deserialize(const QDomElement &element);

	/// Returns body's mass in kg.
	qreal mass() const { return mMass; }

	/// Returns body's friction.
	qreal friction() const { return mFriction; }

	/// Returns body's restitution.
	qreal restitution() const { return mRestitution; }

	/// Returns body's type.
	virtual BodyType bodyType() const = 0;

	/// Returns body's angular damping.
	qreal angularDamping() const { return mAngularDamping; }

	/// Returns body's linear damping.
	qreal linearDamping() const {return mLinearDamping; }

protected:
	ItemProperty<qreal> mMass {"mass", 0.0f};
	ItemProperty<qreal> mFriction {"friction", 0.0f};
	ItemProperty<qreal> mRestitution {"restitution", 0.0f};
	ItemProperty<qreal> mAngularDamping {"angularDamping", 0.0f};
	ItemProperty<qreal> mLinearDamping {"linearDamping", 0.0f};
};

}
}
