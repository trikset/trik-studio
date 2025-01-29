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

#include "nxtOsekCGeneratorPlugin.h"
#include <QtCore/QDir>
#include <QtCore/QDateTime>
#include <QtWidgets/QApplication>

#include <qrkernel/settingsManager.h>
#include <qrkernel/platformInfo.h>
#include <qrutils/singleton.h>

#include "QsLog.h"
#include "nxtOsekCMasterGenerator.h"

using namespace nxt::osekC;
using namespace qReal;
using namespace gui;

NxtOsekCGeneratorPlugin::NxtOsekCGeneratorPlugin()
	: NxtGeneratorPluginBase("NxtOsekCGeneratorRobotModel", tr("Generation (NXT OSEK C)"), 9 /* After 2D model */)
	, mGenerateCodeAction(new QAction(this))
	, mFlashRobotAction(new QAction(this))
	, mUploadProgramAction(new QAction(this))
	, mNxtToolsPresent(false)
	, mCommunicator(utils::Singleton<communication::UsbRobotCommunicationThread>::instance())
{
	const QString key = "pathToArmNoneEabi";
	const QString defaultPath = QDir(PlatformInfo::invariantSettingsPath("pathToNxtTools")).absolutePath()
								+"/arm-gnu-toolchain-13.2.rel1-x86_64-arm-none-eabi";
	if (qReal::SettingsManager::value(key).isNull()) {
		qReal::SettingsManager::setValue(key, defaultPath);
	}
	initActions();
	initHotKeyActions();
}

NxtOsekCGeneratorPlugin::~NxtOsekCGeneratorPlugin() = default;

QString NxtOsekCGeneratorPlugin::defaultFilePath(const QString &projectName) const
{
	return QString("nxt-tools/%1/%1.c").arg(projectName);
}

text::LanguageInfo NxtOsekCGeneratorPlugin::language() const
{
	return qReal::text::Languages::c();
}

QString NxtOsekCGeneratorPlugin::generatorName() const
{
	return "nxtOsekC";
}

bool NxtOsekCGeneratorPlugin::canGenerateTo(const QString &project)
{
	const QFileInfo cFile = generationTarget(project);
	const QFileInfo makeFile(cFile.absolutePath() + "/makefile");
	if (!cFile.exists() || !makeFile.exists()) {
		return true;
	}

	// If c file has much later timestamp then it was edited by user - restrincting generation to this file.
	const int timestampMaxDifference = 100;
	return (cFile.lastModified().toMSecsSinceEpoch()
			- makeFile.lastModified().toMSecsSinceEpoch() < timestampMaxDifference);
}

void NxtOsekCGeneratorPlugin::onCurrentRobotModelChanged(kitBase::robotModel::RobotModelInterface &model)
{
	RobotsGeneratorPluginBase::onCurrentRobotModelChanged(model);
	checkNxtTools();
	bool ourModel = robotModels().contains(&model);
	mUploadProgramAction->setVisible(ourModel);
	mFlashRobotAction->setVisible(ourModel);
	mUploadProgramAction->setEnabled(mNxtToolsPresent);
	mFlashRobotAction->setEnabled(mNxtToolsPresent);
	const QString tooltip = mNxtToolsPresent ? QString() : tr("NXT tools package is not installed");
	mUploadProgramAction->setToolTip(tooltip);
	mFlashRobotAction->setToolTip(tooltip);
}

void NxtOsekCGeneratorPlugin::onCurrentDiagramChanged(const TabInfo &info)
{
	RobotsGeneratorPluginBase::onCurrentDiagramChanged(info);
	checkNxtTools();
	mFlashRobotAction->setEnabled(true);
}

void NxtOsekCGeneratorPlugin::init(const kitBase::KitPluginConfigurator &configurator)
{
	RobotsGeneratorPluginBase::init(configurator);
	mFlashTool.reset(new NxtFlashTool(*mMainWindowInterface->errorReporter(), *mCommunicator));
	connect(&*mFlashTool, &NxtFlashTool::uploadingComplete, this, &NxtOsekCGeneratorPlugin::onUploadingComplete);
}

QList<ActionInfo> NxtOsekCGeneratorPlugin::customActions()
{
	const ActionInfo generateCodeActionInfo(mGenerateCodeAction, "generators", "tools");
	const ActionInfo flashRobotActionInfo(mFlashRobotAction, "", "tools");
	const ActionInfo uploadProgramActionInfo(mUploadProgramAction, "interpreters", "tools");
	return { generateCodeActionInfo, flashRobotActionInfo, uploadProgramActionInfo };
}

QList<HotKeyActionInfo> NxtOsekCGeneratorPlugin::hotKeyActions()
{
	return mHotKeyActionInfos;
}

QIcon NxtOsekCGeneratorPlugin::iconForFastSelector(const kitBase::robotModel::RobotModelInterface &robotModel) const
{
	Q_UNUSED(robotModel)
	return QIcon(":/nxt/osek/images/switch-to-nxt-osek-c.svg");
}

QString NxtOsekCGeneratorPlugin::defaultSettingsFile() const
{
	return ":/nxt/osek/defaultSettings.ini";
}

