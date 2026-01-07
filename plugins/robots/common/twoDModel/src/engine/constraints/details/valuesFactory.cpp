/* Copyright 2007-2015 QReal Research Group
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

#include "valuesFactory.h"

#include <QtCore/QRect>
#include <QMetaProperty>
#include <qrutils/mathUtils/geometry.h>
#include <utils/objectsSet.h>
#include <utils/timelineInterface.h>
#include "src/engine/items/solidItem.h"

using namespace twoDModel::constraints::details;

const auto typeOfNull = "undefined";

ValuesFactory::ValuesFactory(Variables &variables, const Objects &objects, StatusReporter &status)
	: mVariables(variables)
	, mObjects(objects)
	, mStatus(status)
{
}

Value ValuesFactory::invalidValue() const
{
	return []() { return QVariant(); };
}

Value ValuesFactory::boolValue(bool value) const
{
	return [value]() { return value; };
}

Value ValuesFactory::intValue(int value) const
{
	return [value]() { return value; };
}

Value ValuesFactory::doubleValue(qreal value) const
{
	return [value]() { return value; };
}

Value ValuesFactory::stringValue(const QString &value) const
{
	return [value]() { return value; };
}

Value ValuesFactory::specialSyntaxValue(const QString &paramName) const
{
	return [this, paramName]() {
		if (paramName.isEmpty()) {
			reportError(QObject::tr("Using special syntax with an empty variable name"));
		}
		// If it's a variable, then it's a variable.
		auto&& variable = variableValue(paramName, false)();
		if (variable.isNull()) {
			// If it's an object property, then it's an object property.
			variable = objectState(paramName, false)();
		}
		// It's neither one thing nor the other.
		if (variable.isNull()) {
			reportError(QObject::tr("The name %1 is not a valid variable "
						"name or property chain for an object").arg(paramName));
		}
		return variable;
	};
}

Value ValuesFactory::variableValue(const QString &name, bool errorOnNotFound) const
{
	return [this, name, errorOnNotFound]() {
		const QStringList parts = name.split('.');
		if (parts.isEmpty()) {
			reportError(QObject::tr("Requesting variable value with empty name"));
			return QVariant();
		}

		if (!mVariables.contains(parts.first())) {
			// We do not mind the situation when trying to read non-declared varible
			// because really can`t manage the order in which Qt will call event checking,
			// so some variables (for example counters) can be checked before setted.
			return QVariant();
		}

		return propertyChain(mVariables[parts.first()], parts.mid(1), parts.first(), errorOnNotFound);
	};
}

Value ValuesFactory::typeOf(const QString &objectId) const
{
	return [this, objectId]() {
		if (!mObjects.contains(objectId)) {
			return typeOfNull;
		}

		QObject const *object = mObjects[objectId];
		return object == nullptr ? typeOfNull : object->metaObject()->className();
	};
}

Value ValuesFactory::objectState(const QString &path, bool errorOnNotFound) const
{
	return [this, path, errorOnNotFound]() {
		const QStringList parts = path.split('.', QString::SkipEmptyParts);
		if (parts.isEmpty()) {
			reportError(QObject::tr("Object path is empty!"));
			return QVariant();
		}

		QString objectId = parts.first();
		if (!mObjects.contains(objectId)) {
			if (errorOnNotFound) {
				reportError(QObject::tr("No such object: %1").arg(objectId));
			}
			return QVariant();
		}

		int lastObjectPart = 1;
		while (lastObjectPart < parts.count() && mObjects.contains(objectId + "." + parts[lastObjectPart])) {
			objectId += "." + parts[lastObjectPart];
			++lastObjectPart;
		}

		return propertyChain(QVariant::fromValue<QObject *>(mObjects[objectId]),
						parts.mid(lastObjectPart), objectId, errorOnNotFound);
	};
}

Value ValuesFactory::timestamp(const utils::TimelineInterface &timeline) const
{
	return [&timeline]() { return timeline.timestamp(); };
}

Value ValuesFactory::unaryMinus(const Value &value) const
{
	return [value]() { return -value().toInt(); };
}

Value ValuesFactory::abs(const Value &value) const
{
	return [value]() { return qAbs(value().toInt()); };
}

Value ValuesFactory::sum(const Value &left, const Value &right) const
{
	return [left, right]() { return left().toInt() + right().toInt(); };
}

Value ValuesFactory::mul(const Value &left, const Value &right) const
{
	return [left, right]() { return left().toInt() * right().toInt(); };
}


Value ValuesFactory::difference(const Value &left, const Value &right) const
{
	return [left, right]() { return left().toInt() - right().toInt(); };
}

Value ValuesFactory::max(const Value &left, const Value &right) const
{
	return [left, right]() { return qMax(left().toInt(), right().toInt()); };
}

Value ValuesFactory::min(const Value &left, const Value &right) const
{
	return [left, right]() { return qMin(left().toInt(), right().toInt()); };
}

Value ValuesFactory::distance(const Value &point1, const Value &point2) const
{
	return [point1, point2]() { return mathUtils::Geometry::distance(point1().toPoint(), point2().toPoint()); };
}

Value ValuesFactory::boundingRect(const Value &items) const
{
	return [this, items]() {
		bool empty = true;
		int xMin = INT_MAX;
		int yMin = INT_MAX;
		int xMax = INT_MIN;
		int yMax = INT_MIN;
		iterate(items(), [this, &xMin, &yMin, &xMax, &yMax, &empty](const QVariant &item) {
			bool hasBoundingRect{};
			const QRect boundingRect = propertyOf(item, "boundingRect", &hasBoundingRect).toRect();
			if (hasBoundingRect) {
				empty = false;
				xMin = qMin(xMin, boundingRect.left());
				yMin = qMin(yMin, boundingRect.top());
				xMax = qMax(xMax, boundingRect.right());
				yMax = qMax(yMax, boundingRect.bottom());
				return;
			}

			bool hasX{};
			bool hasY{};
			const int x = propertyOf(item, "x", &hasX).toInt();
			const int y = propertyOf(item, "y", &hasY).toInt();
			if (hasX && hasY) {
				empty = false;
				xMin = qMin(xMin, x);
				yMin = qMin(yMin, y);
				xMax = qMax(xMax, x);
				yMax = qMax(yMax, y);
			}
		});

		return empty ? QRect() : QRect(QPoint(xMin, yMin), QPoint(xMax, yMax));
	};
}

QVariant ValuesFactory::propertyChain(const QVariant &value
		, const QStringList &propertyChain, const QString &objectAlias, bool errorOnNotFound) const
{
	QVariant currentValue = value;
	QString currentObjectAlias = objectAlias;
	for (const QString &property : propertyChain) {
		currentValue = propertyOf(currentValue, property, currentObjectAlias, errorOnNotFound);
		currentObjectAlias += "." + property;
		if (!currentValue.isValid()) {
			return {};
		}
	}

	return currentValue;
}

QVariant ValuesFactory::propertyOf(const QVariant &value, const QString &property,
						const QString &objectAlias, bool errorOnNotFound) const
{
	bool hasProperty{};
	bool unknownType{};
	QVariant result = propertyOf(value, property, &hasProperty, &unknownType);

	if (unknownType) {
		if (errorOnNotFound) {
			reportError(QObject::tr("Unknown type of object \"%1\"").arg(objectAlias));
		}
		return {};
	}

	if (!hasProperty) {
		if (errorOnNotFound) {
			reportError(QObject::tr(R"(Object "%1" has no property "%2")").arg(objectAlias, property));
		}
		return {};
	}

	return result;
}

QVariant ValuesFactory::propertyOf(const QVariant &value, const QString &property
		, bool *hasProperty, bool *unknownType) const
{
	QVariant result;

	/// This code is here just because Dmitry can. And everyone else is lazy enough.
	hasProperty && (*hasProperty = false);
	unknownType && (*unknownType = false);

	// Here must be enumerated all types whose properties we can obtain.
	if (value.canConvert<QObject *>()) {
		result = propertyOf(value.value<QObject *>(), property, hasProperty);
	} else if (value.canConvert<QPoint>()) {
		result = propertyOf(value.value<QPoint>(), property, hasProperty);
	} else if (value.canConvert<QRect>()) {
		result = propertyOf(value.value<QRect>(), property, hasProperty);
	} else if (value.canConvert<QVariantList>()) {
		result = propertyOf(value.value<QVariantList>(), property, hasProperty);
	} else {
		unknownType && (*unknownType = true);
	}
	if (result.isNull()) {
		QVariant fallback;
		if (auto *solidItem = dynamic_cast<items::SolidItem *>(value.value<QObject *>())) {
			fallback = propertyOf(solidItem, property, hasProperty);
		}
		if (fallback.isValid()) {
			result = fallback;
		}
	}
	return result;
}

QVariant ValuesFactory::propertyOf(const QObject *object, const QString &property, bool *ok) const
{
	ok && (*ok = true);
	if (!object) {
		return {};
	}

	const int index = object->metaObject()->indexOfProperty(qPrintable(property));
	if (index < 0) {
		ok && (*ok = false);
		return {};
	}

	return object->property(qPrintable(property));
}

QVariant ValuesFactory::propertyOf(const items::SolidItem* item, const QString &property, bool *ok) const
{
	ok && (*ok = true);
	if (!item) {
		return {};
	}
	const auto &mo = items::SolidItem::staticMetaObject;
	const auto index = mo.indexOfProperty(qPrintable(property));
	if (index < 0) {
		ok && (*ok = false);
		return {};
	}

	return mo.property(index).readOnGadget(item);
}

QVariant ValuesFactory::propertyOf(QPoint point, const QString &property, bool *ok) const
{
	ok && (*ok = true);
	if (property == "x") {
		return point.x();
	}

	if (property == "y") {
		return point.y();
	}

	ok && (*ok = false);
	return {};
}

QVariant ValuesFactory::propertyOf(QRect rect, const QString &property, bool *ok) const
{
	ok && (*ok = true);
	if (property == "x") {
		return rect.x();
	}

	if (property == "y") {
		return rect.y();
	}

	if (property == "width") {
		return rect.width();
	}

	if (property == "height") {
		return rect.height();
	}

	ok && (*ok = false);
	return {};
}

QVariant ValuesFactory::propertyOf(const QVariantList &list, const QString &property, bool *ok) const
{
	ok && (*ok = true);
	if (property == "first" && !list.isEmpty()) {
		return list.first();
	}

	if (property == "last" && !list.isEmpty()) {
		return list.last();
	}

	if (property == "size") {
		return list.size();
	}

	if (property == "isEmpty") {
		return list.isEmpty();
	}

	// Accessing list element by index
	bool isInt;
	auto index = property.toInt(&isInt);
	if (isInt && index >= 0 && index < list.size()) {
		return list.at(index);
	}

	ok && (*ok = false);
	return {};
}

void ValuesFactory::iterate(const QVariant &collection, const std::function<void (const QVariant &)> &visitor) const
{
	if (collection.canConvert<utils::ObjectsSetBase *>()) {
		// A good iteration, without copying. Object sets are good for large collections.
		collection.value<utils::ObjectsSetBase *>()->iterate(visitor);
	} else if (collection.canConvert<QVariantList>()) {
		// Warning: the whole list will be copied here!
		for (auto &&item : collection.value<QVariantList>()) {
			visitor(item);
		}
	} else {
		// Fallback case. This is not very nice situation is we get here, but it still can work.
		visitor(collection);
	}
}

void ValuesFactory::reportError(const QString &message) const
{
	Q_EMIT mStatus.checkerError(message);
}
