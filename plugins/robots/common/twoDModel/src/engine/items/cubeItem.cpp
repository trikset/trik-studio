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

#include "cubeItem.h"

#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtSvg/QSvgRenderer>
#include <qrutils/graphicsUtils/rectangleImpl.h>
#include <twoDModel/engine/model/constants.h>

namespace {
	const auto cubeSize = twoDModel::pixelsInCm * 4.0f;
}

using namespace twoDModel::items;

CubeItem::CubeItem(graphicsUtils::AbstractCoordinateSystem *metricSystem,
		QPointF position)
	: mSvgRenderer(new QSvgRenderer)
{
	setCoordinateSystem(metricSystem);
	mSvgRenderer->load(QString(":/icons/2d_cube.svg"));
	setPos(position);
	setZValue(ZValue::Moveable);
	setX2(x1() + cubeSize);
	setY2(y1() + cubeSize);
	setTransformOriginPoint(boundingRect().center());
	RotateItem::init();
	savePos();
}

CubeItem::~CubeItem()
{
	delete mSvgRenderer;
}

QAction *CubeItem::cubeTool()
{
	const auto &result = new QAction(QIcon(":/icons/2d_cube.svg"), tr("Cube (X)"), nullptr);
	result->setShortcuts({QKeySequence(Qt::Key_X), QKeySequence(Qt::Key_4)});
	result->setCheckable(true);
	return result;
}

QRectF CubeItem::boundingRect() const
{
	return graphicsUtils::RectangleImpl::boundingRect(x1(), y1(), x2(), y2(), 0);
}

void CubeItem::drawItem(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option)
	Q_UNUSED(widget)
	mSvgRenderer->render(painter,
		graphicsUtils::RectangleImpl::calcRect(x1(), y1(), x2(), y2()));
}

void CubeItem::setPenBrushForExtraction(QPainter *painter, const QStyleOptionGraphicsItem *option)
{
	Q_UNUSED(option)
	painter->setPen(getStrokePen());
	if (isSelected()) {
		QColor extraColor = getStrokePen().color();
		extraColor.setAlphaF(0.5);
		painter->setBrush(extraColor);
	}
}

void CubeItem::drawExtractionForItem(QPainter *painter)
{
	painter->drawRect(graphicsUtils::RectangleImpl::calcRect(x1(), y1(), x2(), y2()));
}

void CubeItem::savePos()
{
	saveStartPosition();
	AbstractItem::savePos();
}

QDomElement CubeItem::serialize(QDomElement &element) const
{
	QDomElement cubeNode = AbstractItem::serialize(element);
	const auto &coordSystem = coordinateSystem();
	cubeNode.setTagName("cube");
	cubeNode.setAttribute("x",
			      QString::number(coordSystem->toUnit(x1() + scenePos().x())));
	cubeNode.setAttribute("y",
			      QString::number(coordSystem->toUnit(y1() + scenePos().y())));
	cubeNode.setAttribute("markerX",
			      QString::number(coordSystem->toUnit(x1() + mStartPosition.x())));
	cubeNode.setAttribute("markerY",
			      QString::number(coordSystem->toUnit(y1() + mStartPosition.y())));
	cubeNode.setAttribute("rotation", QString::number(rotation()));
	cubeNode.setAttribute("startRotation", QString::number(mStartRotation));
	return cubeNode;
}

void CubeItem::deserialize(const QDomElement &element)
{
	AbstractItem::deserialize(element);
	const auto &coordSystem = coordinateSystem();
	const auto x = coordSystem->toPx(element.attribute("x", "0").toDouble());
	const auto y = coordSystem->toPx(element.attribute("y", "0").toDouble());
	const auto markerX = coordSystem->toPx(element.attribute("markerX", "0").toDouble());
	const auto markerY = coordSystem->toPx(element.attribute("markerY", "0").toDouble());
	const auto rotation = element.attribute("rotation", "0").toDouble();
	mStartRotation = element.attribute("startRotation", "0").toDouble();

	setPos(QPointF(x, y));
	setTransformOriginPoint(boundingRect().center());
	mStartPosition = {markerX, markerY};
	setRotation(rotation);
	emit x1Changed(x1());
}

QPainterPath CubeItem::shape() const
{
	QPainterPath result;
	result.addRect(boundingRect());
	return result;
}

void CubeItem::saveStartPosition()
{
	if (this->editable()) {
		mStartPosition = pos();
		mStartRotation = rotation();
		Q_EMIT x1Changed(x1());
	}
}

void CubeItem::returnToStartPosition()
{
	setPos(mStartPosition);
	setRotation(mStartRotation);
	Q_EMIT x1Changed(x1());
}

QPolygonF CubeItem::collidingPolygon() const
{
	return QPolygonF(boundingRect().adjusted(1, 1, -1, -1).translated(scenePos()));
}

qreal CubeItem::angularDamping() const
{
	return 6.0f;
}

qreal CubeItem::linearDamping() const
{
	return 6.0f;
}

QPainterPath CubeItem::path() const
{
	QPainterPath path;
	path.addRect(boundingRect());
	return sceneTransform().map(path);
}

bool CubeItem::isCircle() const
{
	return false;
}

qreal CubeItem::mass() const
{
	return 0.100f;
}

qreal CubeItem::friction() const
{
	return 0.3f;
}

SolidItem::BodyType CubeItem::bodyType() const
{
	return SolidItem::DYNAMIC;
}
