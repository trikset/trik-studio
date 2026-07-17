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

#pragma once

#include <QtWidgets/QGraphicsTextItem>
#include <QtWidgets/QStyleOptionGraphicsItem>
#include <QtGui/QPainter>
#include <QtGui/QFont>

#include "mainWindow/shapeEdit/item.h"

class Text : public Item
{
	Q_OBJECT
public:
	Text(bool isDynamic = false);
	Text(int x, int y, const QString &text = "text", bool isDynamic = false);
	void init(int x, int y, const QString &text);
	bool isDynamicText();
	virtual void setIsDynamicText(bool isDynamic);
	QRectF boundingRect() const override;
	QRectF realBoundingRect() const override;
	void drawItem(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
	void drawExtractionForItem(QPainter *painter) override;
	void drawFieldForResizeItem(QPainter *painter) override;
	void drawScalingRects(QPainter *painter) override;
	void changeScalingPointState(qreal x, qreal y) override;
	QGraphicsTextItem const &getText();
	void setItemZValue(int zValue) override;

	QPair<QDomElement, Item::DomElementTypes> generateItem(QDomDocument &document,
		const QPoint &topLeftPicture) override;

protected:
	int mX1 {};
	int mY1 {};
	QRectF mBoundingRect;
	QGraphicsTextItem mText;
	bool mIsDynamicText;
	QRectF mRect;
	void drawForDynamicText(QPainter *painter);
};
