/* Copyright 2018 CyberTech Labs Ltd.
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

#include "ballItem.h"

#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtSvg/QSvgRenderer>

#include <twoDModel/engine/model/constants.h>

using namespace twoDModel::items;

BallItem::BallItem(const QPointF &position)
	:MovableItem(position)
{
	mImage.loadFrom(QString(":/icons/2d_ball.svg"));
	setTransformOriginPoint(boundingRect().center());
}

QSize BallItem::itemSize() const
{
	return ballSize;
}

QAction *BallItem::ballTool()
{
	QAction * const result = new QAction(QIcon(":/icons/2d_ball.svg"), tr("Ball (B)"), nullptr);
	result->setShortcuts({QKeySequence(Qt::Key_B), QKeySequence(Qt::Key_4)});
	result->setCheckable(true);
	return result;
}

QDomElement BallItem::serialize(QDomElement &element) const
{
	QDomElement ballNode = MovableItem::serialize(element);
	ballNode.setTagName("ball");
	return ballNode;
}

qreal BallItem::angularDamping() const
{
	return 0.09;
}

qreal BallItem::linearDamping() const
{
	return 0.09;
}

bool BallItem::isCircle() const
{
	return true;
}

qreal BallItem::mass() const
{
	return 0.015;
}

qreal BallItem::friction() const
{
	return 1.0;
}
