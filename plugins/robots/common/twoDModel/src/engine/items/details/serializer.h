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

		if (element.hasAttribute("leftX") && element.hasAttribute("leftY")) {
			x = coordSystem->toPx(element.attribute("leftX", "0").toDouble());
			y = coordSystem->toPx(element.attribute("leftY", "0").toDouble());
			mPreferLeftTopPoint = true;
		} else {
			x = coordSystem->toPx(element.attribute("x", "0").toDouble());
			y = coordSystem->toPx(element.attribute("y", "0").toDouble());
			mPreferLeftTopPoint = false;
		}

		const auto markerX = coordSystem->toPx(element.attribute("markerX", "0").toDouble());
		const auto markerY = coordSystem->toPx(element.attribute("markerY", "0").toDouble());

		const auto rotation = element.attribute("rotation", "0").toDouble();
		auto &&boundingRect = derived->boundingRect();
		if (mPreferLeftTopPoint) {
			derived->setPos(QPointF{
				x + boundingRect.width() / 2,
				y + boundingRect.height() / 2});
		} else {
			derived->setPos(QPointF{x, y});
		}
		derived->setTransformOriginPoint(boundingRect.center());
		derived->setStartPosition({markerX, markerY});
		derived->setRotation(rotation);
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
			auto &&boundingRectTopLeft= derived->boundingRect().topLeft();
			element.setAttribute("leftX",
					 QString::number(coordSystem->toUnit(
					 derivedScenePosition.x() + boundingRectTopLeft.x())));
			element.setAttribute("leftY",
					 QString::number(coordSystem->toUnit(
					 derivedScenePosition.y() + boundingRectTopLeft.y())));
		}
		element.setAttribute("markerX",
					 QString::number(coordSystem->toUnit(startPosition.x())));
		element.setAttribute("markerY",
					 QString::number(coordSystem->toUnit(startPosition.y())));
		element.setAttribute("rotation", QString::number(derived->rotation()));
		element.setAttribute("startRotation", QString::number(startRotation));
	}

private:
	bool mPreferLeftTopPoint {};
};

}
}
