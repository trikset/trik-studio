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
constexpr auto pixelMaximumValue = 50;
}

PopupMetricWidget::~PopupMetricWidget() = default;

PopupMetricWidget::PopupMetricWidget(QWidget *parent): StackMetricWidget(parent)
{
	auto createSpinBoxLambda = [this](qreal step, int decimals, twoDModel::model::SizeUnit unit) {
		auto *spinBox = new QDoubleSpinBox(this);
		addWidget(spinBox, unit, pixelMinimalValue, pixelMaximumValue, step, decimals);
		connect(spinBox, QOverload<qreal>::of(&QDoubleSpinBox::valueChanged), this, [=](qreal value) {
			const auto pxValue = value * countFactor();
			if (qAbs(mCurrentValuePx - pxValue) >= epsilon103) {
				mCurrentValuePx = pxValue;
				Q_EMIT valueChanged(mCurrentValuePx);
			}
		});
	};

	createSpinBoxLambda(1, 0, twoDModel::model::SizeUnit::Unit::Pixels);
	createSpinBoxLambda(1, 0, twoDModel::model::SizeUnit::Unit::Millimeters);
	createSpinBoxLambda(0.1, 1, twoDModel::model::SizeUnit::Unit::Centimeters);
	createSpinBoxLambda(0.05, 2, twoDModel::model::SizeUnit::Unit::Meters);
}

void PopupMetricWidget::setCurrentValue(qreal currentValuePx)
{
	mCurrentValuePx = currentValuePx;
	sizeUnitHandler(currentWidget());
}

void PopupMetricWidget::sizeUnitHandler(QWidget *currentWidget)
{
	if (!currentWidget) {
		return;
	}

	currentWidget->setProperty("value", mCurrentValuePx / countFactor());
}
