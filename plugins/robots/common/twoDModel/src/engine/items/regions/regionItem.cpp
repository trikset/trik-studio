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

#include "regionItem.h"
#include <QtCore/QUuid>
#include <QtXml/QDomElement>
#include <QtGui/QPainter>
#include <qrutils/graphicsUtils/abstractItem.h>
#include <twoDModel/engine/model/metricCoordinateSystem.h>
#include <cmath>

const QColor defaultColor = QColor(135, 206, 250);
const QSizeF defaultSize = QSizeF(200, 200);

using namespace twoDModel::items;

RegionItem::RegionItem(graphicsUtils::AbstractCoordinateSystem *metricSystem,
			QGraphicsItem *parent)
	: TwoDSceneItem(parent)
	, mVisible(false)
	, mTextItem(new QGraphicsTextItem(this))
	, mFilled(true)
	, mDumpPositionInfo(true)
	, mColor(defaultColor)

{
	// The default region is not editable, but this can be changed in the region editing mode
	setEditable(false);
	setCoordinateSystem(metricSystem);
	setZValue(graphicsUtils::AbstractItem::ZValue::Region);
	setPenColor(mColor.name());
	setBrushColor(mColor.name());
	setBrushStyle("Diag");

	auto updateTextPosition = [this](){ setTextPosition(); };
	connect(this, &AbstractItem::positionChanged, this, updateTextPosition);
	connect(this, &AbstractItem::x1Changed, this, updateTextPosition);
	connect(this, &AbstractItem::x2Changed, this, updateTextPosition);
	connect(this, &AbstractItem::y1Changed, this, updateTextPosition);
	connect(this, &AbstractItem::y2Changed, this, updateTextPosition);
}

RegionItem::RegionItem(QSharedPointer<graphicsUtils::AbstractItem>& abstractItem,
		graphicsUtils::AbstractCoordinateSystem *metricSystem,
		QGraphicsItem *parent)
	: RegionItem(metricSystem, parent)
{
	// When creating a region from an existing AbstractItem, we need to copy the position on the scene
	// and other necessary information for creating the region
	setX1(abstractItem->x1());
	setX2(abstractItem->x2());
	setY1(abstractItem->y1());
	setY2(abstractItem->y2());
	setPos(abstractItem->pos());
	savePos();

	// We save the color for the region. The stroke-width parameter is not supported yet because
	// it was not available for ordinary regions, but it can be added if necessary (is there any point in doing so)?
	auto &&abstractItemColor = abstractItem->pen().color();
	setPenColor(abstractItemColor.name());
	setBrushColor(abstractItemColor.name());
	mColor = abstractItemColor;
	update();
}

void RegionItem::switchToMode(EditorMode mode)
{
	// When you enter the region editing mode, the region becomes visible and editable
	// (for example, you can change its shape like an ellipse or a rectangle),
	// otherwise it should be non-editable and retain the visibility initially set by the user.
	TwoDSceneItem::switchToMode(mode);
	if (mode == EditorMode::regionEditorMode) {
		setVisible(true);
		setEditable(true);
		return;
	}
	setVisible(mVisible);
	setEditable(false);
}

bool RegionItem::filled() const
{
	return mFilled;
}

void RegionItem::setFilled(bool filled)
{
	mFilled = filled;
}

QString RegionItem::text() const
{
	return mTextItem->toPlainText();
}

void RegionItem::setText(const QString &text)
{
	mTextItem->setHtml(QString("<div style='background-color:#FFFFFF;color:%2;'>%1</div>")
			.arg(text, mColor.name()));
	mTextItem->setVisible(!text.isEmpty());
}

QPointF RegionItem::textPosition() const
{
	return mTextPosition;
}

void RegionItem::setTextPosition()
{
	const auto x = qMin(x1(), x2());
	const auto y = qMin(y1(), y2());
	QPointF parentScenePosition {x + mTextPosition.x(),
				    y + mTextPosition.y()};
	mTextItem->setPos(parentScenePosition);
}

