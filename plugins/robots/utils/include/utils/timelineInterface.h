/* Copyright 2007-2015 QReal Research Group
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

#include <QtCore/QtGlobal>

namespace utils {

class AbstractTimer;

/// An interface for all objects that may measure time
class TimelineInterface
{
	Q_DISABLE_COPY(TimelineInterface)
public:
	TimelineInterface() = default;
	virtual ~TimelineInterface() = default;

	/// Returns time in ms passed from some point (no matter what point).
	virtual quint64 timestamp() const = 0;

	/// Creates new timer for specific implementation. Transfers ownership.
	virtual AbstractTimer *produceTimer() = 0;
};

}
