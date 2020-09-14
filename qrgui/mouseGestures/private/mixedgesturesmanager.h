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

#include "abstractRecognizer.h"
#include "geometricForms.h"

namespace qReal {
namespace gestures {

class MixedGesturesManager : public GesturesRecognizer<QPair<QVector<qreal>, QVector<qreal>>>
{
public:
	MixedGesturesManager();
	~MixedGesturesManager() override;

	qreal getMaxDistance(const QString &) override;
	bool isMultistroke() override;

	qreal getDistance(QString const &item) override
	{
		const auto key = mGestures[item];
		return getDistance(mKey, key);
	}

	qreal getDistance(const key_type &key1, const key_type &key2) override;
	key_type  getKey(const PathVector &path) override;
};

class MixedClassifier
{
public:
	MixedClassifier() = default;
	MixedClassifier(const MixedClassifier &) = delete;
	MixedClassifier(MixedClassifier &&) = default;
	explicit MixedClassifier(const PathVector &path);
	~MixedClassifier();

	qreal getDistance(const MixedClassifier &classifier);
	MixedClassifier getPoint(const MixedClassifier &centre, qreal centreWeight);
	MixedGesturesManager::key_type  key() const;

private:
	explicit MixedClassifier(MixedGesturesManager::key_type &&key);

	MixedGesturesManager::key_type mKey;
};

}
}
