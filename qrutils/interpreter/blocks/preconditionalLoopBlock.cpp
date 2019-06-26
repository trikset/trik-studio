/* Copyright 2019 CyberTech Labs Ltd.
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

#include "preconditionalLoopBlock.h"

using namespace qReal::interpretation::blocks;

PreconditionalLoopBlock::PreconditionalLoopBlock()
{
}

void PreconditionalLoopBlock::run()
{
	const bool expressionValue = eval<bool>("Condition");
	if (!errorsOccured()) {
		emit done(expressionValue ? mLoopStartBlockId : mNextBlockId);
	}
}

bool PreconditionalLoopBlock::initNextBlocks()
{
	bool conditionFound = false;
	bool nextFound = false;

	const auto & links = mGraphicalModelApi->graphicalRepoApi().outgoingLinks(id());

	for (auto && linkId : links) {
		const auto & targetBlockId = mGraphicalModelApi->graphicalRepoApi().otherEntityFromLink(linkId, id());
		if (targetBlockId.isNull()) {
			error(tr("Outgoing link is not connected"));
			return false;
		}

		const auto & guard = stringProperty(linkId, "Guard").toLower();
		if (guard == "iteration") {
			if (!conditionFound) {
				mLoopStartBlockId = targetBlockId;
				conditionFound = true;
			} else {
				error(tr("Two links marked as \"body\" found"));
				return false;
			}
		} else if (guard == "") {
			if (!nextFound) {
				mNextBlockId = targetBlockId;
				nextFound = true;
			} else {
				error(tr("There must be a link with \"body\" marker on it"));
				return false;
			}
		}
	}

	if (!conditionFound) {
		error(tr("There must be a link with \"body\" marker on it"));
		return false;
	}

	if (!nextFound) {
		error(tr("There must be a non-marked outgoing link"));
		return false;
	}

	return true;
}
