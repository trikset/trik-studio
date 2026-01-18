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

#include <QtCore/QObject>
#include "constants.h"
#include "twoDModel/twoDModelDeclSpec.h"

class QDomElement;

namespace twoDModel {
namespace model {

/// Incapsulates size unit settings used by 2D model.
class TWO_D_MODEL_EXPORT SizeUnit
{
public:
	/// Possible units of measurement
	enum class Unit {
		Pixels
		, Centimeters
		, Meters
		, Millimeters
	};

	SizeUnit() = default;

	/// The current pixel value in centimeters
	qreal pixelsInCm() const;

	twoDModel::model::SizeUnit::Unit unit() const;

	/// Serialize the sizeUnit in the WorldModel
	void serialize(QDomElement &parent) const;

	/// Derialize the sizeUnit in the WorldModel
	void deserialize(const QDomElement &parent);

	/// Set the current unit of measurement
	void setSizeUnit(twoDModel::model::SizeUnit::Unit unit);

	/// Multiplier for conversion to pixels
	qreal countFactor() const;

	/// Convert size from WorldModel to pixels
	qreal toPx(const qreal size) const;

	/// Get current unit string representation
	QString toStr() const;

	static std::map<QString, Unit> currentValues();

	static Unit defaultUnit();
private:
	Unit mSizeUnit { Unit::Pixels };
	qreal mPixelsInCm { twoDModel::pixelsInCm };
};

}
}

Q_DECLARE_METATYPE(twoDModel::model::SizeUnit::Unit)
