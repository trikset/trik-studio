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

#include <qrutils/graphicsUtils/pointImpl.h>

#include "mainWindow/shapeEdit/item.h"
#include "mainWindow/shapeEdit/ellipse.h"

class PointPort : public Item
{
	Q_DISABLE_COPY(PointPort)
public:
	PointPort(qreal x, qreal y, Item *parent = nullptr);
	virtual QRectF boundingRect() const;
	virtual void drawItem(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr);
	virtual void drawExtractionForItem(QPainter* painter);
	virtual void drawFieldForResizeItem(QPainter* painter);
	virtual void drawScalingRects(QPainter* painter);
	virtual void changeDragState(qreal x, qreal y);
	virtual void changeScalingPointState(qreal x, qreal y);
	virtual void resizeItem(QGraphicsSceneMouseEvent *event);

	virtual QPair<QDomElement, Item::DomElementTypes> generateItem(QDomDocument &document
			, const QPoint &topLeftPicture);

	void setType(const QString &type);
	QString getType() const;

private:
	qreal mRadius { -1 };
	qreal mUnrealRadius { -1 };
	graphicsUtils::PointImpl mPointImpl;
	QString mType;
};
