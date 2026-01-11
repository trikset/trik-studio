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

#include "loadWorldCommand.h"
#include "twoDModel/engine/model/model.h"

using namespace twoDModel::commands;

LoadWorldCommand::LoadWorldCommand(view::TwoDModelWidget &twoDwidget, const QDomDocument &data)
	: mWidget(twoDwidget)
	, mNewWorld(data)
	, mOldWorld(mWidget.generateWorldModelWithBlobsXml())
{
}

bool LoadWorldCommand::execute()
{
	loadWorld(mNewWorld.cloneNode().toDocument());
	return true;
}

bool LoadWorldCommand::restoreState()
{
	loadWorld(mOldWorld.cloneNode().toDocument());
	return true;
}

void LoadWorldCommand::loadWorld(const QDomDocument &world)
{
	// This is a very dirty solution, but if we want any diagnostics in xml based on a row/column in
	// the constraint parser, this information is lost during cloneNode.
	// Moreover, this approach may display incorrect lines when parsing constrintXml in several cases:
	// 1. The user uploaded the configuration without a robot and there really was no robots block in his xml,
	// which we will add later, so all positions (in theory) should be shifted by the size of this block.
	// 2.The user uses the old format, where certain information about the robot (such as rotation and startPosition)
	// is not in the <world>, which also requires reformatting the xml tree.
	const auto &worldString = world.toString(4);
	QDomDocument worldDocument;
	worldDocument.setContent(worldString);
	mWidget.loadXmls(worldDocument, true);
	Q_EMIT mWidget.model().modelChanged(mWidget.generateWorldModelXml());
	Q_EMIT mWidget.model().blobsChanged(mWidget.generateBlobsXml());
}
