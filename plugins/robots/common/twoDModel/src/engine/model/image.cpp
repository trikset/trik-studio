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

#include "twoDModel/engine/model/image.h"

#include <QtCore/QFile>
#include <QtCore/QUuid>
#include <QtCore/QBuffer>
#include <QtGui/QPainter>
#include <QtSvg/QSvgRenderer>
#include <QtXml/QDomElement>

#include <QImageReader>
#include <QImageWriter>
#include <qrkernel/logging.h>
#include <qrutils/imagesCache.h>

using namespace twoDModel::model;

const quint64 maxSvgSize = 1000;

Image::~Image() = default;

Image::Image(const QString &id)
	: mImageId(id)
	, mImagesCache(utils::ImagesCache::instance())
{
}

Image::Image(const QString &path, bool memorize)
	: mExternal(!memorize)
	, mImageId(QUuid::createUuid().toString())
	, mImagesCache(utils::ImagesCache::instance())
{
	loadFrom(path);
}

QSharedPointer<Image> Image::deserialize(const QDomElement &element)
{
	const bool external = element.attribute("external") == "true";
	const QString path = element.attribute("path");
	QByteArray content = element.text().toLatin1();
	auto image = QSharedPointer<Image>::create(element.attribute("imageId", QUuid::createUuid().toString()));
	image->setExternal(external);
	if (external) {
		image->loadFrom(path);
	} else {
		image->mPath = path;
		if (path.endsWith("svg", Qt::CaseInsensitive)) {
			image->mIsSvg = true;
			image->mSvgBytes = std::move(content);
			image->mSvgRenderer.reset(new QSvgRenderer(image->mSvgBytes));
		} else {
			auto bytes = QByteArray::fromBase64(content);
			QBuffer buffer(&bytes);
			QImage tempImage;
			if (!tempImage.load(&buffer, "PNG")) {
				QLOG_ERROR() << "Corrupted image" << image->mPath << "when loading from save";
			}
			image->mImage.reset(new QImage(tempImage));
		}
	}

	return image;
}

void Image::serialize(QDomElement &target) const
{
	if (isValid()) {
		target.setAttribute("path", mPath);
		target.setAttribute("external", mExternal ? "true" : "false");
		target.setAttribute("imageId", mImageId);
	} else {
		QLOG_WARN() << "Trying to save invalid image " << mImageId;
	}

	if (mExternal) {
		return;
	}

	if (mIsSvg) {
		if (mSvgBytes.isEmpty()) {
			QFile file(mPath);
			if (file.open(QFile::ReadOnly)) {
				const QDomText svgText = target.ownerDocument().createTextNode(file.readAll());
				target.appendChild(svgText);
			} else {
				QLOG_ERROR() << "Could not open" << mPath << "for reading when embedding svg into save file";
			}
		} else {
			const QDomText svgText = target.ownerDocument().createTextNode(mSvgBytes);
			target.appendChild(svgText);
		}
	} else {
		QByteArray bytes;
		QBuffer buffer(&bytes);
		mImage->save(&buffer, "PNG");
		buffer.close();
		const QDomText text = target.ownerDocument().createTextNode(bytes.toBase64());
		target.appendChild(text);
	}
}

bool Image::isValid() const
{
	return !mPath.isEmpty() && (!mSvgRenderer.isNull() || !mImage->isNull());
}

QSize Image::preferedSize() const
{
	return mIsSvg ? preferedSvgSize() : mImage->size();
}

QSize Image::preferedSvgSize() const
{
	const QSize svgSize = mSvgRenderer->defaultSize();
	const quint64 maxDimension = qMax(svgSize.width(), svgSize.height());
	if (maxDimension <= maxSvgSize) {
		return svgSize;
	}

	// SVG viewbox may be too large. Cropping it here.
	return QSize(svgSize.width() * maxSvgSize / maxDimension, svgSize.height() * maxSvgSize / maxDimension);
}

bool Image::external() const
{
	return mExternal;
}

void Image::setExternal(bool external)
{
	mExternal = external;
}

QString Image::path() const
{
	return mPath;
}

void Image::loadFrom(const QString &path)
{
	mPath = path;
	mIsSvg = path.endsWith(".svg");
	mImage.reset();
	mSvgRenderer.reset();
	if (mIsSvg) {
		mSvgRenderer.reset(new QSvgRenderer(path));
	} else {
		mImage.reset(new QImage(path));
	}
}

void Image::draw(QPainter &painter, const QRect &rect, qreal zoom) const
{
	if (mExternal && !mPath.isEmpty()) {
		mImagesCache->drawImageWithoutCachingSize(mPath, painter, rect, zoom);
	} else if (mIsSvg) {
		mSvgRenderer->render(&painter, rect);
	} else if (!mImage.isNull()) {
		painter.drawImage(rect, *mImage);
	} else {
		painter.save();
		painter.setBrush(Qt::gray);
		painter.setPen(Qt::gray);
		painter.drawRect(rect);
		painter.restore();
	}
}

QString Image::imageId() const
{
	return mImageId;
}
