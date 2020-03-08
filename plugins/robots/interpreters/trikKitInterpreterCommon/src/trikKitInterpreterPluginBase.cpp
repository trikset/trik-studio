/* Copyright 2013-2016 CyberTech Labs Ltd.
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

#include "trikKitInterpreterCommon/trikKitInterpreterPluginBase.h"

#include <QtWidgets/QApplication>
#include <QtXml/QDomDocument>
#include <QComboBox>
#include <QLineEdit>
#include <QProcessEnvironment>
#include <QFileInfo>

#include <twoDModel/engine/twoDModelEngineFacade.h>
#include <qrkernel/settingsManager.h>
#include <qrkernel/settingsListener.h>
#include <qrkernel/platformInfo.h>

#include <qrgui/textEditor/qscintillaTextEdit.h>
#include <qrgui/textEditor/languageInfo.h>

using namespace trik;
using namespace qReal;

const Id robotDiagramType = Id("RobotsMetamodel", "RobotsDiagram", "RobotsDiagramNode");
const Id subprogramDiagramType = Id("RobotsMetamodel", "RobotsDiagram", "SubprogramDiagram");

TrikKitInterpreterPluginBase::TrikKitInterpreterPluginBase() :
	mStart(tr("Start"), nullptr), mStop(tr("Stop"), nullptr)
{
}

TrikKitInterpreterPluginBase::~TrikKitInterpreterPluginBase()
{
	if (mOwnsAdditionalPreferences) {
		delete mAdditionalPreferences;
	}

	if (mOwnsBlocksFactory) {
		delete mBlocksFactory;
	}
}

void TrikKitInterpreterPluginBase::initKitInterpreterPluginBase
		(robotModel::TrikRobotModelBase * const realRobotModel
		, robotModel::twoD::TrikTwoDRobotModel * const twoDRobotModel
		, blocks::TrikBlocksFactoryBase * const blocksFactory
		)
{
	mRealRobotModel.reset(realRobotModel);
	mTwoDRobotModel.reset(twoDRobotModel);
	mBlocksFactory = blocksFactory;

	const auto modelEngine = new twoDModel::engine::TwoDModelEngineFacade(*mTwoDRobotModel);

	mTwoDRobotModel->setEngine(modelEngine->engine());
	mTwoDModel.reset(modelEngine);

	connectDevicesConfigurationProvider(devicesConfigurationProvider()); // ... =(

	mAdditionalPreferences = new TrikAdditionalPreferences({ mRealRobotModel->name() });

	bool enablePython = false;
	if (!friendlyKitName().contains("2014")) {
		if (!qEnvironmentVariableIsEmpty("TRIK_PYTHONPATH")) {
			enablePython = true;
		} else if (PlatformInfo::osType().startsWith("windows")) {
			auto dir = QDir(QCoreApplication::applicationDirPath());
			dir.makeAbsolute();
			auto isOne = false;
			QByteArray value;
			for (auto &&file : dir.entryList()) {
				if (file.endsWith(".zip") && file.startsWith("python"))
				{
					if (isOne) {
						isOne = false;
						value.clear();
						break;
					}
					isOne = true;
					value = dir.filePath(file).toLatin1();
				}
			}
			if (isOne && !value.isNull()) {
				qputenv("TRIK_PYTHONPATH", value);
				enablePython = true;
			}
		}
	}
	mTextualInterpreter.reset(new TrikTextualInterpreter(mTwoDRobotModel, enablePython));
}

void TrikKitInterpreterPluginBase::startCodeInterpretation(const QString &code, const QString &extension)
{
	if (extension.endsWith("py") && QProcessEnvironment::systemEnvironment().value("TRIK_PYTHONPATH").isEmpty()) {
		mMainWindow->errorReporter()->addError(tr("TRIK_PYTHONPATH must be set correctly to run Python script."));
		return;
	}

	emit codeInterpretationStarted(code, extension);

	auto model = mTwoDRobotModel;
	model->stopRobot(); // testStop?
	const QString modelName = model->robotId();

	for (const kitBase::robotModel::PortInfo &port : model->configurablePorts()) {
		const kitBase::robotModel::DeviceInfo deviceInfo = currentConfiguration(modelName, port);
		model->configureDevice(port, deviceInfo);
	}

	model->applyConfiguration();

	mMainWindow->errorReporter()->clear();
	textualInterpreter()->init();

	auto texttab = dynamic_cast<qReal::text::QScintillaTextEdit *>(mMainWindow->currentTab());
	auto savePath = texttab ? mCurrentTabPath : mProjectManager->saveFilePath();
	textualInterpreter()->setCurrentDir(QFileInfo(savePath).absolutePath(), extension);
	textualInterpreter()->setRunning(true);
	emit started();
	textualInterpreter()->interpretScript(code, extension);
}

void TrikKitInterpreterPluginBase::startCodeInterpretation(const QString &code
		, const QString &inputs, const QString &extension)
{

	// we are in exercise mode (maybe rename it later)
	emit codeInterpretationStarted(code, extension);

	auto model = mTwoDRobotModel;
	model->stopRobot(); // testStop?
	const QString modelName = model->robotId();

	for (const kitBase::robotModel::PortInfo &port : model->configurablePorts()) {
		const kitBase::robotModel::DeviceInfo deviceInfo = currentConfiguration(modelName, port);
		model->configureDevice(port, deviceInfo);
	}

	model->applyConfiguration();

	mMainWindow->errorReporter()->clear();
	textualInterpreter()->init();

	textualInterpreter()->setCurrentDir(QFileInfo(mProjectManager->saveFilePath()).absolutePath(), extension);
	textualInterpreter()->setRunning(true);
	emit started();
	textualInterpreter()->interpretScriptExercise(code, inputs, extension);
}

void TrikKitInterpreterPluginBase::handleImitationCameraWork()
{
	auto prepareImagesFromProject = [this](QString) {
		if (mCurrentlySelectedModelName.contains("trik", Qt::CaseInsensitive)
				&& qReal::SettingsManager::value("TrikSimulatedCameraImagesFromProject").toBool()
				&& mProjectManager->somethingOpened()) {
			QVariant rawData = mLogicalModel->logicalRepoApi().metaInformation("cameraImitationImages");

			if (not rawData.isNull()) {
				const QString path = qReal::PlatformInfo::invariantSettingsPath("trikCameraImitationImagesDir");
				QDir dir(path);
				const QString curPath = QDir::currentPath();
				if (dir.exists()) {
					dir.cd(path);
					dir.removeRecursively();
				}

				dir.mkpath(path);
				dir.cd(path);

				QDomDocument images;
				images.setContent(rawData.toString());
				for (QDomElement element = images.firstChildElement("images").firstChildElement("image")
						; !element.isNull()
						; element = element.nextSiblingElement("image"))
				{
					const QString fileName = element.attribute("name");
					QByteArray content = QByteArray::fromBase64(element.text().toLatin1());
					QFile file(dir.filePath(fileName));
					if (file.open(QIODevice::WriteOnly)) {
						file.write(content);
						file.close();
					}
				}

				dir.cd(curPath);
			}
		}

		if (mTextualInterpreter) {
			mTextualInterpreter->reinitRobotsParts();
		}
	};


	connect(mProjectManager, &ProjectManagementInterface::afterOpen, this, prepareImagesFromProject);
	qReal::SettingsListener::listen("TrikSimulatedCameraImagesFromProject", prepareImagesFromProject, this);
	qReal::SettingsListener::listen("TrikSimulatedCameraImagesPath", prepareImagesFromProject, this);

	connect(mAdditionalPreferences, &TrikAdditionalPreferences::packImagesToProjectClicked, this, [this]() {
		// in case if user works with images and want to pack them into qrs
		// we are saving images to metadata using logicalRepoApi
		if (mCurrentlySelectedModelName.contains("trik", Qt::CaseInsensitive)
				&& mProjectManager->somethingOpened()) {
			const QString path = qReal::SettingsManager::value("TrikSimulatedCameraImagesPath").toString();
			QDir dir(path);
			const QStringList imagesToSave = dir.entryList({"*.jpg", "*.png"});
			if (not imagesToSave.isEmpty()) {
				QDomDocument imagesDomDoc("cameraImitationImages");
				QDomElement images = imagesDomDoc.createElement("images");
				for (const QString &img : imagesToSave) {
					QDomElement element = images.ownerDocument().createElement("image");
					element.setAttribute("name", img);

					QFile file(dir.filePath(img));
					if (file.open(QIODevice::ReadOnly)) {
						const QByteArray rowBytes = file.readAll().toBase64();
						QString rawStr(rowBytes);
						Q_ASSERT(rawStr.length() == rowBytes.length());
						const QDomText data = element.ownerDocument().createTextNode(rawStr);
						element.appendChild(data);
						images.appendChild(element);
						file.close();
					}
				}

				imagesDomDoc.appendChild(images);
				mLogicalModel->mutableLogicalRepoApi().setMetaInformation("cameraImitationImages"
						, imagesDomDoc.toString());
				mProjectManager->setUnsavedIndicator(true);
			}
		}
	});
}

TrikTextualInterpreter * TrikKitInterpreterPluginBase::textualInterpreter() const
{
	return mTextualInterpreter.data();
}

void TrikKitInterpreterPluginBase::init(const kitBase::KitPluginConfigurator &configurer)
{
	connect(&configurer.eventsForKitPlugin()
			, &kitBase::EventsForKitPluginInterface::robotModelChanged
			, [this](const QString &modelName) { mCurrentlySelectedModelName = modelName; });

	qReal::gui::MainWindowInterpretersInterface &interpretersInterface
			= configurer.qRealConfigurator().mainWindowInterpretersInterface();

	mProjectManager = &configurer.qRealConfigurator().projectManager();

	mTwoDModel->init(configurer.eventsForKitPlugin()
			, configurer.qRealConfigurator().systemEvents()
			, configurer.qRealConfigurator().logicalModelApi()
			, configurer.qRealConfigurator().controller()
			, interpretersInterface
			, configurer.qRealConfigurator().mainWindowDockInterface()
			, configurer.qRealConfigurator().projectManager()
			, configurer.interpreterControl());

	mRealRobotModel->setErrorReporter(*interpretersInterface.errorReporter());
	mTwoDRobotModel->setErrorReporter(*interpretersInterface.errorReporter());

	mTextualInterpreter->setErrorReporter(*interpretersInterface.errorReporter());

	mMainWindow = &configurer.qRealConfigurator().mainWindowInterpretersInterface();

	mSystemEvents = &configurer.qRealConfigurator().systemEvents();
	mLogicalModel = &configurer.qRealConfigurator().logicalModelApi();

	/// @todo: refactor?
	mStart.setObjectName("runTextualInterpretation");
	mStart.setText(tr("Run program"));
	mStart.setIcon(QIcon(":/trik/qts/images/run.png"));
	mStart.setShortcut(QKeySequence(Qt::Key_F5));

	mStop.setObjectName("stopTextualInterpretation");
	mStop.setText(tr("Stop robot"));
	mStop.setIcon(QIcon(":/trik/qts/images/stop.png"));
	mStop.setShortcut(QKeySequence(Qt::SHIFT + Qt::Key_F5));

	mStop.setVisible(false);
	mStart.setVisible(false);

	connect(&configurer.eventsForKitPlugin()
			, &kitBase::EventsForKitPluginInterface::interpretCode
			, this
			, [this](const QString &code, const QString &inputs, const QString &ext){
		if (mIsModelSelected) {
			startCodeInterpretation(code, inputs, ext);
		}
	});

	connect(&configurer.robotModelManager()
			, &kitBase::robotModel::RobotModelManagerInterface::robotModelChanged
			, this
			, [this](kitBase::robotModel::RobotModelInterface &model){
		mStart.setVisible(false);
		mStop.setVisible(false);

		mIsModelSelected = robotModels().contains(&model);
		/// @todo: would probably make sense to make the current opened tab info available globally somewhere
		auto textTab = dynamic_cast<qReal::text::QScintillaTextEdit *>(mMainWindow->currentTab());
		bool isTextualInterp = mTextualInterpreter->supportedRobotModelNames().contains(model.name());
		/// FIX IT!!!!!!
		mStart.setVisible(mIsModelSelected && isTextualInterp && textTab);
		mStop.setVisible(false); // interpretation should always stop when switching models?
	});

	connect(&configurer.interpreterControl()
// Naive approach to fix crash/pause when stopping from 2d model.
// Changed from `stopAllInterpretation` to `stopped`, see git blame and corresponding PR
			, &kitBase::InterpreterControlInterface::stopped
			, this
			, [this](qReal::interpretation::StopReason reason) {
		if (mTextualInterpreter->isRunning()) {
			testStop(reason);
		}
	});

	connect(&configurer.interpreterControl()
			, &kitBase::InterpreterControlInterface::startScriptInterpretation
			, this
			, [this]() {
		if (!mTextualInterpreter->isRunning() && mIsModelSelected) { // temporary
			testStart();
		}
	});

	connect(&mStart, &QAction::triggered, this, &TrikKitInterpreterPluginBase::testStart);
	connect(&mStop, &QAction::triggered, this, [this](){
		this->testStop(qReal::interpretation::StopReason::userStop);
	});
	connect(mTextualInterpreter.data()
			, &TrikTextualInterpreter::completed
			, this
			, [this](){
		this->testStop(qReal::interpretation::StopReason::finised);
	});
	// refactor?
	connect(this
			, &TrikKitInterpreterPluginBase::started
			, &configurer.eventsForKitPlugin()
			, &kitBase::EventsForKitPluginInterface::interpretationStarted
			);

	connect(this
			, &TrikKitInterpreterPluginBase::stopped
			, &configurer.eventsForKitPlugin()
			, &kitBase::EventsForKitPluginInterface::interpretationStopped
			);

//	connect(&configurer.qRealConfigurator().systemEvents(),
//			&kitBase::EventsForKitPluginInterface:)

	connect(&configurer.eventsForKitPlugin()
			, &kitBase::EventsForKitPluginInterface::interpretationStarted
			, this
			, [this](){ /// @todo
		const bool isQtsInt = mTextualInterpreter->isRunning();
		mStart.setEnabled(isQtsInt);
		mStop.setEnabled(isQtsInt);
	}
	);

	QObject::connect(
				this
				, &TrikKitInterpreterPluginBase::codeInterpretationStarted
				, &configurer.eventsForKitPlugin()
				, &kitBase::EventsForKitPluginInterface::codeInterpretationStarted
				);

	QObject::connect(
				&configurer.eventsForKitPlugin()
				, &kitBase::EventsForKitPluginInterface::interpretationStopped
				, this
				, [this](qReal::interpretation::StopReason reason){ /// @todo
		Q_UNUSED(reason);
		mStart.setEnabled(true);
		mStop.setEnabled(true);
	}
	);

	connect(mSystemEvents
			, &qReal::SystemEvents::activeTabChanged
			, this
			, &TrikKitInterpreterPluginBase::onTabChanged);

	connect(mAdditionalPreferences, &TrikAdditionalPreferences::settingsChanged
			, mRealRobotModel.data(), &robotModel::TrikRobotModelBase::rereadSettings);

	connect(mAdditionalPreferences, &TrikAdditionalPreferences::settingsChanged
			, mTwoDRobotModel.data(), &robotModel::twoD::TrikTwoDRobotModel::rereadSettings);

	handleImitationCameraWork();
}

QList<kitBase::robotModel::RobotModelInterface *> TrikKitInterpreterPluginBase::robotModels()
{
	// @todo: restore it later
	return {/*mRealRobotModel.data(),*/ mTwoDRobotModel.data()};
}

