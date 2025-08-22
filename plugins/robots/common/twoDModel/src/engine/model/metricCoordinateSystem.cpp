/* Copyright 2025 QReal Research Group
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
		twoDModel::model::SizeUnit &metricSystem)
	: mMetricSystem(metricSystem)
{
}

MetricCoordinateSystem::~MetricCoordinateSystem()
{
}

qreal MetricCoordinateSystem::toPx(const qreal size) const
{
	return mMetricSystem.toPx(size);
}

qreal MetricCoordinateSystem::toUnit(const qreal size) const
{
	auto result = size / mMetricSystem.countFactor();
	/// todo: move round to WorldModel settings
	return std::round(result * 1000.0f) / 1000.0f;
}

QPointF MetricCoordinateSystem::toUnit(const QPointF &size) const
{
	auto xResult = size.x() / mMetricSystem.countFactor();
	auto yResult = size.y() / mMetricSystem.countFactor();
	/// todo: move round to WorldModel settings
	return {std::round(xResult * 1000.0f) / 1000.0f,
		std::round(yResult * 1000.0f) / 1000.0f};
}

twoDModel::model::SizeUnit &MetricCoordinateSystem::metricSystem() {
	return mMetricSystem;
}

QPointF MetricCoordinateSystem::toPx(const QPointF &size) const
{
	return QPointF{mMetricSystem.toPx(size.x()),
		                mMetricSystem.toPx(size.y())};
}
