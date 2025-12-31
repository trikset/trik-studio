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
#include <utility>

template<typename T>
class ItemProperty final
{
	Q_DISABLE_COPY_MOVE(ItemProperty)
public:
	explicit ItemProperty(QString name, const T& value)
		: mName(std::move(name)), mValue(value), mWasChanged(false) {}

	ItemProperty() = default;
	operator T() const & { return mValue; } // NOLINT(google-explicit-constructor)

	QString name() const { return mName; }

	bool wasChanged() const { return mWasChanged; }

	void setValue(const T& value) { mValue = value; }

	void changeValue(const T& value) {
		setValue(value);
		mWasChanged = true;
	}

private:
	QString mName;
	T mValue;
	bool mWasChanged {};
};
