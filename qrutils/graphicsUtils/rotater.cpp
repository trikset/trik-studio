/* Copyright 2007-2015 QReal Research Group, Dmitry Mordvinov
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

#include "rotater.h"

#include <QtCore/qmath.h>
#include <QtGui/QCursor>
#include <QtWidgets/QGraphicsSceneMouseEvent>

#include <qrutils/mathUtils/math.h>
#include <qrutils/graphicsUtils/rotateItem.h>

using namespace graphicsUtils;
using namespace mathUtils;

const int rotaterLength = 30;

Rotater::Rotater()
	: AbstractItem(Qt::PointingHandCursor)
{
	setFlag(ItemIsSelectable);
	setFlag(ItemIsMovable, false);

	setAcceptDrops(true);

	QPen pen(Qt::blue);
	pen.setWidth(3);
	setPen(pen);
	setBrush(Qt::NoBrush);
}

void Rotater::setMasterItem(RotateItem *masterItem)
{
	mMaster = masterItem;

	const QRectF rect = mMaster->rect();
	const qreal horizontalRadius = rect.width() / 2;

	mLength = rotaterLength;
	mDrift = drift > horizontalRadius ? drift / 2 : drift;
	mResizeDrift = drift > horizontalRadius ? resizeDrift / 2 : resizeDrift;


	mMaster->setFlag(ItemClipsToShape, false);
	setParentItem(mMaster);

	/// @todo Dispose of hardcoding
	setX1(rect.right());
	// Placing rotater into the center of item`s rigth side
	setY1(rect.y() + rect.height() / 2);
	setX2(x1() + mLength);
	setY2(y1());
}

void Rotater::drawItem(QPainter *painter, const QStyleOptionGraphicsItem *style, QWidget *widget)
{
	Q_UNUSED(style)
	Q_UNUSED(widget)

	painter->setOpacity(0.5);
	const int addLength = mLength / 3;
	const qreal angle = addAngle;
	// Must be equal to mLength
	const qreal checkLength = sqrt((x2() - x1()) * (x2() - x1()) + (y2() - y1()) * (y2() - y1()));
	const qreal x0 = ((checkLength - addLength) * x2() + addLength * x1()) / checkLength;
	const qreal y0 = ((checkLength - addLength) * y2() + addLength * y1()) / checkLength;
	const QPointF first = QTransform().translate(x2() - x0, y2() - y0).rotate(-angle).translate(-x2() + x0, -y2() + y0)
			.rotate(angle).map(QPointF(x0, y0));
	const QPointF second = QTransform().translate(x2() - x0, y2() - y0).rotate(angle).translate(-x2() + x0, -y2() + y0)
			.rotate(-angle).map(QPointF(x0, y0));

	mLineImpl.drawItem(painter, x1(), y1(), x2(), y2());
	mLineImpl.drawItem(painter, x2(), y2(), first.x(), first.y());
	mLineImpl.drawItem(painter, x2(), y2(), second.x(), second.y());
}

void Rotater::setPenBrushForExtraction(QPainter *painter, const QStyleOptionGraphicsItem *option)
{
	Q_UNUSED(option)
	setPenBrushDriftRect(painter);
}

void Rotater::drawExtractionForItem(QPainter *painter)
{
	mLineImpl.drawExtractionForItem(painter, x1(), y1(), x2(), y2(), mDrift);
	drawFieldForResizeItem(painter);
}

void Rotater::setPenBrushDriftRect(QPainter *painter)
{
	QPen pen(Qt::red);
	pen.setWidth(2);
	painter->setPen(pen);
}

QPainterPath Rotater::shape() const
{
	return resizeArea();
}

QRectF Rotater::boundingRect() const
{
	return mLineImpl.boundingRect(x1(), y1(), x2(), y2(), pen().width(), drift);
}

void Rotater::calcResizeItem(QGraphicsSceneMouseEvent *event)
{
	const QPointF masterCenter(mMaster->mapToScene(mMaster->rect().center()));
	const QPointF zeroRotationVector(mLength, 0);

	const qreal mouseX = event->scenePos().x() - masterCenter.x();
	const qreal mouseY = event->scenePos().y() - masterCenter.y();

	const qreal mouseVectorLength = sqrt(mouseX * mouseX + mouseY * mouseY);
	if (mouseVectorLength < EPS) {
		return;
	}

	// Master rotation is signed angle between initial and mouse vector.
	// Calculating it from theese vectors product and cosine theorem
	const qreal vectorProductLength = zeroRotationVector.x() * mouseY
			- zeroRotationVector.y() * mouseX;
	const qreal sin = vectorProductLength / (mouseVectorLength * mLength);

	const qreal translationX = mouseX - zeroRotationVector.x();
	const qreal translationY = mouseY - zeroRotationVector.y();
	const bool cosIsNegative = mouseVectorLength * mouseVectorLength + mLength * mLength
			< translationX * translationX + translationY * translationY;

	const qreal angleInWrongQuarter = asin(sin);
	const qreal angleInRightQuarter = cosIsNegative ? M_PI - angleInWrongQuarter : angleInWrongQuarter;
	const qreal littleAngle = angleInRightQuarter * 180 / M_PI;

	const qreal masterAngleCompensation = mMaster->parentItem()
			? mMaster->parentItem()->rotation()
			: 0.0;

	const qreal deltaAngle = fmod(littleAngle - mMaster->rotation()- masterAngleCompensation, 360);
	const qreal addAngle = deltaAngle > 180 ? -360 : deltaAngle < -180 ? 360 : 0;
	const qreal angle = mMaster->rotation() + deltaAngle + addAngle;

	mMaster->setRotation(angle * 180 / M_PI - masterAngleCompensation);
}

void Rotater::resizeItem(QGraphicsSceneMouseEvent *event)
{
	if (dragState() == BottomRight) {
		if (mMaster->editable()) {
			AbstractItem::resizeItem(event);
		}
	}
}

QPainterPath Rotater::resizeArea() const
{
	QPainterPath result;
	result.addEllipse(QPointF(x2(), y2()), mResizeDrift, mResizeDrift);
	return result;
}

void Rotater::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if (dragState() != BottomRight) {
		event->ignore();
	}

	AbstractItem::mousePressEvent(event);
	mMaster->setSelected(true);
	// Deselecting parent in QGraphicsItem::mousePressEvent will ungrab mouse from rotater. We need to workarround here.
	/// @todo: This must be fixed in RotateItem itemChange method.
	grabMouse();

	emit mMaster->mouseInteractionStarted();
}

void Rotater::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	if (dragState() == BottomRight) {
		if (mMaster->editable()) {
			AbstractItem::resizeItem(event);
		}

		mMaster->setSelected(true);
	}
}

void Rotater::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	if (dragState() == BottomRight) {
		AbstractItem::mouseReleaseEvent(event);
		ungrabMouse();

		emit mMaster->mouseInteractionStopped();
	}
}

void Rotater::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
	QGraphicsItem::contextMenuEvent(event);
}
