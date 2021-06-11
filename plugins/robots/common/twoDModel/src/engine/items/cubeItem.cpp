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

#include "cubeItem.h"

#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtSvg/QSvgRenderer>

#include <twoDModel/engine/model/constants.h>

using namespace twoDModel::items;

CubeItem::CubeItem(const QPointF &position)
	:MovableItem(position)
{
	mSvgRenderer->load(QString(":/icons/2d_cube.svg"));
	setTransformOriginPoint(boundingRect().center());
}

QSize CubeItem::itemSize() const
{
	return cubeSize;
}

QAction *CubeItem::cubeTool()
{
	QAction * const result = new QAction(QIcon(":/icons/2d_cube.svg"), tr("Cube (C)"), nullptr);
	result->setShortcuts({QKeySequence(Qt::Key_C), QKeySequence(Qt::Key_3)});
	result->setCheckable(true);
	return result;
}

QDomElement CubeItem::serialize(QDomElement &element) const
{
	QDomElement cubeNode = MovableItem::serialize(element);
	cubeNode.setTagName("cube");
	return cubeNode;
}

qreal CubeItem::angularDamping() const
{
	return 6.0;
}

qreal CubeItem::linearDamping() const
{
	return 6.0;
}

bool CubeItem::isCircle() const
{
	return false;
}

qreal CubeItem::mass() const
{
	return 0.05;
}

qreal CubeItem::friction() const
{
	return 0.2;
}