QColor RegionItem::color() const
{
	return mColor;
}

void RegionItem::setColor(const QColor &color)
{
	mColor = color;
	setText(text());  // To update text color
}

bool RegionItem::containsPoint(QPointF point) const
{
	const auto localPoint = mapFromScene(point);
	return shapeWihoutResizeArea().contains(localPoint);
}

bool RegionItem::containsItem(QGraphicsItem *item) const
{
	return containsPoint(item->boundingRect().center() + item->scenePos());
}

QDomElement RegionItem::serialize(QDomElement &element) const
{
	QDomElement regionNode = AbstractItem::serialize(element);
	regionNode.setTagName("region");

	regionNode.setAttribute("type", regionType());
	regionNode.setAttribute("filled", filled() ? "true" : "false");

	const auto &mMetricSystem = coordinateSystem();

	if (!text().isEmpty()) {
		regionNode.setAttribute("text", text());
		regionNode.setAttribute("textX",
				     QString::number(mMetricSystem->toUnit(textPosition().x())));
		regionNode.setAttribute("textY",
				     QString::number(mMetricSystem->toUnit(textPosition().y())));
	}

	if (mDumpPositionInfo) {
		const auto x = qMin(x1(), x2()) + scenePos().x();
		const auto y = qMin(y1(), y2()) + scenePos().y();
		regionNode.setAttribute("x",
				     QString::number(mMetricSystem->toUnit(x)));
		regionNode.setAttribute("y",
				     QString::number(mMetricSystem->toUnit(y)));

		const auto width = qAbs(x2() - x1());
		const auto height = qAbs(y2() - y1());

		regionNode.setAttribute("height",
				     QString::number(mMetricSystem->toUnit(height)));
		regionNode.setAttribute("width",
				     QString::number(mMetricSystem->toUnit(width)));
	}

	regionNode.setAttribute("visible", mVisible ? "true" : "false");

	regionNode.setAttribute("color", color().name());
	element.appendChild(regionNode);
	return regionNode;
}

void RegionItem::setDumpPositionInfo(bool needDump)
{
	mDumpPositionInfo = needDump;
}

void RegionItem::deserialize(const QDomElement &element)
{
	AbstractItem::deserialize(element);
	if (element.hasAttribute("filled")) {
		setFilled(element.attribute("filled") == "true");
		setBrushStyle(mFilled ? "Diag" : "None");
	}

	if (element.hasAttribute("color")) {
		setColor(QColor(element.attribute("color")));
		setPenColor(mColor.name());
		setBrushColor(mColor.name());
	}

	if (element.hasAttribute("visible")) {
		mVisible = element.attribute("visible") == "true";
		setVisible(mVisible);
	}

	if (mDumpPositionInfo) {
		const auto x = element.attribute("x", "0");
		const auto y = element.attribute("y", "0");
		const auto point = deserializePoint(x, y);
		setPos(QPointF());
		setX1(point.x());
		setY1(point.y());
		const auto height = element.attribute("height", QString::number(defaultSize.height()));
		const auto width = element.attribute("width", QString::number(defaultSize.width()));
		const auto size = deserializePoint(width, height);
		setX2(x1() + size.x());
		setY2(y1() + size.y());
	}

	const auto textX = element.attribute("textX", "0");
	const auto textY = element.attribute("textY", "0");
	mTextPosition = deserializePoint(textX, textY);
	setTextPosition();

	if (element.hasAttribute("text")) {
		setText(element.attribute("text"));
	}
}

QPointF RegionItem::deserializePoint(const QString &textX, const QString &textY)
{
	bool xOk = false;
	bool yOk = false;
	const qreal x = textX.toDouble(&xOk);
	const qreal y = textY.toDouble(&yOk);
	if (xOk && yOk) {
		const auto &mMetricSystem = coordinateSystem();
		return mMetricSystem->toPx({x, y});
	} /// @todo: else report error

	return {};
}
