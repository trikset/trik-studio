/* Copyright 2016-2018 CyberTech Labs Ltd.
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

#include "imageItem.h"

#include <QtGui/QPainter>
#include <QtWidgets/QAction>
#include <QtWidgets/QGraphicsSceneMouseEvent>

#include <qrkernel/settingsManager.h>

using namespace twoDModel::items;
using namespace qReal;
using namespace graphicsUtils;

ImageItem::ImageItem(const QSharedPointer<model::Image> &image, const QRect &geometry)
	: mImage(image)
{
	setX(0);
	setY(0);
	setX1(geometry.left());
	setY1(geometry.top());
	setX2(geometry.right());
	setY2(geometry.bottom());
	setBackgroundRole(false);
	unsetCursor();
	connect(this, &AbstractItem::mouseInteractionStarted, this, [this](){
			mEstimatedPos = pos();
		});
}

AbstractItem *ImageItem::clone() const
{
	const auto cloned = new ImageItem(mImage, QRect(x1(), y1(), x2() - x1(), y2() - y1()));
	AbstractItem::copyTo(cloned);
	return cloned;
}

void ImageItem::drawExtractionForItem(QPainter* painter)
{
	if (isSelected() || !isBackground()) {
		AbstractItem::drawExtractionForItem(painter);
		setPenBrushDriftRect(painter);
		painter->drawRect(calcNecessaryBoundingRect().toRect());
	}
}

QPainterPath ImageItem::resizeArea() const
{
	QRectF itemBoundingRect = calcNecessaryBoundingRect();
	const qreal x1 = itemBoundingRect.left();
	const qreal x2 = itemBoundingRect.right();
	const qreal y1 = itemBoundingRect.top();
	const qreal y2 = itemBoundingRect.bottom();

	QPainterPath result;
	result.addRect(QRectF(x1, y1, resizeDrift, resizeDrift));
	result.addRect(QRectF(x2 - resizeDrift, y2 - resizeDrift, resizeDrift, resizeDrift));
	result.addRect(QRectF(x1, y2 - resizeDrift, resizeDrift, resizeDrift));
	result.addRect(QRectF(x2 - resizeDrift, y1, resizeDrift, resizeDrift));

	return result;
}

QAction *ImageItem::imageTool()
{
	QAction * const result = new QAction(loadTextColorIcon(":/icons/2d_image.svg"), tr("Image (I)"), nullptr);
	result->setShortcuts({QKeySequence(Qt::Key_I), QKeySequence(Qt::Key_Minus)});
	result->setCheckable(false);
	return result;
}

QRectF ImageItem::boundingRect() const
{
	return RectangleImpl::boundingRect(x1(), y1(), x2(), y2(), drift);
}

QRectF ImageItem::calcNecessaryBoundingRect() const
{
	return QRectF(qMin(x1(), x2()), qMin(y1(), y2()), qAbs(x2() - x1()), qAbs(y2() - y1()));
}

void ImageItem::drawItem(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option)
	Q_UNUSED(widget)
	const qreal zoom = scene()->views().isEmpty() ? 1.0 : scene()->views().first()->transform().m11();
	mImage->draw(*painter, calcNecessaryBoundingRect().toRect(), zoom);
}

QPainterPath ImageItem::shape() const
{
	QPainterPath result;
	result.addRect(calcNecessaryBoundingRect());
	return result;
}

QDomElement ImageItem::serialize(QDomElement &parent) const
{
	QDomElement imageNode = AbstractItem::serialize(parent);
	imageNode.setTagName("image");

//	mImage.serialize(imageNode);
	imageNode.setAttribute("rect", QString("%1:%2:%3:%4").arg(
			QString::number(x1())
			, QString::number(y1())
			, QString::number(x2() - x1())
			, QString::number(y2() - y1())));
	imageNode.setAttribute("position", QString::number(x()) + ":" + QString::number(y()));
	imageNode.setAttribute("imageId", mImage->imageId());
	imageNode.setAttribute("isBackground", mBackgroundRole ? "true" : "false");
	return imageNode;
}

void ImageItem::deserialize(const QDomElement &element)
{
	AbstractItem::deserialize(element);
	QRectF rect;
	if (element.hasAttribute("backgroundRect")) {
		rect = deserializeRect(element.attribute("backgroundRect"));
		setPos(0, 0);
		setBackgroundRole(true);
	} else {
		rect = deserializeRect(element.attribute("rect"));
		setPos(RectangleImpl::deserializePoint(element.attribute("position")));
		setBackgroundRole(element.attribute("isBackground", "false") == "true");
	}
	setX1(rect.left());
	setX2(rect.right());
	setY1(rect.top());
	setY2(rect.bottom());
}

QSharedPointer<twoDModel::model::Image> ImageItem::image() const
{
	return mImage;
}

bool ImageItem::memorizes() const
{
	return !mImage->external();
}

QString ImageItem::path() const
{
	return mImage->path();
}

void ImageItem::setMemorize(bool memorize)
{
	mImage->setExternal(!memorize);
	emit internalImageChanged();
}

void ImageItem::setPath(const QString &path)
{
	mImage->loadFrom(path);
	update();
	emit internalImageChanged();
}

void ImageItem::setBackgroundRole(bool background)
{
	mBackgroundRole = background;
	if (!isSelected()) {
		setEditable(!mBackgroundRole);
		setFlag(ItemIsSelectable, !mBackgroundRole);
	}
	setZValue(background ? ZValue::Background : ZValue::Picture);
}

bool ImageItem::isBackground() const
{
	return mBackgroundRole;
}

QVariant ImageItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
	if (change == QGraphicsItem::ItemSelectedHasChanged) {
		emit selectedChanged(value.toBool());
		if (!value.toBool() && isBackground()) {
			setFlag(ItemIsSelectable, false);
			setEditable(false);
			unsetCursor();
		}
	}

	return AbstractItem::itemChange(change, value);
}

void ImageItem::updateCursor(QGraphicsSceneHoverEvent *event)
{
	if (isSelected() || !isBackground()) {
		if (resizeArea().contains(event->pos())) {
			setCursor(getResizeCursor());
		} else {
			unsetCursor();
		}
	}
}

void ImageItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
	if (isBackground()) {
		setEditable(true);
		setFlag(ItemIsSelectable);
	}
	AbstractItem::mousePressEvent(event);
}

QRectF ImageItem::deserializeRect(const QString &string) const
{
	const QStringList splittedStr = string.split(":");
	if (splittedStr.count() == 4) {
		const auto x = splittedStr[0].toDouble();
		const auto y = splittedStr[1].toDouble();
		const auto w = splittedStr[2].toDouble();
		const auto h = splittedStr[3].toDouble();
		return QRectF(x, y, w, h);
	}

	return QRectF();
}

void ImageItem::resizeItem(QGraphicsSceneMouseEvent *event)
{
	mEstimatedPos += event->scenePos() - event->lastScenePos();
	const auto showGrid = SettingsManager::value("2dShowGrid").toBool();
	if (!showGrid || event->modifiers() == Qt::ControlModifier) {
		if (dragState() != None) {
			calcResizeItem(event);
		} else {
			setPos(mEstimatedPos);
		}
	} else if (dragState() != None) {
		setFlag(QGraphicsItem::ItemIsMovable, false);
		const auto gridSize = SettingsManager::value("2dGridCellSize").toInt();
		const auto x = alignedCoordinate(event->scenePos().x(), gridSize);
		const auto y = alignedCoordinate(event->scenePos().y(), gridSize);
		setXYWithDragState(mapFromScene(x, y));
	} else {
		setFlag(QGraphicsItem::ItemIsMovable, false);
		// move
		setPos(mEstimatedPos);
		// and align top left corner to grid
		QRectF itemBoundingRect = calcNecessaryBoundingRect();
		const auto topLeft = mapToScene(QPointF(itemBoundingRect.left(), itemBoundingRect.top()));
		const auto gridSize = SettingsManager::value("2dGridCellSize").toInt();
		const auto x = alignedCoordinate(topLeft.x(), gridSize);
		const auto y = alignedCoordinate(topLeft.y(), gridSize);
		auto delta = QPointF(x, y) - topLeft;
		moveBy(delta.x(), delta.y());
	}
}
