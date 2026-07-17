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

#include <qrutils/graphicsUtils/lineImpl.h>

#include "mainWindow/shapeEdit/item.h"

class Line : public Item
{
	Q_OBJECT
public:
	Line(qreal x1, qreal y1, qreal x2, qreal y2, Item *parent = nullptr);
	QLineF line() const;
	QPainterPath shape() const override;
	QRectF boundingRect() const override;
	QRectF realBoundingRect() const override;
	void drawItem(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
	void drawExtractionForItem(QPainter *painter) override;
	void drawScalingRects(QPainter *painter) override;
	void changeScalingPointState(qreal x, qreal y) override;
	void resizeItem(QGraphicsSceneMouseEvent *event) override;
	void reshapeRectWithShift() override;

	QPair<QPair<QString, QString>, QPair<QString, QString>> setXandYBefore(QRect rect);
	void setDomXandY(QDomElement &dom, const QPair<QPair<QString, QString>, QPair<QString, QString>> &pair);
	QPair<QDomElement, Item::DomElementTypes> generateItem(QDomDocument &document,
		const QPoint &topLeftPicture) override;

private:
	graphicsUtils::LineImpl mLineImpl;
};
