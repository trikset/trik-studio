/* Copyright 2018 CyberTech Labs Ltd.
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

#include <qrutils/graphicsUtils/abstractItem.h>

#include "src/engine/items/solidItem.h"

class QSvgRenderer;

namespace twoDModel {
namespace items {

class MovableItem : public graphicsUtils::AbstractItem, public SolidItem
{
	Q_OBJECT
	Q_DISABLE_COPY(MovableItem)

public:
	explicit MovableItem(const QPointF &position);
	~MovableItem() override;

	void drawItem(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	void drawExtractionForItem(QPainter *painter) override;
	void setPenBrushForExtraction(QPainter *painter, const QStyleOptionGraphicsItem *option) override;

	void drawFieldForResizeItem(QPainter* painter) override { Q_UNUSED(painter) }
	void resizeItem(QGraphicsSceneMouseEvent *event) override;
	void savePos() override;

	QDomElement serialize(QDomElement &element) const override;
	void deserialize(const QDomElement &element) override;

	void saveStartPosition();
	void returnToStartPosition();

	BodyType bodyType() const override;
	QRectF boundingRect() const override;
	QPolygonF collidingPolygon() const override;
	QPainterPath shape () const override;
	QPainterPath path() const;

	virtual QSize itemSize() const = 0;

protected:
	QSvgRenderer *mSvgRenderer;

private:
	QPointF mStartPosition;
	qreal mStartRotation {0.0};
	QPointF mEstimatedPos;
};

}
}
