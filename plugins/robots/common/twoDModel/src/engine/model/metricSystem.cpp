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

#include <QtXml/QDomElement>

#include "twoDModel/engine/model/metricSystem.h"

using namespace twoDModel::model;

namespace {
	/// Translation of a string representation into a unit
	static SizeUnit::Unit stringToUnit(const QString &unit) {
		if (unit.isEmpty()) {
			return SizeUnit::Unit::Pixels;
		}
		if (unit == "cm") {
			return SizeUnit::Unit::Centimeters;
		}
		if (unit == "mm") {
			return SizeUnit::Unit::Millimeters;
		}
		if (unit == "m") {
			return SizeUnit::Unit::Meters;
		}
		return SizeUnit::Unit::Pixels;
	}

	/// Translation of a unit into a string representation
	static QString unitToString(const SizeUnit::Unit &unit) {
		if (unit == SizeUnit::Unit::Centimeters) {
			return "cm";
		}
		if (unit == SizeUnit::Unit::Millimeters) {
			return "mm";
		}
		if (unit == SizeUnit::Unit::Meters) {
			return "m";
		}
		return {};
	}
}

qreal SizeUnit::pixelsInCm() const
{
	return mPixelsInCm;
}


void SizeUnit::serialize(QDomElement &parent) const
{
	if (mSizeUnit != Unit::Pixels) {
		parent.setAttribute("sizeUnit", unitToString(mSizeUnit));
	}
}

void SizeUnit::deserialize(const QDomElement &parent)
{
	if (!parent.isNull()) {
		setUnit(stringToUnit(parent.attribute("sizeUnit", "")));
	} else {
		setUnit(defaultUnit());
	}
	emit sizeUnitChanged(mSizeUnit);
}

void SizeUnit::setUnit(const Unit &unit)
{
	mSizeUnit = unit;
}

qreal SizeUnit::countFactor() const
{
	if (mSizeUnit == Unit::Meters) {
		return mPixelsInCm * 100.0f;
	}
	if (mSizeUnit == Unit::Millimeters) {
		return mPixelsInCm * 0.1f;
	}
	if (mSizeUnit == Unit::Centimeters) {
		return mPixelsInCm;
	}
	return 1.0f;
}

qreal SizeUnit::toPx(const qreal size) const
{
	if (mSizeUnit == Unit::Meters) {
		return size * mPixelsInCm * 100.0f;
	}
	if (mSizeUnit == Unit::Millimeters) {
		return size * mPixelsInCm * 0.1f;
	}
	if (mSizeUnit == Unit::Centimeters) {
		return size * mPixelsInCm;
	}
	return size;
}

std::map<QString, SizeUnit::Unit> SizeUnit::currentValues() const
{
	return {
		{"Pixels", Unit::Pixels }
		, {"Centimeters", Unit::Centimeters}
		, {"Meters", Unit::Meters}
		, {"Millimeters", Unit::Millimeters}
	};
}

SizeUnit::Unit SizeUnit::defaultUnit() const {
	return Unit::Pixels;
}
