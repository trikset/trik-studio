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

#include "trikCppGeneratorLibrary/trikCppGeneratorPluginBase.h"

#include <QtWidgets/QApplication>
#include <QtCore/QFileInfo>
#include <QtCore/QStateMachine>
#include <QtCore/QState>
#include <QtCore/QFinalState>
#include <QtCore/QDir>
#include <QtCore/QProcess>

#include <qrkernel/logging.h>
#include <trikGeneratorBase/trikGeneratorPluginBase.h>
#include <trikGeneratorBase/robotModel/generatorModelExtensionInterface.h>
#include <trikKit/robotModel/trikRobotModelBase.h>
#include <utils/robotCommunication/tcpRobotCommunicator.h>
#include <utils/robotCommunication/runProgramProtocol.h>
#include <utils/robotCommunication/stopRobotProtocol.h>
#include <utils/robotCommunication/uploadProgramProtocol.h>
#include <utils/robotCommunication/networkCommunicationErrorReporter.h>

#include "trikCppMasterGenerator.h"
#include "emptyShell.h"

using namespace trik::cpp;
using namespace kitBase::robotModel;
using namespace qReal;
using namespace utils::robotCommunication;

TrikCppGeneratorPluginBase::TrikCppGeneratorPluginBase(
		trik::robotModel::TrikRobotModelBase * const robotModel
		, kitBase::blocksBase::BlocksFactoryInterface * const blocksFactory
		, const QStringList &pathsToTemplates)
	: TrikGeneratorPluginBase(robotModel, blocksFactory)
	, mGenerateCodeAction(new QAction(nullptr))
	, mUploadProgramAction(new QAction(nullptr))
	, mRunProgramAction(new QAction(nullptr))
	, mStopRobotAction(new QAction(nullptr))
	, mRobotModel(*robotModel)
	, mPathsToTemplates(pathsToTemplates)
{
}

TrikCppGeneratorPluginBase::~TrikCppGeneratorPluginBase()
{
}

void TrikCppGeneratorPluginBase::init(const kitBase::KitPluginConfigurator &configurer)
{
	const auto errorReporter = configurer.qRealConfigurator().mainWindowInterpretersInterface().errorReporter();
	RobotsGeneratorPluginBase::init(configurer);
	mCommunicator.reset(new TcpRobotCommunicator("TrikTcpServer"));
	NetworkCommunicationErrorReporter::connectErrorReporter(*mCommunicator, *errorReporter);

	mUploadProgramProtocol.reset(new UploadProgramProtocol(*mCommunicator));
	mRunProgramProtocol.reset(new RunProgramProtocol(*mCommunicator, mRobotModel.robotConfigFileVersion()));
	mStopRobotProtocol.reset(new StopRobotProtocol(*mCommunicator));

	const auto timeout = [this, errorReporter]() {
		errorReporter->addError(tr("Network operation timed out"));
		onProtocolFinished();
	};

	connect(mUploadProgramProtocol.data(), &UploadProgramProtocol::timeout, timeout);
	connect(mRunProgramProtocol.data(), &RunProgramProtocol::timeout, timeout);
	connect(mStopRobotProtocol.data(), &StopRobotProtocol::timeout, timeout);

	connect(mUploadProgramProtocol.data(), &UploadProgramProtocol::error
	        , this, &TrikCppGeneratorPluginBase::onProtocolFinished);
	connect(mRunProgramProtocol.data(), &RunProgramProtocol::error
	        , this, &TrikCppGeneratorPluginBase::onProtocolFinished);
	connect(mStopRobotProtocol.data(), &StopRobotProtocol::error
	        , this, &TrikCppGeneratorPluginBase::onProtocolFinished);

	connect(mUploadProgramProtocol.data(), &UploadProgramProtocol::success
	        , this, &TrikCppGeneratorPluginBase::onProtocolFinished);
	connect(mRunProgramProtocol.data(), &RunProgramProtocol::success
	        , this, &TrikCppGeneratorPluginBase::onProtocolFinished);
	connect(mStopRobotProtocol.data(), &StopRobotProtocol::success
	        , this, &TrikCppGeneratorPluginBase::onProtocolFinished);

	connect(mRunProgramProtocol.data(), &RunProgramProtocol::configVersionMismatch
			, [this, errorReporter](const QString &expected, const QString &actual) {
				Q_UNUSED(expected)
				Q_UNUSED(actual)
				errorReporter->addError(
						QString(tr("Casing model mismatch, check TRIK Studio settings, \"Robots\" page. It seems that "
								"TRIK casing version selected in TRIK Studio differs from version on robot.")));
			}
	);
}

