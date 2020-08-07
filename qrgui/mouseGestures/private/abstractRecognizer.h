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

#include <QtCore/QString>
#include <QtCore/QMap>
#include <QtWidgets/QWidget>
#include <QtGui/QMouseEvent>

#include <qrkernel/ids.h>

#include "geometricForms.h"
#include "pathCorrector.h"

namespace qReal {
namespace gestures {

class GesturesManager
{
	Q_DISABLE_COPY(GesturesManager)
public:
	GesturesManager() = default;
	virtual ~GesturesManager() = default;
	virtual void initIdealGestures(QMap<QString, PathVector> const &objects) = 0;
	virtual void setKey(const PathVector &path) = 0;
	virtual qreal getMaxDistance(const QString &object) = 0;
	virtual qreal getDistance(const QString &object) = 0;
	virtual bool isMultistroke() = 0;
};

template <typename TKey>
class GesturesRecognizer : public GesturesManager
{
public:
	using key_type = TKey;

	GesturesRecognizer() = default;

	~GesturesRecognizer() override = default;

	qreal getDistance(const QString &item) override
	{
		TKey key = mGestures[item];
		return getDistance(mKey, key);
	}

	void initIdealGestures(QMap<QString, PathVector> const &objects) override
	{
		for (auto &&object : objects.keys()) {
			mGestures.insert(object, getKey(objects[object]));
		}
	}

	void setKey(const PathVector &path) override
	{
		mKey = getKey(path);
	}

	virtual qreal getMaxDistance(const QString &object) override = 0;

protected:
	TKey mKey;
	virtual qreal getDistance(const key_type &key1, const key_type &key2) = 0;
	virtual TKey getKey(const PathVector &path) = 0;
	QMap<QString, key_type> mGestures;
	//maybe to do several lists for multistroke gestures
};

}
}
