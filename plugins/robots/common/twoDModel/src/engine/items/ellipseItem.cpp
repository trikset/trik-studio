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

const int currentDrift = drift / 2;

EllipseItem::EllipseItem(const QPointF &begin, const QPointF &end)
	: mEllipseImpl()
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
	result->setShortcut(QKeySequence(Qt::Key_E));
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
	return QRectF(qMin(x1(), x2()), qMin(y1(), y2()), qAbs(x2() - x1()), qAbs(y2() - y1()));
}

QRectF EllipseItem::boundingRect() const
{
	return mEllipseImpl.boundingRect(x1(), y1(), x2(), y2(), currentDrift);
}

void EllipseItem::drawItem(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	Q_UNUSED(option);
	Q_UNUSED(widget);
	mEllipseImpl.drawEllipseItem(painter, x1(), y1(), x2(), y2());
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
	x = splittedStr[0].toInt();
	y = splittedStr[1].toInt();
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
	result.setFillRule(filled() ? Qt::WindingFill : Qt::OddEvenFill);
	result.addEllipse(mEllipseImpl.boundingRect(x1(), y1(), x2(), y2(), pen().width()/2));
	result.addEllipse(mEllipseImpl.boundingRect(x1(), y1(), x2(), y2(), -pen().width()/2));
	if (isSelected()) {
		QRectF itemBoundingRect = calcNecessaryBoundingRect();
		const qreal x1 = itemBoundingRect.left();
		const qreal x2 = itemBoundingRect.right();
		const qreal y1 = itemBoundingRect.top();
		const qreal y2 = itemBoundingRect.bottom();

		result.addRect(QRectF(x1, y1, resizeDrift, resizeDrift));
		result.addRect(QRectF(x2 - resizeDrift, y2 - resizeDrift, resizeDrift, resizeDrift));
		result.addRect(QRectF(x1, y2 - resizeDrift, resizeDrift, resizeDrift));
		result.addRect(QRectF(x2 - resizeDrift, y1, resizeDrift, resizeDrift));
	}
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
