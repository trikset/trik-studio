/* Copyright 2017 QReal Research Group
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

#include "pioneerLuaGeneratorPlugin.h"

#include <qrkernel/logging.h>
#include <qrkernel/settingsManager.h>
#include <qrkernel/settingsListener.h>
#include <qrkernel/platformInfo.h>
#include <pioneerKit/blocks/pioneerBlocksFactory.h>
#include <pioneerKit/constants.h>

#include "pioneerLuaMasterGenerator.h"
#include "communicator/communicationManager.h"
#include "robotModel/pioneerGeneratorRobotModel.h"
#include "widgets/pioneerAdditionalPreferences.h"

#include <QLineEdit>

using namespace pioneer;
using namespace pioneer::lua;
using namespace qReal;

PioneerLuaGeneratorPlugin::PioneerLuaGeneratorPlugin()
	: mGenerateCodeAction(new QAction(this))
	, mUploadProgramAction(new QAction(this))
	, mBlocksFactory(new blocks::PioneerBlocksFactory)
	, mGeneratorForRealCopterRobotModel(
			new PioneerGeneratorRobotModel(
					kitId()
					, "Pioneer"
					, modelNames::realCopter
					, tr("Pioneer model (real copter)")
					, 9
			))
	, mUploader()
{
//	mAdditionalPreferences = new PioneerAdditionalPreferences;

	mGenerateCodeAction->setText(tr("Generate to Pioneer Lua"));
	mGenerateCodeAction->setIcon(QIcon(":/pioneer/lua/images/generateLuaCode.svg"));
	connect(
			mGenerateCodeAction
			, &QAction::triggered
			, this
			, [this](){ PioneerLuaGeneratorPlugin::generateCode(true); }
			, Qt::UniqueConnection
	);

	mUploader.setProgram("pioneer-uploader.exe");
	connect(&mUploader, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished)
			, this, &PioneerLuaGeneratorPlugin::uploadFinished);

	mUploadProgramAction->setText(tr("Upload generated program to Pioneer"));
	mUploadProgramAction->setIcon(QIcon(":/pioneer/lua/images/upload.svg"));
	connect(
			mUploadProgramAction
			, &QAction::triggered
			, this
			, &PioneerLuaGeneratorPlugin::uploadProgram
			, Qt::UniqueConnection
	);
}

PioneerLuaGeneratorPlugin::~PioneerLuaGeneratorPlugin()
{
	if (mOwnsAdditionalPreferences) {
		delete mAdditionalPreferences;
	}
}

void PioneerLuaGeneratorPlugin::init(const kitBase::KitPluginConfigurator &configurator)
{
	generatorBase::RobotsGeneratorPluginBase::init(configurator);

	mMetamodel = &configurator.qRealConfigurator().logicalModelApi().editorManagerInterface();
}

QList<ActionInfo> PioneerLuaGeneratorPlugin::customActions()
{
	const ActionInfo generateCodeActionInfo(mGenerateCodeAction, "generators", "tools");
	const ActionInfo uploadProgramActionInfo(mUploadProgramAction, "generators", "tools");
	return { generateCodeActionInfo, uploadProgramActionInfo, /*runProgramActionInfo, stopProgramActionInfo*/ };
}

QList<HotKeyActionInfo> PioneerLuaGeneratorPlugin::hotKeyActions()
{
	mGenerateCodeAction->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_G));
	mUploadProgramAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_U));

	HotKeyActionInfo generateActionInfo(
			"Generator.GeneratePioneerLua"
			, tr("Generate Lua script for Pioneer Quadcopter")
			, mGenerateCodeAction);

	HotKeyActionInfo uploadProgramInfo(
			"Generator.UploadPioneerLua"
			, tr("Upload Pioneer program")
			, mUploadProgramAction);

	return { generateActionInfo, uploadProgramInfo/*, runProgramInfo, stopProgramInfo */};
}

QIcon PioneerLuaGeneratorPlugin::iconForFastSelector(const kitBase::robotModel::RobotModelInterface &robotModel) const
{
	Q_UNUSED(robotModel)
	return QIcon(":/pioneer/lua/images/switchToPioneerGenerator.svg");
}

int PioneerLuaGeneratorPlugin::priority() const
{
	return 9;
}

QString PioneerLuaGeneratorPlugin::kitId() const
{
	return "pioneerKit";
}

QList<kitBase::robotModel::RobotModelInterface *> PioneerLuaGeneratorPlugin::robotModels()
{
	return { mGeneratorForRealCopterRobotModel.data() };
}

QSharedPointer<kitBase::blocksBase::BlocksFactoryInterface> PioneerLuaGeneratorPlugin::blocksFactoryFor(
		const kitBase::robotModel::RobotModelInterface *model)
{
	Q_UNUSED(model)
	return mBlocksFactory;
}

QList<kitBase::AdditionalPreferences *> PioneerLuaGeneratorPlugin::settingsWidgets()
{
	mOwnsAdditionalPreferences = false;
	return { mAdditionalPreferences };
}

QList<QWidget *>PioneerLuaGeneratorPlugin::listOfQuickPreferencesFor(
		const kitBase::robotModel::RobotModelInterface &model)
{
	Q_UNUSED(model)
	return {ipSelector(), portSelector(), modeSelector()};
}

QWidget * PioneerLuaGeneratorPlugin::modeSelector()
{
	auto selector = new QComboBox;
	selector->addItems({"usb", "wifi"});
	connectSelector(selector, settings::pioneerBaseStationMode);
	selector->setToolTip(tr("Choose robot`s mode"));
	selector->setEditable(false);
	selector->setMinimumContentsLength(4);
	return selector;
}