QList<ActionInfo> TrikCppGeneratorPluginBase::customActions()
{
	mGenerateCodeAction->setObjectName("generateTRIKCode");
	mGenerateCodeAction->setText(tr("Generate TRIK code"));
	mGenerateCodeAction->setIcon(QIcon(":/trik/cpp/images/generateCppCode.svg"));
	ActionInfo generateCodeActionInfo(mGenerateCodeAction, "generators", "tools");
	connect(mGenerateCodeAction, SIGNAL(triggered()), this, SLOT(generateCode()), Qt::UniqueConnection);

	mUploadProgramAction->setObjectName("uploadProgram");
	mUploadProgramAction->setText(tr("Upload program"));
	mUploadProgramAction->setIcon(QIcon(":/trik/cpp/images/uploadProgram.svg"));
	ActionInfo uploadProgramActionInfo(mUploadProgramAction, "generators", "tools");
	connect(mUploadProgramAction, SIGNAL(triggered()), this, SLOT(uploadProgram()), Qt::UniqueConnection);

	mRunProgramAction->setObjectName("runProgram");
	mRunProgramAction->setText(tr("Run program"));
	mRunProgramAction->setIcon(QIcon(":/trik/cpp/images/run.png"));
	ActionInfo runProgramActionInfo(mRunProgramAction, "interpreters", "tools");
	connect(mRunProgramAction, SIGNAL(triggered()), this, SLOT(runProgram()), Qt::UniqueConnection);

	mStopRobotAction->setObjectName("stopRobot");
	mStopRobotAction->setText(tr("Stop robot"));
	mStopRobotAction->setIcon(QIcon(":/trik/cpp/images/stop.png"));
	ActionInfo stopRobotActionInfo(mStopRobotAction, "interpreters", "tools");
	connect(mStopRobotAction, SIGNAL(triggered()), this, SLOT(stopRobot()), Qt::UniqueConnection);

	return {generateCodeActionInfo, uploadProgramActionInfo, runProgramActionInfo, stopRobotActionInfo};
}

QList<HotKeyActionInfo> TrikCppGeneratorPluginBase::hotKeyActions()
{
	mGenerateCodeAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_G));
	mUploadProgramAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_U));
	mRunProgramAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F5));
	mStopRobotAction->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_F5));

	HotKeyActionInfo generateCodeInfo("Generator.GenerateTrik", tr("Generate TRIK Code"), mGenerateCodeAction);
	HotKeyActionInfo uploadProgramInfo("Generator.UploadTrik", tr("Upload TRIK Program"), mUploadProgramAction);
	HotKeyActionInfo runProgramInfo("Generator.RunTrik", tr("Run TRIK Program"), mRunProgramAction);
	HotKeyActionInfo stopRobotInfo("Generator.StopTrik", tr("Stop TRIK Robot"), mStopRobotAction);

	return {generateCodeInfo, uploadProgramInfo, runProgramInfo, stopRobotInfo};
}

QIcon TrikCppGeneratorPluginBase::iconForFastSelector(const RobotModelInterface &robotModel) const
{
	Q_UNUSED(robotModel)

	return QIcon(":/trik/cpp/images/switch-to-trik-cpp.svg");
}

generatorBase::MasterGeneratorBase *TrikCppGeneratorPluginBase::masterGenerator()
{
	return new TrikCppMasterGenerator(*mRepo
			, *mMainWindowInterface->errorReporter()
			, *mParserErrorReporter
			, *mRobotModelManager
			, *mTextLanguage
			, mMainWindowInterface->activeDiagram()
			, mPathsToTemplates);
}

