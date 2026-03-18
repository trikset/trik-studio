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

#pragma once
#include <QWidget>
#include <QSharedPointer>
#include "twoDModel/engine/model/metricSystem.h"
#include <unordered_map>

class QStackedWidget;

namespace twoDModel {
namespace view {

/// A class that represents a set of QDoubleSpinBox's for different units of measurement,
/// as they may require different sinlgeSterp, suffix, and other parameters.
class StackMetricWidget : public QWidget
{
	Q_OBJECT
public:
	explicit StackMetricWidget(qreal rangeMinimum, qreal rangeMaximum, QWidget *parent = nullptr);
	~StackMetricWidget() override;
	void init();
	virtual void setValue(QObject *currentSpinBox) = 0;
	virtual void createSpinBoxes() = 0;
public Q_SLOTS:
	void onSizeUnitChanged(const QSharedPointer<twoDModel::model::SizeUnit> &unit);
protected:
	qreal countFactor();
	void updateValues(QObject *spinBox, twoDModel::model::SizeUnit sizeUnit, qreal step) const;
	QStackedWidget *mStackedWidget;
	std::unordered_map<twoDModel::model::SizeUnit::Unit, QWidget *> mSlubSpinBoxes;
private:
	void setupUI();
	QSharedPointer<twoDModel::model::SizeUnit> mUnit;
	qreal mRangeMinimum {};
	qreal mRangeMaximum {};
};

}
}
