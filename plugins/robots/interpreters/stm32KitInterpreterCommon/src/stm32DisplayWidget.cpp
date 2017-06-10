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

#include "stm32KitInterpreterCommon/stm32DisplayWidget.h"
#include "ui_stm32DisplayWidget.h"

#include <qrkernel/exception/exception.h>
#include <qrkernel/logging.h>

using namespace stm32;

Stm32DisplayWidget::Stm32DisplayWidget(QWidget *parent)
	: twoDModel::engine::TwoDModelDisplayWidget(parent)
	, mUi(new Ui::Stm32DisplayWidget)
	, mBackground(":/icons/stm32_controller.png", "PNG")
{
	mUi->setupUi(this);
	resetLed();
}

Stm32DisplayWidget::~Stm32DisplayWidget()
{
	delete mUi;
}

void Stm32DisplayWidget::setPainter(qReal::ui::PainterInterface *painter)
{
	TwoDModelDisplayWidget::setPainter(painter);
	mUi->display->setPainter(painter);
}

void Stm32DisplayWidget::repaintDisplay()
{
	mUi->display->repaint();
}

int Stm32DisplayWidget::displayWidth() const
{
	return mUi->display->width();
}

int Stm32DisplayWidget::displayHeight() const
{
	return mUi->display->height();
}

bool Stm32DisplayWidget::buttonIsDown(const QString &buttonPort) const
{
	if (buttonPort == "Left") {
		return mUi->buttonLeft->isDown();
	} else if (buttonPort == "Right") {
		return mUi->buttonRight->isDown();
	} else if (buttonPort == "Up") {
		return mUi->buttonUp->isDown();
	} else if (buttonPort == "Down") {
		return mUi->buttonDown->isDown();
	} else if (buttonPort == "Enter") {
		return mUi->buttonEnter->isDown();
	} else if (buttonPort == "Esc") {
		return mUi->buttonEscape->isDown();
	} else if (buttonPort == "Power") {
		return mUi->buttonPower->isDown();
	}

	QLOG_WARN() << "Button on port" << buttonPort << "is not supported by 2d model";

	return false;
}

QColor Stm32DisplayWidget::ledColor() const
{
	return mUi->led->palette().color(QPalette::Background);
}

void Stm32DisplayWidget::setLedColor(const QColor &color)
{
	QPalette backgroundPalette(palette());
	backgroundPalette.setColor(QPalette::Background, color);
	backgroundPalette.setColor(QPalette::Base, color);
	mUi->led->setPalette(backgroundPalette);
	mUi->led->show();
}

void Stm32DisplayWidget::paintEvent(QPaintEvent *event)
{
	QWidget::paintEvent(event);
	QPainter painter(this);
	painter.drawImage(QRect(0, 0, width(), height()), mBackground);
}

void Stm32DisplayWidget::reset()
{
	TwoDModelDisplayWidget::reset();
	resetLed();
}

void Stm32DisplayWidget::resetLed()
{
	setLedColor("red");
}
