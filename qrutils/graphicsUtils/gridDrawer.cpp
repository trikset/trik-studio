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

#include <QtCore/QLineF>
#include <cmath>
#include "gridDrawer.h"

using namespace graphicsUtils;

GridDrawer::GridDrawer() = default;

void GridDrawer::drawGrid(QPainter *painter, const QRectF &rect, const qreal gridSize)
{
	const auto firstVerticalLineIndex = static_cast<int>(std::floor(rect.left() / gridSize));
	const auto lastVerticalLineIndex = static_cast<int>(std::ceil(rect.right() / gridSize));

	for (auto i = firstVerticalLineIndex; i <= lastVerticalLineIndex; ++i) {
		const auto currentVerticalLineX = i * gridSize;
		painter->drawLine(QPointF(currentVerticalLineX, rect.top()),
					QPointF(currentVerticalLineX, rect.bottom()));
	}

	const auto firstHorizontalLineIndex = static_cast<int>(std::floor(rect.top() / gridSize));
	const auto lastHorizontalLineIndex = static_cast<int>(std::floor(rect.bottom() / gridSize));

	for (auto i = firstHorizontalLineIndex; i <= lastHorizontalLineIndex; ++i) {
		const auto currentHorizontalLineY = i * gridSize;
		painter->drawLine(QPointF(rect.left(), currentHorizontalLineY),
			QPointF(rect.right(), currentHorizontalLineY));
	}
}
