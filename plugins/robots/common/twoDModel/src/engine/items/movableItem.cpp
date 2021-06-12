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

#include "movableItem.h"

#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtSvg/QSvgRenderer>

#include <twoDModel/engine/model/constants.h>
#include <qrkernel/settingsManager.h>

using namespace twoDModel::items;

MovableItem::MovableItem(const QPointF &position)
	: mEstimatedPos(position)
{
	setPos(position);
}

void MovableItem::init() {
	setZValue(ZValue::Moveable);
	connect(this, &AbstractItem::mouseInteractionStarted, this, [this](){
			mEstimatedPos = pos();
		});
	mImage.reset(new model::Image(defaultImagePath(), false));
	setTransformOriginPoint(boundingRect().center());
}

MovableItem::~MovableItem()
{
}

void MovableItem::drawItem(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option)
	Q_UNUSED(widget)
	mImage->draw(*painter, QRect({-itemSize().width() / 2, -itemSize().height() / 2}, itemSize()));
}

void MovableItem::setPenBrushForExtraction(QPainter *painter, const QStyleOptionGraphicsItem *option)
{
	Q_UNUSED(option)
	painter->setPen(getStrokePen());
	if (isSelected()) {
		QColor extraColor = getStrokePen().color();
		extraColor.setAlphaF(0.5);
		painter->setBrush(extraColor);
	}
}

void MovableItem::drawExtractionForItem(QPainter *painter)
{
	painter->drawPath(shape());
}

void MovableItem::savePos()
{
	saveStartPosition();
	AbstractItem::savePos();
}

QDomElement MovableItem::serialize(QDomElement &element) const
{
	QDomElement movableNode = AbstractItem::serialize(element);
	movableNode.setTagName("movable");
	movableNode.setAttribute("x", QString::number(x1() + scenePos().x()));
	movableNode.setAttribute("y", QString::number(y1() + scenePos().y()));
	movableNode.setAttribute("markerX", QString::number(x1() + mStartPosition.x()));
	movableNode.setAttribute("markerY", QString::number(y1() + mStartPosition.y()));
	movableNode.setAttribute("rotation", QString::number(rotation()));
	movableNode.setAttribute("startRotation", QString::number(mStartRotation));
	if (!mImage->external()) {
		movableNode.setAttribute("imageId", mImage->imageId());
	}
	return movableNode;
}

void MovableItem::deserialize(const QDomElement &element)
{
	AbstractItem::deserialize(element);

	qreal x = element.attribute("x", "0").toDouble();
	qreal y = element.attribute("y", "0").toDouble();
	qreal markerX = element.attribute("markerX", "0").toDouble();
	qreal markerY = element.attribute("markerY", "0").toDouble();
	qreal rotation = element.attribute("rotation", "0").toDouble();
	mStartRotation = element.attribute("startRotation", "0").toDouble();

	setPos(QPointF(x, y));
	setTransformOriginPoint(boundingRect().center());
	mStartPosition = {markerX, markerY};
	setRotation(rotation);
	emit x1Changed(x1());
}

QRectF MovableItem::boundingRect() const
{
	return QRectF({-static_cast<qreal>(itemSize().width()) / 2, -static_cast<qreal>(itemSize().height()) / 2}
				  , itemSize());
}

void MovableItem::resizeItem(QGraphicsSceneMouseEvent *event)
{
	Q_UNUSED(event)
	mEstimatedPos += event->scenePos() - event->lastScenePos();
	const auto gridSize = qReal::SettingsManager::value("2dGridCellSize").toInt();
	auto x = alignedCoordinate(mEstimatedPos.x() - gridSize/2, gridSize) + gridSize/2;
	auto y = alignedCoordinate(mEstimatedPos.y() - gridSize/2, gridSize) + gridSize/2;
	setPos(x, y);
	update();
}

QPainterPath MovableItem::shape() const
{
	QPainterPath result;
	if (isCircle()) {
		result.addEllipse(boundingRect());
	} else {
		result.addRect(boundingRect());
	}
	return result;
}

void MovableItem::saveStartPosition()
{
	mStartPosition = pos();
	mStartRotation = rotation();
	emit x1Changed(x1());
}

void MovableItem::returnToStartPosition()
{
	setPos(mStartPosition);
	setRotation(mStartRotation);
	emit x1Changed(x1());
}

QPolygonF MovableItem::collidingPolygon() const
{
	return QPolygonF(boundingRect().adjusted(1, 1, -1, -1).translated(scenePos()));
}

QPainterPath MovableItem::path() const
{
	QPainterPath path;
	QPolygonF collidingPlgn = collidingPolygon();
	QMatrix m;
	m.rotate(rotation());

	QPointF firstP = collidingPlgn.at(0);
	collidingPlgn.translate(-firstP.x(), -firstP.y());

	if (isCircle()) {
		path.addEllipse(collidingPlgn.boundingRect());
	} else {
		path.addRect(collidingPlgn.boundingRect());
	}
	path = m.map(path);
	path.translate(firstP.x(), firstP.y());

	return path;
}

void MovableItem::resetImage(const QSharedPointer<model::Image> image) {
	if (image.isNull()) {
		mImage->loadFrom(defaultImagePath());
		mImage->setExternal(false);
	} else {
		mImage = image;
	}
	update();
}

QSharedPointer<twoDModel::model::Image> MovableItem::image() const
{
	return mImage;
}

SolidItem::BodyType MovableItem::bodyType() const
{
	return SolidItem::DYNAMIC;
}
