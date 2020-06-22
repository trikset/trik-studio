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

#include "image.h"

#include <QtGui/QBitmap>
#include <QtGui/QImageWriter>

Image::Image(const QString &fileName, qreal x, qreal y, Item* parent)
	: Item(parent)
	, mImage(fileName)
	, mRectangleImpl()
{
	mFileName = fileName;
	QPixmap* pixmap = new QPixmap(fileName);
	mPixmapItem = new QGraphicsPixmapItem(*pixmap);
	mNeedScalingRect = true;
	mDomElementType = pictureType;
	setX1(x);
	setY1(y);
	setX2(x + pixmap->width());
	setY2(y + pixmap->height());
}

QRectF Image::boundingRect() const
{
	return mRectangleImpl.boundingRect(x1(), y1(), x2(), y2(), scalingDrift);
}

void Image::drawItem(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	Q_UNUSED(option);
	Q_UNUSED(widget);

	mRectangleImpl.drawImageItemWithMirrored(painter, x1(), y1(), x2(), y2(), mImage);
}

void Image::setItemZValue(int zValue)
{
	mZValue = zValue;
	mPixmapItem->setZValue(zValue);
	setZValue(zValue);
}

QPair<QDomElement, Item::DomElementTypes> Image::generateItem(QDomDocument &document, const QPoint &topLeftPicture)
{
	QDomElement image = document.createElement("image");
	setXandY(image, sceneBoundingRectCoord(topLeftPicture));
	image.setAttribute("name", "images/" + mFileName.section('/', -1));

	return QPair<QDomElement, Item::DomElementTypes>(image, mDomElementType);
}
