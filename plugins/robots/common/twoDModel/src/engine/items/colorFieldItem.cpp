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

#include "colorFieldItem.h"
#include <cmath>
#include <QMenu>
#include <memory>

using namespace twoDModel::items;

ColorFieldItem::ColorFieldItem(
		graphicsUtils::AbstractCoordinateSystem *metricSystem,
		QGraphicsItem* parent)
	: AbstractItem(parent)
{
	setCoordinateSystem(metricSystem);
	setZValue(ZValue::Shape);
}

ColorFieldItem::~ColorFieldItem() = default;

QColor ColorFieldItem::color() const
{
	return pen().color();
}

void ColorFieldItem::propagateSwitchToRegionMenu(QGraphicsSceneContextMenuEvent *event)
{
	if (!editable()) {
		return;
	}

	if (!isSelected()) {
		scene()->clearSelection();
		setSelected(true);
	}

	event->accept();

	auto &&menu = std::make_unique<QMenu>();
	auto &&removeAction = menu->addAction(QObject::tr("Remove"));
	auto &&convertToRegionAction = menu->addAction(QObject::tr("Convert to region"));;
	auto &&bindToRegionAction = menu->addAction(QObject::tr("Bind to region"));;

	if (!inEditorMode() || mBindedToRegion) {
		menu->removeAction(convertToRegionAction);
		menu->removeAction(bindToRegionAction);
	}

	auto &&selectedAction = menu->exec(event->screenPos());
	if (selectedAction == removeAction) {
		Q_EMIT deletedWithContextMenu();
	} else if (selectedAction == convertToRegionAction) {
		Q_EMIT convertToRegionWithContextMenu(*this);
	} else if (selectedAction == bindToRegionAction) {
		mBindedToRegion = true;
		Q_EMIT bindToRegionWithContextMenu(*this);
	}
}

void ColorFieldItem::setColor(const QColor &color)
{
	setPenColor(color.name());
	setBrushColor(color.name());
	update();
}

int ColorFieldItem::thickness() const
{
	return pen().width();
}

void ColorFieldItem::setThickness(int thickness)
{
	setPenWidth(thickness);
	update();
}
