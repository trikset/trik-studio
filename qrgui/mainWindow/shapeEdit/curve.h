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

#include <QtGui/QPainter>

#include "mainWindow/shapeEdit/item.h"
#include "mainWindow/shapeEdit/path.h"

class Curve : public Path
{
	Q_OBJECT
public:
	Curve(QPointF start, QPointF end, QPointF c1);
	void  setCXandCY(qreal x, qreal y);
	QRectF searchMaxMinCoord() const;
	QRectF boundingRect() const override;
	QPainterPath shape() const override;
	void drawItem(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
	void drawExtractionForItem(QPainter* painter) override;
	void drawScalingRects(QPainter* painter) override;
	void drawFieldForResizeItem(QPainter* painter) override;

	void changeDragState(qreal x, qreal y) override;
	void calcResizeItem(QGraphicsSceneMouseEvent *event) override;

	QPair<QDomElement, Item::DomElementTypes> generateItem(QDomDocument &document
			, const QPoint &topLeftPicture) override;

private:
	QPointF mC1;
	QPointF mC2;
	QPainterPath* mCurvePath;
};
