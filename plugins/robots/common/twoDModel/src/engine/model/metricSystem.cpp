#include <QtXml/QDomElement>

#include "twoDModel/engine/model/metricSystem.h"

using namespace twoDModel::model;

namespace {
        /// Translation of a string representation into a unit
        static MetricSystem::Unit stringToUnit(const QString &unit) {
		if (unit.isEmpty()) {
			return MetricSystem::Unit::Pixels;
		}
		if (unit == "cm") {
			return MetricSystem::Unit::Centimeters;
		}
		if (unit == "mm") {
			return MetricSystem::Unit::Millimeters;
		}
		if (unit == "m") {
			return MetricSystem::Unit::Meters;
		}
		return MetricSystem::Unit::Pixels;
	}

	/// Translation of a unit into a string representation
	static QString unitToString(const MetricSystem::Unit &unit) {
		if (unit == MetricSystem::Unit::Centimeters) {
			return "cm";
		}
		if (unit == MetricSystem::Unit::Millimeters) {
			return "mm";
		}
		if (unit == MetricSystem::Unit::Meters) {
			return "m";
		}
		return {};
	}
}

qreal MetricSystem::pixelsInCm() const
{
	return mPixelsInCm;
}


void MetricSystem::serialize(QDomElement &parent) const
{
	if (mMetricUnit != Unit::Pixels) {
		parent.setAttribute("metricUnit", unitToString(mMetricUnit));
	}
}

void MetricSystem::deserialize(const QDomElement &parent)
{
	if (!parent.isNull()) {
		setUnit(stringToUnit(parent.attribute("metricUnit", "")));
	}

	emit metricUnitChanged(mMetricUnit);
}

void MetricSystem::setUnit(const Unit &unit)
{
	mMetricUnit = unit;
}

qreal MetricSystem::countFactor() const
{
	if (mMetricUnit == Unit::Meters) {
		return mPixelsInCm * 100.0f;
	}
	if (mMetricUnit == Unit::Millimeters) {
		return mPixelsInCm * 0.1f;
	}
	if (mMetricUnit == Unit::Centimeters) {
		return mPixelsInCm;
	}
	return 1.0f;
}

qreal MetricSystem::toPx(const qreal size) const
{
	if (mMetricUnit == Unit::Meters) {
		return size * mPixelsInCm * 100.0f;
	}
	if (mMetricUnit == Unit::Millimeters) {
		return size * mPixelsInCm * 0.1f;
	}
	if (mMetricUnit == Unit::Centimeters) {
		return size * mPixelsInCm;
	}
	return size;
}

std::map<QString, MetricSystem::Unit> MetricSystem::currentValues() const
{
	return {
		{"Pixels", Unit::Pixels }
		, {"Centimeters", Unit::Centimeters}
		, {"Meters", Unit::Meters}
		, {"Millimeters", Unit::Millimeters}
	};
}
