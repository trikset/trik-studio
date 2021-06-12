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

#include "blackBoxBlock.h"
#include <QMetaObject>
#include <QHeaderView>

using namespace qReal::interpretation::blocks;

enum Column {
	input = 0
	, output = 1
};

BlackBoxBlock::BlackBoxBlock()
	: mTable(new QTableWidget(1, 2))
{
	mTable->setItem(lastRaw(), input, new QTableWidgetItem());
	mTable->setVisible(false);
	mTable->setHorizontalHeaderLabels({"input", "output"});
	mTable->setAttribute(Qt::WA_DeleteOnClose);
	mTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	connect(mTable, &QWidget::destroyed, this, &BlackBoxBlock::finishTable);
	connect(mTable, &QTableWidget::cellChanged, this, &BlackBoxBlock::onCellChanged);
}

void BlackBoxBlock::run()
{
	mTable->setVisible(true);
}

void BlackBoxBlock::onCellChanged(int row, int col) {
	if (row == lastRaw() && col == input && !mTable->item(row, col)->text().isEmpty()) {
		// Find subprogram diagram
		const Id logicalId = mGraphicalModelApi->logicalId(id());
		const Id logicalDiagram = mLogicalModelApi->logicalRepoApi().outgoingExplosion(logicalId);
		const IdList diagrams = mGraphicalModelApi->graphicalIdsByLogicalId(logicalDiagram);
		if (!diagrams.isEmpty()) {
			// Add next row
			mTable->insertRow(mTable->rowCount());
			mTable->setItem(lastRaw(), input, new QTableWidgetItem());
			// Set last input not editable
			auto inputItem = mTable->item(lastRaw() - 1, input);
			inputItem->setFlags(inputItem->flags() ^ Qt::ItemIsEditable);
			// Set input value
			evalCode(mTable->horizontalHeaderItem(input)->text() + " = " + inputItem->text());
			// Goto subprogram
			emit stepInto(diagrams[0]);
		} else {
			error("Can't find diagram");
		}
	}
}

void BlackBoxBlock::finishedSteppingInto()
{
	// Put output to table and set it not editable
	auto res = evalCode<QString>(mTable->horizontalHeaderItem(output)->text());
	auto item = new QTableWidgetItem(res);
	item->setFlags(item->flags() ^ Qt::ItemIsEditable);
	mTable->setItem(lastRaw() - 1, output, item);
	// Goto start
	mTable->setCurrentCell(lastRaw(), input);
	emit done(id());
}

void BlackBoxBlock::finishTable()
{
	emit done(mNextBlockId);
}

int BlackBoxBlock::lastRaw()
{
	return mTable->rowCount() - 1;
}