kitBase::blocksBase::BlocksFactoryInterface *TrikKitInterpreterPluginBase::blocksFactoryFor(
		const kitBase::robotModel::RobotModelInterface *model)
{
	Q_UNUSED(model);

	mOwnsBlocksFactory = false;
	return mBlocksFactory;
}

kitBase::robotModel::RobotModelInterface *TrikKitInterpreterPluginBase::defaultRobotModel()
{
	return mTwoDRobotModel.data();
}

QList<kitBase::AdditionalPreferences *> TrikKitInterpreterPluginBase::settingsWidgets()
{
	mOwnsAdditionalPreferences = false;
	return {mAdditionalPreferences};
}

QWidget *TrikKitInterpreterPluginBase::quickPreferencesFor(const kitBase::robotModel::RobotModelInterface &model)
{
	return model.name().toLower().contains("twod")
			? nullptr
			: produceIpAddressConfigurer();
}

QList<qReal::ActionInfo> TrikKitInterpreterPluginBase::customActions()
{
	return { qReal::ActionInfo(&mStart, "interpreters", "tools"), qReal::ActionInfo(&mStop, "interpreters", "tools") };
}

QList<HotKeyActionInfo> TrikKitInterpreterPluginBase::hotKeyActions()
{
	return {};
}

QString TrikKitInterpreterPluginBase::defaultSettingsFile() const
{
	return ":/trikDefaultSettings.ini";
}

