/* Copyright 2022 CyberTech Labs Ltd.
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

#include <qrutils/graphicsUtils/abstractItem.h>

namespace twoDModel {
namespace items {

class CommentItem : public graphicsUtils::AbstractItem
{
	Q_OBJECT
	Q_DISABLE_COPY(CommentItem)

public:
	explicit CommentItem(const QPointF &begin, const QPointF &end);

	/// Creates and returns comment item for 2D model palette.
	/// Transfers ownership.
	static QAction *commentTool();

	QRectF boundingRect() const override;
	QPainterPath shape() const override;

	void drawItem(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
	void drawExtractionForItem(QPainter* painter) override;
	QPainterPath resizeArea() const override;

	QDomElement serialize(QDomElement &parent) const override;
	void deserialize(const QDomElement &element) override;
};

}
}
