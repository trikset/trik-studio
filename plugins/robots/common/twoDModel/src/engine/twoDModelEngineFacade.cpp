/* Copyright 2007-2015 QReal Research Group, Dmitry Mordvinov
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

#include "twoDModel/engine/twoDModelEngineFacade.h"

#include <kitBase/readOnly.h>
#include <qrkernel/logging.h>
#include <qrutils/smartDock.h>

#include "twoDModel/engine/model/model.h"
#include "twoDModel/engine/view/twoDModelWidget.h"
#include "twoDModelEngineApi.h"

#include <qrgui/plugins/toolPluginInterface/usedInterfaces/errorReporterInterface.h>

using namespace twoDModel::engine;

TwoDModelEngineFacade::TwoDModelEngineFacade(twoDModel::robotModel::TwoDRobotModel &robotModel)
	: mRobotModelName(robotModel.name())
	, mModel(new model::Model())
	, mView(new view::TwoDModelWidget(*mModel, nullptr))
	, mApi(new TwoDModelEngineApi(*mModel, *mView))
	, mDock(new utils::SmartDock("2dModelDock", mView))
{
	mModel->addRobotModel(robotModel);
	connect(mView, &view::TwoDModelWidget::runButtonPressed, this, &TwoDModelEngineFacade::runButtonPressed);
	connect(mView, &view::TwoDModelWidget::stopButtonPressed, this, &TwoDModelEngineFacade::stopButtonPressed);
	connect(mView, &view::TwoDModelWidget::widgetClosed, this, &TwoDModelEngineFacade::stopButtonPressed);
	connect(mDock, &utils::SmartDock::dockedChanged, mView, &view::TwoDModelWidget::setCompactMode);
}

TwoDModelEngineFacade::~TwoDModelEngineFacade(){
	if (mDock && !mDock->parent()) {
		delete mDock;
	}
	delete mView;
}

void TwoDModelEngineFacade::init(const kitBase::EventsForKitPluginInterface &eventsForKitPlugin,
								 const qReal::SystemEvents &systemEvents,
								 qReal::LogicalModelAssistInterface &logicalModel,
								 qReal::ControllerInterface &controller,
								 qReal::gui::MainWindowInterpretersInterface &interpretersInterface,
								 qReal::gui::MainWindowDockInterface &dockInterface,
								 const qReal::ProjectManagementInterface &projectManager,
								 kitBase::InterpreterControlInterface &interpreterControl)
{
	mModel->init(*interpretersInterface.errorReporter(), interpreterControl, logicalModel);
	dockInterface.registerEditor(*mView);
	mView->setController(controller);

	const auto onActiveTabChanged = [this](const qReal::TabInfo &info) {
		mView->setEnabled(info.type() != qReal::TabInfo::TabType::other);
		mCurrentTabInfo = info.type();
	};

	const auto reloadWorld = [this, &logicalModel, &interpretersInterface, &projectManager]() {
		QLOG_DEBUG() << "Reloading 2D world model...";
		const QString xml = projectManager.somethingOpened()
								? logicalModel.logicalRepoApi().metaInformation("worldModel").toString()
								: QString();
		QDomDocument worldModel;
		QString errorMessage;
		int errorLine, errorColumn;
		if (!xml.isEmpty() && !worldModel.setContent(xml, &errorMessage, &errorLine, &errorColumn)) {
			interpretersInterface.errorReporter()->addError(
				QString("%1:%2: %3").arg(QString::number(errorLine), QString::number(errorColumn), errorMessage));
		}

		const QString blobsXml = projectManager.somethingOpened()
									 ? logicalModel.logicalRepoApi().metaInformation("blobs").toString()
									 : QString();
		QDomDocument blobs;
		if (!blobsXml.isEmpty() && !blobs.setContent(blobsXml, &errorMessage, &errorLine, &errorColumn)) {
			interpretersInterface.errorReporter()->addError(
				QString("%1:%2: %3").arg(QString::number(errorLine), QString::number(errorColumn), errorMessage));
		}

		if (!worldModel.firstChild().isNull()) {
			worldModel.firstChild().appendChild(blobs.firstChild().firstChild());
		}

		mView->loadXmls(worldModel);
		mView->resetDrawAction();

		loadReadOnlyFlags(logicalModel);
		QLOG_DEBUG() << "Reloading 2D world done";
	};

	const auto connectTwoDModel = [this, &eventsForKitPlugin, &interpreterControl]() {
		connect(&eventsForKitPlugin,
				&kitBase::EventsForKitPluginInterface::interpretationStarted,
				this,
				&twoDModel::TwoDModelControlInterface::onStartInterpretation,
				Qt::UniqueConnection);

		connect(&eventsForKitPlugin,
				&kitBase::EventsForKitPluginInterface::interpretationStopped,
				this,
				&twoDModel::TwoDModelControlInterface::onStopInterpretation,
				Qt::UniqueConnection);

		connect(this, &twoDModel::TwoDModelControlInterface::runButtonPressed, this, [this, &interpreterControl]() {
			if (mCurrentTabInfo == qReal::TabInfo::TabType::editor) {
				interpreterControl.interpret();
			} else {
				emit interpreterControl.startScriptInterpretation();
			}
		});

		connect(this,
				&TwoDModelEngineFacade::stopButtonPressed,
				&interpreterControl,
				[&interpreterControl]() { Q_EMIT interpreterControl.stopAllInterpretation(); },
				Qt::UniqueConnection);
	};

	auto disconnectTwoDModel = [this, &eventsForKitPlugin, &interpreterControl]() {
		disconnect(&eventsForKitPlugin,
				   &kitBase::EventsForKitPluginInterface::interpretationStarted,
				   this,
				   &twoDModel::TwoDModelControlInterface::onStartInterpretation);

		disconnect(&eventsForKitPlugin,
				   &kitBase::EventsForKitPluginInterface::interpretationStopped,
				   this,
				   &twoDModel::TwoDModelControlInterface::onStopInterpretation);

		disconnect(this,
				   &twoDModel::TwoDModelControlInterface::runButtonPressed,
				   &interpreterControl,
				   &kitBase::InterpreterControlInterface::interpret);

		disconnect(this,
				   &twoDModel::TwoDModelControlInterface::stopButtonPressed,
				   &interpreterControl,
				   &kitBase::InterpreterControlInterface::userStopRobot);
	};

	connect(&projectManager, &qReal::ProjectManagementInterface::afterOpen, this, reloadWorld);
	connect(&projectManager, &qReal::ProjectManagementInterface::closed, this, reloadWorld);
	connect(&systemEvents, &qReal::SystemEvents::activeTabChanged, this, onActiveTabChanged);

	connect(mModel.data(), &model::Model::modelChanged, this, [&logicalModel](const QDomDocument &xml) {
		logicalModel.mutableLogicalRepoApi().setMetaInformation("worldModel", xml.toString(4));
	});

	connect(mModel.data(), &model::Model::blobsChanged, this, [&logicalModel](const QDomDocument &xml) {
		logicalModel.mutableLogicalRepoApi().setMetaInformation("blobs", xml.toString(4));
	});

	connect(&eventsForKitPlugin,
			&kitBase::EventsForKitPluginInterface::robotModelChanged,
			this,
			[this, connectTwoDModel, disconnectTwoDModel, reloadWorld](const QString &modelName) {
				const bool isCurrentModel = modelName == mRobotModelName;
				if (isCurrentModel) {
					connectTwoDModel();
					mDock->attachToMainWindow(Qt::TopDockWidgetArea);
					reloadWorld();
				} else {
					disconnectTwoDModel();
					mDock->detachFromMainWindow();
				}
			});
}

kitBase::DevicesConfigurationProvider &TwoDModelEngineFacade::devicesConfigurationProvider()
{
	return *mView;
}

TwoDModelEngineInterface &TwoDModelEngineFacade::engine()
{
	return *mApi;
}

void TwoDModelEngineFacade::onStartInterpretation()
{
	if (!mModel->settings().realisticPhysics() &&
			(!mModel->worldModel().balls().isEmpty() || !mModel->worldModel().skittles().isEmpty())) {
		mModel->errorReporter()->addWarning(tr("Realistic physics' must be turned on to enjoy skittles and balls"));
	}
	mModel->timeline().start();
}

void TwoDModelEngineFacade::onStopInterpretation(qReal::interpretation::StopReason reason)
{
	mModel->timeline().stop(reason);
}

void TwoDModelEngineFacade::loadReadOnlyFlags(const qReal::LogicalModelAssistInterface &logicalModel)
{
	kitBase::ReadOnlyFlags readOnlyFlags = kitBase::ReadOnly::None;

	const auto load = [&](const QString &tag, kitBase::ReadOnly::ReadOnlyEnum flag) {
		if (logicalModel.logicalRepoApi().metaInformation(tag).toBool()) {
			readOnlyFlags |= flag;
		}
	};

	load("twoDModelWorldReadOnly", kitBase::ReadOnly::World);
	load("twoDModelSensorsReadOnly", kitBase::ReadOnly::Sensors);
	load("twoDModelRobotPositionReadOnly", kitBase::ReadOnly::RobotPosition);
	load("twoDModelRobotConfigurationReadOnly", kitBase::ReadOnly::RobotSetup);
	load("twoDModelSimulationSettingsReadOnly", kitBase::ReadOnly::SimulationSettings);

	mView->setInteractivityFlags(readOnlyFlags);
}
