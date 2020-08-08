/* Copyright 2015 CyberTech Labs Ltd.
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

#include "utils/canvas/textObject.h"

#include <QtCore/QJsonObject>
#include <QtGui/QPainter>

using namespace utils;

const int maxScreenSize = 320;

TextObject::TextObject(QObject *parent)
	: CanvasObject(parent)
	, mX(0)
	, mY(0)
{
}

TextObject::TextObject(int x, int y, const QString &text
					   , const QColor &color, int thickness, int fontSize, QObject *parent)
	: CanvasObject(color, thickness, parent)
	, mX(x)
	, mY(y)
	, mText(text)
	, mFontSize(fontSize)
{
}

int TextObject::x() const
{
	return mX;
}

void TextObject::setX(int x)
{
	mX = x;
}

int TextObject::y() const
{
	return mY;
}

void TextObject::setY(int y)
{
	mY = y;
}

QPoint TextObject::pos() const
{
	return QPoint(mX, mY);
}

QString TextObject::text() const
{
	return mText;
}

int TextObject::fontSize() const
{
	return mFontSize;
}

void TextObject::setText(const QString &text)
{
	mText = text;
}

void TextObject::setFontSize(int fontSize)
{
	mFontSize = fontSize;
}

void TextObject::paint(QPainter *painter, const QRect &outputRect)
{
	CanvasObject::paint(painter, outputRect);
	painter->setPen(Qt::black);
	if (mFontSize > 0) {
		QFont font;
		font.setPixelSize(mFontSize);
		painter->setFont(font);
	}
	painter->drawText(QRectF(mX, mY, maxScreenSize, maxScreenSize), Qt::AlignLeft | Qt::AlignTop, mText);
}

QJsonObject TextObject::toJson() const
{
	QJsonObject result;
	result["type"] = "text";
	result["x"] = x();
	result["y"] = y();
	result["text"] = text();
	result["color"] = color().name();
	result["thickness"] = thickness();
	result["fontSize"] = fontSize();
	return result;
}
