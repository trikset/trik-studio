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

#include "ellipseItem.h"

#include <QtWidgets/QAction>

using namespace twoDModel::items;
using namespace graphicsUtils;

EllipseItem::EllipseItem(const QPointF &begin, const QPointF &end)
{
	setX1(begin.x());
	setY1(begin.y());
	setX2(end.x());
	setY2(end.y());
	setPrivateData();
}

AbstractItem *EllipseItem::clone() const
{
	EllipseItem * const cloned = new EllipseItem({x1(), y1()}, {x2(), y2()});
	AbstractItem::copyTo(cloned);
	return cloned;
}

QAction *EllipseItem::ellipseTool()
{
	QAction * const result = new QAction(QIcon(":/icons/2d_ellipse.png"), tr("Ellipse (E)"), nullptr);
	result->setShortcuts({QKeySequence(Qt::Key_E), QKeySequence(Qt::Key_8)});
	result->setCheckable(true);
	return result;
}

void EllipseItem::setPrivateData()
{
	QPen pen(this->pen());
	pen.setColor(Qt::blue);
	pen.setStyle(Qt::SolidLine);
	setPen(pen);
}

QRectF EllipseItem::calcNecessaryBoundingRect() const
{
	qreal penWidth = pen().widthF();
	return QRectF(qMin(x1(), x2()), qMin(y1(), y2()), qAbs(x2() - x1()),
			qAbs(y2() - y1())).adjusted(-penWidth, -penWidth, penWidth, penWidth);
}

QRectF EllipseItem::boundingRect() const
{
	return mEllipseImpl.boundingRect(x1(), y1(), x2(), y2(), (pen().width() + drift) / 2);
}

void EllipseItem::drawItem(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	Q_UNUSED(option)
	Q_UNUSED(widget)
	mEllipseImpl.drawEllipseItem(painter, x1(), y1(), x2(), y2());
}

void EllipseItem::drawExtractionForItem(QPainter *painter)
{
	AbstractItem::drawExtractionForItem(painter);
	painter->setPen(getStrokePen());
	painter->setBrush(Qt::transparent);
	painter->drawEllipse(mEllipseImpl.boundingRect(x1(), y1(), x2(), y2(), pen().width()/2));
	if (!filled()) {
		painter->drawEllipse(mEllipseImpl.boundingRect(x1(), y1(), x2(), y2(), -pen().width()/2));
	}
}

QDomElement EllipseItem::serialize(QDomElement &parent) const
{
	QDomElement ellipseNode = ColorFieldItem::serialize(parent);
	setPenBrushToElement(ellipseNode, "ellipse");
	ellipseNode.setAttribute("begin", QString::number(x1() + scenePos().x())
			 + ":" + QString::number(y1() + scenePos().y()));
	ellipseNode.setAttribute("end", QString::number(x2() + scenePos().x())
			 + ":" + QString::number(y2() + scenePos().y()));
	return ellipseNode;
}

void EllipseItem::deserialize(const QDomElement &element)
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

QPainterPath EllipseItem::shape() const
{
	QPainterPath result;
	result.setFillRule(Qt::WindingFill);

	if (!filled()) {
		QPainterPathStroker ps;
		ps.setWidth(pen().width());
		result.addEllipse(mEllipseImpl.boundingRect(x1(), y1(), x2(), y2(), 0));
		result = ps.createStroke(result);
	} else {
		result.addEllipse(mEllipseImpl.boundingRect(x1(), y1(), x2(), y2(), pen().width()/2));
	}

	if (isSelected()) {
		result.addPath(resizeArea());
	}

	return result;
}

QPainterPath EllipseItem::resizeArea() const
{
	QPainterPath result;
	result.addRect(QRectF(x1(), y1(), 0, 0).adjusted(-resizeDrift, -resizeDrift, resizeDrift, resizeDrift));
	result.addRect(QRectF(x1(), y2(), 0, 0).adjusted(-resizeDrift, -resizeDrift, resizeDrift, resizeDrift));
	result.addRect(QRectF(x2(), y1(), 0, 0).adjusted(-resizeDrift, -resizeDrift, resizeDrift, resizeDrift));
	result.addRect(QRectF(x2(), y2(), 0, 0).adjusted(-resizeDrift, -resizeDrift, resizeDrift, resizeDrift));
	return result;
}

bool EllipseItem::filled() const
{
	return brush().style() != Qt::NoBrush;
}

void EllipseItem::setFilled(bool filled)
{
	setBrushStyle(filled ? "Solid" : "None");
	update();
}
