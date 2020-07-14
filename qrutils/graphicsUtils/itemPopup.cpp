/* Copyright 2015 QReal Research Group, Dmitry Mordvinov
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

#include "itemPopup.h"

#include <QtWidgets/QLayout>
#include <QtWidgets/QGraphicsView>

#include "abstractScene.h"
#include <qrutils/graphicsUtils/rotateItem.h>

using namespace graphicsUtils;

ItemPopup::ItemPopup(AbstractScene &scene, QWidget *parent)
	: QFrame(parent)
	, mScene(scene)
{
	hide();

	setStyleSheet("QFrame {border-radius: 3; background: #3F000000; border: 1px solid gray;}");

	connect(&mScene, &AbstractScene::leftButtonPressed, this, &ItemPopup::onMousePressedScene);
	connect(&mScene, &AbstractScene::leftButtonReleased, this, &ItemPopup::onMouseReleasedScene);
	connect(&mScene, &AbstractScene::selectionChanged, this, &ItemPopup::checkSelection);
}

ItemPopup::~ItemPopup()
{
}

void ItemPopup::setEnabled(bool enabled)
{
	mEnabled = enabled;
	if (!enabled && isVisible()) {
		detach();
		hide();
	}
}

bool ItemPopup::suits(QGraphicsItem *item)
{
	return dynamic_cast<AbstractItem *>(item) != nullptr;
}

bool ItemPopup::attachTo(QGraphicsItem *item)
{
	attachTo(QList<QGraphicsItem *>() << item);
	return true;
}

bool ItemPopup::attachTo(const QList<QGraphicsItem *> &items)
{
	mCurrentItems = items;
	return true;
}

void ItemPopup::detach()
{
	mCurrentItems.clear();
}

void ItemPopup::updateDueToLayout()
{
	setFixedSize(layout()->sizeHint());
}

QVariant ItemPopup::dominantPropertyValue(const QString &property) const
{
	QMap<QVariant, int> valuesCounts;
	for (QGraphicsItem * const item : mCurrentItems) {
		if (QObject * const object = dynamic_cast<QObject *>(item)) {
			const QVariant value = object->property(qUtf8Printable(property));
			if (value.isValid()) {
				++valuesCounts[value];
			}
		}
	}

	QVariant result;
	for (const QVariant &value : valuesCounts.keys()) {
		if (valuesCounts[value] > valuesCounts[result]) {
			result = value;
		}
	}

	return result;
}

void ItemPopup::setPropertyMassively(const QString &property, const QVariant &value)
{
	QStringList idsForExternalProcessing;
	for (QGraphicsItem * const item : mCurrentItems) {
		if (AbstractItem * const object = dynamic_cast<AbstractItem *>(item)) {
			// If item is abstract item then changing its property with undo/redo tracking
			idsForExternalProcessing << object->id();
		} else if (QObject * const object = dynamic_cast<QObject *>(item)) {
			// Else just setting it for 1 time, no way to track it
			object->setProperty(qUtf8Printable(property), value);
		}
	}

	emit propertyChanged(idsForExternalProcessing, property, value);
}

void ItemPopup::onMousePressedScene()
{
	mMousePressed = true;
	if (isVisible()) {
		detach();
		hide();
	}
}

void ItemPopup::onMouseReleasedScene()
{
	mMousePressed = false;
	checkSelection();
}

void ItemPopup::checkSelection()
{
	if (!mEnabled && mMousePressed) {
		return;
	}

	QList<QGraphicsItem *> items;
	for (QGraphicsItem * const item : mScene.selectedItems()) {
		if (suits(item)) {
			items << item;
		}
	}

	if (items.isEmpty()) {
		detach();
		hide();
		return;
	}

	const bool shouldShow = items.count() == 1 ? attachTo(items.first()) : attachTo(items);
	if (!shouldShow) {
		return;
	}

	show();

	for (auto &item : items) {
		if (auto *rotateItem = dynamic_cast<graphicsUtils::RotateItem *>(item)) {
			items.append(&rotateItem->rotater());
		}
	}

	// Item`s pos will be just under this widget`s middle, 10 px below.
	QGraphicsView * const view = mScene.views().first();
	Q_ASSERT(view);
	const QPointF scenePos = leftmostTopmost(items);
	const QPoint moveAbove = view->viewport()->mapToGlobal(view->mapFromScene(scenePos));
	const QPoint globalPoint{moveAbove.x() - size().width() / 2, moveAbove.y() - size().height() - 10};
	move(parentWidget()->mapFromGlobal(globalPoint));
}

void ItemPopup::mousePressEvent(QMouseEvent *event)
{
	Q_UNUSED(event)
	hide();
}

bool ItemPopup::hasProperty(const QString &property) const
{
	for (QGraphicsItem * const item : mCurrentItems) {
		if (QObject * const object = dynamic_cast<QObject *>(item)) {
			if (object->metaObject()->indexOfProperty(qUtf8Printable(property)) >= 0) {
				return true;
			}
		}
	}

	return false;
}

QPointF ItemPopup::leftmostTopmost(const QList<QGraphicsItem *> &items)
{
	QPointF result{INT_MAX, INT_MAX};
	for (const QGraphicsItem *item : items) {
		result.setX(qMin(result.x(), item->sceneBoundingRect().left()));
		result.setY(qMin(result.y(), item->sceneBoundingRect().top()));
	}

	return result;
}
