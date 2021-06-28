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
	: mTable(new QTableWidget(1, 0))
	, mFinishButton(new QPushButton(tr("Finish")))
{
	mTable->setAttribute(Qt::WA_DeleteOnClose);
	mTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	mTable->setWindowFlag(Qt::WindowStaysOnTopHint);
	mTable->move(170, 200);
	connect(mTable, &QWidget::destroyed, this, &BlackBoxBlock::finishTable);
	connect(mTable, &QTableWidget::itemChanged, this, &BlackBoxBlock::onChanged);
	connect(mFinishButton, &QPushButton::pressed, this, &BlackBoxBlock::finishTable);
}

void BlackBoxBlock::setNotEditable(QTableWidgetItem* item) {
	item->setFlags(item->flags() ^ Qt::ItemIsEditable);
}

void BlackBoxBlock::run()
{
	bool ok;
	int inputsCount = mLogicalModelApi->logicalRepoApi().property(
			mGraphicalModelApi->logicalId(id()), "inputsCount").toInt(&ok);
	if (!ok) {
		error(tr("Inputs count must be int"));
		return;
	} else if (inputsCount < 1) {
		error(tr("Inputs count must be more or equal to 1"));
		return;
	}
	mTable->setColumnCount(inputsCount + 1);
	QStringList headers;
	if (inputsCount == 1) {
		headers << "input";
		mInputItems.append(new QTableWidgetItem());
		mTable->setItem(lastRow(), 0, mInputItems[0]);
	} else {
		for (int i = 0; i < inputsCount; i++) {
			mInputItems.append(new QTableWidgetItem());
			mTable->setItem(lastRow(), i, mInputItems[i]);
			headers << "input" + QString::number(i + 1);
		}
	}
	headers << "output";
	mTable->setHorizontalHeaderLabels(headers);
	mTable->setCellWidget(lastRow(), mInputItems.size(), mFinishButton);

	mTable->setWindowTitle("Black Box");
	mTable->resize(140 * (mInputItems.size() + 1), 720);
	mTable->setVisible(true);
}

void BlackBoxBlock::onChanged(QTableWidgetItem* item) {
	if (mInputItems.contains(item)) {
		for (int i = 0; i < mInputItems.size(); i++) {
			if (mInputItems[i]->text().isEmpty()) {
				activateCell(mInputItems[i]);
				return;
			}
		}
		// Find subprogram diagram
		const Id logicalId = mGraphicalModelApi->logicalId(id());
		const Id logicalDiagram = mLogicalModelApi->logicalRepoApi().outgoingExplosion(logicalId);
		const IdList diagrams = mGraphicalModelApi->graphicalIdsByLogicalId(logicalDiagram);
		if (!diagrams.isEmpty()) {
			for (int i = 0; i < mInputItems.size(); i++) {
				evalCode(mTable->horizontalHeaderItem(i)->text() + " = " + mInputItems[i]->text());
			}
			emit stepInto(diagrams[0]);
		} else {
			error(tr("Can't find diagram"));
		}
	}
}

void BlackBoxBlock::finishedSteppingInto()
{
	QList<QString> lastInputs;
	for (int i = 0; i < mInputItems.size(); i++) {
		lastInputs.append(mInputItems[i]->text());
		mInputItems[i]->setText("");
	}

	// Add row for results
	mTable->insertRow(mTable->rowCount() - 1);

	for (int i = 0; i < mInputItems.size(); i++) {
		auto curInput = new QTableWidgetItem(lastInputs[i]);
		setNotEditable(curInput);
		mTable->setItem(lastRow() - 1, i, curInput);
	}

	auto res = evalCode<QString>(mTable->horizontalHeaderItem(mInputItems.size())->text());
	auto curOutput = new QTableWidgetItem(res);
	setNotEditable(curOutput);
	mTable->setItem(lastRow() - 1, mInputItems.size(), curOutput);

	// Goto start
	activateCell(mInputItems[0]);
}

void BlackBoxBlock::finishTable()
{
	mTable->removeRow(lastRow());
	emit done(mNextBlockId);
}

int BlackBoxBlock::lastRow()
{
	return mTable->rowCount() - 1;
}

void BlackBoxBlock::activateCell(QTableWidgetItem* item)
{
	mTable->setCurrentItem(item);
	mTable->scrollToItem(item);
}
