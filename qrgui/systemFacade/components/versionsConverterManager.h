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

#pragma once

#include "qrgui/models/models.h"
#include "qrgui/plugins/toolPluginInterface/projectConverter.h"
#include "qrgui/plugins/pluginManager/toolPluginManager.h"

namespace qReal {

/// Performs validation and convertion of models due to editor versions that created them.
/// @todo: This class is not implemented at the moment.
/// It only displays error message if versions mismatch detected.
class VersionsConverterManager
{
public:
	explicit VersionsConverterManager(models::Models &models, ToolPluginManager &toolManager);

	/// Performs validation and convertion of models due to editor versions that created them.
	bool validateCurrentProject();

	QString errorMessage() const;

	bool converted() const;

private:
	bool convertProject(const Version &enviromentVersion
			, const Version &saveVersion
			, QList<ProjectConverter> const &converters);

	void displayTooOldEnviromentError(const Version &saveVersion);
	void displayCannotConvertError();
	void displayTooOldSaveError(const Version &saveVersion);

	void showError(const QString &errorMessage);

	models::Models &mModels;
	const std::multimap<QString, ProjectConverter> mConverters;
	QString mErrorMessage;
	bool mConverted {false};
};

}
