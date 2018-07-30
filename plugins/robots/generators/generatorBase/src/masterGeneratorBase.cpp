/* Copyright 2013-2016 CyberTech Labs Ltd., Dmitry Mordvinov
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

#include "generatorBase/masterGeneratorBase.h"

#include <QtCore/QDir>
#include <QtCore/QPair>
#include <QtCore/QStack>
#include <QtCore/QRegularExpression>

#include <qrutils/outFile.h>
#include <qrutils/fileSystemUtils.h>
#include <qrutils/stringUtils.h>
#include <qrtext/languageToolboxInterface.h>

#include "structuralControlFlowGenerator.h"
#include "generatorBase/gotoControlFlowGenerator.h"
#include "generatorBase/lua/luaProcessor.h"
#include "generatorBase/parts/variables.h"
#include "generatorBase/parts/subprograms.h"
#include "generatorBase/parts/threads.h"
#include "generatorBase/parts/sensors.h"
#include "generatorBase/parts/initTerminateCodeGenerator.h"

using namespace generatorBase;
using namespace qReal;

MasterGeneratorBase::MasterGeneratorBase(const qrRepo::RepoApi &repo
		, ErrorReporterInterface &errorReporter
		, const kitBase::robotModel::RobotModelManagerInterface &robotModelManager
		, qrtext::LanguageToolboxInterface &textLanguage
		, const utils::ParserErrorReporter &parserErrorReporter
		, const Id &diagramId)
	: mRepo(repo)
	, mErrorReporter(errorReporter)
	, mRobotModelManager(robotModelManager)
	, mTextLanguage(textLanguage)
	, mDiagram(diagramId)
	, mParserErrorReporter(parserErrorReporter)
{
}

void MasterGeneratorBase::setProjectDir(const QFileInfo &fileInfo)
{
	mProjectName = fileInfo.completeBaseName();
	mProjectDir = fileInfo.absolutePath();
}

void MasterGeneratorBase::initialize()
{
	mCustomizer = createCustomizer();
	mCustomizer->factory()->initialize();
	setPathsToTemplates(mCustomizer->factory()->pathsToTemplates());

	mValidator = createValidator();

	mGotoControlFlowGenerator = new GotoControlFlowGenerator(mRepo
			, mErrorReporter, *mCustomizer, *mValidator, mDiagram, this);
	mStructuralControlFlowGenerator = new StructuralControlFlowGenerator(mRepo
			, mErrorReporter, *mCustomizer, *mValidator, mDiagram, this);
}

QString MasterGeneratorBase::generate(const QString &indentString)
{
	if (mDiagram.isNull()) {
		mErrorReporter.addCritical(QObject::tr("There is no opened diagram"));
		return QString();
	}

	beforeGeneration();
	if (!QDir(mProjectDir).exists()) {
		QDir().mkpath(mProjectDir);
	}

	mTextLanguage.clear();
	mCustomizer->factory()->setMainDiagramId(mDiagram);

	for (parts::InitTerminateCodeGenerator *generator : mCustomizer->factory()->initTerminateGenerators()) {
		generator->reinit();
	}



	QString mainCode;
	const semantics::SemanticTree *mainControlFlow = mStructuralControlFlowGenerator->generate();
	if (mainControlFlow && !mStructuralControlFlowGenerator->cantBeGeneratedIntoStructuredCode()) {
		mainCode = mainControlFlow->toString(1, indentString);
		const parts::Subprograms::GenerationResult subprogramsResult = mCustomizer->factory()->subprograms()->generate(
				mStructuralControlFlowGenerator, indentString);
		switch (subprogramsResult) {
		case parts::Subprograms::GenerationResult::success:
			break;
		case parts::Subprograms::GenerationResult::error:
			mainCode = QString();
			break;
		case parts::Subprograms::GenerationResult::fatalError:
			return QString();
		}
	} else {
		if (mStructuralControlFlowGenerator->errorsOccured()) {
			return QString();
		}
	}

	if (mainCode.isEmpty() && supportsGotoGeneration()) {
		mErrorReporter.addInformation(tr("This diagram cannot be generated into the structured code."\
				" Generating it into the code with 'goto' statements."));
		const semantics::SemanticTree *gotoMainControlFlow = mGotoControlFlowGenerator->generate();
		if (gotoMainControlFlow) {
			mainCode = gotoMainControlFlow->toString(1, indentString);
			const parts::Subprograms::GenerationResult gotoSubprogramsResult = mCustomizer->factory()
					->subprograms()->generate(mGotoControlFlowGenerator, indentString);
			if (gotoSubprogramsResult != parts::Subprograms::GenerationResult::success) {
				mainCode = QString();
			}
		}
	}

	if (mainCode.isEmpty()) {
		const QString errorMessage = supportsGotoGeneration()
				? tr("This diagram cannot be even generated into the code with 'goto'"\
						"statements. Please contact the developers (WTF did you do?)")
				: tr("This diagram cannot be generated into the structured code.");
		mErrorReporter.addError(errorMessage);
		return QString();
	}

	QString resultCode = readTemplate("main.t");
	replaceWithAutoIndent(resultCode, "@@SUBPROGRAMS_FORWARDING@@"
			, mCustomizer->factory()->subprograms()->forwardDeclarations());
	replaceWithAutoIndent(resultCode, "@@SUBPROGRAMS@@"
			, mCustomizer->factory()->subprograms()->implementations());
	replaceWithAutoIndent(resultCode, "@@THREADS_FORWARDING@@"
			, mCustomizer->factory()->threads().generateDeclarations());
	replaceWithAutoIndent(resultCode, "@@THREADS@@"
			, mCustomizer->factory()->threads().generateImplementations(indentString));
	replaceWithAutoIndent(resultCode, "@@MAIN_CODE@@", mainCode);
	replaceWithAutoIndent(resultCode, "@@INITHOOKS@@", utils::StringUtils::addIndent(
			mCustomizer->factory()->initCode(), 1, indentString));
	replaceWithAutoIndent(resultCode, "@@TERMINATEHOOKS@@", utils::StringUtils::addIndent(
			mCustomizer->factory()->terminateCode(), 1, indentString));
	replaceWithAutoIndent(resultCode, "@@USERISRHOOKS@@", utils::StringUtils::addIndent(
			mCustomizer->factory()->isrHooksCode(), 1, indentString));
	const QString constantsString = mCustomizer->factory()->variables()->generateConstantsString();
	const QString variablesString = mCustomizer->factory()->variables()->generateVariableString();
	if (resultCode.contains("@@CONSTANTS@@")) {
		replaceWithAutoIndent(resultCode, "@@CONSTANTS@@", constantsString);
		replaceWithAutoIndent(resultCode, "@@VARIABLES@@", variablesString);
	} else {
		replaceWithAutoIndent(resultCode, "@@VARIABLES@@", constantsString + "\n" + variablesString);
	}

	// This will remove too many empty lines
	resultCode.replace(QRegExp("\n(\n)+"), "\n\n");

	processGeneratedCode(resultCode);

	generateLinkingInfo(resultCode);

	const QString pathToOutput = targetPath();
	outputCode(pathToOutput, resultCode);

	afterGeneration();

	return pathToOutput;
}

void MasterGeneratorBase::generateLinkingInfo(QString &resultCode)
{
	const QString open = "@~(qrm:(/\\w+)+/\\{(\\w+-)+\\w+\\})~@";
	const QString close = "@#%1#@";
	QRegExp re;
	QStack<QPair<QString, int>> stack;
	QList<QPair<QString, QPair<int, int>>> results;
	int lineNumber = 1;

	for (const QString &line : resultCode.split("\n")){
		re.setPattern(open);
		const int pos = re.indexIn(line);
		if (pos > -1) {
			const QString id = re.cap(1);
			stack.push(QPair<QString, int>(id, lineNumber));
		}

		if (!stack.isEmpty()) {
			const QString id = stack.top().first;
			if (line.contains(close.arg(id))) {
				results.append(qMakePair(id, qMakePair(stack.top().second, lineNumber)));
				stack.pop();
			}
		}

		lineNumber++;
	}

	QString out;

	qSort(results.begin(), results.end()
			, [](QPair<QString, QPair<int, int>> r1, QPair<QString, QPair<int, int>> r2) -> bool {
				return r1.second.first < r2.second.first;
			});

	for (const QPair<QString, QPair<int, int>> &res : results) {
		out += QString("%1@%2@%3\n").arg(res.first
				, QString::number(res.second.first)
				, QString::number(res.second.second));
	}

	outputCode(targetPath() + ".dbg", out);

	cleanUpLinkingInfo(resultCode);
}

void MasterGeneratorBase::cleanUpLinkingInfo(QString &code)
{
	code.remove(QRegExp("@(~|#)qrm:(((/\\w+)+/\\{(\\w+-)+\\w+\\})|(/))(~|#)@"));
}

lua::LuaProcessor *MasterGeneratorBase::createLuaProcessor()
{
	return new lua::LuaProcessor(mErrorReporter, mTextLanguage, mParserErrorReporter, this);
}

PrimaryControlFlowValidator *MasterGeneratorBase::createValidator()
{
	return new PrimaryControlFlowValidator(mRepo, mErrorReporter, *mCustomizer, this);
}

bool MasterGeneratorBase::supportsSwitchUnstableToBreaks() const
{
	return false;
}

void MasterGeneratorBase::beforeGeneration()
{
}

void MasterGeneratorBase::processGeneratedCode(QString &generatedCode)
{
	Q_UNUSED(generatedCode)
}

void MasterGeneratorBase::afterGeneration()
{
}

void MasterGeneratorBase::outputCode(const QString &path, const QString &code)
{
	QFile::remove(path);

	// File creation and modified timestamps should be equal after all.
	// But straitforward removal will not work due to the tunel file system effect:
	// http://stackoverflow.com/questions/661977/why-windows-sets-new-created-files-created-time-property-to-old-time
	utils::OutFile out(path);
	utils::FileSystemUtils::setCreationDateToNow(path);
	out() << code;
}

void MasterGeneratorBase::replaceWithAutoIndent(QString &where, const QString &what, const QString &withWhat)
{
	const QRegularExpression regexp(QString("^(([ \\t]*)%1)$").arg(what), QRegularExpression::MultilineOption);
	const QRegularExpressionMatch match = regexp.match(where, 0
			, QRegularExpression::NormalMatch, QRegularExpression::NoMatchOption);
	if (match.hasMatch()) {
		const QString wholeString = match.captured(1);
		const QString indentString = match.captured(2);
		where.replace(wholeString, utils::StringUtils::addIndent(withWhat, 1, indentString));
	}
}
