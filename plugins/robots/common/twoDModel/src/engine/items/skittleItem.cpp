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
#include <QtWidgets/QAction>
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
	: mSvgRenderer(new QSvgRenderer)
	, mDiameterPx(skittleDiameter)
	, mMass(skittleMass)
	, mFriction(skittleFriction)
	, mRestitution(skittleRestituion)
	, mAngularDamping(skittleAngularDamping)
	, mLinearDamping(skittleLinearDamping)
{
	setCoordinateSystem(metricSystem);
	mSvgRenderer->load(QString(":/icons/2d_can.svg"));
	setPos(position);
	setZValue(ZValue::Moveable);
	setTransformOriginPoint(boundingRect().center());
}

SkittleItem::~SkittleItem()
{
	delete mSvgRenderer;
}

QAction *SkittleItem::skittleTool()
{
	QAction * const result = new QAction(QIcon(":/icons/2d_can.svg"), tr("Can (C)"), nullptr);
	result->setShortcuts({QKeySequence(Qt::Key_C), QKeySequence(Qt::Key_3)});
	result->setCheckable(true);
	return result;
}

QRectF SkittleItem::boundingRect() const
{
	return QRectF({ -mDiameterPx / 2, -mDiameterPx / 2 }
			, QSizeF{mDiameterPx, mDiameterPx});
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
	skittleNode.setTagName("skittle");
	auto *coordSystem = coordinateSystem();
	skittleNode.setAttribute("x",
	                         QString::number(coordSystem->toUnit(x1() + scenePos().x())));
	skittleNode.setAttribute("y",
	                         QString::number(coordSystem->toUnit(y1() + scenePos().y())));
	skittleNode.setAttribute("markerX",
	                         QString::number(coordSystem->toUnit(x1() + mStartPosition.x())));
	skittleNode.setAttribute("markerY",
	                         QString::number(coordSystem->toUnit(y1() + mStartPosition.y())));
	skittleNode.setAttribute("rotation", QString::number(rotation()));
	skittleNode.setAttribute("startRotation", QString::number(mStartRotation));
	SolidItem::serialize(skittleNode);
	if (propertyChanged(mDiameterPx, skittleDiameter)) {
		skittleNode.setAttribute("diameter", QString::number(coordSystem->toUnit(mDiameterPx)));
	}
	return skittleNode;
}

void SkittleItem::deserialize(const QDomElement &element)
{
	AbstractItem::deserialize(element);
	auto *coordSystem = coordinateSystem();
	qreal x = coordSystem->toPx(element.attribute("x", "0").toDouble());
	qreal y = coordSystem->toPx(element.attribute("y", "0").toDouble());
	qreal markerX = coordSystem->toPx(element.attribute("markerX", "0").toDouble());
	qreal markerY = coordSystem->toPx(element.attribute("markerY", "0").toDouble());
	qreal rotation = element.attribute("rotation", "0").toDouble();
	mStartRotation = element.attribute("startRotation", "0").toDouble();

	if (element.hasAttribute("diameter")) {
		setDiameter(coordSystem->toPx(
				element.attribute("diameter").toDouble()));
	}
	if (element.hasAttribute("mass")) {
		mMass = element.attribute("mass").toDouble();
	}
	if (element.hasAttribute("friction")) {
		mFriction = element.attribute("friction").toDouble();
	}
	if (element.hasAttribute("angularDamping")) {
		mAngularDamping = element.attribute("angularDamping").toDouble();
	}
	if (element.hasAttribute("linearDamping")) {
		mLinearDamping = element.attribute("linearDamping").toDouble();
	}
	setPos(QPointF(x, y));
	setTransformOriginPoint(boundingRect().center());
	mStartPosition = {markerX, markerY};
	setRotation(rotation);
	emit x1Changed(x1());
}

void SkittleItem::saveStartPosition()
{
	if (this->editable()) {
		mStartPosition = pos();
		mStartRotation = rotation();
		emit x1Changed(x1());
	}
}

void SkittleItem::returnToStartPosition()
{
	setPos(mStartPosition);
	setRotation(mStartRotation);
	emit x1Changed(x1());
}

QPolygonF SkittleItem::collidingPolygon() const
{
	return QPolygonF(boundingRect().adjusted(1, 1, -1, -1).translated(scenePos()));
}

qreal SkittleItem::angularDamping(bool getDefault) const
{
	return getDefault ? skittleAngularDamping : mAngularDamping;
}

qreal SkittleItem::linearDamping(bool getDefault) const
{
	return getDefault ? skittleLinearDamping : mLinearDamping;
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

qreal SkittleItem::mass(bool getDefault) const
{
	return getDefault ? skittleMass : mMass;
}

qreal SkittleItem::friction(bool getDefault) const
{
	return getDefault ? skittleFriction : mFriction;
}

qreal SkittleItem::restitution(bool getDefault) const
{
	return getDefault ? skittleRestituion : mRestitution;
}

void SkittleItem::setDiameter(const qreal diameter)
{
	prepareGeometryChange();
	mDiameterPx = diameter;
}

SolidItem::BodyType SkittleItem::bodyType() const
{
	return SolidItem::DYNAMIC;
}