void NxtOsekCGeneratorPlugin::initActions()
{
	mGenerateCodeAction->setObjectName("generateCode");
	mGenerateCodeAction->setText(tr("Generate code"));
	mGenerateCodeAction->setIcon(QIcon(":/nxt/osek/images/generateOsekCode.svg"));
	connect(mGenerateCodeAction, SIGNAL(triggered()), this, SLOT(generateCode()));

	mFlashRobotAction->setObjectName("flashRobot");
	mFlashRobotAction->setText(tr("Flash robot"));
	mFlashRobotAction->setIcon(QIcon(":/nxt/osek/images/flashRobot.svg"));
	connect(mFlashRobotAction, SIGNAL(triggered()), this, SLOT(flashRobot()));

	mUploadProgramAction->setObjectName("uploadProgram");
	mUploadProgramAction->setText(tr("Upload program"));
	mUploadProgramAction->setIcon(QIcon(":/nxt/osek/images/run.png"));
	connect(mUploadProgramAction, SIGNAL(triggered()), this, SLOT(uploadProgram()));
}

void NxtOsekCGeneratorPlugin::initHotKeyActions()
{
	mGenerateCodeAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_G));
	mUploadProgramAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_U));

	HotKeyActionInfo generateActionInfo("Generator.GenerateNxt", tr("Generate NXT OSEK code"), mGenerateCodeAction);
	HotKeyActionInfo uploadActionInfo("Generator.UploadNxt", tr("Upload program to NXT device"), mUploadProgramAction);

	mHotKeyActionInfos << generateActionInfo << uploadActionInfo;
}

void NxtOsekCGeneratorPlugin::onUploadingComplete(bool success)
{
	if (!success) {
		return;
	}

	const NxtFlashTool::RunPolicy runPolicy = static_cast<NxtFlashTool::RunPolicy>(
			SettingsManager::value("nxtFlashToolRunPolicy").toInt());

	switch (runPolicy) {
	case NxtFlashTool::Ask:
		if (mFlashTool->askToRun(mMainWindowInterface->windowWidget())) {
			mFlashTool->runLastProgram();
		}
		break;
	case NxtFlashTool::AlwaysRun:
		mFlashTool->runLastProgram();
		break;
	default:
		break;
	}
}

generatorBase::MasterGeneratorBase *NxtOsekCGeneratorPlugin::masterGenerator()
{
	return new NxtOsekCMasterGenerator(*mRepo
			, *mMainWindowInterface->errorReporter()
			, *mParserErrorReporter
			, *mRobotModelManager
			, *mTextLanguage
			, mMainWindowInterface->activeDiagram()
			, generatorName());
}

void NxtOsekCGeneratorPlugin::regenerateExtraFiles(const QFileInfo &newFileInfo)
{
	// Static cast is possible and correct, but dynamic will be more flexible.
	if (auto nxtGenerator = qobject_cast<NxtOsekCMasterGenerator*>(masterGenerator())) {
		QScopedPointer<NxtOsekCMasterGenerator> generator(nxtGenerator);
		generator->initialize();
		generator->setProjectDir(newFileInfo);
		generator->generateOilAndMakeFiles();
	}
}

void NxtOsekCGeneratorPlugin::flashRobot()
{
	if (!mNxtToolsPresent) {
		mMainWindowInterface->errorReporter()->addError(tr("flash.sh not found."\
				" Make sure it is present in QReal installation directory"));
	} else {
		mFlashTool->flashRobot();
	}
}

void NxtOsekCGeneratorPlugin::uploadProgram()
{
	if (!mNxtToolsPresent) {
		mMainWindowInterface->errorReporter()->addError(
				tr("NXT tools package is not installed"));
	} else {
		const QFileInfo fileInfo = generateCodeForProcessing();

		if (fileInfo != QFileInfo()) {
			mFlashTool->uploadProgram(fileInfo);
		}
	}
}

void NxtOsekCGeneratorPlugin::checkNxtTools()
{
	const QDir dir(PlatformInfo::invariantSettingsPath("pathToNxtTools"));
	auto compilePath = dir.absolutePath() + "/compile.sh";

	auto nxtToolsPresent = dir.exists()
			&& QFileInfo::exists(dir.absolutePath() + "/gnuarm")
			&& QFileInfo::exists(dir.absolutePath() + "/nexttool")
			&& QFileInfo::exists(dir.absolutePath() + "/nxtOSEK")
			&& QFileInfo::exists(compilePath) && QFileInfo(compilePath).isFile();

	if (!nxtToolsPresent) {
		mNxtToolsPresent  = false;
		QLOG_ERROR() << "Missing" << dir.absolutePath() << "or mandatory subdirectory" <<
			dir.entryList(QDir::Filter::NoFilter, QDir::SortFlag::DirsFirst | QDir::SortFlag::Name);
		return;
	}

	auto osType = PlatformInfo::osType();
	if (osType == "linux") {
		mNxtToolsPresent = true;
	}
	else if (osType == "windows") {
		auto compileBatPath = dir.absolutePath() + "/compile.bat";
		mNxtToolsPresent = QFileInfo::exists(compileBatPath) && QFileInfo(compileBatPath).isFile();
	}
}
