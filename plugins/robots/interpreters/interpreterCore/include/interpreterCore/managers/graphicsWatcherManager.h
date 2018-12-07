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

#pragma once

#include <QtCore/QObject>

#include <utils/sensorsGraph.h>
#include <kitBase/devicesConfigurationProvider.h>

#include <qrtext/debuggerInterface.h>

namespace interpreterCore {

class RobotModelManager;

/// Incapsulates inner operations on managing graphics watcher in the dock window.
class GraphicsWatcherManager : public QObject, public kitBase::DevicesConfigurationProvider
{
public:
	/// Constructor.
	/// @param parser - blocks parser, used to show values of variables on graphs.
	/// @param robotManager - object that controls currently selected robot model.
	/// @param parent - parent of this widget in Qt widget hierarchy.
	GraphicsWatcherManager(const qrtext::DebuggerInterface &parser
			, RobotModelManager &robotManager
			, QObject *parent = nullptr);

	/// Returns the graphics watcher widget itself for placing it into dock. Takes ownership over result.
	QWidget *widget();

public slots:
	/// Starts graphics watcher`s job even if user stopped it himself.
	void forceStart();

	/// Stops graphics watcher`s job even if user started it himself.
	void forceStop();

private:
	void onDeviceConfigurationChanged(const QString &robotId
			, const kitBase::robotModel::PortInfo &port
			, const kitBase::robotModel::DeviceInfo &sensor
			, Reason reason) override;

	void updateSensorsList(const QString &currentRobotModel);

	QScopedPointer<utils::sensorsGraph::SensorsGraph> mWatcher;
	RobotModelManager &mRobotManager;
};

}
