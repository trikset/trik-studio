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

#include "stm32CppGeneratorPlugin.h"

#include <QtWidgets/QApplication>
#include <QtCore/QFileInfo>
#include <QtCore/QStateMachine>
#include <QtCore/QState>
#include <QtCore/QFinalState>
#include <QtCore/QDir>
#include <QtCore/QProcess>

#include <qrkernel/logging.h>
#include <stm32GeneratorBase/stm32GeneratorPluginBase.h>
#include <stm32GeneratorBase/robotModel/generatorModelExtensionInterface.h>
#include <stm32Kit/robotModel/stm32RobotModelBase.h>

#include "stm32CppMasterGenerator.h"

using namespace stm32::cpp;
using namespace kitBase::robotModel;
using namespace qReal;

Stm32CppGeneratorPlugin::Stm32CppGeneratorPlugin()
    : Stm32GeneratorPluginBase("Stm32CppGeneratorRobotModel", tr("Generation (C++)"), 9 /* After 2D model */)
	, mGenerateCodeAction(new QAction(nullptr))
	, mUploadProgramAction(new QAction(nullptr))
	, mRunProgramAction(new QAction(nullptr))
	, mStopRobotAction(new QAction(nullptr))
    , mPathsToTemplates({":/stm32Cpp/templates"})
{
}

Stm32CppGeneratorPlugin::~Stm32CppGeneratorPlugin()
{
}

void Stm32CppGeneratorPlugin::init(const kitBase::KitPluginConfigurator &configurer)
{
	RobotsGeneratorPluginBase::init(configurer);
}

QList<ActionInfo> Stm32CppGeneratorPlugin::customActions()
{
	mGenerateCodeAction->setObjectName("generateSTM32Code");
	mGenerateCodeAction->setText(tr("Generate STM32 code"));
	mGenerateCodeAction->setIcon(QIcon(":/stm32/cpp/images/generateCppCode.svg"));
	ActionInfo generateCodeActionInfo(mGenerateCodeAction, "generators", "tools");
	connect(mGenerateCodeAction, SIGNAL(triggered()), this, SLOT(generateCode()), Qt::UniqueConnection);

	mUploadProgramAction->setObjectName("uploadProgram");
	mUploadProgramAction->setText(tr("Upload program"));
	mUploadProgramAction->setIcon(QIcon(":/stm32/cpp/images/uploadProgram.svg"));
	ActionInfo uploadProgramActionInfo(mUploadProgramAction, "generators", "tools");
	connect(mUploadProgramAction, SIGNAL(triggered()), this, SLOT(uploadProgram()), Qt::UniqueConnection);

	mRunProgramAction->setObjectName("runProgram");
	mRunProgramAction->setText(tr("Run program"));
	mRunProgramAction->setIcon(QIcon(":/stm32/cpp/images/run.png"));
	ActionInfo runProgramActionInfo(mRunProgramAction, "interpreters", "tools");
	connect(mRunProgramAction, SIGNAL(triggered()), this, SLOT(runProgram()), Qt::UniqueConnection);

	mStopRobotAction->setObjectName("stopRobot");
	mStopRobotAction->setText(tr("Stop robot"));
	mStopRobotAction->setIcon(QIcon(":/stm32/cpp/images/stop.png"));
	ActionInfo stopRobotActionInfo(mStopRobotAction, "interpreters", "tools");
	connect(mStopRobotAction, SIGNAL(triggered()), this, SLOT(stopRobot()), Qt::UniqueConnection);

	return {generateCodeActionInfo, uploadProgramActionInfo, runProgramActionInfo, stopRobotActionInfo};
}

QList<HotKeyActionInfo> Stm32CppGeneratorPlugin::hotKeyActions()
{
	mGenerateCodeAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_G));
	mUploadProgramAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_U));
	mRunProgramAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F5));
	mStopRobotAction->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_F5));

	HotKeyActionInfo generateCodeInfo("Generator.GenerateStm32", tr("Generate STM32 Code"), mGenerateCodeAction);
	HotKeyActionInfo uploadProgramInfo("Generator.UploadStm32", tr("Upload STM32 Program"), mUploadProgramAction);
	HotKeyActionInfo runProgramInfo("Generator.RunStm32", tr("Run STM32 Program"), mRunProgramAction);
	HotKeyActionInfo stopRobotInfo("Generator.StopStm32", tr("Stop STM32 Robot"), mStopRobotAction);

	return {generateCodeInfo, uploadProgramInfo, runProgramInfo, stopRobotInfo};
}

