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

#include "runner.h"

#include <QtCore/QFile>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonValue>
#include <QtWidgets/QApplication>

#include <qrutils/widgets/consoleDock.h>
#include <kitBase/robotModel/robotParts/shell.h>
#include <kitBase/robotModel/robotModelUtils.h>
#include <qrkernel/logging.h>
#include <twoDModel/engine/model/model.h>
#include <twoDModel/engine/model/timeline.h>

using namespace twoDModel;

Runner::Runner(const QString &report, const QString &trajectory,
	       const QString &input, const QString &mode, const QString &qrsFile):
	mInputsFile(input)
	, mMode(mode)
	, mSaveFile(qrsFile)
{
	mQRealFacade.reset(new qReal::SystemFacade());
	mProjectManager.reset(new qReal::ProjectManager(mQRealFacade->models()));
	mErrorReporter.reset(new qReal::ConsoleErrorReporter());
	mMainWindow.reset(new qReal::NullMainWindow(*mErrorReporter, mQRealFacade->events()
				, &*mProjectManager, &mQRealFacade->models().graphicalModelAssistApi()));

	mController.reset(new qReal::Controller());
	mSceneCustomizer.reset(new qReal::gui::editor::SceneCustomizer());
	mTextManager.reset(new qReal::text::TextManager(mQRealFacade->events(), *mMainWindow));
	mConfigurator.reset(new qReal::PluginConfigurator(mQRealFacade->models().repoControlApi()
							 , mQRealFacade->models().graphicalModelAssistApi()
							 , mQRealFacade->models().logicalModelAssistApi()
							 , *mController
							 , *mMainWindow
							 , *mMainWindow
							 , *mProjectManager
							 , *mSceneCustomizer
							 , mQRealFacade->events()
							 , *mTextManager));
	mReporter.reset(new Reporter(report, trajectory));
	mPluginFacade.reset(new interpreterCore::RobotsPluginFacade());
	mPluginFacade->init(*mConfigurator);
	for (auto &&defaultSettingsFile : mPluginFacade->defaultSettingsFiles()) {
		qReal::SettingsManager::loadDefaultSettings(defaultSettingsFile);
	}

	connect(&*mErrorReporter, &qReal::ConsoleErrorReporter::informationAdded, &*mReporter, &Reporter::addInformation);
	connect(&*mErrorReporter, &qReal::ConsoleErrorReporter::errorAdded, &*mReporter, &Reporter::addError);
	connect(&*mErrorReporter, &qReal::ConsoleErrorReporter::criticalAdded, &*mReporter, &Reporter::addError);
	connect(&*mErrorReporter, &qReal::ConsoleErrorReporter::logAdded, &*mReporter, &Reporter::addLog);

	/* 
	HACK: Upon initialization of the EV3 kit plugin, a subscription to the sensorAdded event in the Box2DPhysicsEngine 
	is registered with a delay using QTimerSingleShot(10). While this does not pose an issue when 
	utilizing TRIK Studio, it becomes problematic when using the 2D-model projectManager->open function, 
	as the subscription is established too late. As a consequence, the sensors are not properly processed by Box2D.
	*/
	QEventLoop loop;
	QTimer::singleShot(10, &loop, &QEventLoop::quit);
	loop.exec();
	mProjectManager->open(mSaveFile);
}

Runner::~Runner()
{
	mReporter->onInterpretationEnd();
	mReporter->reportMessages();
	mPluginFacade.reset();
	mReporter.reset();
	mConfigurator.reset();
	mTextManager.reset();
	mSceneCustomizer.reset();
	mController.reset();
	mMainWindow.reset();
	mErrorReporter.reset();
	mProjectManager.reset();
	mQRealFacade.reset();
}

bool Runner::generate(const QString &generatePath, const QString &generateMode)
{
	for (auto&& action: mPluginFacade->actionsManager().actions()){
		if (generateMode == "python") {
			if (action.action()->objectName() == "generatePythonTrikCode") {
				emit action.action()->triggered();
			}
		}
		if (generateMode == "javascript") {
			if (action.action()->objectName() == "generateTRIKCode") {
				emit action.action()->triggered();
			}
		}
		if (generateMode == "nxt") {
			if (action.action()->objectName() == "generateCode") {
				emit action.action()->triggered();
			}
		}
	}

	auto codes = mTextManager->code(mMainWindow->activeDiagram());
	if (codes.empty()) {
		// The application has already logged a
		// description of the problem that prevented script generation.
		return false;
	}
	auto path = mTextManager->path(codes.first());
	if (!QFile::copy(path, generatePath)) {
		QLOG_ERROR() << "File with name " << generatePath << " already exist";
		return false;
	}
	return true;
}

