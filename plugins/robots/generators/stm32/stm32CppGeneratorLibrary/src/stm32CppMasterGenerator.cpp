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

#include "stm32CppMasterGenerator.h"

#include "stm32CppControlFlowValidator.h"

using namespace stm32::cpp;

Stm32CppMasterGenerator::Stm32CppMasterGenerator(const qrRepo::RepoApi &repo
		, qReal::ErrorReporterInterface &errorReporter
		, const utils::ParserErrorReporter &parserErrorReporter
		, const kitBase::robotModel::RobotModelManagerInterface &robotModelManager
		, qrtext::LanguageToolboxInterface &textLanguage
		, const qReal::Id &diagramId
		, const QStringList &pathsToTemplates)
	: Stm32MasterGeneratorBase(repo, errorReporter, parserErrorReporter, robotModelManager, textLanguage
			, diagramId, pathsToTemplates)
{
}

QString Stm32CppMasterGenerator::targetPath()
{
	return QString("%1/%2.cpp").arg(mProjectDir, mProjectName);
}

bool Stm32CppMasterGenerator::supportsGotoGeneration() const
{
	return false;
}

generatorBase::PrimaryControlFlowValidator *Stm32CppMasterGenerator::createValidator()
{
	return new Stm32CppControlFlowValidator(mRepo, mErrorReporter, *mCustomizer, this);
}
