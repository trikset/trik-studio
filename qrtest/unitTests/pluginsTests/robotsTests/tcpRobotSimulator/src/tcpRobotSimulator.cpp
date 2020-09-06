/* Copyright 2016 CyberTech Labs Ltd.
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

#include "tcpRobotSimulator/tcpRobotSimulator.h"

#include <QtCore/QThread>
#include <QtCore/QMetaObject>

#include "connection.h"

using namespace tcpRobotSimulator;

TcpRobotSimulator::TcpRobotSimulator(int port)
{
	if(!listen(QHostAddress::LocalHost, port)) {
		qErrnoWarning(errno, "Failed to open TCP port");
	}
}

TcpRobotSimulator::~TcpRobotSimulator()
{
}

void TcpRobotSimulator::incomingConnection(qintptr socketDescriptor)
{
	mConnection = new Connection(Protocol::messageLength, Heartbeat::use, mConfigVersion);
	mConnectionThread.reset(new QThread());
	mConnection->moveToThread(mConnectionThread.data());
	connect(mConnectionThread.data(), &QThread::finished, mConnection, &QObject::deleteLater);
	connect(mConnection, &Connection::runProgramRequestReceivedSignal
			, this, &TcpRobotSimulator::runProgramRequestReceivedSignal, Qt::QueuedConnection);
	connect(mConnectionThread.data(), &QThread::started
			, mConnection, [this, socketDescriptor](){ mConnection->init(socketDescriptor); });
	mConnectionThread->start();
}

bool TcpRobotSimulator::runProgramRequestReceived() const
{
	return mConnection && mConnection->runProgramRequestReceived();
}

bool TcpRobotSimulator::configVersionRequestReceived() const
{
	return mConnection && mConnection->configVersionRequestReceived();
}

bool TcpRobotSimulator::versionRequestReceived() const
{
	return mConnection && mConnection->versionRequestReceived();
}

void TcpRobotSimulator::setConfigVersion(const QString &configVersion)
{
	mConfigVersion = configVersion;
}
