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
#include "gridSizeWidget.h"
#include <cmath>

using namespace twoDModel::view;

namespace {
constexpr auto pixelMinimalValue = 10.0;
constexpr auto pixelMaximumValue = 150.0;
}

GridSizeWidget::~GridSizeWidget() = default;

GridSizeWidget::GridSizeWidget(QWidget *parent)
	: QWidget(parent)
	, mUnit(nullptr)
	, mStackedWidget(new QStackedWidget(this))
{
	setupUI();
	createSpinBoxes();
}

void GridSizeWidget::createSpinBoxes()
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
		connect(spinBox, QOverload<qreal>::of(&QDoubleSpinBox::valueChanged),
						this, &GridSizeWidget::gridSizeChanged);
	};

	// Create custom Pixels SpinBox
	createSpinBoxLambda(0.1, 3, twoDModel::model::SizeUnit::Unit::Pixels);
	// Create custom Millimiter SpinBox
	createSpinBoxLambda(0.1, 3, twoDModel::model::SizeUnit::Unit::Millimeters);
	// Create custom Centimeter SpinBox
	createSpinBoxLambda(0.1, 3, twoDModel::model::SizeUnit::Unit::Centimeters);
	// Create custom Meter SpinBox
	createSpinBoxLambda(0.05, 3, twoDModel::model::SizeUnit::Unit::Meters);

	mStackedWidget->setCurrentWidget(mSlubSpinBoxes[twoDModel::model::SizeUnit::defaultUnit()]);
}

void GridSizeWidget::updateValues(QObject *spinBox,
				  twoDModel::model::SizeUnit sizeUnit,
				  qreal step) {
	const auto displayMin = pixelMinimalValue / sizeUnit.countFactor();
	const auto displayMax = pixelMaximumValue / sizeUnit.countFactor();
	spinBox->setProperty("minimum", displayMin);
	spinBox->setProperty("maximum", displayMax);
	spinBox->setProperty("suffix", " " +sizeUnit.toStr());
	spinBox->setProperty("singleStep", step);
}

void GridSizeWidget::setupUI()
{
	auto *layout = new QHBoxLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(mStackedWidget);
}

qreal GridSizeWidget::countFactor()
{
	return mUnit ? mUnit->countFactor() : 1.0f;
}

void GridSizeWidget::onSizeUnitChanged(const QSharedPointer<twoDModel::model::SizeUnit> &unit)
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

void GridSizeWidget::onGridParameterChanged()
{
	blockSignals(true);
	setValue(mStackedWidget->currentWidget());
	blockSignals(false);
}

void GridSizeWidget::setValue(QObject *currentSpinBox)
{
	if (!currentSpinBox) {
		return;
	}
	const auto gridSize = qReal::SettingsManager::value("2dDoubleGridCellSize").toReal();
	currentSpinBox->setProperty("value", gridSize / countFactor());
}
