/* Copyright 2017 CyberTech Labs Ltd.
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

#include <src/engine/items/movableItem.h>

namespace twoDModel {
namespace items {

class SkittleItem : public MovableItem
{
	Q_OBJECT
	Q_DISABLE_COPY(SkittleItem)

public:
	explicit SkittleItem(const QPointF &position);

	/// Creates and returns skittle item for 2D model palette.
	/// Transfers ownership.
	static QAction *skittleTool();

	QDomElement serialize(QDomElement &element) const override;

	bool isCircle() const override;
	qreal mass() const override;
	qreal friction() const override;
	qreal angularDamping() const override;
	qreal linearDamping() const override;
	QSize itemSize() const override;
};

}
}
