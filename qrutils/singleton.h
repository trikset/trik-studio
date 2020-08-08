/* Copyright 2016 CyberTech Labs Ltd.
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

#include <QMutex>
#include <QSharedPointer>

#pragma once

namespace utils {

/// Instantiates and provides to all callers single instance of the some type.
template<typename T>
class Singleton
{
public:
	/// Creates single instance of some type (given in class template) if it does not exist and returns it.
	static QSharedPointer<T> instance()
	{
		static QMutex m;
		QMutexLocker lock(&m);
		static QWeakPointer<T> instance;
		if (auto result = instance.lock()) {
			return result;
		} else {
			result = QSharedPointer<T>(new T());
			instance = result;
			return result;
		}
	}
};

}
