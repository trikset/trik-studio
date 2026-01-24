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

#pragma once

#include <QtWidgets/QFrame>

class QGraphicsView;

namespace twoDModel {
namespace model {
class SizeUnit;
}
namespace view {

/// A widget for displaying distances on grid in centimeters.
class Ruler : public QFrame
{
	Q_OBJECT

	Q_PROPERTY(Qt::Orientation orientation READ orientation WRITE setOrientation)

public:
	explicit Ruler(QWidget *parent = nullptr);
	~Ruler() override;

	/// Returns the orientation of this ruler.
	Qt::Orientation orientation() const;

public Q_SLOTS:
	/// Returns the orientation of this ruler.
	void setOrientation(Qt::Orientation orientation);

	void onSizeUnitChanged(const QSharedPointer<twoDModel::model::SizeUnit> &unit);

	/// Configures this ruller to work with the given graphics view.
	void setScene(QGraphicsView *scene);
private:
	void paintEvent(QPaintEvent *event) override;

	qreal relevantCoordinate(QPointF point) const;
	qreal countFactor() const;
	qreal relevantDimension(QSizeF size) const;
	qreal irrelevantDimension(QSizeF size) const;
	QPointF makePoint(qreal relevantCoordinate, qreal irrelevantCoordinate) const;
	QPointF drawingPoint(qreal relevantCoordinate, QSizeF textSize) const;
	QRectF textBoundingRect(const QString &text) const;
	Qt::Orientation mOrientation;
	QSharedPointer<twoDModel::model::SizeUnit> mSizeUnit;
	QGraphicsView *mView {};  // Doesn`t take owership
	QFont mFont;
};

}
}
