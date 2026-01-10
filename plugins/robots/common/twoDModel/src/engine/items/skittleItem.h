/* Copyright 2017 CyberTech Labs Ltd.
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
#include "src/engine/items/solidItem.h"
#include <qrutils/graphicsUtils/abstractItem.h>
#include "details/serializer.h"

class QSvgRenderer;

namespace twoDModel {
namespace items {

class SkittleItem final: public graphicsUtils::AbstractItem, public SolidItem, public Serializer<SkittleItem>
{
	Q_OBJECT
	Q_DISABLE_COPY(SkittleItem)

public:
	explicit SkittleItem(graphicsUtils::AbstractCoordinateSystem *metricSystem,
			     QPointF position);

	~SkittleItem() override;

	/// Creates and returns skittle item for 2D model palette.
	/// Transfers ownership.
	static QAction *skittleTool();

	QRectF boundingRect() const override;
	void drawItem(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	void drawExtractionForItem(QPainter *painter) override;
	void setPenBrushForExtraction(QPainter *painter, const QStyleOptionGraphicsItem *option) override;

	void drawFieldForResizeItem(QPainter* painter) override { Q_UNUSED(painter) }
	void resizeItem(QGraphicsSceneMouseEvent *event) override { Q_UNUSED(event) }
	void savePos() override;

	QDomElement serialize(QDomElement &element) const override;
	void deserialize(const QDomElement &element) override;
	void setStartPosition(QPointF startPosition);
	void setStartRotation(qreal startPosition);
	qreal startRotation() const;
	QPointF startPosition() const;
	void saveStartPosition();
	void returnToStartPosition();
	QPainterPath shape() const override;
	bool isCircle() const override;
	BodyType bodyType() const override;
	QPolygonF collidingPolygon() const override;
	QPainterPath path() const;

private:
	void setDiameter(const qreal diameter);
	QPointF mStartPosition;
	qreal mStartRotation {0.0};
	ItemProperty<qreal> mDiameterPx;
	// bool mPreferLeftTopPoint {};
	std::unique_ptr<QSvgRenderer> mSvgRenderer;
};
}
}
