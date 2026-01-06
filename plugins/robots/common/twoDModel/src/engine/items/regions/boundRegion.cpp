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

#include "boundRegion.h"
#include <qrutils/graphicsUtils/rectangleImpl.h>
#include <qrutils/graphicsUtils/abstractItem.h>
#include "src/engine/items/ellipseItem.h"
#include "src/engine/items/rectangleItem.h"
#include <QsLog.h>
#include <QtXml/QDomElement>
#include <QSharedPointer>
#include <utility>

using namespace twoDModel::items;

const int defaultStroke = 0;

BoundRegion::BoundRegion(graphicsUtils::AbstractCoordinateSystem *metricSystem
			, QSharedPointer<graphicsUtils::AbstractItem> abstractItem
			, QString boundId, QGraphicsItem *parent)
	: RegionItem(abstractItem, metricSystem, parent)
	, mBoundItem(abstractItem)
	, mBoundId(std::move(boundId))
	, mStroke(defaultStroke)
{
	RegionItem::setDumpPositionInfo(false);
	// Unlike a regular region, we don't just copy the element once;
	// any change to the associated AbstractItem should also change the region.
	connect(&*abstractItem, &AbstractItem::positionChanged, this, [this](QPointF p) {this->setPos(p);} );
	connect(&*abstractItem, &AbstractItem::x1Changed, this, &AbstractItem::setX1);
	connect(&*abstractItem, &AbstractItem::y1Changed, this, &AbstractItem::setY1);
	connect(&*abstractItem, &AbstractItem::x2Changed, this, &AbstractItem::setX2);
	connect(&*abstractItem, &AbstractItem::y2Changed, this, &AbstractItem::setY2);
	connect(&*abstractItem, &AbstractItem::penChanged, this, [this](const QPen &pen){
		setPenColor(pen.color().name());
	});

	if (auto colorFieldItem = qSharedPointerCast<items::ColorFieldItem>(abstractItem)) {
		colorFieldItem->setBindedToRegion(true);
	}
}

int BoundRegion::stroke() const
{
	return mStroke;
}

void BoundRegion::setStroke(int stroke)
{
	mStroke = stroke;
}

QDomElement BoundRegion::serialize(QDomElement &element) const
{
	auto &&regionNode = RegionItem::serialize(element);
	regionNode.setAttribute("boundItem", mBoundId);
	const auto &metricSystem = coordinateSystem();
	regionNode.setAttribute("stroke", metricSystem->toUnit(mStroke));
	return regionNode;
}

void BoundRegion::deserialize(const QDomElement &element)
{
	RegionItem::deserialize(element);
	if (element.hasAttribute("stroke")) {
		bool ok = false;
		const auto &metricSystem = coordinateSystem();
		const int stroke = element.attribute("stroke").toInt(&ok);
		if (ok) {
			mStroke = static_cast<int>(metricSystem->toPx(stroke));
		}
	}
}

void BoundRegion::switchToMode(EditorMode mode)
{
	// Unlike the regular scenario, the region becomes uneditable
	// (not movable or resizable, simply because the associated AbstractItem is editable,
	// but this should not apply to other parameters if they are supported in the future,
	// such as setting the boundRegion text)
	// NOLINTNEXTLINE(bugprone-parent-virtual-call)
	TwoDSceneItem::switchToMode(mode);
	if (mode == EditorMode::regionEditorMode) {
		setVisible(true);
		setEditable(false);
		return;
	}
	setVisible(visible());
	setEditable(false);
}

QRectF BoundRegion::boundingRect() const
{
	QSharedPointer<graphicsUtils::AbstractItem> strong = mBoundItem.toStrongRef();
	return strong ? strong->boundingRect().adjusted(-mStroke, -mStroke, mStroke, mStroke) : QRectF{};
}

void BoundRegion::drawItem(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option)
	Q_UNUSED(widget)
	QSharedPointer<graphicsUtils::AbstractItem> strong = mBoundItem.toStrongRef();
	painter->drawPath(shape());
}

QPainterPath BoundRegion::shape() const
{
	QSharedPointer<graphicsUtils::AbstractItem> strong = mBoundItem.toStrongRef();
	QPainterPath result;
	if (!strong) {
		return {};
	}

	// We are not interested in whether the associated AbstractItem is filled.
	// From our perspective, a region cannot be a path, and the shape of a region should not contain
	// the resize area of the associated object.
	if (auto *ellipseItem = dynamic_cast<items::EllipseItem *>(strong.data())) {
		result = ellipseItem->shapeWihoutResizeArea();
	}
	else if (auto *rectangleItem = dynamic_cast<items::RectangleItem *>(strong.data())) {
		result = rectangleItem->shapeWihoutResizeArea();
	} else {
		QLOG_ERROR() << "This type of object that inherits AbstractItem is "
				"not currently supported for creating a boundRegion";
		return {};
	}

	if (!mStroke) {
		return result;
	}

	QPainterPathStroker stroker;
	stroker.setWidth(mStroke);
	return stroker.createStroke(result);
}

QPainterPath BoundRegion::shapeWihoutResizeArea() const
{
	return shape();
}

QString BoundRegion::regionType() const
{
	return "bound";
}
