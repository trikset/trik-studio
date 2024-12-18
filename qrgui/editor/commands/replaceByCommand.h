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

#pragma once

#include "editor/editorViewScene.h"
#include "models/commands/createElementsCommand.h"
#include "models/commands/removeElementsCommand.h"

namespace qReal {
namespace gui {
namespace editor {
namespace commands {

class ReplaceByCommand : public qReal::commands::AbstractCommand
{
public:
	ReplaceByCommand(const models::Models &models, gui::editor::EditorViewScene &scene
			, NodeElement *elementToRemove, const ElementInfo &elementToCreate);
protected:
	bool execute() override;
	bool restoreState() override;

	qReal::commands::CreateElementsCommand mCreateCommand;
	qReal::commands::RemoveElementsCommand mRemoveCommand;

	EditorViewScene &mScene;

	ElementInfo mOldInfo;
	ElementInfo mNewInfo;
private:
	void reconnect(ElementInfo &oldInfo, ElementInfo &newInfo);
};

}
}
}
}
