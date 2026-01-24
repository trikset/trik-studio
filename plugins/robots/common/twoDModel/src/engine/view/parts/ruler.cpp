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

#include "ruler.h"
#include <QtGui/QPainter>
#include <QtWidgets/QGraphicsView>
#include <QtCore/QtMath>

#include <qrkernel/settingsManager.h>
#include "twoDModel/engine/model/metricSystem.h"

using namespace twoDModel::view;

const qreal gap = 5;  // The gap between the ruler borders and text on it.
const int frequency = 50;  // The text on the ruler will not be met more often than once per this number of pixels.

Ruler::Ruler(QWidget *parent)
	: QFrame(parent)
	, mOrientation(Qt::Horizontal)
	, mSizeUnit(nullptr)
{
	mFont.setPixelSize(8);
}

Ruler::~Ruler() = default;

Qt::Orientation Ruler::orientation() const
{
	return mOrientation;
}

void Ruler::onSizeUnitChanged(const QSharedPointer<twoDModel::model::SizeUnit> &unit)
{
	mSizeUnit = unit;
}

void Ruler::setOrientation(Qt::Orientation orientation)
{
	mOrientation = orientation;

	const QString theLongestText = "-123.45";  // The longest text that ruler must place into itself.
	const QSizeF theLargestSize = textBoundingRect(theLongestText).size();
	if (orientation == Qt::Horizontal) {
		setFixedHeight(static_cast<int>(theLargestSize.height() + 2 * gap));
	} else {
		setFixedWidth(static_cast<int>(theLargestSize.width() + 2 * gap));
	}
}

void Ruler::paintEvent(QPaintEvent *event)
{
	QFrame::paintEvent(event);
	QPainter painter(this);
	painter.setFont(mFont);

	const auto gridSize = qReal::SettingsManager::value("2dDoubleGridCellSize").toReal();
	const auto currentCountFactor = countFactor();
	const auto sceneRect = mView->mapToScene(mView->viewport()->geometry()).boundingRect();
	const auto startPos = relevantCoordinate(sceneRect.topLeft());
	const auto endPos = relevantCoordinate(sceneRect.bottomRight());

	const auto zoom = mView->transform().m11();
	const auto skipCells = qMax(1, qCeil((frequency / zoom) / gridSize));
	const auto effectiveStep = skipCells * gridSize;
	const auto startIdx = static_cast<int>(std::floor(startPos / effectiveStep));
	const auto endIdx = static_cast<int>(std::ceil(endPos / effectiveStep));

	for (int i = startIdx; i <= endIdx; ++i) {
		const qreal coordinate = i * effectiveStep;
		QString text = QString::number(coordinate / currentCountFactor, 'f', 3);
		if (text.contains('.')) {
			while (text.endsWith('0')) {
				text.chop(1);
			}
			if (text.endsWith('.')) {
				text.chop(1);
			}
		}
		const auto &boundingRect = textBoundingRect(text);
		const auto relevantPosition = relevantCoordinate(mView->mapFromScene(makePoint(coordinate, 0)));
		const auto position = drawingPoint(relevantPosition, boundingRect.size());
		const auto alignment = makePoint(relevantDimension(boundingRect.size()) / 2, 0);
		if (relevantPosition >= 0 && relevantPosition <= relevantDimension(this->size())) {
			painter.drawText(position - boundingRect.topLeft() - alignment, text);
		}
	}
}

qreal Ruler::relevantCoordinate(QPointF point) const
{
	return orientation() == Qt::Horizontal ? point.x() : point.y();
}

qreal Ruler::countFactor() const
{
	if (mSizeUnit) {
		return mSizeUnit->countFactor();
	}
	return 1.0f;
}

qreal Ruler::relevantDimension(QSizeF size) const
{
	return orientation() == Qt::Horizontal ? size.width() : size.height();
}

qreal Ruler::irrelevantDimension(QSizeF size) const
{
	return orientation() == Qt::Horizontal ? size.height() : size.width();
}

QPointF Ruler::makePoint(qreal relevantCoordinate, qreal irrelevantCoordinate) const
{
	return orientation() == Qt::Horizontal
			? QPointF(relevantCoordinate, irrelevantCoordinate)
			: QPointF(irrelevantCoordinate, relevantCoordinate);
}

QPointF Ruler::drawingPoint(qreal relevantCoordinate, QSizeF textSize) const
{
	return makePoint(relevantCoordinate, (irrelevantDimension(size()) - irrelevantDimension(textSize)) / 2);
}

QRectF Ruler::textBoundingRect(const QString &text) const
{
	return QFontMetrics(mFont).boundingRect(text);
}

void Ruler::setScene(QGraphicsView *scene)
{
	mView = scene;
}
