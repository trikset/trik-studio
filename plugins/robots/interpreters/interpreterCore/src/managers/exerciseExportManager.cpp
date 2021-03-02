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

#include "exerciseExportManager.h"

#include <QtWidgets/QFileDialog>
#include <QtCore/QUuid>

#include <qrgui/models/logicalModelAssistApi.h>
#include <qrgui/plugins/toolPluginInterface/usedInterfaces/projectManagementInterface.h>
#include <qrrepo/repoControlInterface.h>
#include <qrutils/widgets/qRealFileDialog.h>

#include "src/ui/exerciseExportDialog.h"

using namespace interpreterCore;
using namespace kitBase;

ExerciseExportManager::ExerciseExportManager(qReal::LogicalModelAssistInterface &logicalModel
		, qrRepo::RepoControlInterface &repoControlApi, qReal::ProjectManagementInterface &projectManager)
	: mLogicalModel(logicalModel)
	, mRepoControlApi(repoControlApi)
	, mProjectManager(projectManager)
{
}

ExerciseExportManager::~ExerciseExportManager()
{
}

bool ExerciseExportManager::save()
{
	ui::ExerciseExportDialog dialog;
	if (dialog.exec() == QDialog::Rejected) {
		return true;
	}

	ReadOnlyFlags flags = dialog.readOnlyFlags();

	QString fileName = utils::QRealFileDialog::getSaveFileName("SaveAsTask"
			, nullptr
			, QObject::tr("Select file to export save to")
			, "."
			, QObject::tr("QReal Save File(*.qrs)"));

	if (fileName.isEmpty()) {
		return false;
	}

	if (!fileName.isEmpty() && !fileName.endsWith(".qrs", Qt::CaseInsensitive)) {
		fileName += ".qrs";
	}

	// Save meta information
	QHash<QString, QVariant> metaInfo;
	for (const auto &metaKey : mLogicalModel.logicalRepoApi().metaInformationKeys()) {
		metaInfo[metaKey] = mLogicalModel.logicalRepoApi().metaInformation(metaKey);
	}
	// Set new meta information
	const auto setFlag = [this, &flags] (const QString &tag, ReadOnly::ReadOnlyEnum flag) {
		mLogicalModel.mutableLogicalRepoApi().setMetaInformation(tag, flags.testFlag(flag));
	};
	setFlag("twoDModelWorldReadOnly", ReadOnly::World);
	setFlag("twoDModelSensorsReadOnly", ReadOnly::Sensors);
	setFlag("twoDModelRobotPositionReadOnly", ReadOnly::RobotPosition);
	setFlag("twoDModelRobotConfigurationReadOnly", ReadOnly::RobotSetup);
	setFlag("twoDModelSimulationSettingsReadOnly", ReadOnly::SimulationSettings);
	mLogicalModel.mutableLogicalRepoApi().setMetaInformation("exerciseId", QUuid::createUuid().toString());

	// Save exercise
	auto workingFile = mRepoControlApi.workingFile();
	mRepoControlApi.setWorkingFile(fileName);
	auto success = mRepoControlApi.saveAll();
	mRepoControlApi.setWorkingFile(workingFile);

	// Restore meta information
	mLogicalModel.mutableLogicalRepoApi().clearMetaInformation();
	for (const auto &metaKey : metaInfo.keys()) {
		mLogicalModel.mutableLogicalRepoApi().setMetaInformation(metaKey, metaInfo[metaKey]);
	}

	return success;
}
