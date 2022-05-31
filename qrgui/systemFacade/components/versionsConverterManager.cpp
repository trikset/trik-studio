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

#include "versionsConverterManager.h"

using namespace qReal;

VersionsConverterManager::VersionsConverterManager(models::Models &models, ToolPluginManager &toolManager)
	: mModels(models)
	, mConverters(toolManager.projectConverters())
{
}

bool VersionsConverterManager::validateCurrentProject()
{
	mConverted = false;
	mErrorMessage = QString();

	QSet<QString> editorsToCheck;
	const IdList allElements = mModels.logicalModelAssistApi().children(Id::rootId());
	for (const Id &element : allElements) {
		editorsToCheck << element.editor();
	}

	const QMap<Id, Version> savedVersions = mModels.logicalModelAssistApi().editorVersions();

	for (const QString &editor : editorsToCheck) {
		const Version currentVersion = mModels.logicalModelAssistApi()
				.editorManagerInterface().version(Id(editor));
		const Version savedVersion = savedVersions[Id(editor)];

		if (currentVersion == savedVersion) {
			continue;
		}

		if (currentVersion < savedVersion) {
			displayTooOldEnviromentError(savedVersion);
			return false;
		}

		QList<ProjectConverter> l;
		auto const &cs = mConverters.equal_range(editor);

		for(auto i = cs.first; i != cs.second && i!=mConverters.end(); ++i) {
			l.push_back(i->second);
		}

		if (!convertProject(currentVersion, savedVersion, l)) {
			return false;
		}
	}

	return true;
}

bool VersionsConverterManager::convertProject(const Version &enviromentVersion
		, const Version &saveVersion
		, QList<ProjectConverter> const &converters)
{
	// Stage I: Sorting converters by versions
	QList<ProjectConverter> sortedConverters = converters;
	std::sort(sortedConverters.begin(), sortedConverters.end()
		, [=](const ProjectConverter &converter1, const ProjectConverter &converter2)
	{
		return converter1.fromVersion() < converter2.fromVersion();
	});

	// Stage II: Checking that versions are not overlapped
	for (int index = 0; index < sortedConverters.count() - 1; ++index) {
		if (sortedConverters[index].toVersion() > sortedConverters[index + 1].fromVersion()) {
			qWarning() << "Converter versions are overlapped!";
			return false;
		}
	}

	bool converterApplied = false;

	// Stage III: Sequentially applying converters
	for (ProjectConverter &converter : sortedConverters) {
		if (converter.fromVersion() >= saveVersion && converter.toVersion() <= enviromentVersion) {
			const ProjectConverter::ConvertionResult result = converter.convert(
					mModels.graphicalModelAssistApi()
					, mModels.logicalModelAssistApi());
			switch (result) {
			case ProjectConverter::Success:
				converterApplied = true;
				break;
			case ProjectConverter::NoModificationsMade:
				break;
			case ProjectConverter::SaveInvalid:
				displayCannotConvertError();
				return false;
			case ProjectConverter::VersionTooOld:
				displayTooOldSaveError(saveVersion);
				return false;
			}
		}
	}

	// Stage IV: Notifying user
	if (converterApplied) {
		mConverted = true;
		mErrorMessage = QObject::tr("Project was automaticly converted from version %1 to version %2."\
				" Please check its contents.").arg(saveVersion.toString(), enviromentVersion.toString());
		mModels.mutableLogicalRepoApi().setMetaInformation(
				converters.first().editor() + "Version", enviromentVersion.toString());
	}

	return true;
}

void VersionsConverterManager::displayCannotConvertError()
{
	const QString errorMessage = QObject::tr("The attempt to automaticly convert this project "\
			"to the current enviroment version failed and thus save file can`t be opened. ");

	showError(errorMessage);
}

void VersionsConverterManager::displayTooOldSaveError(const Version &saveVersion)
{
	const bool showVersionDetails = saveVersion.isValid();
	const QString reason = showVersionDetails
			? QObject::tr("This project was created by version %1 of the editor.").arg(saveVersion.toString())
			: QObject::tr("This project was created by too old version of the editor.");

	const QString errorMessage = reason + QObject::tr(" It is now considered outdated and cannot be opened.");

	showError(errorMessage);
}

void VersionsConverterManager::displayTooOldEnviromentError(const Version &saveVersion)
{
	const QString errorMessage = QObject::tr("The save you are trying to open is made by version %1 of editor, "\
			"whitch is newer than currently installed enviroment. "\
			"Update your version before opening this save.").arg(saveVersion.toString());

	showError(errorMessage);
}

void VersionsConverterManager::showError(const QString &errorMessage)
{
	mErrorMessage = errorMessage;
}

bool VersionsConverterManager::converted() const
{
	return mConverted;
}

QString VersionsConverterManager::errorMessage() const
{
	return mErrorMessage;
}
