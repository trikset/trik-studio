/* Copyright 2007-2018 CyberTech Labs Ltd.
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

#include "wallItem.h"

#include <QtWidgets/QAction>
#include <QtWidgets/QGraphicsSceneMouseEvent>

#include <qrkernel/settingsManager.h>
#include <qrutils/mathUtils/geometry.h>
#include <twoDModel/engine/model/constants.h>

using namespace twoDModel::items;
using namespace qReal;
using namespace graphicsUtils;

WallItem::WallItem(const QPointF &begin, const QPointF &end)
	: mImage(":/icons/2d_wall.png")
	, mWallWidth(5)
{
	setX1(begin.x());
	setY1(begin.y());
	setX2(end.x());
	setY2(end.y());
	setFlags(ItemIsSelectable | ItemIsMovable | ItemSendsScenePositionChanges);
	setPrivateData();
	setAcceptDrops(true);
}

WallItem *WallItem::clone() const
{
	WallItem * const cloned = new WallItem({x1(), y1()}, {x2(), y2()});
	AbstractItem::copyTo(cloned);
	connect(this, &AbstractItem::positionChanged, cloned, &WallItem::recalculateBorders);
	connect(this, &AbstractItem::x1Changed, cloned, &WallItem::recalculateBorders);
	connect(this, &AbstractItem::y1Changed, cloned, &WallItem::recalculateBorders);
	connect(this, &AbstractItem::x2Changed, cloned, &WallItem::recalculateBorders);
	connect(this, &AbstractItem::y2Changed, cloned, &WallItem::recalculateBorders);

	cloned->mCellNumbX1 = mCellNumbX1;
	cloned->mCellNumbY1 = mCellNumbY1;
	cloned->mCellNumbX2 = mCellNumbX2;
	cloned->mCellNumbY2 = mCellNumbY2;

	cloned->mPath = mPath;
	return cloned;
}

QAction *WallItem::wallTool()
{
	QAction * const result = new QAction(QIcon(":/icons/2d_wall.png"), tr("Wall (W)"), nullptr);
	result->setShortcut(QKeySequence(Qt::Key_W));
	result->setCheckable(true);
	return result;
}

void WallItem::setPrivateData()
{
	setZValue(ZValue::Wall);
	QPen pen(this->pen());
	pen.setWidth(mWallWidth);
	pen.setStyle(Qt::NoPen);
	setPen(pen);
	QBrush brush(this->brush());
	brush.setStyle(Qt::SolidPattern);
	brush.setTextureImage(mImage);
	setBrush(brush);
}

QPointF WallItem::begin() const
{
	return QPointF(x1(), y1()) + mPos;
}

QPointF WallItem::end() const
{
	return QPointF(x2(), y2()) + mPos;
}

QRectF WallItem::boundingRect() const
{
	return mLineImpl.boundingRect(x1(), y1(), x2(), y2(), pen().width(), mWallWidth);
}

QPainterPath WallItem::shape() const
{
	QPainterPath result;
	result.setFillRule(Qt::WindingFill);
	result.addPath(mLineImpl.shape(mWallWidth, x1(), y1(), x2(), y2()));
	result.addPath(resizeArea());
	return result;
}

QPainterPath WallItem::resizeArea() const
{
	return mLineImpl.fieldForResizeItem(mWallWidth, x1(), y1(), x2(), y2());
}

void WallItem::drawItem(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option)
	Q_UNUSED(widget)
	painter->drawPath(mLineImpl.shape(mWallWidth, x1(), y1(), x2(), y2()));
	recalculateBorders();
}

void WallItem::setPenBrushForExtraction(QPainter *painter, const QStyleOptionGraphicsItem *option)
{
	Q_UNUSED(option)
	QPen pen(mStrokePen);
	if (!isSelected() && isHovered()) {
		pen.setWidthF(2.25);
		pen.setDashPattern({3,3});
		pen.setCapStyle(Qt::FlatCap);
	}
	painter->setPen(pen);
}

void WallItem::drawExtractionForItem(QPainter *painter)
{
	mLineImpl.drawExtractionForItem(painter, x1(), y1(), x2(), y2(), mWallWidth);
	mLineImpl.drawFieldForResizeItem(painter, mWallWidth, x1(), y1(), x2(), y2());
}

qreal WallItem::width() const
{
	return pen().width();
}

QVariant WallItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
	if (change == QGraphicsItem::ItemScenePositionHasChanged) {
		emit positionChanged(value.toPointF());
		return value;
	}

	return AbstractItem::itemChange(change, value);
}

QDomElement WallItem::serialize(QDomElement &parent) const
{
	QDomElement wallNode = AbstractItem::serialize(parent);
	wallNode.setTagName("wall");
	setPenBrushToElement(wallNode, "wall");
	mLineImpl.serialize(wallNode, x1() + mPos.x(), y1() + mPos.y()
			, x2() + mPos.x(), y2() + mPos.y());
	return wallNode;
}

void WallItem::deserialize(const QDomElement &element)
{
	AbstractItem::deserialize(element);
	const QPair<QPointF, QPointF> points = mLineImpl.deserialize(element);
	const QPointF begin = points.first;
	const QPointF end = points.second;

	mPos = QPointF();
	setPos(mPos);
	setX1(begin.x());
	setY1(begin.y());
	setX2(end.x());
	setY2(end.y());

	readPenBrush(element);
	if (pen().width()) {
		mWallWidth = pen().width();
	}

	recalculateBorders();
}

QPainterPath WallItem::path() const
{
	return mPath;
}

void WallItem::recalculateBorders()
{
	QPainterPath wallPath;
	wallPath.moveTo(begin());

	if (mathUtils::Geometry::eq(begin(), end())) {
		wallPath.lineTo(end().x() + 0.1, end().y());
	} else {
		wallPath.lineTo(end());
	}

	QPainterPathStroker stroker;
	stroker.setCapStyle(Qt::FlatCap);
	stroker.setWidth(mWallWidth);
	mPath = stroker.createStroke(wallPath);
}

void WallItem::resizeItem(QGraphicsSceneMouseEvent *event)
{
	if (event->modifiers() & Qt::ShiftModifier && (dragState() == TopLeft || dragState() == BottomRight)) {
		AbstractItem::resizeItem(event);
		reshapeRectWithShift();
	} else {
		if (SettingsManager::value("2dShowGrid").toBool()) {
			resizeWithGrid(event, SettingsManager::value("2dGridCellSize").toInt());
		} else {
			if (dragState() == TopLeft || dragState() == BottomRight) {
				AbstractItem::resizeItem(event);
			} else {
				setFlag(QGraphicsItem::ItemIsMovable, true);
			}
		}
	}
}

void WallItem::reshapeRectWithShift()
{
	const qreal differenceX = qAbs(x2() - x1());
	const qreal differenceY = qAbs(y2() - y1());
	const qreal differenceXY = qAbs(differenceX - differenceY);
	const qreal size = qMax(differenceX, differenceY);
	const int delta = size / 2;
	if (differenceXY > delta) {
		const qreal corner1X = dragState() == TopLeft ? x2() : x1();
		const qreal corner1Y = dragState() == TopLeft ? y2() : y1();
		const qreal corner2X = dragState() == TopLeft ? x1() : x2();
		const qreal corner2Y = dragState() == TopLeft ? y1() : y2();
		const QPair<qreal, qreal> res = mLineImpl.reshapeRectWithShiftForLine(corner1X, corner1Y, corner2X, corner2Y
				, differenceX, differenceY, size);
		if (dragState() == TopLeft) {
			setX1(res.first);
			setY1(res.second);
		} else {
			setX2(res.first);
			setY2(res.second);
		}
	} else {
		const qreal size = qMax(qAbs(x2() - x1()), qAbs(y2() - y1()));
		if (dragState() == TopLeft) {
			setX1(x1() > x2() ? x2() + size : x2() - size);
			setY1(y1() > y2() ? y2() + size : y2() - size);
		} else {
			setX2(x2() > x1() ? x1() + size : x1() - size);
			setY2(y2() > y1() ? y1() + size : y1() - size);
		}
	}
}

void WallItem::resizeWithGrid(QGraphicsSceneMouseEvent *event, int indexGrid)
{
	const qreal x = mapFromScene(event->scenePos()).x();
	const qreal y = mapFromScene(event->scenePos()).y();

	setFlag(QGraphicsItem::ItemIsMovable, dragState() == None);

	if (dragState() == TopLeft) {
		setX1(x);
		setY1(y);
		reshapeBeginWithGrid(indexGrid);
	} else if (dragState() == BottomRight) {
		setX2(x);
		setY2(y);
		reshapeEndWithGrid(indexGrid);
	} else {
		const int coefX = static_cast<int>(pos().x()) / indexGrid;
		const int coefY = static_cast<int>(pos().y()) / indexGrid;
		mPos = QPointF(alignedCoordinate(pos().x(), coefX, indexGrid),
				alignedCoordinate(pos().y(), coefY, indexGrid));
		setPos(mPos);
		update();
	}
}

void WallItem::reshapeEndWithGrid(int indexGrid)
{
	const int coefX = static_cast<int>(x2()) / indexGrid;
	const int coefY = static_cast<int>(y2()) / indexGrid;

	setX2(alignedCoordinate(x2(), coefX, indexGrid));
	setY2(alignedCoordinate(y2(), coefY, indexGrid));

	mCellNumbX2 = x2() / indexGrid;
	mCellNumbY2 = y2() / indexGrid;
}

void WallItem::reshapeBeginWithGrid(int indexGrid)
{
	const int coefX = static_cast<int> (x1()) / indexGrid;
	const int coefY = static_cast<int> (y1()) / indexGrid;
	setX1(alignedCoordinate(x1(), coefX, indexGrid));
	setY1(alignedCoordinate(y1(), coefY, indexGrid));
	mCellNumbX1 = x1() / indexGrid;
	mCellNumbY1 = y1() / indexGrid;
}

void WallItem::alignTheWall(int indexGrid)
{
	countCellNumbCoordinates(indexGrid);
	setBeginCoordinatesWithGrid(indexGrid);
	setEndCoordinatesWithGrid(indexGrid);
}

QPolygonF WallItem::collidingPolygon() const
{
	const QPolygonF polygon = mPath.toFillPolygon();
	// here we have "one point" wall
	if (polygon.isEmpty()) {
		auto offset = QPointF(mWallWidth, mWallWidth);
		return QRectF(begin() - offset, begin() + offset);
	}

	QRectF abcdBoundingRect = polygon.boundingRect();
	QLineF ab(abcdBoundingRect.topLeft(), abcdBoundingRect.topRight());
	QLineF bc(abcdBoundingRect.topRight(), abcdBoundingRect.bottomRight());
	QLineF dc(abcdBoundingRect.bottomLeft(), abcdBoundingRect.bottomRight());
	QLineF ad(abcdBoundingRect.topLeft(), abcdBoundingRect.bottomLeft());

	QList<QPointF> abIntersection = mathUtils::Geometry::intersection(ab, mPath);
	QList<QPointF> bcIntersection = mathUtils::Geometry::intersection(bc, mPath);
	QList<QPointF> dcIntersection = mathUtils::Geometry::intersection(dc, mPath);
	QList<QPointF> adIntersection = mathUtils::Geometry::intersection(ad, mPath);

	Q_ASSERT(abIntersection.length() == 2);
	Q_ASSERT(bcIntersection.length() == 2);
	Q_ASSERT(dcIntersection.length() == 2);
	Q_ASSERT(adIntersection.length() == 2);

	// it is rotated rect
	if (abIntersection.first() == abIntersection.last()
			|| bcIntersection.first() == bcIntersection.last()
			|| dcIntersection.first() == dcIntersection.last()
			|| adIntersection.first() == adIntersection.last()) {
		return QPolygonF() << abIntersection.first() << bcIntersection.first()
				<< dcIntersection.first() << adIntersection.first();
	}

	// else we have the same polygon as abcdBoundingRect
	return abcdBoundingRect;
}

qreal WallItem::mass() const
{
	return 0.0;
}

qreal WallItem::friction() const
{
	return 1.0;
}

SolidItem::BodyType WallItem::bodyType() const
{
	return BodyType::STATIC;
}

void WallItem::countCellNumbCoordinates(int indexGrid)
{
	mCellNumbX1 = x1() / indexGrid;
	mCellNumbY1 = y1() / indexGrid;

	if (qAbs(y2() - y1()) > qAbs(x2() - x1())) {
		mCellNumbX2 = mCellNumbX1;
		mCellNumbY2 = y2() / indexGrid;
	} else {
		mCellNumbX2 = x2() / indexGrid;
		mCellNumbY2 = mCellNumbY1;
	}
}

void WallItem::setBeginCoordinatesWithGrid(int indexGrid)
{
	setX1(mCellNumbX1 * indexGrid);
	setY1(mCellNumbY1 * indexGrid);
}

void WallItem::setEndCoordinatesWithGrid(int indexGrid)
{
	setX2(mCellNumbX2 * indexGrid);
	setY2(mCellNumbY2 * indexGrid);
}

void WallItem::setDraggedEnd(qreal x, qreal y)
{
	setX2(x1() - x);
	setY2(y1() - y);
}

qreal WallItem::alignedCoordinate(qreal coord, int coef, const int indexGrid) const
{
	const int coefSign = coef ? coef / qAbs(coef) : 0;

	if (qAbs(qAbs(coord) - qAbs(coef) * indexGrid) <= indexGrid / 2) {
		return coef * indexGrid;
	} else if (qAbs(qAbs(coord) - (qAbs(coef) + 1) * indexGrid) <= indexGrid / 2) {
		return (coef + coefSign) * indexGrid;
	}

	return coord;
}
