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

#include "fakeScene.h"

#include "twoDModel/engine/model/worldModel.h"
#include "src/engine/items/wallItem.h"
#include "src/engine/items/colorFieldItem.h"
#include "src/engine/items/imageItem.h"

using namespace twoDModel;
using namespace view;
using namespace model;

FakeScene::FakeScene(const WorldModel &world)
{
	connect(&world, &WorldModel::wallAdded, this, [=](const QSharedPointer<items::WallItem> &wall) {
		addClone(wall, wall->clone());
	});
	connect(&world, &WorldModel::colorItemAdded
			, this, [=](const QSharedPointer<items::ColorFieldItem> &item) {
		addClone(item, item->clone());
	});
	connect(&world, &WorldModel::imageItemAdded, this, [=](const QSharedPointer<items::ImageItem> &item) {
		if (!item->isBackground()) {
			addClone(item, item->clone());
		}
	});
	connect(&world, &WorldModel::traceItemAddedOrChanged
			, this, [this](const QSharedPointer<QGraphicsPathItem> &item, bool justChanged) {
		// if traceItem was changed need delete old clone before adding new clone
		if (justChanged) {
			deleteItem(item);
		}
		addClone(item, new QGraphicsPathItem(item->path()));
	});
	connect(&world, &WorldModel::itemRemoved, this, &FakeScene::deleteItem);
}

void FakeScene::addClone(const QWeakPointer<QGraphicsItem> &original, QGraphicsItem * const cloned)
{
	mClonedItems[original] = cloned;
	addItem(cloned);

	// Interesting things happen here. Fake scene behaviours really strangely without this hack.
	// Lines, ellipses and stylus is drawn correctly, but PARTIALLY until it moves the first time
	// (or other things like dragging out some item over the fake scene bounds).
	// That means that if user draws color field until he drags newly drawn item (what happens rarely)
	// light sensor or camera will see only some parts of the item. How? I don`t know, bu I think
	// that the nature of this phenomenon is somewhere deeply in Qt (or we just do something wrong, but
	// then some very unobvious thing is wrong). One way to fix that is simply to move item when we
	// change its corners.
	if (auto &&orit = qSharedPointerDynamicCast<graphicsUtils::AbstractItem>(original.lock())) {
		const auto hack = [=]() { cloned->moveBy(1, 1); cloned->moveBy(-1, -1); };
		connect(&*orit, &graphicsUtils::AbstractItem::x1Changed, this, hack);
		connect(&*orit, &graphicsUtils::AbstractItem::y1Changed, this, hack);
		connect(&*orit, &graphicsUtils::AbstractItem::x2Changed, this, hack);
		connect(&*orit, &graphicsUtils::AbstractItem::y2Changed, this, hack);
	}
}

void FakeScene::deleteItem(const QSharedPointer<QGraphicsItem> &original)
{
	if (mClonedItems.contains(original)) {
		removeItem(mClonedItems[original]);
		delete mClonedItems[original];
		mClonedItems.remove(original);
	}
}

QImage view::FakeScene::render(const QRectF &piece)
{
	QImage result(piece.size().toSize(), QImage::Format_RGB32);
	result.fill(Qt::white);
	QPainter painter(&result);
	QGraphicsScene::render(&painter, QRectF(), piece);
	return result;
}
