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

#include <qrutils/graphicsUtils/rotateItem.h>

namespace twoDModel {
namespace items {

class StartPosition : public graphicsUtils::RotateItem
{
public:
	explicit StartPosition(const QSizeF &robotSize, QGraphicsItem *parent = nullptr);

	QRectF boundingRect() const override;
	void drawItem(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

	QDomElement serialize(QDomElement &parent) const override;
	void deserialize(const QDomElement &startPositionElement) override;
	void deserializeCompatibly(const QDomElement &robotElement);

private:
	void drawFieldForResizeItem(QPainter* painter) override;
	void changeDragState(qreal x, qreal y) override;

	void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

	const QSizeF mRobotSize;
};

}
}
