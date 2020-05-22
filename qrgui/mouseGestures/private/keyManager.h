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

#include <QtCore/QPointF>
#include <QtCore/QList>

namespace qReal {
namespace gestures {

class KeyManager
{
public:
	KeyManager();
	QString getKey(QList<QPoint> const &path);

private:
	void analysePoints(QList<QPoint> const &path);
	void clear();

	int mLeftBound {-1};
	int mRightBound {-1};
	int mUpperBound {-1};
	int mLowerBound {-1};
	static const int inMovement = 20;
	static const int iSize = 7;
	static const int unidimensionalLimit = 4;
};

}
}
