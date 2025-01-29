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

#include "replaceByCommand.h"

#include "nodeElement.h"
#include "edgeElement.h"

using namespace qReal;
using namespace qReal::commands;
using namespace qReal::gui::editor::commands;

ReplaceByCommand::ReplaceByCommand(const models::Models &models, gui::editor::EditorViewScene &scene
		, NodeElement *elementToRemove, const ElementInfo &elementToCreate)
	: mCreateCommand(models, {elementToCreate})
	, mRemoveCommand(models)
	, mScene(scene)
{
	mCreateCommand.setNewPosition(elementToRemove->pos());
	mRemoveCommand.withItemsToDelete({elementToRemove->id()});
}

void ReplaceByCommand::reconnect(ElementInfo &oldInfo, ElementInfo &newInfo)
{
	auto *removed = mScene.getNodeById(oldInfo.id());
	auto *created = mScene.getNodeById(newInfo.id());
	if (!removed || !created) return;
	for (auto edge : removed->edgeList()) {
		const auto &srcElem = removed == edge->src() ? created : edge->src();
		const auto &dstElem = removed == edge->dst() ? created : edge->dst();
		mScene.reConnectLink(edge, srcElem, dstElem);
	}
}

bool ReplaceByCommand::execute()
{
	mCreateCommand.redo();
	mNewInfo = mCreateCommand.results().first();
	mOldInfo = mRemoveCommand.results().first();
	reconnect(mOldInfo, mNewInfo);
	mRemoveCommand.redo();
	return true;
}

bool ReplaceByCommand::restoreState()
{
	mRemoveCommand.undo();
	reconnect(mNewInfo, mOldInfo);
	mCreateCommand.undo();
	return true;
}