bool Runner::interpret(const bool background, const int customSpeedFactor, bool closeOnFinish
			, const bool closeOnSuccess, const bool showConsole, const QString &filePath)
{
	/// @todo: A bit hacky way to get 2D model window. Actually we must not have need in this.
	/// GUI must be separated from logic and not appear here at all.
	QList<view::TwoDModelWidget *> twoDModelWindows;
	for (auto &&widget : QApplication::allWidgets()) {
		if (const auto twoDModelWindow = dynamic_cast<view::TwoDModelWidget *>(widget)) {
			twoDModelWindows << twoDModelWindow;
			if (background) {
				twoDModelWindow->setBackgroundMode();
				twoDModelWindow->hide();
			}
		}
	}

	connect(&mPluginFacade->eventsForKitPlugins(), &kitBase::EventsForKitPluginInterface::interpretationStopped
			, this, [this, closeOnFinish, closeOnSuccess](qReal::interpretation::StopReason reason) {
		if (closeOnFinish || (closeOnSuccess && reason == qReal::interpretation::StopReason::finished))
			QTimer::singleShot(0, this, &Runner::close);
	});

	if (closeOnFinish) {
		connect(&mPluginFacade->eventsForKitPlugins(), &kitBase::EventsForKitPluginInterface::interpretationErrored
				, this, [this]() { QTimer::singleShot(0, this, &Runner::close); });
	}

	const auto robotName = mPluginFacade->robotModelManager().model().name();

	for (auto &&twoDModelWindow : twoDModelWindows) {
		connect(twoDModelWindow, &view::TwoDModelWidget::widgetClosed, &*mMainWindow
				, [this]() { this->mMainWindow->emulateClose(); });

		if (showConsole) {
			attachNewConsoleTo(twoDModelWindow);
		}

		auto &t = twoDModelWindow->model().timeline();
		t.setImmediateMode(background);
		if (customSpeedFactor >= model::Timeline::normalSpeedFactor) {
			t.setSpeedFactor(customSpeedFactor);
		}

		const auto models = twoDModelWindow->model().robotModels();
		if (!models.isEmpty() && models[0]->info().name() == robotName) {
			twoDModelWindow->bringToFront();
		}
	}

	mReporter->onInterpretationStart();
	if (mMode == "script") {
		return mPluginFacade->interpretCode(mInputsFile, filePath);
	} else if (mMode == "diagram") {
		mPluginFacade->actionsManager().runAction().trigger();
	}

	return true;
}

void Runner::connectRobotModel(const model::RobotModel *robotModel, const qReal::ui::ConsoleDock* console)
{
	connect(robotModel, &model::RobotModel::positionRecalculated
			, this, &Runner::onRobotRided, Qt::UniqueConnection);

	connect(&robotModel->info().configuration(), &kitBase::robotModel::ConfigurationInterface::deviceConfigured
			, this, [=](kitBase::robotModel::robotParts::Device *device)
	{
		connect(device, &kitBase::robotModel::robotParts::Device::propertyChanged, this
				, [=](const QString &property, const QVariant &value) {
			onDeviceStateChanged(robotModel->info().robotId(), device, property, value);
		});
		if (console) {
			if (auto * shell = qobject_cast<kitBase::robotModel::robotParts::Shell*>(device)) {
				connect(shell, &kitBase::robotModel::robotParts::Shell::textPrinted
						, console, &qReal::ui::ConsoleDock::print);
			}
		}
	});
}

void Runner::onRobotRided(const QPointF &newPosition, const qreal newRotation)
{
	mReporter->newTrajectoryPoint(
			static_cast<model::RobotModel *>(sender())->info().robotId()
			, mPluginFacade->interpreter().timeElapsed()
			, newPosition
			, newRotation
			);
}

void Runner::onDeviceStateChanged(const QString &robotId
		, const kitBase::robotModel::robotParts::Device *device
		, const QString &property
		, const QVariant &value)
{
	mReporter->newDeviceState(robotId
			, mPluginFacade->interpreter().timeElapsed()
			, device->deviceInfo().name()
			, device->port().name()
			, property
			, value
							 );
}

void Runner::attachNewConsoleTo(view::TwoDModelWidget *twoDModelWindow)
{
	qReal::ui::ConsoleDock* console = nullptr;
	if (auto layout = dynamic_cast<QGridLayout*>(twoDModelWindow->layout())) {
		console = new qReal::ui::ConsoleDock(tr("Robot console"), mMainWindow->windowWidget());
		mRobotConsoles << console;
		// TODO: hack to add console for each widget
		layout->addWidget(console, layout->rowCount(), 0, 1, -1);
	}

	for (auto &&robotModel : twoDModelWindow->model().robotModels()) {
		connectRobotModel(robotModel, console);
	}
}

void Runner::close()
{
	mMainWindow->emulateClose(mReporter->lastMessageIsError() ? 1 : 0);
	while (!mRobotConsoles.empty()) {
		mRobotConsoles.first()->deleteLater();
		mRobotConsoles.removeFirst();
	}
}
