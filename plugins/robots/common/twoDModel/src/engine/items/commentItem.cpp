/* Copyright 2022 CyberTech Labs Ltd.
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

#include "commentItem.h"

#include <QtGui/QIcon>
#include <QtWidgets/QAction>

#include <qrutils/graphicsUtils/rectangleImpl.h>

#include <QDebug>

using namespace twoDModel::items;
using namespace graphicsUtils;

CommentItem::CommentItem(const QPointF &begin, const QPointF &end)
	: mText(this)
{
	setPrivateData();
	setX1(begin.x());
	setY1(begin.y());
	setX2(end.x());
	setY2(end.y());
}

QAction *CommentItem::commentTool()
{
	QAction * const result = new QAction(QIcon(":/icons/2d_ball.svg"), tr("Comment (M)"), nullptr);
	result->setShortcuts({QKeySequence(Qt::Key_M), QKeySequence(Qt::Key_0)});
	result->setCheckable(true);
	return result;
}

QRectF CommentItem::boundingRect() const
{
	return RectangleImpl::boundingRect(x1(), y1(), x2(), y2(), (pen().width() + drift) / 2);
}

QPainterPath CommentItem::shape() const
{
	QPainterPath result;
	result.setFillRule(Qt::WindingFill);

	QPainterPathStroker ps;
	ps.setWidth(pen().width());
	result.addRect(RectangleImpl::boundingRect(x1(), y1(), x2(), y2(), 0));
	result = ps.createStroke(result);

	if (isSelected()) {
		result.addPath(resizeArea());
	}

	return result;
}

void CommentItem::drawItem(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	Q_UNUSED(option)
	Q_UNUSED(widget)
	RectangleImpl::drawRectItem(painter, x1(), y1(), x2(), y2());
}

void CommentItem::drawExtractionForItem(QPainter* painter)
{
	AbstractItem::drawExtractionForItem(painter);
}

QPainterPath CommentItem::resizeArea() const
{
	QPainterPath result;
	result.addRect(QRectF(x1(), y1(), 0, 0).adjusted(-resizeDrift, -resizeDrift, resizeDrift, resizeDrift));
	result.addRect(QRectF(x1(), y2(), 0, 0).adjusted(-resizeDrift, -resizeDrift, resizeDrift, resizeDrift));
	result.addRect(QRectF(x2(), y1(), 0, 0).adjusted(-resizeDrift, -resizeDrift, resizeDrift, resizeDrift));
	result.addRect(QRectF(x2(), y2(), 0, 0).adjusted(-resizeDrift, -resizeDrift, resizeDrift, resizeDrift));
	return result;
}

QDomElement CommentItem::serialize(QDomElement &parent) const
{
	QDomElement commentNode = AbstractItem::serialize(parent);
	commentNode.setTagName("comment");
	commentNode.setAttribute("begin", QString::number(x1() + scenePos().x())
			 + ":" + QString::number(y1() + scenePos().y()));
	commentNode.setAttribute("end", QString::number(x2() + scenePos().x())
			 + ":" + QString::number(y2() + scenePos().y()));
	commentNode.setAttribute("text", mText.toHtml());
	return commentNode;
}

void CommentItem::deserialize(const QDomElement &element)
{
	AbstractItem::deserialize(element);

	mText.setHtml(element.attribute("text"));

	const QString beginStr = element.attribute("begin", "0:0");
	QStringList splittedStr = beginStr.split(":");
	auto x = splittedStr[0].toDouble();
	auto y = splittedStr[1].toDouble();
	const QPointF begin = QPointF(x, y);

	const QString endStr = element.attribute("end", "0:0");
	splittedStr = endStr.split(":");
	x = splittedStr[0].toDouble();
	y = splittedStr[1].toDouble();
	const QPointF end = QPointF(x, y);

	setPos(QPointF());
	setX1(begin.x());
	setY1(begin.y());
	setX2(end.x());
	setY2(end.y());
}

void CommentItem::setPrivateData()
{
	// IKHON zValue ?
	setZValue(ZValue::Shape);
	QPen pen(this->pen());
	pen.setColor(Qt::darkGray);
	pen.setStyle(Qt::DashLine);
	setPen(pen);

	connect(this, &AbstractItem::x1Changed, this, &CommentItem::updateTextPos);
	connect(this, &AbstractItem::y1Changed, this, &CommentItem::updateTextPos);
	connect(this, &AbstractItem::x2Changed, this, &CommentItem::updateTextPos);
	connect(this, &AbstractItem::y2Changed, this, &CommentItem::updateTextPos);

	mText.setPlainText("Your comment can be here");
	mText.setTextInteractionFlags(Qt::TextEditorInteraction);
	auto font = mText.font();
	font.setPixelSize(20);
	mText.setFont(font);
}

void CommentItem::updateTextPos()
{
	mText.setX(resizeDrift + qMin(x1(), x2()));
	mText.setY(resizeDrift + qMin(y1(), y2()));
}
