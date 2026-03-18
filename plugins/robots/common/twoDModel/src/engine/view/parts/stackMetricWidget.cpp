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

StackMetricWidget::~StackMetricWidget() = default;

StackMetricWidget::StackMetricWidget(qreal rangeMinimum, qreal rangeMaximum, QWidget *parent)
	: QWidget(parent)
	, mStackedWidget(new QStackedWidget(this))
	, mUnit(nullptr)
	, mRangeMinimum(rangeMinimum)
	, mRangeMaximum(rangeMaximum)
{
	setupUI();
}

void StackMetricWidget::init()
{
	createSpinBoxes();
}

void StackMetricWidget::updateValues(QObject *spinBox, twoDModel::model::SizeUnit sizeUnit,qreal step) const {
	const auto displayMin = mRangeMinimum / sizeUnit.countFactor();
	const auto displayMax = mRangeMaximum / sizeUnit.countFactor();
	spinBox->setProperty("minimum", displayMin);
	spinBox->setProperty("maximum", displayMax);
	spinBox->setProperty("suffix", " " +sizeUnit.toStr());
	spinBox->setProperty("singleStep", step);
}

void StackMetricWidget::setupUI()
{
	auto *layout = new QHBoxLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(mStackedWidget);
}

qreal StackMetricWidget::countFactor()
{
	return mUnit ? mUnit->countFactor() : 1.0f;
}

void StackMetricWidget::onSizeUnitChanged(const QSharedPointer<twoDModel::model::SizeUnit> &unit)
{
	blockSignals(true);
	mUnit = unit;
	const auto it = mSlubSpinBoxes.find(mUnit->unit());
	if (it != mSlubSpinBoxes.end() && it->second != mStackedWidget->currentWidget()) {
	    mStackedWidget->setCurrentWidget(it->second);
	    setValue(it->second);
	}
	blockSignals(false);
}
