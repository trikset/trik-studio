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
#include <QHeaderView>

using namespace qReal::interpretation::blocks;

enum Column {
	input = 0
	, output = 1
};

BlackBoxBlock::BlackBoxBlock()
	: mTable(new QTableWidget(1, 2))
{
	inputItem = new QTableWidgetItem();
	outputItem = new QTableWidgetItem("Finish");
	setNotEditable(outputItem);
	mTable->setItem(lastRaw(), input, inputItem);
	mTable->setItem(lastRaw(), output, outputItem);
	mTable->setVisible(false);
	mTable->setHorizontalHeaderLabels({"input", "output"});
	mTable->setAttribute(Qt::WA_DeleteOnClose);
	mTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	mTable->setWindowFlag(Qt::WindowStaysOnTopHint);
	mTable->resize(280, 720);
	mTable->move(170, 200);
	connect(mTable, &QWidget::destroyed, this, &BlackBoxBlock::finishTable);
	connect(mTable, &QTableWidget::itemChanged, this, &BlackBoxBlock::onChanged);
	connect(mTable, &QTableWidget::itemDoubleClicked, this, &BlackBoxBlock::onDoubleClick);
}

void BlackBoxBlock::setNotEditable(QTableWidgetItem* item) {
	item->setFlags(item->flags() ^ Qt::ItemIsEditable);
}

void BlackBoxBlock::run()
{
	mTable->setWindowTitle("Black Box");
	mTable->setVisible(true);
}

void BlackBoxBlock::onDoubleClick(QTableWidgetItem* item) {
	if (item == outputItem) {
		mTable->removeRow(lastRaw());
		finishTable();
	}
}

void BlackBoxBlock::onChanged(QTableWidgetItem* item) {
	if (item == inputItem && !item->text().isEmpty()) {
		// Find subprogram diagram
		const Id logicalId = mGraphicalModelApi->logicalId(id());
		const Id logicalDiagram = mLogicalModelApi->logicalRepoApi().outgoingExplosion(logicalId);
		const IdList diagrams = mGraphicalModelApi->graphicalIdsByLogicalId(logicalDiagram);
		if (!diagrams.isEmpty()) {
			evalCode(mTable->horizontalHeaderItem(input)->text() + " = " + inputItem->text());
			emit stepInto(diagrams[0]);
		} else {
			error("Can't find diagram");
		}
	}
}

void BlackBoxBlock::finishedSteppingInto()
{
	auto lastInput = inputItem->text();
	inputItem->setText("");

	// Add raw for results
	mTable->insertRow(mTable->rowCount() - 1);

	auto curInput = new QTableWidgetItem(lastInput);
	setNotEditable(curInput);
	mTable->setItem(lastRaw() - 1, input, curInput);

	auto res = evalCode<QString>(mTable->horizontalHeaderItem(output)->text());
	auto curOutput = new QTableWidgetItem(res);
	setNotEditable(curOutput);
	mTable->setItem(lastRaw() - 1, output, curOutput);

	// Goto start
	mTable->setCurrentItem(inputItem);
	mTable->scrollToItem(inputItem);
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