QIcon TrikKitInterpreterPluginBase::iconForFastSelector(
		const kitBase::robotModel::RobotModelInterface &robotModel) const
{
	return &robotModel == mRealRobotModel.data()
			? QIcon(":/icons/switch-real-trik.svg")
			: &robotModel == mTwoDRobotModel.data()
					? QIcon(":/icons/switch-2d.svg")
					: QIcon();
}

kitBase::DevicesConfigurationProvider *TrikKitInterpreterPluginBase::devicesConfigurationProvider()
{
	return &mTwoDModel->devicesConfigurationProvider();
}

QWidget *TrikKitInterpreterPluginBase::produceIpAddressConfigurer()
{
	auto quickPreferences = new QComboBox;
	quickPreferences->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	quickPreferences->setEditable(true);
	quickPreferences->setCurrentText(tr("Enter robot`s IP-address here..."));
	quickPreferences->setMinimumContentsLength(15);
	quickPreferences->setSizeAdjustPolicy(QComboBox::SizeAdjustPolicy::AdjustToMinimumContentsLength);
	quickPreferences->lineEdit()->setAlignment(Qt::AlignRight);
	const auto updateQuickPreferences = [quickPreferences]() {
		const QString ip = qReal::SettingsManager::value("TrikTcpServer").toString();

		// Handle duplicates
		auto found = false;
		for(int i = 0; i < quickPreferences->count(); ++i) {
			if (quickPreferences->itemText(i) == ip) {
				found = true;
				break;
			}
		}

		if (!found) {
			quickPreferences->insertItem(0, ip);
		}

		// Focus on new value
		if (quickPreferences->currentText() != ip) {
			quickPreferences->setCurrentText(ip);
		}
	};

	updateQuickPreferences();
	connect(mAdditionalPreferences, &TrikAdditionalPreferences::settingsChanged, this, updateQuickPreferences);
	qReal::SettingsListener::listen("TrikTcpServer", updateQuickPreferences, this);
	connect(quickPreferences->lineEdit(), &QLineEdit::editingFinished, this, [quickPreferences]() {
		qReal::SettingsManager::setValue("TrikTcpServer", quickPreferences->lineEdit()->text().trimmed());
	});

	connect(this, &QObject::destroyed, quickPreferences, &QObject::deleteLater);
	return quickPreferences;
}

