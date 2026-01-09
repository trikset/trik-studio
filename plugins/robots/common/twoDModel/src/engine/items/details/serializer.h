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

#pragma once

#include "itemProperty.h"
#include <QDomElement>
#include <QPointF>

namespace twoDModel {
namespace items {

template<typename Derived>
class Serializer
{
	Q_DISABLE_COPY_MOVE(Serializer)
public:
	Serializer() = default;
	~Serializer() = default;
	void deserialize(const QDomElement &element)
	{
		auto &&derived = static_cast<Derived *>(this);
		auto &&coordSystem = derived->coordinateSystem();
		qreal x {};
		qreal y {};

		if (element.hasAttribute("begin")) {
			const auto &point = deserializePoint(element.attribute("begin"));
			x = point.x();
			y = point.y();
			mPreferLeftTopPoint = true;
		} else {
			x = coordSystem->toPx(element.attribute("x", "0").toDouble());
			y = coordSystem->toPx(element.attribute("y", "0").toDouble());
			mPreferLeftTopPoint = false;
		}

		const auto markerX = coordSystem->toPx(element.attribute("markerX", "0").toDouble());
		const auto markerY = coordSystem->toPx(element.attribute("markerY", "0").toDouble());

		const auto rotation = element.attribute("rotation", "0").toDouble();
		const auto startRotation = element.attribute("startRotation", "0").toDouble();
		auto &&boundingRect = derived->boundingRect();
		derived->setTransformOriginPoint(boundingRect.center());
		derived->setRotation(rotation);
		derived->setStartRotation(startRotation);
		if (mPreferLeftTopPoint) {
			const auto currentTopLeft = derived->mapToScene(boundingRect.topLeft());
			const auto offsetX = x - currentTopLeft.x();
			const auto offsetY = y - currentTopLeft.y();
			derived->moveBy(offsetX, offsetY);
		} else {
			derived->setPos(QPointF{x, y});
		}
		derived->setStartPosition({markerX, markerY});
	}

	void serialize(QDomElement &element) const
	{
		auto &&derived = static_cast<const Derived *>(this);
		auto &&coordSystem = derived->coordinateSystem();
		const auto startRotation = derived->startRotation();
		const auto startPosition = derived->startPosition();
		const auto derivedScenePosition = derived->scenePos();
		if (!mPreferLeftTopPoint) {
			element.setAttribute("x",
					 QString::number(coordSystem->toUnit(derivedScenePosition.x())));
			element.setAttribute("y",
					 QString::number(coordSystem->toUnit(derivedScenePosition.y())));
		} else {
			auto &&boundingRectTopLeft = derived->mapToScene(derived->boundingRect().topLeft());
			auto x1InSystem = coordSystem->toUnit(boundingRectTopLeft.x());
			auto y1InSystem = coordSystem->toUnit(boundingRectTopLeft.y());
			element.setAttribute("begin", QString::number(x1InSystem) + ":" + QString::number(y1InSystem));
		}

		element.setAttribute("markerX",
					 QString::number(coordSystem->toUnit(startPosition.x())));
		element.setAttribute("markerY",
					 QString::number(coordSystem->toUnit(startPosition.y())));
		element.setAttribute("rotation", QString::number(derived->rotation()));
		element.setAttribute("startRotation", QString::number(startRotation));
	}

	QPointF deserializePoint(const QString &string) const
	{
		auto &&derived = static_cast<const Derived *>(this);
		auto &&coordSystem = derived->coordinateSystem();
		const auto &splittedStr = string.split(":");
		if (splittedStr.count() == 2) {
			const qreal x = splittedStr[0].toDouble();
			const qreal y = splittedStr[1].toDouble();
			return coordSystem->toPx({x, y});
		}
		return {};
	}

private:
	bool mPreferLeftTopPoint {};
};

}
}
