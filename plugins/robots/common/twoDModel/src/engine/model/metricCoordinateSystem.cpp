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

#include "twoDModel/engine/model/metricCoordinateSystem.h"
#include "twoDModel/engine/model/metricSystem.h"
#include <cmath>

using namespace twoDModel::model;

MetricCoordinateSystem::MetricCoordinateSystem(
		twoDModel::model::SizeUnit *metricSystem,
		QObject* parent)
	: graphicsUtils::AbstractCoordinateSystem(parent)
	,  mMetricSystem(metricSystem)
{
}

MetricCoordinateSystem::~MetricCoordinateSystem()
{
}

qreal MetricCoordinateSystem::toPx(const qreal size) const
{
	if (mMetricSystem.isNull()) {
		return size;
	}

	return mMetricSystem->toPx(size);
}

qreal MetricCoordinateSystem::toUnit(const qreal size) const
{
	if (mMetricSystem.isNull()) {
		return size;
	}

	auto result = size / mMetricSystem->countFactor();
	/// todo: move round to WorldModel settings
	return std::round(result * 10000.0f) / 10000.0f;
}

QPointF MetricCoordinateSystem::toUnit(const QPointF &size) const
{
	return {this->toUnit(size.x()), this->toUnit(size.y())};
}

QPointF MetricCoordinateSystem::toPx(const QPointF &size) const
{
	return QPointF{this->toPx(size.x()), this->toPx(size.y())};
}
