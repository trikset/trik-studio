/* Copyright 2007-2015 QReal Research Group
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

#include "interpreterCore/managers/devicesConfigurationManager.h"

#include <QtXml/QDomDocument>

#include <qrkernel/settingsManager.h>
#include <kitBase/robotModel/robotModelUtils.h>

using namespace interpreterCore;
using namespace kitBase;
using namespace robotModel;
using namespace qReal;

const QString diagramName = "RobotsDiagramNode";

DevicesConfigurationManager::DevicesConfigurationManager(
		qReal::GraphicalModelAssistInterface &graphicalModelAssistInterface
		, qReal::LogicalModelAssistInterface &logicalModelAssistInterface
		, qReal::gui::MainWindowInterpretersInterface &mainWindowInterpretersInterface
		, qReal::ProjectManagementInterface &projectManager
		)
	: DevicesConfigurationProvider("DevicesConfigurationManager")
	, mGraphicalModelAssistInterface(graphicalModelAssistInterface)
	, mLogicalModelAssistInterface(logicalModelAssistInterface)
	, mMainWindowInterpretersInterface(mainWindowInterpretersInterface)
{
	connect(&projectManager, &qReal::ProjectManagementInterface::afterOpen
			, this, &DevicesConfigurationManager::onOpenedProjectChanged);
	connect(&projectManager, &qReal::ProjectManagementInterface::closed
			, this, &DevicesConfigurationManager::onOpenedProjectChanged);
}

void DevicesConfigurationManager::load(const QString &worldModel)
{
	clearConfiguration(Reason::loading);
	QMap<QString, QMap<PortInfo, DeviceInfo>> const parsed = RobotModelUtils::deserializeFromWorldModel(worldModel);
	for (const QString &robotId : parsed.keys()) {
		for (const PortInfo &port : parsed[robotId].keys()) {
			deviceConfigurationChanged(robotId, port, parsed[robotId][port], Reason::loading);
		}
	}
}

Id DevicesConfigurationManager::mainDiagramId() const
{
	Id result;
	const IdList diagrams = mGraphicalModelAssistInterface.children(Id::rootId());
	for (const Id &logicalDiagramId : diagrams) {
		if (logicalDiagramId.element() == diagramName && mLogicalModelAssistInterface.isLogicalId(logicalDiagramId)) {
			if (!result.isNull()) {
				// Then there are more than two robot diagrams in this save, ignoring all of them...
				return Id();
			}

			result = logicalDiagramId;
		}
	}

	return result;
}

void DevicesConfigurationManager::onDeviceConfigurationChanged(const QString &robotId
		, const PortInfo &port, const DeviceInfo &sensor, Reason reason)
{
	Q_UNUSED(robotId)
	Q_UNUSED(port)
	Q_UNUSED(sensor)
	Q_UNUSED(reason)
}

void DevicesConfigurationManager::onOpenedProjectChanged()
{
	const Id logicalRootId = mGraphicalModelAssistInterface.logicalId(mMainWindowInterpretersInterface.activeDiagram());
	if (logicalRootId.element() != diagramName) {
		return;
	}

	const auto &worldModel = logicalRootId.isNull()
			? QString()
			: mLogicalModelAssistInterface.mutableLogicalRepoApi().metaInformation("worldModel").toString();
	load(worldModel);
}
