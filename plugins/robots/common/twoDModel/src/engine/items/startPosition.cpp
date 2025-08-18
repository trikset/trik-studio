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

#include "startPosition.h"

#include "twoDModel/engine/model/constants.h"

using namespace twoDModel::items;

const QSizeF size = QSizeF(13, 13);
const int lineWidth = 3;

StartPosition::StartPosition(graphicsUtils::AbstractCoordinateSystem *metricSystem,
                             const QSizeF &robotSize, QGraphicsItem *parent)
        : RotateItem(parent)
	, mRobotSize(robotSize)
{
	setCoordinateSystem(metricSystem);
	setX(mRobotSize.width() / 2);
	setY(mRobotSize.height() / 2);
	RotateItem::init();
}

QRectF StartPosition::boundingRect() const
{
	return QRectF(-size.width() / 2, -size.height() / 2, size.width(), size.height());
}

void StartPosition::drawItem(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option)
	Q_UNUSED(widget)
	painter->save();
	QPen pen(Qt::red);
	pen.setWidth(lineWidth);
	painter->setPen(pen);
	painter->drawLine(-size.width() / 2, -size.height() / 2, size.width() / 2, size.height() / 2);
	painter->drawLine(-size.width() / 2, size.height() / 2, size.width() / 2, -size.height() / 2);
	painter->restore();
}

QDomElement StartPosition::serialize(QDomElement &parent) const
{
	auto *coordSystem = coordinateSystem();
	QDomElement startPositionElement = RotateItem::serialize(parent);
	startPositionElement.setTagName("startPosition");
	startPositionElement.setAttribute("x",
	                                  QString::number(coordSystem->toUnit(scenePos().x())));
	startPositionElement.setAttribute("y",
	                                  QString::number(coordSystem->toUnit(scenePos().y())));
	startPositionElement.setAttribute("direction", QString::number(rotation()));
	return startPositionElement;
}

void StartPosition::deserialize(const QDomElement &startPositionElement)
{
	auto *coordSystem = coordinateSystem();
	auto x = coordSystem->toPx(startPositionElement.attribute("x").toDouble());
	auto y = coordSystem->toPx(startPositionElement.attribute("y").toDouble());
	setX(x);
	setY(y);
	setRotation(startPositionElement.attribute("direction").toDouble());
}

void StartPosition::deserializeCompatibly(const QDomElement &robotElement)
{
	const QDomElement startPositionElement = robotElement.firstChildElement("startPosition");
	auto *coordSystem = coordinateSystem();
	if (startPositionElement.isNull()) {
		const QStringList robotPositionParts = robotElement.attribute("position", "0:0").split(":");
		const QString robotX = robotPositionParts.count() != 2 ? "0" : robotPositionParts[0];
		const QString robotY = robotPositionParts.count() != 2 ? "0" : robotPositionParts[1];
		setX(coordSystem->toPx(robotX.toDouble()) + mRobotSize.width() / 2);
		setY(coordSystem->toPx(robotY.toDouble()) + mRobotSize.height() / 2);
		setRotation(robotElement.attribute("direction", "0").toDouble());
	} else {
		deserialize(startPositionElement);
	}
}

void StartPosition::drawFieldForResizeItem(QPainter *painter)
{
	Q_UNUSED(painter)
}

void StartPosition::changeDragState(qreal x, qreal y)
{
	Q_UNUSED(x)
	Q_UNUSED(y)
	setDragState(None);
}

void StartPosition::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
	Q_UNUSED(event)
}