QWidget * PioneerLuaGeneratorPlugin::ipSelector()
{
	auto selector = new QComboBox;
	connectSelector(selector, settings::pioneerBaseStationIP);
	selector->setToolTip(tr("Robot`s IP-address"));
	selector->setMinimumContentsLength(15);
	return selector;
}

QWidget * PioneerLuaGeneratorPlugin::portSelector()
{
	auto selector = new QComboBox;
	connectSelector(selector, settings::pioneerBaseStationPort);
	selector->setToolTip(tr("Robot`s port"));
	selector->setMinimumContentsLength(4);
	return selector;
}

void PioneerLuaGeneratorPlugin::connectSelector(QComboBox * selector, QString settings)
{
	selector->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	selector->setEditable(true);
	selector->setSizeAdjustPolicy(QComboBox::SizeAdjustPolicy::AdjustToMinimumContentsLength);
	selector->lineEdit()->setAlignment(Qt::AlignRight);
	const auto updateQuickPreferences = [selector, settings]() {
		const QString value = qReal::SettingsManager::value(settings).toString();

		// Handle duplicates
		auto found = false;
		for(int i = 0; i < selector->count(); ++i) {
			if (selector->itemText(i) == value) {
				found = true;
				break;
			}
		}

		if (!found) {
			selector->insertItem(0, value);
		}

		// Focus on new value
		if (selector->currentText() != value) {
			selector->setCurrentText(value);
		}
	};

	updateQuickPreferences();
	qReal::SettingsListener::listen(settings, updateQuickPreferences, this);
	connect(selector->lineEdit(), &QLineEdit::editingFinished, this, [selector, settings]() {
		qReal::SettingsManager::setValue(settings, selector->lineEdit()->text().trimmed());
	});
}

QString PioneerLuaGeneratorPlugin::defaultSettingsFile() const
{
	return ":/pioneer/lua/pioneerLuaDefaultSettings.ini";
}

void PioneerLuaGeneratorPlugin::onCurrentRobotModelChanged(kitBase::robotModel::RobotModelInterface &model)
{
	RobotsGeneratorPluginBase::onCurrentRobotModelChanged(model);
	bool ourModel = robotModels().contains(&model);
	mGenerateCodeAction->setVisible(ourModel);
	mUploadProgramAction->setVisible(ourModel);
}

void PioneerLuaGeneratorPlugin::onCurrentDiagramChanged(const qReal::TabInfo &info)
{
	generatorBase::RobotsGeneratorPluginBase::onCurrentDiagramChanged(info);
}

QString PioneerLuaGeneratorPlugin::defaultFilePath(const QString &projectName) const
{
	return QString("pioneer/%1/%1.lua").arg(projectName);
}

text::LanguageInfo PioneerLuaGeneratorPlugin::language() const
{
	return qReal::text::Languages::lua(QStringList{ "function", "end", "math" });
}

QString PioneerLuaGeneratorPlugin::generatorName() const
{
	return "pioneer/lua";
}

generatorBase::MasterGeneratorBase *PioneerLuaGeneratorPlugin::masterGenerator()
{
	return new PioneerLuaMasterGenerator(*mRepo
			, *mMainWindowInterface->errorReporter()
			, *mParserErrorReporter
			, *mRobotModelManager
			, *mTextLanguage
			, mMainWindowInterface->activeDiagram()
			, generatorName()
			, *mMetamodel);
}

void PioneerLuaGeneratorPlugin::regenerateExtraFiles(const QFileInfo &newFileInfo)
{
	Q_UNUSED(newFileInfo)
}

void PioneerLuaGeneratorPlugin::uploadProgram()
{
	const QFileInfo program = generateCodeForProcessing();
	if (!program.exists()) return;
	if (!PlatformInfo::osType().startsWith("windows")) {
		mMainWindowInterface->errorReporter()->addError(tr("Sorry, but uploading works only on Windows"));
		return;
	}
	if (!QFile::exists(mUploader.program())) {
		auto link = "<a href=\"https://docs.geoscan.aero/ru/master/programming/trik/trik_main.html\">"
				+ tr("site") + "</a>";
		mMainWindowInterface->errorReporter()->addInformation(tr("Please download uploader from ") + link);
		return;
	}
	setActionsEnabled(false);
	mUploader.setArguments({ program.path()
			, qReal::SettingsManager::value(settings::pioneerBaseStationIP).toString()
			, qReal::SettingsManager::value(settings::pioneerBaseStationPort).toString()
			, qReal::SettingsManager::value(settings::pioneerBaseStationMode).toString() });
	mUploader.start();
}

void PioneerLuaGeneratorPlugin::uploadFinished()
{
	const auto & reporter = mMainWindowInterface->errorReporter();
	const QString output = mUploader.readAllStandardOutput();
	const QString error = mUploader.readAllStandardError();
	const int exitCode = mUploader.exitCode();
	if (!output.isEmpty()) {
		for (const auto & line : output.split(QRegExp("[\r\n]"),QString::SkipEmptyParts)) {
			reporter->addInformation(line);
			qDebug() << "Info: " << line;
		}
	}
	if (!error.isEmpty()) {
		for (const auto & line : error.split(QRegExp("[\r\n]"),QString::SkipEmptyParts)) {
			reporter->addError(line);
		}
	}
	if (exitCode != 0) reporter->addCritical(tr("Exit code ") + QString::number(exitCode));
	setActionsEnabled(true);
}

void PioneerLuaGeneratorPlugin::setActionsEnabled(bool isEnabled)
{
	mUploadProgramAction->setEnabled(isEnabled);
}
