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
#include "stackMetricWidget.h"
#include <cmath>

using namespace twoDModel::view;

StackMetricWidget::StackMetricWidget(QWidget *parent)
	: QWidget(parent)
	, mStackedWidget(new QStackedWidget(this))
	, mUnit(nullptr)
{
	auto *layout = new QHBoxLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(mStackedWidget);
}

StackMetricWidget::~StackMetricWidget() = default;

void StackMetricWidget::addWidget(QWidget *widget, twoDModel::model::SizeUnit sizeUnit,
				     qreal rangeMinimum, qreal rangeMaximum, qreal step, qreal decimals)
{
	const auto displayMin = rangeMinimum / sizeUnit.countFactor();
	const auto displayMax = rangeMaximum / sizeUnit.countFactor();
	widget->setProperty("minimum", displayMin);
	widget->setProperty("maximum", displayMax);
	widget->setProperty("suffix", " " + sizeUnit.toStr());
	widget->setProperty("singleStep", step);
	widget->setProperty("decimals", decimals);

	mSlubWidgets.emplace(sizeUnit.unit(), widget);
	mStackedWidget->addWidget(widget);
}

QWidget *StackMetricWidget::currentWidget() const
{
	return mStackedWidget->currentWidget();
}

qreal StackMetricWidget::countFactor() const
{
	return mUnit ? mUnit->countFactor() : 1.0f;
}

void StackMetricWidget::onSizeUnitChanged(const QSharedPointer<twoDModel::model::SizeUnit> &unit)
{
	blockSignals(true);
	mUnit = unit;
	const auto it = mSlubWidgets.find(mUnit->unit());
	if (it != mSlubWidgets.end() && it->second != mStackedWidget->currentWidget()) {
	    mStackedWidget->setCurrentWidget(it->second);
	    sizeUnitHandler(it->second);
	}

	blockSignals(false);
}
