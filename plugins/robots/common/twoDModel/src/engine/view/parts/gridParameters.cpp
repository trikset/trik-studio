/* Copyright 2012-2015 QReal Research Group, Dmitry Chernov, Dmitry Mordvinov
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

#include "gridParameters.h"
#include <QtWidgets/QHBoxLayout>
#include <QtCore/QString>
#include "twoDModel/engine/model/metricSystem.h"
#include <qrkernel/settingsManager.h>

using namespace twoDModel::view;

namespace {
	constexpr auto minLE = 10;
	constexpr auto maxLE = 150;
	constexpr auto scale = 10000.0f;
}

GridParameters::GridParameters(QWidget *parent)
	: QFrame(parent)
{
	auto *layout = new QHBoxLayout(this);
	mShowGridCheckBox = new QCheckBox(this);
	mShowGridCheckBox->setText(tr("Grid"));
	mShowGridCheckBox->setTristate(false);
	mCellSize = new QSlider(this);
	mCellSize->setOrientation(Qt::Horizontal);
	mCellSize->setMinimum(minLE * scale);
	mCellSize->setMaximum(maxLE * scale);
	mCellSize->setSingleStep(0.1 * scale);
	mCellSize->setPageStep(scale);
	mCellSize->setEnabled(false);

	layout->addWidget(mShowGridCheckBox);
	layout->addWidget(mCellSize);
	layout->setContentsMargins(5, 5, 5, 5);

	connect(mShowGridCheckBox, &QAbstractButton::toggled, mCellSize, &QWidget::setEnabled);
	connect(mShowGridCheckBox, &QAbstractButton::toggled, this, &GridParameters::showGrid);
	connect(mCellSize, &QAbstractSlider::valueChanged, this, &GridParameters::setCellSize);

	const bool showGrid = qReal::SettingsManager::value("2dShowGrid").toBool();
	const qreal gridSize = qReal::SettingsManager::value("2dDefaultGridCellSize").toReal();
	mShowGridCheckBox->setChecked(showGrid);
	mCellSize->setValue(qRound(gridSize * scale));
	setLayout(layout);

	// Bring the slider values closer to the step values (which should ideally be 0.1 of the unit of measurement)
	connect(mCellSize, &QSlider::sliderMoved, this, [this](int rawValue) {
		const auto step = mCellSize->singleStep();
		const auto snapped = qRound(static_cast<double>(rawValue) / step) * step;
		if (snapped != rawValue) {
			mCellSize->setValue(snapped);
		}
	});
}

void GridParameters::onSizeUnitChanged(const QSharedPointer<twoDModel::model::SizeUnit> &unit)
{
	mSizeUnit = unit;
	mCellSize->blockSignals(true);
	const auto factor = unit->countFactor();
	// We adapt the slider to the coordinate system in such a way as to cover the desired range of values.
	// Thus, with the selected millimeters, the range will be from 35000 to 525000, which corresponds
	// to the size of the cell from 35 mm to 525 and allows you to set its size with an accuracy
	// of a thousandth of a millimeter. mCellSize->setSingleStep(0.1 * scale) means that for the selected system,
	// the step will be 1000 units. In other words, 0.1 of the selected measurement system
	mCellSize->setMinimum(qRound((minLE / factor) * scale));
	mCellSize->setMaximum(qRound((maxLE / factor) * scale));
	const qreal currentGlobal = qReal::SettingsManager::value("2dDoubleGridCellSize").toReal();
	mCellSize->setValue(qRound((currentGlobal / factor) * scale));
	mCellSize->blockSignals(false);
}

void GridParameters::onGridParametersChangedOutside(qreal newCellSize)
{
	mCellSize->setValue(qRound(newCellSize * scale));
}

GridParameters::~GridParameters() = default;

void GridParameters::showGrid(bool isGridEnabled)
{
	qReal::SettingsManager::setValue("2dShowGrid", isGridEnabled);
	Q_EMIT parametersChanged();
}

void GridParameters::setCellSize(int cellSizeValue)
{
	const auto factor = mSizeUnit ? mSizeUnit->countFactor() : 1.0;
	const auto unitsValue = static_cast<qreal>(cellSizeValue) * factor / scale;
	qReal::SettingsManager::setValue("2dDoubleGridCellSize", unitsValue);
	Q_EMIT parametersChanged();
}
