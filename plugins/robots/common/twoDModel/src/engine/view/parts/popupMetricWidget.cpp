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

#include <QHBoxLayout>
#include <QStackedWidget>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <qrkernel/settingsManager.h>
#include "popupMetricWidget.h"
#include <cmath>

using namespace twoDModel::view;

namespace {
constexpr auto pixelMinimalValue = 1;
constexpr auto pixelMaximumValue = 30;
constexpr auto epsilon = 0.001;
}

PopupMetricWidget::~PopupMetricWidget() = default;

PopupMetricWidget::PopupMetricWidget(QWidget *parent)
	: StackMetricWidget(pixelMinimalValue, pixelMaximumValue, parent)
{}

void PopupMetricWidget::setCurrentValue(int currentValuePx)
{
	mCurrentValuePx = currentValuePx;
}

void PopupMetricWidget::createSpinBoxes()
{
	auto createSpinBoxLambda = [this](qreal step, int decimals,
				twoDModel::model::SizeUnit::Unit unit) {
		twoDModel::model::SizeUnit sizeUnit {};
		sizeUnit.setSizeUnit(unit);
		auto *spinBox = new QDoubleSpinBox(this);
		updateValues(spinBox, sizeUnit, step);
		spinBox->setDecimals(decimals);
		mSlubSpinBoxes.emplace(unit, spinBox);
		mStackedWidget->addWidget(spinBox);
		connect(spinBox, QOverload<qreal>::of(&QDoubleSpinBox::valueChanged), this, [=](qreal value) {
			const auto pxValue = value * countFactor();
			if (qAbs(mCurrentValuePx - pxValue) >= epsilon) {
				mCurrentValuePx = pxValue;
				Q_EMIT valueChanged(static_cast<int>(mCurrentValuePx));
			}
		});
	};

	// Create custom Pixels SpinBox
	createSpinBoxLambda(1, 0, twoDModel::model::SizeUnit::Unit::Pixels);
	// Create custom Millimiter SpinBox
	createSpinBoxLambda(1, 0, twoDModel::model::SizeUnit::Unit::Millimeters);
	// Create custom Centimeter SpinBox
	createSpinBoxLambda(0.1, 2, twoDModel::model::SizeUnit::Unit::Centimeters);
	// Create custom Meter SpinBox
	createSpinBoxLambda(0.05, 3, twoDModel::model::SizeUnit::Unit::Meters);

	mStackedWidget->setCurrentWidget(mSlubSpinBoxes[twoDModel::model::SizeUnit::defaultUnit()]);
}

void PopupMetricWidget::setValue(QObject *currentSpinBox)
{
	if (!currentSpinBox) {
		return;
	}
	currentSpinBox->setProperty("value", mCurrentValuePx / countFactor());
}