void TrikKitInterpreterPluginBase::testStart()
{
	mStop.setVisible(true);
	mStart.setVisible(false);
	/// todo: bad


	auto texttab = dynamic_cast<qReal::text::QScintillaTextEdit *>(mMainWindow->currentTab());
	auto isJS = [](const QString &ext){ return ext == "js" || ext == "qts"; };
	auto isPython = [](const QString &ext){ return ext == "py"; };

	if (texttab) {
		if (isJS(texttab->currentLanguage().extension)) {
			startCodeInterpretation(texttab->text(), "js");
		} else if (isPython(texttab->currentLanguage().extension)) {
			startCodeInterpretation(texttab->text(), "py");
		}
	} else {
		mStop.setVisible(false);
		mStart.setVisible(true);
		/// todo: refactor the whole button shenanigans
	}
}

void TrikKitInterpreterPluginBase::testStop(qReal::interpretation::StopReason reason)
{
	mStop.setVisible(false);
	mStart.setVisible(true);

	textualInterpreter()->abort();
	mTwoDRobotModel->stopRobot();
	emit stopped(reason);
}

void TrikKitInterpreterPluginBase::onTabChanged(const TabInfo &info)
{
	mCurrentTabPath = info.pathToOpenedTextFile();
	if (!mIsModelSelected) {
		return;
	}
	const bool isCodeTab = info.type() == qReal::TabInfo::TabType::code;
	const bool isQtsInterp = mTextualInterpreter->supportedRobotModelNames().contains(mCurrentlySelectedModelName);

	if (isCodeTab) {
		auto texttab = dynamic_cast<qReal::text::QScintillaTextEdit *>(mMainWindow->currentTab());
		auto isScript = [](const QString &ext){ return ext == "py" || ext == "js" || ext == "qts"; };
		bool enable = texttab && isScript(texttab->currentLanguage().extension) && isQtsInterp;
		mStart.setEnabled(enable);
		mStop.setEnabled(enable);
		//mStart.setVisible(enable);
	} else {
		mStart.setEnabled(false); // Should matter
		mStop.setEnabled(false);
	}

	if (mTextualInterpreter->isRunning()) {
		mStop.trigger(); // Should interpretation should always stops at the change of tabs or not?
	}

	mStart.setVisible(isCodeTab && isQtsInterp);
	mStop.setVisible(false);
}
