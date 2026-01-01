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

#include <QtWidgets/QGraphicsItem>
#include <QPointer>
#include <qrutils/graphicsUtils/abstractItem.h>

class QDomElement;
class QGraphicsTextItem;

namespace twoDModel {

namespace model {
class MetricCoordinateSystem;
}

namespace items {

/// Represents some zone on the 2D model world, probably with some text like "Start zone".
class RegionItem : public graphicsUtils::AbstractItem
{
	Q_OBJECT
	Q_DISABLE_COPY(RegionItem)

public:
	/// A constructor for creating a region before deserialization.
	explicit RegionItem(
			graphicsUtils::AbstractCoordinateSystem *metricSystem,
	                QGraphicsItem *parent = nullptr);

	/// A constructor for creating a region from an existing graphicsUtils::AbstractItem
	/// by copying the fields of that AbstractItem once.
	explicit RegionItem(QSharedPointer<graphicsUtils::AbstractItem>& abstractItem,
			graphicsUtils::AbstractCoordinateSystem *metricSystem,
			QGraphicsItem *parent = nullptr);

	/// Returns true if the region is filled with hatching.
	bool filled() const;

	/// Enables or disables filling region with hatching.
	void setFilled(bool filled);

	/// Returns text that written over the region.
	QString text() const;

	/// Sets text that written over the region.
	void setText(const QString &text);

	/// Returns the upper-left corner of the text relatively to upper-left corner of the item.
	QPointF textPosition() const;

	/// Sets the upper-left corner of the text relatively to upper-left corner of the item.
	void setTextPosition();

	/// Returns the color of the item`s borders, text and hatching.
	QColor color() const;

	/// Sets the color of the item`s borders, text and hatching.
	void setColor(const QColor &color);

	/// Returns true if the given point in scene coordinates is contained by this region.
	bool containsPoint(QPointF point) const;

	/// Returns true if the center of the bounding rect of the given item is contained by this region.
	bool containsItem(QGraphicsItem *item) const;

	QDomElement serialize(QDomElement &element) const override;

	/// A general function for deserializing regions. RegionItem is responsible for deserializing the color,
	/// text, filled, and optionally the location of this region (not relevant in the case of BoundRegion)
	void deserialize(const QDomElement &element) override;

	void setDumpPositionInfo(bool needDump);

	/// A function for managing the state of a region. By default, the region should be
	/// (invisible to the user on the scene if the initial visibility was set to false during deserialization).
	/// In the case of region editing mode, each region should be visible
	virtual void switchToEditorMode(bool toEditor);

	/// The initial visibility of the region obtained during deserialization
	///  (possibly explicitly set by the user in the region editing mode in the future)
	bool visible() const { return mVisible; };

	/// Now that Region is a full-fledged graphical element that can be resized,
	/// it is important to ensure that no extra regions are included in its shape when checking constraints.
	/// The shape method for QGraphicsItem is also used for hit-testing when resizing elements
	/// (for example, in hoverMoveEvent), which means that using a shape that contains a resize area is not suitable
	/// for checking whether an object belongs to a region (if the region is selected). To do this, we should use the
	/// shapeWihoutResizeArea or containsItem/containsPoint methods of the Region class.
	virtual QPainterPath shapeWihoutResizeArea() const = 0;

protected:
	virtual QString regionType() const = 0;

private:
	QPointF deserializePoint(const QDomElement &element, const QString &xAttribute, const QString &yAttribute);
	bool mVisible {};
	QGraphicsTextItem *mTextItem;  // Takes ownership
	QPointF mTextPosition {};
	bool mFilled;
	bool mDumpPositionInfo {true};
	QColor mColor;
};

}
}
