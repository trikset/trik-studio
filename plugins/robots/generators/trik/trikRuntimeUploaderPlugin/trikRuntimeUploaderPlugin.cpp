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

#include "trikRuntimeUploaderPlugin.h"

#include <QtCore/QProcess>
#include <QtWidgets/QApplication>

#include <qrkernel/settingsManager.h>
#include <qrkernel/settingsListener.h>

using namespace trik;

TrikRuntimeUploaderPlugin::TrikRuntimeUploaderPlugin()
	: mAction(new QAction(QIcon(":/trik/images/flashRobot.svg"), tr("Upload Runtime"), nullptr))
{
	connect(mAction, &QAction::triggered, this, &TrikRuntimeUploaderPlugin::uploadRuntime);
	mAction->setVisible(qReal::SettingsManager::value("SelectedRobotKit").toString() == "trikKit");
	qReal::SettingsListener::listen("SelectedRobotKit", [this](const QString selectedKit) {
		mAction->setVisible(selectedKit == "trikKit");
	});
}

void TrikRuntimeUploaderPlugin::init(const qReal::PluginConfigurator &configurator)
{
	mMainWindowInterface = &configurator.mainWindowInterpretersInterface();
}

QList<qReal::ActionInfo> TrikRuntimeUploaderPlugin::actions()
{
	return { qReal::ActionInfo(mAction, "", "tools") };
}

void TrikRuntimeUploaderPlugin::uploadRuntime()
{
	const QString openConnection = QString("open scp://root@%1")
			.arg(qReal::SettingsManager::value("TrikTcpServer").toString());

	const QString killTrikGui = "call killall trikGui";
	const QString createTrikDirectory = "call mkdir -p /home/root/trik";
	const QString removePermissions = "call chmod a-x trik/trik*";
	const QString restorePermissions = "call chmod a+x trik/trik*";
	const QString restartTrikGui = "call /bin/sh -c '/etc/trik/trikGui.sh &'";

	const QString moveCommand = "synchronize remote trikRuntime /home/root/trik";

	const QString rawWinscpPath = qReal::SettingsManager::value("WinScpPath").toString();
	const QString winscpPath = rawWinscpPath.startsWith("./")
			? QApplication::applicationDirPath() + rawWinscpPath.mid(1)
			: rawWinscpPath;

	const QStringList args = {
			"/command"
			, openConnection
			, createTrikDirectory
			, removePermissions
			, killTrikGui
			, moveCommand
			, restorePermissions
			, restartTrikGui
			, "exit"
	};

	if (!QProcess::startDetached(winscpPath, args, QApplication::applicationDirPath())) {
		mMainWindowInterface->errorReporter()->addError(
			tr("WinSCP process failed to launch, check path in settings.")
		);
	} else {
		mMainWindowInterface->errorReporter()->addWarning(
			tr("Attention! Started to download the runtime. Please do not turn off the robot.")
		);
	}
}
