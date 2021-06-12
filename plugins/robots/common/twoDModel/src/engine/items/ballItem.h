/* Copyright 2018 CyberTech Labs Ltd.
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

#include "src/engine/items/movableItem.h"

class QSvgRenderer;

namespace twoDModel {
namespace items {

class BallItem : public twoDModel::items::MovableItem
{
	Q_OBJECT
	Q_DISABLE_COPY(BallItem)

public:
	explicit BallItem(const QPointF &position);

	/// Creates and returns ball item for 2D model palette.
	/// Transfers ownership.
	static QAction *ballTool();

	QDomElement serialize(QDomElement &element) const override;

	bool isCircle() const override;
	qreal mass() const override;
	qreal friction() const override;
	qreal angularDamping() const override;
	qreal linearDamping() const override;
	QSize itemSize() const override;
	QString defaultImagePath() const override;
};

}
}
