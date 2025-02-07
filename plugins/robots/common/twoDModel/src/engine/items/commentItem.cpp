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
#include <QTextDocument>
#include <QMenu>

#include <qrutils/graphicsUtils/rectangleImpl.h>

#include <QDebug>

using namespace twoDModel::items;
using namespace graphicsUtils;

CommentItem::CommentItem(const QPointF &begin, const QPointF &end)
	: mTextItem(this)
	, mHtmlText("Your comment can be here")
{
	setX1(qMin(begin.x(), end.x()));
	setY1(qMin(begin.y(), end.y()));
	setX2(qMax(begin.x(), end.x()));
	setY2(qMax(begin.y(), end.y()));
	setPrivateData();
}

QAction *CommentItem::commentTool()
{
	auto * const result = new QAction(loadTextColorIcon(":/icons/2d_comment.svg"), tr("Text (T)"), nullptr);
	result->setShortcuts({QKeySequence(Qt::Key_T), QKeySequence(Qt::Key_0)});
	result->setCheckable(true);
	return result;
}

QRectF CommentItem::boundingRect() const
{
	return RectangleImpl::boundingRect(x1(), y1(), x2(), y2(), resizeDrift);
}

QPainterPath CommentItem::shape() const
{
	QPainterPath result;

	result.addRect(moveRect());

	if (isSelected()) {
		result.addPath(resizeArea());
	}

	return result;
}

void CommentItem::drawItem(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	Q_UNUSED(option)
	Q_UNUSED(widget)
	painter->drawRect(moveRect());
	painter->setBrush(Qt::transparent);
	RectangleImpl::drawRectItem(painter, x1(), y1(), x2(), y2());
}

void CommentItem::drawExtractionForItem(QPainter* painter)
{
	AbstractItem::drawExtractionForItem(painter);
}

void CommentItem::calcResizeItem(QGraphicsSceneMouseEvent *event)
{
	setFlag(QGraphicsItem::ItemIsMovable, false);
	const auto x = mapFromScene(event->scenePos()).x();
	const auto y = mapFromScene(event->scenePos()).y();
	const auto textRect = textBoundingRect();
	const auto state = dragState();

	switch (state) {
	case TopLeft:
	case BottomLeft:
		if (x <= x2() - textRect.width()) setX1(x);
		break;
	case TopRight:
	case BottomRight:
		if (x >= x1() + textRect.width()) setX2(x);
		break;
	default:
		break;
	}

	switch (state) {
	case TopLeft:
	case TopRight:
		if (y <= y2() - textRect.height()) setY1(y);
		break;
	case BottomLeft:
	case BottomRight:
		if (y >= y1() + textRect.height()) setY2(y);
		break;
	default:
		break;
	}
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
	commentNode.setAttribute("text", mTextItem.toHtml());
	return commentNode;
}

void CommentItem::deserialize(const QDomElement &element)
{
	mIsEditing = false;
	AbstractItem::deserialize(element);

	mTextItem.setHtml(element.attribute("text"));
	mHtmlText = mTextItem.toHtml();
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
	setX1(qMin(begin.x(), end.x()));
	setY1(qMin(begin.y(), end.y()));
	setX2(qMax(begin.x(), end.x()));
	setY2(qMax(begin.y(), end.y()));
}

void CommentItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
	if (!editable()) {
		return;
	}

	if (!isSelected()) {
		scene()->clearSelection();
		setSelected(true);
	}

	event->accept();

	QMenu *menu = new QMenu();
	QAction *removeAction = menu->addAction(QObject::tr("Remove"));
	QAction *editAction = menu->addAction(mIsEditing ? QObject::tr("Save") : QObject::tr("Edit"));
	QAction *cancelAction = menu->addAction(QObject::tr("Cancel"));
	if (!mIsEditing) menu->removeAction(cancelAction);
	QAction *selectedAction = menu->exec(event->screenPos());
	delete menu;
	if (selectedAction == removeAction) {
		emit deletedWithContextMenu();
	} else if (selectedAction == editAction) {
		mIsEditing ? endEditing() : startEditing();
	} else if (selectedAction == cancelAction) {
		endEditing();
	}
}

void CommentItem::startEditing() {
	mIsEditing = true;
	setBrushStyle("Solid");
	mTextItem.setTextInteractionFlags(Qt::TextEditorInteraction);
	mTextItem.setHtml(mHtmlText);
	mTextItem.setFocus();
	update();
}

void CommentItem::endEditing()
{
	mIsEditing = false;
	setBrushStyle("None");
	mTextItem.setTextInteractionFlags(Qt::NoTextInteraction);
	mHtmlText = mTextItem.toHtml();
	mTextItem.setHtml(mHtmlText);
	updateSize();
	update();
}

QRectF CommentItem::moveRect() const
{
	return QRectF((x1() + x2())/2, y1(), 0, 0).adjusted(-2*resizeDrift, -resizeDrift, 2*resizeDrift, resizeDrift);
}

QRectF CommentItem::textBoundingRect() const
{
	return mTextItem.sceneBoundingRect().adjusted(-resizeDrift, -resizeDrift, resizeDrift, resizeDrift);
}

void CommentItem::setPrivateData()
{
	// IKHON zValue ?
	setZValue(ZValue::Shape);
	setPenColor("darkGray");
	setPenStyle("Dash");
	setBrush("None", "red");

	connect(this, &AbstractItem::x1Changed, this, &CommentItem::updateTextPos);
	connect(this, &AbstractItem::y1Changed, this, &CommentItem::updateTextPos);

	mTextItem.setTextInteractionFlags(Qt::NoTextInteraction);
	auto font = mTextItem.font();
	font.setPixelSize(20);
	mTextItem.setFont(font);
	mTextItem.setHtml(mHtmlText);
	updateTextPos();
	updateSize();
}

void CommentItem::updateTextPos()
{
	mTextItem.setX(resizeDrift + x1());
	mTextItem.setY(resizeDrift + y1());
}

void CommentItem::updateSize()
{
	const auto rect = textBoundingRect();
	setX2(qMax(x2(), x1() + rect.width()));
	setY2(qMax(y2(), y1() + rect.height()));
}
