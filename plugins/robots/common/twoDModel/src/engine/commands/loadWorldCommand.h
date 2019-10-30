/* Copyright 2015-2016 CyberTech Labs Ltd.
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

#include <qrgui/controller/commands/abstractCommand.h>
#include <QtXml/QDomElement>
#include "twoDModel/engine/view/twoDModelWidget.h"

namespace twoDModel {
namespace commands {

/// Load 2D model world.
class LoadWorldCommand : public qReal::commands::AbstractCommand
{
public:
	/// Creates instance of command using XML \a data.
	LoadWorldCommand(view::TwoDModelWidget &twoDwidget, const QDomDocument data);

private:
	bool execute() override;
	bool restoreState() override;

	void loadWorld(QDomDocument world);

	view::TwoDModelWidget &mWidget;
	const QDomDocument mNewWorld;
	const QDomDocument mOldWorld;
};

}
}
