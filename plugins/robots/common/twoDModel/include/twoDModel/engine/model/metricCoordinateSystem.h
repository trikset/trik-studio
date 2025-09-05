/* Copyright 2025 CyberTech Labs Ltd.
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
#include <QObject>
#include <QPointer>
#include <qrutils/graphicsUtils/abstractCoordinateSystem.h>

namespace twoDModel {

namespace model {

class SizeUnit;

/// The metric system, which is an implementation of the qrutils
/// AbstractCoordinateSystem interface for using the metric system in 2D model items
class MetricCoordinateSystem: public graphicsUtils::AbstractCoordinateSystem
{
	Q_OBJECT
public:
	explicit MetricCoordinateSystem(twoDModel::model::SizeUnit *metricSystem,
					QObject* parent = nullptr);

	~MetricCoordinateSystem();

	/// Conversе of units of measurement into pixels
	qreal toPx(const qreal size) const override;

	/// Conversе of QPointF into pixels
	QPointF toPx(const QPointF &size) const override;

	/// Converting pixels to units of measurement
	qreal toUnit(const qreal size) const override;

	/// Converting pixels to QPointF
	QPointF toUnit(const QPointF &size) const override;
private:
	// Doesn't take ownership, ownership is twoDModel::model::Settings.
	// The lifetime of this object is greater than MetricCoordinateSystem (see Model.h)
	QPointer<twoDModel::model::SizeUnit> mMetricSystem;
};

}
}
