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

#include <QtCore/QList>

#include <qrutils/graphicsUtils/stylusImpl.h>

#include "mainWindow/shapeEdit/item.h"
#include "mainWindow/shapeEdit/line.h"

class Stylus : public Item
{
	Q_OBJECT
public:
	QList<Line *> mListLine;
	Stylus(qreal x1, qreal y1, Item* parent);
	void addLine(qreal x2, qreal y2);
	void addLineInList(Line *line);

	QRectF boundingRect() const override;
	QPainterPath shape() const override;
	void drawItem(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
	void drawExtractionForItem(QPainter* painter) override;
	void drawFieldForResizeItem(QPainter* painter) override;
	void drawScalingRects(QPainter* painter) override;
	void setPenStyle(const QString &text) override;
	virtual void setPenWidth(int width);
	void setPenColor(const QString &text) override;
	void setBrushStyle(const QString &text) override;
	void setBrushColor(const QString &text) override;
	QPair<QDomElement, Item::DomElementTypes> generateItem(QDomDocument &document
			, const QPoint &topLeftPicture) override;

private:
	qreal mTmpX1;
	qreal mTmpY1;
	QList<AbstractItem *> mAbstractListLine;
	graphicsUtils::StylusImpl mStylusImpl;
};
