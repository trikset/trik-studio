/* Copyright 2018 CyberTech Labs Ltd.
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

#include "ballItem.h"

#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtSvg/QSvgRenderer>

#include <twoDModel/engine/model/constants.h>

using namespace twoDModel::items;

namespace {
	constexpr int defaultBallDiameterPx = 30;
	constexpr qreal ballMass = 0.015f;
	constexpr qreal ballFriction = 1.0f;
	constexpr qreal ballRestitution = 0.8f;
	constexpr qreal ballAngularDamping = 0.09f;
	constexpr qreal ballLinearDamping = 0.09f;
}

BallItem::BallItem(graphicsUtils::AbstractCoordinateSystem *metricSystem,
		QPointF position)
	: mSvgRenderer(std::make_unique<QSvgRenderer>())
	, mDiameterPx("diameter", defaultBallDiameterPx)
{
	mMass.setValue(ballMass);
	mFriction.setValue(ballFriction);
	mRestitution.setValue(ballRestitution);
	mAngularDamping.setValue(ballAngularDamping);
	mLinearDamping.setValue(ballLinearDamping);
	setCoordinateSystem(metricSystem);
	mSvgRenderer->load(QString(":/icons/2d_ball.svg"));
	setPos(position);
	setZValue(ZValue::Moveable);
	setTransformOriginPoint(boundingRect().center());
}

BallItem::~BallItem()
{
}

QAction *BallItem::ballTool()
{
	QAction * const result = new QAction(QIcon(":/icons/2d_ball.svg"), tr("Ball (B)"), nullptr);
	result->setShortcuts({QKeySequence(Qt::Key_B), QKeySequence(Qt::Key_4)});
	result->setCheckable(true);
	return result;
}

QRectF BallItem::boundingRect() const
{
	return QRectF({ -mDiameterPx / 2.0, -mDiameterPx / 2.0}
			, QSizeF{mDiameterPx, mDiameterPx});
}

void BallItem::drawItem(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option)
	Q_UNUSED(widget)
	mSvgRenderer->render(painter, boundingRect());
}

void BallItem::setPenBrushForExtraction(QPainter *painter, const QStyleOptionGraphicsItem *option)
{
	Q_UNUSED(option)
	painter->setPen(getStrokePen());
	if (isSelected()) {
		QColor extraColor = getStrokePen().color();
		extraColor.setAlphaF(0.5);
		painter->setBrush(extraColor);
	}
}

void BallItem::drawExtractionForItem(QPainter *painter)
{
	painter->drawEllipse(boundingRect());
}

void BallItem::savePos()
{
	saveStartPosition();
	AbstractItem::savePos();
}

QDomElement BallItem::serialize(QDomElement &element) const
{
	QDomElement ballNode = AbstractItem::serialize(element);
	auto *coordSystem = coordinateSystem();
	ballNode.setTagName("ball");
	ballNode.setAttribute("x",
	                      QString::number(coordSystem->toUnit(x1() + scenePos().x())));
	ballNode.setAttribute("y",
	                      QString::number(coordSystem->toUnit(y1() + scenePos().y())));
	ballNode.setAttribute("markerX",
	                      QString::number(coordSystem->toUnit(x1() + mStartPosition.x())));
	ballNode.setAttribute("markerY",
	                      QString::number(coordSystem->toUnit(y1() + mStartPosition.y())));
	ballNode.setAttribute("rotation", QString::number(rotation()));
	ballNode.setAttribute("startRotation", QString::number(mStartRotation));
	SolidItem::serialize(ballNode);
	if (mDiameterPx.wasChanged()) {
		ballNode.setAttribute("diameter", QString::number(coordSystem->toUnit(mDiameterPx)));
	}
	return ballNode;
}

void BallItem::deserialize(const QDomElement &element)
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

	SolidItem::deserialize(element);
	setPos(QPointF(x, y));
	setTransformOriginPoint(boundingRect().center());
	mStartPosition = {markerX, markerY};
	setRotation(rotation);
	Q_EMIT x1Changed(x1());
}

QPainterPath BallItem::shape() const
{
	QPainterPath result;
	result.addEllipse(boundingRect());
	return result;
}

void BallItem::saveStartPosition()
{
	if (this->editable()) {
		mStartPosition = pos();
		mStartRotation = rotation();
		Q_EMIT x1Changed(x1());
	}
}

void BallItem::returnToStartPosition()
{
	setPos(mStartPosition);
	setRotation(mStartRotation);
	Q_EMIT x1Changed(x1());
}

QPolygonF BallItem::collidingPolygon() const
{
	return QPolygonF(boundingRect().adjusted(1, 1, -1, -1).translated(scenePos()));
}

QPainterPath BallItem::path() const
{
	QPainterPath path;
	QPolygonF collidingPlgn = collidingPolygon();
	QMatrix m;
	m.rotate(rotation());

	QPointF firstP = collidingPlgn.at(0);
	collidingPlgn.translate(-firstP.x(), -firstP.y());

	path.addEllipse(collidingPlgn.boundingRect());
	path = m.map(path);
	path.translate(firstP.x(), firstP.y());

	return path;
}

bool BallItem::isCircle() const
{
	return true;
}

SolidItem::BodyType BallItem::bodyType() const
{
	return SolidItem::BodyType::DYNAMIC;
}

void BallItem::setDiameter(const qreal diameter)
{
	prepareGeometryChange();
	mDiameterPx.changeValue(diameter);
}
