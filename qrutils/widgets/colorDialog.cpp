/* Copyright 2026 CyberTech Labs Ltd.
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

#include "colorDialog.h"
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStyle>
#include <QColorDialog>
#include <qrkernel/settingsManager.h>
#include <qrkernel/settingsListener.h>

using namespace qReal::ui;

QPixmap ColorDialog::getColorPixMap() const
{
	QPixmap pixmap(16, 16);
	pixmap.fill(mSavedColor);
	return pixmap;
}

ColorDialog::ColorDialog(QWidget *parent)
	: QWidget(parent)
{
	auto *button = new QPushButton(getColorPixMap(), tr("Select background color in the 2D-model editor..."), this);
	button->setObjectName("colorButton");
	auto *layout = new QHBoxLayout(this);
	layout->addWidget(button);
	connect(button, &QPushButton::clicked, this, &ColorDialog::chooseColor);
}

void ColorDialog::configure(const QString &settingsKey)
{
	mSettingsKey = settingsKey;
	qReal::SettingsListener::listen(mSettingsKey, [this](const QColor &color) {  setColor(color); }, this);
}

void ColorDialog::save()
{
	if (!mSettingsKey.isEmpty()) {
		setColor(mSavedColor);
		SettingsManager::setValue(mSettingsKey, mSavedColor);
	}
}

void ColorDialog::restore()
{
	if (!mSettingsKey.isEmpty()) {
		const auto& value = SettingsManager::value(mSettingsKey);
		if (value.canConvert<QColor>()) {
			mSavedColor = value.value<QColor>();
		}
	}
}

void ColorDialog::setColor(const QColor &color)
{
	mSavedColor = color;
	if (auto *button = findChild<QPushButton *>("colorButton")) {
		button->setIcon(QIcon(getColorPixMap()));
	}
}

void ColorDialog::chooseColor()
{
	const auto &chosenColor = QColorDialog::getColor(mSavedColor, this, tr("Select the background color of the scene"));

	if (chosenColor.isValid()) {
		mSavedColor = chosenColor;
	}
}
