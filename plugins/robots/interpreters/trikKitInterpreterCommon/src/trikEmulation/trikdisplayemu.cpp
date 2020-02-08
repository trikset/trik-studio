/* Copyright 2016-2017 CyberTech Labs Ltd.
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

#include <trikKitInterpreterCommon/trikEmulation/trikdisplayemu.h>

#include <kitBase/robotModel/robotModelUtils.h>
///todo:
#include <trikKitInterpreterCommon/robotModel/twoD/parts/twoDDisplay.h>

using namespace trik;
using robotModel::twoD::parts::Display;

TrikDisplayEmu::TrikDisplayEmu(const QSharedPointer<robotModel::twoD::TrikTwoDRobotModel> &model)
	: mTwoDRobotModel(model), mDisplay(nullptr)
{
}

Qt::ConnectionType TrikDisplayEmu::callType() const {
	return Qt::AutoConnection;
	// Very strange, but forced blocking connection causes SIGSEGV crash....
	// return thread() != mDisplay->thread()? Qt::BlockingQueuedConnection : Qt::DirectConnection;
}

trikControl::DisplayWidgetInterface &TrikDisplayEmu::graphicsWidget()
{
	return mDisplayWidgetInterface;
}

void TrikDisplayEmu::init()
{
	mDisplay = kitBase::robotModel::RobotModelUtils::findDevice<Display>(*mTwoDRobotModel, "DisplayPort");
}

void TrikDisplayEmu::showImage(const QString &fileName)
{
	const bool smile = fileName.endsWith(QLatin1String("sad.png"));
	QMetaObject::invokeMethod(mDisplay, [=](){ mDisplay->drawSmile(smile); }, callType());
}

void TrikDisplayEmu::show(const QVector<int32_t> &array, int width, int height, const QString &format)
{
	QMetaObject::invokeMethod(mDisplay, [=](){ mDisplay->show(array, width, height, format); }, callType());
}

void TrikDisplayEmu::addLabel(const QString &text, int x, int y)
{
	QMetaObject::invokeMethod(mDisplay, [=](){ mDisplay->printText(x, y, text); }, callType());
}

void TrikDisplayEmu::setPainterColor(const QString &color)
{
	QMetaObject::invokeMethod(mDisplay, [=](){ mDisplay->setPainterColor(color); }, callType());
}

void TrikDisplayEmu::setPainterWidth(int penWidth)
{
	QMetaObject::invokeMethod(mDisplay,[=](){ mDisplay->setPainterWidth(penWidth); }, callType());
}

void TrikDisplayEmu::drawLine(int x1, int y1, int x2, int y2)
{
	QMetaObject::invokeMethod(mDisplay, [=](){ mDisplay->drawLine(x1, y1, x2, y2); }, callType());
}

void TrikDisplayEmu::drawPoint(int x, int y)
{
	QMetaObject::invokeMethod(mDisplay, [=]() { mDisplay->drawPixel(x, y); }, callType());
}

void TrikDisplayEmu::drawRect(int x, int y, int w, int h, bool filled)
{
	QMetaObject::invokeMethod(mDisplay, [=](){ mDisplay->drawRect(x, y, w, h, filled); }, callType());
}

void TrikDisplayEmu::drawEllipse(int x, int y, int w, int h, bool filled)
{
	QMetaObject::invokeMethod(mDisplay, [=](){ mDisplay->drawEllipse(x, y, w, h, filled); }, callType());
}

void TrikDisplayEmu::drawArc(int x, int y, int w, int h, int start, int span)
{
	QMetaObject::invokeMethod(mDisplay, [=]() { mDisplay->drawArc(x, y, w, h, start, span); },  callType());
}

void TrikDisplayEmu::setBackground(const QString &color)
{
	QMetaObject::invokeMethod(mDisplay, [=](){ mDisplay->setBackground(color); }, callType());
}

void TrikDisplayEmu::clear()
{
	QMetaObject::invokeMethod(mDisplay, &Display::clearScreen, callType());
}

void TrikDisplayEmu::reset()
{
	QMetaObject::invokeMethod(mDisplay, &Display::reset, callType());
}

void TrikDisplayEmu::redraw()
{
	QMetaObject::invokeMethod(mDisplay, &Display::redraw,  callType());
}
