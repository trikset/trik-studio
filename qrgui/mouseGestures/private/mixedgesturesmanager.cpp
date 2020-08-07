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

#include "mixedgesturesmanager.h"

#include "rectanglegesturesmanager.h"
#include "nearestposgridgesturesmanager.h"
#include "keyBuilder.h"

const qreal weight1 = 0.2; //0.3: 891 0.2: 899
const qreal weight2 = 1 - weight1;

using namespace qReal::gestures;

MixedGesturesManager::MixedGesturesManager() = default;

MixedGesturesManager::~MixedGesturesManager() = default;

qreal MixedGesturesManager::getMaxDistance(const QString &)
{
	return 30;
}
bool MixedGesturesManager::isMultistroke()
{
	return true;
}

qreal MixedGesturesManager::getDistance(const key_type &key1, const key_type &key2)
{
	RectangleGesturesManager rectMan;
	NearestPosGridGesturesManager gridMan;
	qreal dist1 = rectMan.getDistance(key1.first, key2.first);
	qreal dist2 = gridMan.getDistance(key1.second, key2.second);
	return dist1 * weight1 + dist2 * weight2;
}

MixedGesturesManager::key_type MixedGesturesManager::getKey(const PathVector &path)
{
	RectangleGesturesManager rectMan;
	NearestPosGridGesturesManager gridMan;
	const auto &key1 = rectMan.getKey(path);
	const auto &key2 = gridMan.getKey(path);
	return {key1, key2};
}

MixedClassifier::MixedClassifier(MixedGesturesManager::key_type &&key)
	: mKey(key)
{
}

MixedClassifier::MixedClassifier(const PathVector &path)
{
	MixedGesturesManager gManager;
	mKey = gManager.getKey(path);
}

MixedClassifier::~MixedClassifier() = default;

qreal MixedClassifier::getDistance(const MixedClassifier &classifier)
{
	const auto &key = classifier.key();
	MixedGesturesManager gManager;
	return gManager.getDistance(key, mKey);
}

MixedClassifier MixedClassifier::getPoint(const MixedClassifier &centre, qreal centreWeight)
{
	const auto &key1 = centre.key().first;
	const auto &key2 = centre.key().second;
	MixedGesturesManager::key_type::first_type finalKey1(gridSize * gridSize);
	MixedGesturesManager::key_type::second_type finalKey2(gridSize * gridSize);
	for (int i = 0; i < gridSize * gridSize; i ++) {
		finalKey1[i] = (key1[i] * centreWeight + mKey.first[i]) / (centreWeight + 1);
		finalKey2[i] = (key2[i] * centreWeight + mKey.second[i]) / (centreWeight + 1);
	}

	return MixedClassifier(MixedGesturesManager::key_type {finalKey1, finalKey2});
}

MixedGesturesManager::key_type MixedClassifier::key() const
{
	return mKey;
}
