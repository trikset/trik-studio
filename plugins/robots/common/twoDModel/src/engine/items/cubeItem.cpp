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
	const auto defaultCubeEdgePx = twoDModel::pixelsInCm * 4.0f;
	constexpr qreal cubeMass = 0.1f;
	constexpr qreal cubeFriction = 0.3f;
	constexpr qreal cubeRestituion = 0.8f;
	constexpr qreal cubeAngularDamping = 6.0f;
	constexpr qreal cubeLinearDamping = 6.0f;
}

using namespace twoDModel::items;

CubeItem::CubeItem(graphicsUtils::AbstractCoordinateSystem *metricSystem,
		QPointF position)
	: mSvgRenderer(std::make_unique<QSvgRenderer>())
	, mEdgeSizePx("edgeSize", defaultCubeEdgePx)

{
	mMass.setValue(cubeMass);
	mFriction.setValue(cubeFriction);
	mRestitution.setValue(cubeRestituion);
	mAngularDamping.setValue(cubeAngularDamping);
	mLinearDamping.setValue(cubeLinearDamping);
	setCoordinateSystem(metricSystem);
	mSvgRenderer->load(QString(":/icons/2d_cube.svg"));
	setPos(position);
	setZValue(ZValue::Moveable);
	setX1(-mEdgeSizePx / 2.0f);
	setY1(-mEdgeSizePx / 2.0f);
	setX2(x1() + mEdgeSizePx);
	setY2(y1() + mEdgeSizePx);
	setTransformOriginPoint(boundingRect().center());
	RotateItem::init();
	savePos();
}

CubeItem::~CubeItem() = default;

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
	RotateItem::savePos();
}

void CubeItem::setStartPosition(QPointF startPosition)
{
	mStartPosition = startPosition;
}

void CubeItem::setStartRotation(qreal startRotation)
{
	mStartRotation = startRotation;
}

qreal CubeItem::startRotation() const
{
	return mStartRotation;
}

QPointF CubeItem::startPosition() const
{
	return mStartPosition;
}

QDomElement CubeItem::serialize(QDomElement &element) const
{
	QDomElement cubeNode = AbstractItem::serialize(element);
	Serializer<CubeItem>::serialize(cubeNode);
	SolidItem::serialize(cubeNode);
	cubeNode.setTagName("cube");
	auto &&coordSystem = coordinateSystem();
	if (mEdgeSizePx.wasChanged()) {
		cubeNode.setAttribute("edgeSize", QString::number(coordSystem->toUnit(mEdgeSizePx)));
	}

	return cubeNode;
}

void CubeItem::deserialize(const QDomElement &element)
{
	AbstractItem::deserialize(element);
	SolidItem::deserialize(element);

	auto *coordSystem = coordinateSystem();
	if (element.hasAttribute("edgeSize")) {
		setEdgeSize(coordSystem->toPx(
				    element.attribute("edgeSize").toDouble()));
	}

	Serializer<CubeItem>::deserialize(element);
	// Update rotater position
	RotateItem::init();
	savePos();
	Q_EMIT x1Changed(x1());
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
	return boundingRect().adjusted(1, 1, -1, -1).translated(scenePos());
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

void CubeItem::setEdgeSize(const qreal edge)
{
	prepareGeometryChange();
	mEdgeSizePx.changeValue(edge);
	setX1(-mEdgeSizePx / 2.0f);
	setY1(-mEdgeSizePx / 2.0f);
	setX2(x1() + mEdgeSizePx);
	setY2(y1() + mEdgeSizePx);
}

SolidItem::BodyType CubeItem::bodyType() const
{
	return SolidItem::BodyType::DYNAMIC;
}