QIcon Stm32CppGeneratorPlugin::iconForFastSelector(const RobotModelInterface &robotModel) const
{
	Q_UNUSED(robotModel)

	return QIcon(":/stm32/cpp/images/switch-to-stm32-cpp.svg");
}

generatorBase::MasterGeneratorBase *Stm32CppGeneratorPlugin::masterGenerator()
{
	return new Stm32CppMasterGenerator(*mRepo
			, *mMainWindowInterface->errorReporter()
			, *mParserErrorReporter
			, *mRobotModelManager
			, *mTextLanguage
			, mMainWindowInterface->activeDiagram()
			, mPathsToTemplates);
}

QString Stm32CppGeneratorPlugin::defaultFilePath(const QString &projectName) const
{
	return QString("stm32/%1/%1.cpp").arg(projectName);
}

text::LanguageInfo Stm32CppGeneratorPlugin::language() const
{
	return qReal::text::Languages::cpp({"brick"});
}

QString Stm32CppGeneratorPlugin::generatorName() const
{
	return "stm32Cpp";
}

void Stm32CppGeneratorPlugin::uploadProgram()
{
	QProcess compileProcess;
	const QFileInfo fileInfo = generateCodeForProcessing();

#ifdef Q_OS_WIN

	const QFileInfo compileFile = QFileInfo("./libraries/compileAndUploadWin.bat");
	const QString compileBatch = compileFile.absoluteFilePath();

	compileProcess.setWorkingDirectory(fileInfo.absoluteDir().path());

	compileProcess.start("cmd", {"/C", compileBatch});
#endif

#ifdef Q_OS_LINUX
	const QFileInfo compileFile = QFileInfo("./libraries/compileAndUploadLinux.sh");
	const QString compileBatch = compileFile.absoluteFilePath();

	compileProcess.setWorkingDirectory(fileInfo.absoluteDir().path());

	QProcess makeScriptExecutable;
	makeScriptExecutable.start("chmod", {"a+x", compileBatch});

	makeScriptExecutable.waitForStarted();
	if (makeScriptExecutable.state() != QProcess::Running) {
		mMainWindowInterface->errorReporter()->addError(tr("Script is wrong!"));
		return;
	}

	makeScriptExecutable.waitForFinished();

	compileProcess.start("sh", {"-c", compileBatch});
#endif

#ifdef Q_OS_MAC
	const QFileInfo compileFile = QFileInfo("./libraries/compileAndUploadMacOS.sh");
	const QString compileBatch = compileFile.absoluteFilePath();

	compileProcess.setWorkingDirectory(fileInfo.absoluteDir().path());

	QProcess makeScriptExecutable;
	makeScriptExecutable.start("chmod", {"a+x", compileBatch});

	makeScriptExecutable.waitForStarted();
	if (makeScriptExecutable.state() != QProcess::Running) {
		mMainWindowInterface->errorReporter()->addError(tr("Script is wrong!"));
		return;
	}

	makeScriptExecutable.waitForFinished();

	compileProcess.start("sh", {"-c", compileBatch});
#endif

	compileProcess.waitForStarted();
	if (compileProcess.state() != QProcess::Running) {
		mMainWindowInterface->errorReporter()->addError(tr("Unable to launch assembly"));
		return;
	}

	compileProcess.waitForFinished();

	QStringList errors = QString(compileProcess.readAllStandardError()).split("\n", QString::SkipEmptyParts);
	errors << QString(compileProcess.readAllStandardOutput()).split("\n", QString::SkipEmptyParts);
	for (const auto &error : errors) {
		mMainWindowInterface->errorReporter()->addInformation(error);
	}

	return;
}

void Stm32CppGeneratorPlugin::runProgram()
{
	uploadProgram();
}

void Stm32CppGeneratorPlugin::stopRobot()
{
}

void Stm32CppGeneratorPlugin::onProtocolFinished()
{
	mUploadProgramAction->setEnabled(true);
	mRunProgramAction->setEnabled(true);
	mStopRobotAction->setEnabled(true);
}

void Stm32CppGeneratorPlugin::disableButtons()
{
	mUploadProgramAction->setEnabled(false);
	mRunProgramAction->setEnabled(false);
	mStopRobotAction->setEnabled(false);
}