QString TrikCppGeneratorPluginBase::defaultFilePath(const QString &projectName) const
{
	return QString("trik/%1/%1.cpp").arg(projectName);
}

text::LanguageInfo TrikCppGeneratorPluginBase::language() const
{
	return qReal::text::Languages::c({"brick"});
}

QString TrikCppGeneratorPluginBase::generatorName() const
{
	return "trikCpp";
}

void TrikCppGeneratorPluginBase::addShellDevice(robotModel::GeneratorModelExtensionInterface &robotModel) const
{
	const PortInfo shellPort("ShellPort", output);
	EmptyShell * const shell = new EmptyShell(DeviceInfo::create<trik::robotModel::parts::TrikShell>(), shellPort);
	connect(mCommunicator.data(), &TcpRobotCommunicator::printText, shell, &EmptyShell::print);
	robotModel.addDevice(shellPort, shell);
}

void TrikCppGeneratorPluginBase::uploadProgram()
{
	QProcess compileProcess;
	const QFileInfo fileInfo = generateCodeForProcessing();

//	const QString compileBatch = "C:\\RTK\\STM32F4\\mybuild\\compileAndUpload.bat";
	const QString compileBatch = "C:\\STM32_Diploma\\STM32-template\\STM32-template-project\\compileAndUpload.bat";

	compileProcess.setWorkingDirectory(fileInfo.absoluteDir().path());

    #ifdef Q_OS_WIN
	    compileProcess.start("cmd", {"/C", compileBatch});
    #endif

	compileProcess.waitForStarted();
	if (compileProcess.state() != QProcess::Running) {
		mMainWindowInterface->errorReporter()->addError(tr("Unable to launch assembly"));
		return;
	}

	compileProcess.waitForFinished();

	/// @todo: will not work since PascalABC uses console device instead of stdout or stderr for error output, so
	///        it will always return exit code 0 (even when using console command that actually captures exit code,
	///        start cmd /c "pabcnetc.exe <file name>.pas || call echo %errorLevel% > exitcode.txt"
	///        Need to patch PascalABC.NET compiler to fix that. Or maybe it already can do it, but more investigation
	///        is needed.
	//if (compileProcess.exitCode() != 0) {
	    //mMainWindowInterface->errorReporter()->addError(tr("Assembly failed"));
	    QStringList errors = QString(compileProcess.readAllStandardError()).split("\n", QString::SkipEmptyParts);
		errors << QString(compileProcess.readAllStandardOutput()).split("\n", QString::SkipEmptyParts);
		for (const auto &error : errors) {
			mMainWindowInterface->errorReporter()->addInformation(error);
		}

		return;
	// }
}

void TrikCppGeneratorPluginBase::runProgram()
{
	uploadProgram();
//	const QFileInfo fileInfo = generateCodeForProcessing();
//	if (fileInfo != QFileInfo() && !fileInfo.absoluteFilePath().isEmpty()) {
//		if (mRunProgramProtocol) {
//			disableButtons();
//			mRunProgramProtocol->run(fileInfo);
//		} else {
//			QLOG_ERROR() << "Run program protocol is not initialized";
//		}
//	} else {
//		QLOG_ERROR() << "Code generation failed, aborting";
//	}
}

void TrikCppGeneratorPluginBase::stopRobot()
{
	if (mStopRobotProtocol) {
		disableButtons();
		mStopRobotProtocol->run(
				"script.system(\"killall aplay\"); \n"
				"script.system(\"killall vlc\");"
				);
	} else {
		QLOG_ERROR() << "Stop robot protocol is not initialized";
	}
}

void TrikCppGeneratorPluginBase::onProtocolFinished()
{
	mUploadProgramAction->setEnabled(true);
	mRunProgramAction->setEnabled(true);
	mStopRobotAction->setEnabled(true);
}

void TrikCppGeneratorPluginBase::disableButtons()
{
	mUploadProgramAction->setEnabled(false);
	mRunProgramAction->setEnabled(false);
	mStopRobotAction->setEnabled(false);
}
