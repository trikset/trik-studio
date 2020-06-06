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
	QDomDocument blobs;
	QDomNodeList blobsList = world.elementsByTagName("blobs");
	if (blobsList.length()) {
		QDomElement root = blobs.createElement("root");
		root.appendChild(blobsList.at(0));
		blobs.appendChild(root);
	} else {
		blobs = QDomDocument();
	}

	mWidget.loadXmls(world, blobs, true);
	Q_EMIT mWidget.model().modelChanged(mWidget.generateWorldModelXml());
	Q_EMIT mWidget.model().blobsChanged(mWidget.generateBlobsXml());
}
