/* Copyright 2021 CyberTech Labs Ltd.
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

#include "qrutils/interpreter/block.h"
#include <QTableWidget>
#include <QPushButton>

namespace qReal {
namespace interpretation {
namespace blocks {


/// Interpreter`s implementation for subprogram block.
/// Starts explosed diagram interpretation using stepInto(Id) signal.
class QRUTILS_EXPORT BlackBoxBlock : public Block
{
	Q_OBJECT

public:
	BlackBoxBlock();

	void run() override;
	void finishedSteppingInto() override;

public slots:
	void finishTable();

private slots:
	void onChanged(QTableWidgetItem* item);

private:
	void setNotEditable(QTableWidgetItem* item);
	int lastInputRow();
	void activateCell(QTableWidgetItem* item);
	QTableWidget* mTable;
	QList<QTableWidgetItem*> mInputItems;
	QTableWidgetItem* mRunItem;
	QPushButton* mFinishButton;
	bool mIsRunning;
};

}
}
}
