/* Copyright 2020 CyberTech Labs Ltd.
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

#include "inputBlock.h"

using namespace qReal::interpretation::blocks;

InputBlock::InputBlock()
{
	connect(&mDialog, &QInputDialog::textValueSelected, this, &InputBlock::onValueSelected);
	connect(&mDialog, &QDialog::rejected, this, &InputBlock::onRejected);
	mDialog.setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
	mDialog.setWindowFlag(Qt::WindowStaysOnTopHint);
	mDialog.setWindowFlag(Qt::WindowContextHelpButtonHint, false);
	mDialog.setInputMode(QInputDialog::TextInput);
	mDialog.setWindowTitle(tr("Input"));
}

void InputBlock::run()
{
	const auto var = stringProperty("variable");
	const auto defaultValue = stringProperty("default");
	auto prompt = stringProperty("prompt");
	if (prompt.isEmpty()) {
		prompt = tr("Input value for %1:").arg(var);
	}
	mDialog.setLabelText(prompt);
	mDialog.setTextValue(defaultValue);
	mDialog.open();
}

bool InputBlock::initNextBlocks()
{
	mNextBlockId = Id();
	mCancelBlockId = Id();

	if (!isCorrectBlock() || !checkLinksCount()) {
		return false;
	}

	const IdList links = mGraphicalModelApi->graphicalRepoApi().outgoingLinks(id());
	for (const Id &linkId : links) {
		const Id targetBlockId = mGraphicalModelApi->graphicalRepoApi().otherEntityFromLink(linkId, id());
		if (targetBlockId.isNull() || targetBlockId == Id::rootId()) {
			error(tr("Outgoing link is not connected"));
			return false;
		}

		if (stringProperty(linkId, "Guard").toLower() == tr("cancel")) {
			if (mCancelBlockId.isNull()) {
				mCancelBlockId = targetBlockId;
			} else {
				error(tr("Two links marked with \"cancel\" found"));
				return false;
			}
		} else {
			if (mNextBlockId.isNull()) {
				mNextBlockId = targetBlockId;
			} else {
				error(tr("At least one of the two links must be marked with \"cancel\""));
				return false;
			}
		}
	}

	if (mNextBlockId.isNull()) {
		error(tr("At least one link must be not marked with \"cancel\""));
		return false;
	}

	return true;
}

void InputBlock::onValueSelected(const QString &text) {
	auto value = text;
	if (value.isEmpty()) {
		const auto defaultValue = stringProperty("default");
		if (defaultValue.isEmpty()) {
			onRejected();
			return;
		} else {
			value = defaultValue;
		}
	}
	evalCode(stringProperty("variable") + " = " + value);
	if (!errorsOccured()) {
		emit done(mNextBlockId);
	}
}

void InputBlock::onRejected() {
	if (mCancelBlockId.isNull()) {
		error(tr("You must input some value!"));
	} else {
		emit done(mCancelBlockId);
	}
}

bool InputBlock::checkLinksCount() {
	const IdList links = mGraphicalModelApi->graphicalRepoApi().outgoingLinks(id());
	if (links.count() == 0) {
		error(tr("No outgoing links, please connect this block to something or use Final Node to end program"));
		return false;
	}
	if (links.size() > 2) {
		error(tr("There should be a maximum of TWO links outgoing from input block"));
		return false;
	}
	return true;
}

void InputBlock::setFailedStatus()
{
	mDialog.close();
	Block::setFailedStatus();
}

InputBlock::~InputBlock()
{
	mDialog.deleteLater();
}
