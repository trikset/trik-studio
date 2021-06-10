/* Copyright 2017-2018 CyberTech Labs Ltd.
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

#include "skittleItem.h"

#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtSvg/QSvgRenderer>

#include <twoDModel/engine/model/constants.h>

using namespace twoDModel::items;

SkittleItem::SkittleItem(const QPointF &position)
	:MovableItem(position)
{
	mSvgRenderer->load(QString(":/icons/2d_can.svg"));
	setTransformOriginPoint(boundingRect().center());
}

QSize SkittleItem::itemSize() const
{
	return skittleSize;
}

QAction *SkittleItem::skittleTool()
{
	QAction * const result = new QAction(QIcon(":/icons/2d_can.svg"), tr("Can (C)"), nullptr);
	result->setShortcuts({QKeySequence(Qt::Key_C), QKeySequence(Qt::Key_3)});
	result->setCheckable(true);
	return result;
}

QDomElement SkittleItem::serialize(QDomElement &element) const
{
	QDomElement skittleNode = MovableItem::serialize(element);
	skittleNode.setTagName("skittle");
	return skittleNode;
}

qreal SkittleItem::angularDamping() const
{
	return 6.0;
}

qreal SkittleItem::linearDamping() const
{
	return 6.0;
}

bool SkittleItem::isCircle() const
{
	return true;
}

qreal SkittleItem::mass() const
{
	return 0.05;
}

qreal SkittleItem::friction() const
{
	return 0.2;
}
