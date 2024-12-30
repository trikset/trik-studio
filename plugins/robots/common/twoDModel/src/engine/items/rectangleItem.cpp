/* Copyright 2015 CyberTech Labs Ltd.
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

#include "rectangleItem.h"

#include <QtWidgets/QAction>

using namespace twoDModel::items;
using namespace graphicsUtils;

RectangleItem::RectangleItem(const QPointF &begin, const QPointF &end)
{
	setX1(begin.x());
	setY1(begin.y());
	setX2(end.x());
	setY2(end.y());
	setPrivateData();
}

AbstractItem *RectangleItem::clone() const
{
	RectangleItem * const cloned = new RectangleItem({x1(), y1()}, {x2(), y2()});
	AbstractItem::copyTo(cloned);
	return cloned;
}

QAction *RectangleItem::rectangleTool()
{
	QAction * const result = new QAction(loadTextColorIcon(":/icons/2d_rectangle.svg"), tr("Rectangle (R)"), nullptr);
	result->setShortcuts({QKeySequence(Qt::Key_R), QKeySequence(Qt::Key_7)});
	result->setCheckable(true);
	return result;
}

void RectangleItem::setPrivateData()
{
	QPen pen(this->pen());
	pen.setColor(Qt::blue);
	pen.setStyle(Qt::SolidLine);
	setPen(pen);
}

QRectF RectangleItem::calcNecessaryBoundingRect() const
{
	qreal penWidth = pen().widthF();
	return QRectF(qMin(x1(), x2()), qMin(y1(), y2()), qAbs(x2() - x1()),
			qAbs(y2() - y1())).adjusted(-penWidth, -penWidth, penWidth, penWidth);
}

QRectF RectangleItem::boundingRect() const
{
	return RectangleImpl::boundingRect(x1(), y1(), x2(), y2(), (pen().width() + drift) / 2);
}

void RectangleItem::drawItem(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	Q_UNUSED(option)
	Q_UNUSED(widget)
	RectangleImpl::drawRectItem(painter, x1(), y1(), x2(), y2());
}

void RectangleItem::drawExtractionForItem(QPainter *painter)
{
	AbstractItem::drawExtractionForItem(painter);
	painter->setPen(getStrokePen());
	painter->setBrush(Qt::transparent);
	painter->drawRect(RectangleImpl::boundingRect(x1(), y1(), x2(), y2(), pen().width()/2));
	if (!filled()) {
		painter->drawRect(RectangleImpl::boundingRect(x1(), y1(), x2(), y2(), -pen().width()/2));
	}
}

QDomElement RectangleItem::serialize(QDomElement &parent) const
{
	QDomElement rectangleNode = ColorFieldItem::serialize(parent);
	setPenBrushToElement(rectangleNode, "rectangle");
	rectangleNode.setAttribute("begin", QString::number(x1() + scenePos().x())
			 + ":" + QString::number(y1() + scenePos().y()));
	rectangleNode.setAttribute("end", QString::number(x2() + scenePos().x())
			 + ":" + QString::number(y2() + scenePos().y()));
	return rectangleNode;
}

void RectangleItem::deserialize(const QDomElement &element)
{
	AbstractItem::deserialize(element);
	const QString beginStr = element.attribute("begin", "0:0");
	QStringList splittedStr = beginStr.split(":");
	auto x = splittedStr[0].toFloat();
	auto y = splittedStr[1].toFloat();
	const QPointF begin = QPointF(x, y);

	const QString endStr = element.attribute("end", "0:0");
	splittedStr = endStr.split(":");
	x = splittedStr[0].toFloat();
	y = splittedStr[1].toFloat();
	const QPointF end = QPointF(x, y);

	setPos(QPointF());
	setX1(begin.x());
	setY1(begin.y());
	setX2(end.x());
	setY2(end.y());
	readPenBrush(element);
}

QPainterPath RectangleItem::shape() const
{
	QPainterPath result;
	result.setFillRule(Qt::WindingFill);

	if (!filled()) {
		QPainterPathStroker ps;
		ps.setWidth(pen().width());
		result.addRect(RectangleImpl::boundingRect(x1(), y1(), x2(), y2(), 0));
		result = ps.createStroke(result);
	} else {
		result.addRect(RectangleImpl::boundingRect(x1(), y1(), x2(), y2(), pen().width()/2));
	}

	if (isSelected()) {
		result.addPath(resizeArea());
	}

	return result;
}

QPainterPath RectangleItem::resizeArea() const
{
	QPainterPath result;
	result.addRect(QRectF(x1(), y1(), 0, 0).adjusted(-resizeDrift, -resizeDrift, resizeDrift, resizeDrift));
	result.addRect(QRectF(x1(), y2(), 0, 0).adjusted(-resizeDrift, -resizeDrift, resizeDrift, resizeDrift));
	result.addRect(QRectF(x2(), y1(), 0, 0).adjusted(-resizeDrift, -resizeDrift, resizeDrift, resizeDrift));
	result.addRect(QRectF(x2(), y2(), 0, 0).adjusted(-resizeDrift, -resizeDrift, resizeDrift, resizeDrift));
	return result;
}

bool RectangleItem::filled() const
{
	return brush().style() != Qt::NoBrush;
}

void RectangleItem::setFilled(bool filled)
{
	setBrushStyle(filled ? "Solid" : "None");
	update();
}
