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
#include <cstdint>

namespace twoDModel {
namespace model {

class ColorDetector {
public:
	enum class ColorCode : uint8_t {
	    Unknown  = 0,
	    Black    = 1,
	    Blue     = 2,
	    Green    = 3,
	    Yellow   = 4,
	    Red      = 5,
	    White    = 6,
	    Cyan     = 7,
	    Magenta  = 8,
	    Brown    = 9,
	};

	static ColorCode detect(uint16_t hue, uint8_t sat, uint8_t val) noexcept;
};
}
}
