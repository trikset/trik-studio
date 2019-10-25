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

#include "rangeSensorItem.h"

#include <QtWidgets/QGraphicsSceneMouseEvent>

using namespace twoDModel::view;
using namespace kitBase::robotModel;

RangeSensorItem::RangeSensorItem(const model::WorldModel &worldModel
		, model::SensorsConfiguration &configuration
		, const PortInfo &port
		, QPair<qreal, int> angleAndRange
		, const QString &pathToImage
		, const QRect &imageSize
		)
	: SensorItem(configuration, port, pathToImage, imageSize)
	, mWorldModel(worldModel)
	, mIcon(":/icons/sensors/2d_sonar.png")
	, mAngle(angleAndRange.first)
	, mRange(angleAndRange.second)
{
	setFlags(ItemIsSelectable | ItemIsMovable | ItemSendsGeometryChanges);
}

void RangeSensorItem::drawItem(QPainter *painter, const QStyleOptionGraphicsItem *style, QWidget *widget)
{
	Q_UNUSED(style)
	Q_UNUSED(widget)

	painter->save();
	painter->setOpacity(0.2);
	painter->setBrush(Qt::black);
	painter->drawPath(scanningRegion());
	painter->restore();

	SensorItem::drawItem(painter, style, widget);
}

void RangeSensorItem::drawExtractionForItem(QPainter *painter)
{
	if (!isSelected()) {
		return;
	}

	SensorItem::drawExtractionForItem(painter);

	painter->save();
	const QPen pen = QPen(Qt::black);
	painter->setPen(pen);
	painter->setOpacity(0.7);
	painter->setRenderHints(painter->renderHints() | QPainter::Antialiasing);
	painter->drawPath(shape());
	painter->restore();
}

QRectF RangeSensorItem::boundingRect() const
{
	return scanningRegion().boundingRect().adjusted(-25, -15, 25, 15);
}

QPainterPath RangeSensorItem::scanningRegion() const
{
	return mWorldModel.rangeSensorScanningRegion(QPointF(), QPair<qreal, int>(mAngle, mRange));
}

QPainterPath RangeSensorItem::shape() const
{
	QPainterPath result;
	result.addRect(mBoundingRect);
	return result;
}

QRectF RangeSensorItem::rect() const
{
	return SensorItem::boundingRect();
}

void RangeSensorItem::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	if (!imageRect().contains(mouseEvent->pos())) {
		setFlag(ItemIsMovable, false);
	}

	AbstractItem::mousePressEvent(mouseEvent);
}
