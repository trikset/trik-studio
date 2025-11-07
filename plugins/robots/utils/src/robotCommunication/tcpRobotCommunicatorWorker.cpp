/* Copyright 2013-2016 CyberTech Labs Ltd., Dmitry Mordvinov, Yurii Litvinov, Grigorii Zimin
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

#include "src/robotCommunication/tcpRobotCommunicatorWorker.h"

#include <QtNetwork/QHostAddress>

#include <qrkernel/settingsManager.h>
#include <qrkernel/logging.h>

#include "utils/requiredVersion.h"

using namespace utils::robotCommunication;

static const uint controlPort = 8888;
static const uint telemetryPort = 9000;

TcpRobotCommunicatorWorker::TcpRobotCommunicatorWorker(const QString &robotIpRegistryKey)
	: mRobotIpRegistryKey(robotIpRegistryKey)
{
	qRegisterMetaType<MessageKind>("MessageKind");
}

TcpRobotCommunicatorWorker::~TcpRobotCommunicatorWorker()
{
}

void TcpRobotCommunicatorWorker::init()
{
	mVersionTimer.reset(new QTimer());
	mVersionTimer->setSingleShot(true);
	QObject::connect(mVersionTimer.data(), &QTimer::timeout, this, &TcpRobotCommunicatorWorker::onVersionTimeOut);

	mControlConnection.reset(new TcpConnectionHandler(controlPort));
	mTelemetryConnection.reset(new TcpConnectionHandler(telemetryPort));

	QObject::connect(mControlConnection.data(), &TcpConnectionHandler::messageReceived
			, this, &TcpRobotCommunicatorWorker::processControlMessage, Qt::DirectConnection);
	QObject::connect(mTelemetryConnection.data(), &TcpConnectionHandler::messageReceived
			, this, &TcpRobotCommunicatorWorker::processTelemetryMessage, Qt::DirectConnection);
}

void TcpRobotCommunicatorWorker::deinit()
{
	mTelemetryConnection.reset();
	mControlConnection.reset();
	mVersionTimer.reset();
}

void TcpRobotCommunicatorWorker::uploadProgram(const QString &programName, const QString &programContents)
{
	connect();
	if (!mControlConnection->isConnected()) {
		// Error is already reported by connect().
		return;
	}

	mControlConnection->send("file:" + programName + ":" + programContents);
	Q_EMIT uploadProgramDone();
}

void TcpRobotCommunicatorWorker::runProgram(const QString &programName)
{
	connect();
	if (!mControlConnection->isConnected()) {
		// Error is already reported by connect().
		return;
	}

	mControlConnection->send("run:" + programName);
	Q_EMIT startedRunning();
}

void TcpRobotCommunicatorWorker::runDirectCommand(const QString &directCommand, bool asScript)
{
	connect();
	if (!mControlConnection->isConnected()) {
		return;
	}

	const QString command = asScript ? "directScript" : "direct";
	mControlConnection->send(command + ":" + directCommand);
	Q_EMIT runDirectCommandDone();
}

void TcpRobotCommunicatorWorker::stopRobot()
{
	connect();
	if (!mControlConnection->isConnected()) {
		return;
	}

	mControlConnection->send("stop");
	Q_EMIT stopRobotDone();
}

void TcpRobotCommunicatorWorker::requestCasingVersion()
{
	connect();
	if (!mControlConnection->isConnected()) {
		return;
	}

	mControlConnection->send("configVersion");
}

void TcpRobotCommunicatorWorker::requestData(const QString &sensor)
{
	if (!mTelemetryConnection->isConnected()) {
		return;
	}

	mTelemetryConnection->send("sensor:" + sensor);
}

void TcpRobotCommunicatorWorker::requestData()
{
	if (!mTelemetryConnection->isConnected()) {
		return;
	}

	mTelemetryConnection->send("data");
}

void TcpRobotCommunicatorWorker::processControlMessage(const QString &message)
{
	const QString errorMarker("error: ");
	const QString infoMarker("info: ");
	const QString versionMarker("version: ");
	const QString printMarker("print: ");
	const QString fileContentsMarker("fileContents: ");
	const QString mailMarker("mail: ");
	const QString configVersionMarker("configVersion: ");

	if (message.startsWith(versionMarker)) {
		mVersionTimer->stop();
		const QString currentVersion = message.mid(versionMarker.length());
		if (currentVersion != requiredVersion) {
			Q_EMIT trikRuntimeVersionError();
		}
	} else if (message.startsWith(errorMarker)) {
		Q_EMIT messageFromRobot(MessageKind::error, message.mid(errorMarker.length()));
	} else if (message.startsWith(infoMarker)) {
		Q_EMIT messageFromRobot(MessageKind::info, message.mid(infoMarker.length()));
	} else if (message.startsWith(printMarker)) {
		Q_EMIT messageFromRobot(MessageKind::text, message.mid(printMarker.length()));
	} else if (message.startsWith(fileContentsMarker)) {
		Q_EMIT messageFromRobot(MessageKind::fileContents, message.mid(fileContentsMarker.length()));
	} else if (message.startsWith(mailMarker)) {
		Q_EMIT messageFromRobot(MessageKind::mail, message.mid(mailMarker.length()));
	} else if (message == "keepalive") {
		// Just ignoring it
	} else if (message.startsWith(configVersionMarker)) {
		const QString configVersion = message.mid(configVersionMarker.length());
		Q_EMIT casingVersionReceived(configVersion);
	} else {
		QLOG_INFO() << "Incoming message of unknown type: " << message;
	}
}

void TcpRobotCommunicatorWorker::processTelemetryMessage(const QString &message)
{
	const QString sensorMarker("sensor:");
	const QString allDataMarker("allData:");

	if (message.startsWith(sensorMarker)) {
		QString data(message);
		data.remove(0, sensorMarker.length());
		handleValue(data);
	} else if (message.startsWith(allDataMarker)) {
		QString data(message);
		data.remove(0, allDataMarker.length());
		QStringList values = data.split(';');
		for (auto const &value : values) {
			handleValue(value);
		}
	} else if (message == "keepalive") {
		// Just ignoring it
	} else {
		QLOG_INFO() << "Incoming message of unknown type: " << message;
	}
}

void TcpRobotCommunicatorWorker::handleValue(const QString &data)
{
	const auto &temp = data;
	QStringList portAndValue = temp.split(":");
	if (portAndValue[1].startsWith('(')) {
		portAndValue[1].remove(0, 1);
		portAndValue[1].remove(portAndValue[1].length() - 1, 1);
		const QStringList stringValues = portAndValue[1].split(",");
		QVector<int> values;
		for (const QString &value : stringValues) {
			values.push_back(value.toInt());
		}

		Q_EMIT newVectorSensorData(portAndValue[0], values);
	} else {
		Q_EMIT newScalarSensorData(portAndValue[0], portAndValue[1].toInt());
	}
}

void TcpRobotCommunicatorWorker::onVersionTimeOut()
{
	mVersionTimer->stop();
	Q_EMIT trikRuntimeVersionGettingError();
}

void TcpRobotCommunicatorWorker::versionRequest()
{
	mControlConnection->send("version");
	mVersionTimer->start(3000);
}

void TcpRobotCommunicatorWorker::connect()
{
	const QString server = qReal::SettingsManager::value(mRobotIpRegistryKey).toString();
	const QHostAddress hostAddress(server);
	if (hostAddress.isNull()) {
		QLOG_ERROR() << "Unable to resolve host.";
		Q_EMIT connectionError(tr("Unable to resolve host."));
		return;
	}

	if (mControlConnection->isConnected() && mTelemetryConnection->isConnected()) {
		if (mCurrentIp == server) {
			return;
		}

		disconnectConnection();
	}

	mCurrentIp = server;
	const bool result = mControlConnection->connect(hostAddress) && mTelemetryConnection->connect(hostAddress);
	if (result) {
		versionRequest();
		Q_EMIT connected();
	} else {
		Q_EMIT connectionError(tr("Connection failed. IP: %1").arg(server));
	}
}

void TcpRobotCommunicatorWorker::disconnectConnection()
{
	mControlConnection->disconnect();
	mTelemetryConnection->disconnect();

	Q_EMIT disconnected();
}
