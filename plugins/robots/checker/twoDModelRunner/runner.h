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

#include <QtCore/QScopedPointer>

#include <qrgui/systemFacade/systemFacade.h>
#include <qrgui/systemFacade/components/consoleErrorReporter.h>
#include <qrgui/systemFacade/components/nullMainWindow.h>
#include <qrgui/systemFacade/components/projectManager.h>
#include <qrgui/systemFacade/components/nullTextManager.h>
#include <qrgui/controller/controller.h>
#include <qrgui/editor/sceneCustomizer.h>
#include <qrgui/plugins/toolPluginInterface/pluginConfigurator.h>
#include <interpreterCore/robotsPluginFacade.h>
#include "reporter.h"
#include <twoDModel/engine/view/twoDModelWidget.h>

namespace qReal {
namespace ui {
class ConsoleDock;
}
}

namespace twoDModel {

namespace model {
class RobotModel;
}

/// Creates instances null QReal environment, of robots plugin and runs interpretation on 2D model window.
class Runner : public QObject
{
	Q_OBJECT

public:
	/// Constructor.
	/// @param report A path to a file where JSON report about the session will be written after it ends.
	/// @param trajectory A path to a file where robot`s trajectory will be written during the session.
	Runner(const QString &report, const QString &trajectory);

	/// Constructor.
	/// @param report A path to a file where JSON report about the session will be written after it ends.
	/// @param trajectory A path to a file where robot`s trajectory will be written during the session.
	/// @param input A path to a file where JSON with inputs for JavaScript.
	/// @param mode Interpret mode.
	Runner(const QString &report, const QString &trajectory, const QString &input, const QString &mode);

	~Runner();

	/// Starts the interpretation process. The given save file will be opened and interpreted in 2D model window.
	/// @param saveFile QReal save file (qrs) that will be opened and interpreted.
	/// @param background If true then the save file will be interpreted in the fastest speed and 2D model window
	/// will be closed immediately after the interpretation stopped.
	/// @param speedFactor can be used when not in background mode to tune interpretation speed
	/// @param closeOnSuccessMode If true then model will be closed if the program finishes without errors.
	/// @param showConsole If true then robot's console will be showed.
	bool interpret(const QString &saveFile, bool background, int speedFactor, bool closeOnSuccess, bool showConsole);

private slots:
	void close();

private:
	void connectRobotModel(const model::RobotModel *robotModel, const qReal::ui::ConsoleDock* console);
	void onRobotRided(const QPointF &newPosition, const qreal newRotation);
	void onDeviceStateChanged(const QString &robotId, const kitBase::robotModel::robotParts::Device *device
			, const QString &property, const QVariant &value);
	void attachNewConsoleTo(view::TwoDModelWidget *twoDModelWindow);

	qReal::SystemFacade mQRealFacade;
	qReal::Controller mController;
	qReal::ConsoleErrorReporter mErrorReporter;
	qReal::ProjectManager mProjectManager;
	qReal::NullMainWindow mMainWindow;
	qReal::NullTextManager mTextManager;
	qReal::gui::editor::SceneCustomizer mSceneCustomizer;
	qReal::PluginConfigurator mConfigurator;
	interpreterCore::RobotsPluginFacade mPluginFacade;
	Reporter mReporter;
	QList<qReal::ui::ConsoleDock *> mRobotConsoles;
	QString mInputsFile;
	QString mMode;
};

}
