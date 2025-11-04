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

#include "twoDModel/engine/model/colorDetector.h"

using namespace twoDModel::model;

namespace {
	using ColorCode = ColorDetector::ColorCode;
	struct ColorRange {
	    uint16_t hueMin;
	    uint16_t hueMax;
	    uint8_t satMin;
	    uint8_t satMax;
	    uint8_t valMin;
	    uint8_t valMax;
	    ColorCode code;

	    constexpr ColorCode match(uint16_t hue, uint8_t sat, uint8_t val) const noexcept {
		if (val < valMin || val > valMax) {
			return ColorCode::Unknown;
		}

		if (sat < satMin || sat > satMax) {
			return ColorCode::Unknown;
		}

		if (code == ColorCode::Black || code == ColorCode::White) {
		    return code;
		}

		const auto hueOk = (hueMin <= hueMax)
		    ? (hue >= hueMin && hue <= hueMax)
		    : (hue >= hueMin || hue <= hueMax);

		return hueOk ? code : ColorCode::Unknown;
	    }
	};

	constexpr ColorRange sColorTable[] = {
	    {   0,    0,    0, 255, 0,   90,  ColorCode::Black   },
	    {   0,    0,    0, 25,  200, 255, ColorCode::White   },
	    { 342,   18,  200, 255, 200, 255, ColorCode::Red     },
	    {  15,   45,  200, 255, 130, 180, ColorCode::Brown   },
	    {  42,   78,  200, 255, 200, 255, ColorCode::Yellow  },
	    { 102,  138,  180, 255, 200, 255, ColorCode::Green   },
	    { 162,  198,  200, 255, 200, 255, ColorCode::Cyan    },
	    { 222,  258,  200, 255, 200, 255, ColorCode::Blue    },
	    { 282,  318,  200, 255, 200, 255, ColorCode::Magenta }
	};

}

ColorDetector::ColorCode ColorDetector::detect(uint16_t hue, uint8_t sat, uint8_t val) noexcept {
	for (auto &&range : sColorTable) {
	    const auto code = range.match(hue, sat, val);
	    if (code != ColorCode::Unknown) {
		return code;
	    }
	}
	return ColorCode::Unknown;
}
