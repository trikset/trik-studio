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

#include "ellipseRegion.h"
#include "src/engine/items/ellipseItem.h"
#include <qrutils/graphicsUtils/rectangleImpl.h>
#include <qrutils/graphicsUtils/abstractItem.h>
#include <QSharedPointer>

using namespace twoDModel::items;

EllipseRegion::EllipseRegion(graphicsUtils::AbstractCoordinateSystem *metricSystem,
			     QGraphicsItem *parent)
	: RegionItem(metricSystem, parent)
{}

EllipseRegion::EllipseRegion(QSharedPointer<graphicsUtils::AbstractItem> item,
		graphicsUtils::AbstractCoordinateSystem *metricSystem,
		QGraphicsItem *parent):
	RegionItem(item, metricSystem, parent)
{}

QString EllipseRegion::regionType() const
{
	return "ellipse";
}

void EllipseRegion::drawItem(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option)
	Q_UNUSED(widget)
	graphicsUtils::RectangleImpl::drawEllipseItem(painter, x1(), y1(), x2(), y2());
}

QRectF EllipseRegion::boundingRect() const
{
	// Drift, for example, to expand the hit-zone when resizing
	// (the expansion squares are located at the boundary points of the boundingRect)
	return graphicsUtils::RectangleImpl::boundingRect(x1(), y1(), x2(), y2(), (pen().width() + drift) / 2);
}

QPainterPath EllipseRegion::shape() const
{
	QPainterPath result;
	result.setFillRule(Qt::WindingFill);
	// For the pen().width() region, it will always be 1 regardless of its parent ellipse.
	// pen().width() / 2 is written if this behavior changes in the future.
	// At the same time, we do not make a difference between filled and not filled
	// parent shapes with QPainterPathStroker, as the region cannot be a path at the moment.
	result.addEllipse(graphicsUtils::RectangleImpl::boundingRect(x1(), y1(), x2(), y2(), pen().width() / 2));
	if (isSelected()) {
		 result.addPath(resizeArea());
	}
	return result;
}

QPainterPath EllipseRegion::shapeWihoutResizeArea() const
{
	QPainterPath result;
	result.addEllipse(graphicsUtils::RectangleImpl::boundingRect(x1(), y1(), x2(), y2(), pen().width() / 2));
	return result;
}

QPainterPath EllipseRegion::resizeArea() const
{
	QPainterPath result;
	result.addRect(QRectF(x1(), y1(), 0, 0).adjusted(-resizeDrift, -resizeDrift, resizeDrift, resizeDrift));
	result.addRect(QRectF(x1(), y2(), 0, 0).adjusted(-resizeDrift, -resizeDrift, resizeDrift, resizeDrift));
	result.addRect(QRectF(x2(), y1(), 0, 0).adjusted(-resizeDrift, -resizeDrift, resizeDrift, resizeDrift));
	result.addRect(QRectF(x2(), y2(), 0, 0).adjusted(-resizeDrift, -resizeDrift, resizeDrift, resizeDrift));
	return result;
}
