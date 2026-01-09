/* Copyright 2017-2018 CyberTech Labs Ltd.
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

#include "skittleItem.h"

#include <QtGui/QIcon>
#include <QtWidgets/QAction> //clazy:exclude=qt6-header-fixes
#include <QtSvg/QSvgRenderer>
#include <twoDModel/engine/model/constants.h>

using namespace twoDModel::items;

namespace {
	constexpr int skittleDiameter = 20;
	constexpr qreal skittleMass = 0.05f;
	constexpr qreal skittleFriction = 0.2f;
	constexpr qreal skittleRestituion = 0.8f;
	constexpr qreal skittleAngularDamping = 6.0f;
	constexpr qreal skittleLinearDamping = 6.0f;
}

SkittleItem::SkittleItem(graphicsUtils::AbstractCoordinateSystem *metricSystem,
			QPointF position)
	: mDiameterPx("diameter", skittleDiameter)
	, mSvgRenderer(std::make_unique<QSvgRenderer>())
{
	mMass.setValue(skittleMass);
	mFriction.setValue(skittleFriction);
	mRestitution.setValue(skittleRestituion);
	mAngularDamping.setValue(skittleAngularDamping);
	mLinearDamping.setValue(skittleLinearDamping);
	setCoordinateSystem(metricSystem);
	mSvgRenderer->load(QString(":/icons/2d_can.svg"));
	setPos(position);
	setZValue(ZValue::Moveable);
	setTransformOriginPoint(boundingRect().center());
}

SkittleItem::~SkittleItem() = default;

QAction *SkittleItem::skittleTool()
{
	auto * const result = new QAction(QIcon(":/icons/2d_can.svg"), tr("Can (C)"), nullptr);
	result->setShortcuts({QKeySequence(Qt::Key_C), QKeySequence(Qt::Key_3)});
	result->setCheckable(true);
	return result;
}

QRectF SkittleItem::boundingRect() const
{
	return {{-mDiameterPx / 2, -mDiameterPx / 2} , QSizeF{mDiameterPx, mDiameterPx}};
}

QPainterPath SkittleItem::shape() const
{
	QPainterPath result;
	result.addEllipse(boundingRect());
	return result;
}

void SkittleItem::drawItem(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option)
	Q_UNUSED(widget)
	mSvgRenderer->render(painter, boundingRect());
}

void SkittleItem::setPenBrushForExtraction(QPainter *painter, const QStyleOptionGraphicsItem *option)
{
	Q_UNUSED(option)
	painter->setPen(getStrokePen());
	if (isSelected()) {
		QColor extraColor = getStrokePen().color();
		extraColor.setAlphaF(0.5);
		painter->setBrush(extraColor);
	}
}

void SkittleItem::drawExtractionForItem(QPainter *painter)
{
	painter->drawEllipse(boundingRect());
}

void SkittleItem::savePos()
{
	saveStartPosition();
	AbstractItem::savePos();
}

QDomElement SkittleItem::serialize(QDomElement &element) const
{
	QDomElement skittleNode = AbstractItem::serialize(element);
	Serializer<SkittleItem>::serialize(skittleNode);
	SolidItem::serialize(skittleNode);
	skittleNode.setTagName("skittle");

	auto &&coordSystem = coordinateSystem();
	if (mDiameterPx.wasChanged()) {
		skittleNode.setAttribute("diameter", QString::number(coordSystem->toUnit(mDiameterPx)));
	}
	return skittleNode;
}

void SkittleItem::deserialize(const QDomElement &element)
{
	AbstractItem::deserialize(element);
	SolidItem::deserialize(element);

	auto *coordSystem = coordinateSystem();
	if (element.hasAttribute("diameter")) {
		setDiameter(coordSystem->toPx(
				element.attribute("diameter").toDouble()));
	}

	Serializer<SkittleItem>::deserialize(element);
	Q_EMIT x1Changed(x1());
}

void SkittleItem::setStartPosition(QPointF startPosition)
{
	mStartPosition = startPosition;
}

void SkittleItem::setStartRotation(qreal startRotation)
{
	mStartRotation = startRotation;
}

qreal SkittleItem::startRotation() const
{
	return mStartRotation;
}

QPointF SkittleItem::startPosition() const
{
	return mStartPosition;
}

void SkittleItem::saveStartPosition()
{
	if (this->editable()) {
		mStartPosition = pos();
		mStartRotation = rotation();
		Q_EMIT x1Changed(x1());
	}
}

void SkittleItem::returnToStartPosition()
{
	setPos(mStartPosition);
	setRotation(mStartRotation);
	Q_EMIT x1Changed(x1());
}

QPolygonF SkittleItem::collidingPolygon() const
{
	return boundingRect().adjusted(1, 1, -1, -1).translated(scenePos());
}

QPainterPath SkittleItem::path() const
{
	QPainterPath path;
	QPolygonF collidingPlgn = collidingPolygon();
	QMatrix m;
	m.rotate(rotation());

	const QPointF firstP = collidingPlgn.at(0);
	collidingPlgn.translate(-firstP.x(), -firstP.y());

	path.addEllipse(collidingPlgn.boundingRect());
	path = m.map(path);
	path.translate(firstP.x(), firstP.y());

	return path;
}

bool SkittleItem::isCircle() const
{
	return true;
}

void SkittleItem::setDiameter(const qreal diameter)
{
	prepareGeometryChange();
	mDiameterPx.changeValue(diameter);
}

SolidItem::BodyType SkittleItem::bodyType() const
{
	return SolidItem::BodyType::DYNAMIC;
}
