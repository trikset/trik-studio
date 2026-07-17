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

#include <QtWidgets/QAbstractItemView>

#include "qrgui/models/details/modelsImplementation/abstractModel.h"

namespace qReal {
namespace models {
namespace details {
namespace modelsImplementation {

class AbstractView : public QAbstractItemView
{
	Q_OBJECT

public:
	explicit AbstractView(AbstractModel *const model);
	~AbstractView() override;

public Q_SLOTS:
	void rowsAboutToBeMoved(const QModelIndex &sourceParent, int sourceStart, int sourceEnd,
		const QModelIndex &destinationParent, int destinationRow);
	void rowsMoved(const QModelIndex &sourceParent, int sourceStart, int sourceEnd,
		const QModelIndex &destinationParent, int destinationRow);

protected Q_SLOTS:
	void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight,
		QVector<int> const &roles = QVector<int>()) override;
	void rowsAboutToBeRemoved(const QModelIndex &parent, int start, int end) override;
	void rowsInserted(const QModelIndex &parent, int start, int end) override;

protected:
	AbstractModel *const mModel;

	// Unneeded stuff from QAbstractItemView. It would be helpful if Qt Model/View framework
	// were moved to QtCore and got separated from GUI concerns, since Model/View pattern
	// is more general.
	QModelIndex indexAt(const QPoint &point) const override;
	QRect visualRect(const QModelIndex &index) const override;
	void scrollTo(const QModelIndex &index, ScrollHint hint = EnsureVisible) override;
	bool isDescendentOf(const QModelIndex &descendent, const QModelIndex &ancestor);
	QModelIndex moveCursor(QAbstractItemView::CursorAction cursorAction, Qt::KeyboardModifiers modifiers) override;
	int horizontalOffset() const override;
	int verticalOffset() const override;
	bool isIndexHidden(const QModelIndex &index) const override;
	void setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags command) override;
	QRegion visualRegionForSelection(const QItemSelection &selection) const override;
};

}
}
}
}
