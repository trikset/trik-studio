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
#include "src/engine/view/scene/twoDSceneItem.h"

namespace twoDModel {

namespace model {
class SizeUnit;
}

namespace items {

class ColorFieldItem: public view::TwoDSceneItem
{
	Q_OBJECT

	Q_PROPERTY(QColor color READ color WRITE setColor)
	Q_PROPERTY(int thickness READ thickness WRITE setThickness)

	Q_DISABLE_COPY(ColorFieldItem)

public:
	explicit ColorFieldItem(
	                graphicsUtils::AbstractCoordinateSystem *metricSystem,
	                QGraphicsItem *parent = nullptr);
	~ColorFieldItem() override;

	/// Returns a color of this item.
	QColor color() const;

	/// Sets a color of this item.
	void setColor(const QColor &color);

	/// Returns a thickness of this item in px.
	int thickness() const;

	/// Sets a thickness of this item.
	/// @param The thickness value in px.
	void setThickness(int thickness);

	/// Creates a copy of this graphical item. Transfers ownership to the caller.
	virtual AbstractItem *clone() const = 0;

	void setBindedToRegion(bool bindedtoRegion) {
		mBindedToRegion = bindedtoRegion;
	};

protected:
	/// At the moment, we create regions from ellipses and rectangles, including from the UI by adding additional
	/// options to the context menu of ellipses and rectangles on the scene.
	/// Switching to the region editing mode for them means that the corresponding options appear in the context menu.
	void propagateSwitchToRegionMenu(QGraphicsSceneContextMenuEvent *event);
Q_SIGNALS:
	/// A signal emitted when an element is converted to a region via the context menu.
	void convertToRegionWithContextMenu(const twoDModel::items::ColorFieldItem &);
	/// A signal emitted when the region is bound to this element through the context menu.
	void bindToRegionWithContextMenu(const twoDModel::items::ColorFieldItem &);
private:
	bool mBindedToRegion {};
};

}
}
