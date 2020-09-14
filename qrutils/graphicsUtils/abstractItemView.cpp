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

#include "abstractItemView.h"

using namespace graphicsUtils;

AbstractView::AbstractView(QWidget * parent) : QGraphicsView(parent)
{
}

void AbstractView::zoomIn()
{
	scaleTo(1.5);
	emit zoomChanged();
}

void AbstractView::zoomOut()
{
	scaleTo(1/1.5);
}

void AbstractView::wheelEvent(QWheelEvent *event)
{
	QGraphicsView::wheelEvent(event);
	if (event->buttons() == Qt::MidButton) {
		if (event->delta() >= 0)
			zoomOut();
		else
			zoomIn();
	}
}

void AbstractView::scrollContentsBy(int dx, int dy)
{
	QGraphicsView::scrollContentsBy(dx, dy);
	if (scene()) {
		scene()->update();
	}

	emit contentsRectChanged();
}

void AbstractView::setScaleLimits(qreal minAbsScale, qreal maxAbsScale)
{
	if (minAbsScale > 0) {
		mMinAbsScale = minAbsScale;
	}

	if (maxAbsScale > 0) {
		mMaxAbsScale = maxAbsScale;
	}

	if (mMaxAbsScale < mMinAbsScale) {
		std::swap(mMaxAbsScale, mMinAbsScale);
	}
}

void AbstractView::scaleTo(qreal newScaleMultiplier)
{
	auto newAbsScale = newScaleMultiplier * mCurrentAbsScale;
	if (mMinAbsScale <= newAbsScale && newAbsScale <= mMaxAbsScale) {
		mCurrentAbsScale = newAbsScale;
		scale(newScaleMultiplier, newScaleMultiplier);
		emit zoomChanged();
	}
}

void AbstractView::keyPressEvent(QKeyEvent *event)
{
	QGraphicsView::keyPressEvent(event);
	if (event->matches(QKeySequence::Delete))
		emit deleteItem();
}
