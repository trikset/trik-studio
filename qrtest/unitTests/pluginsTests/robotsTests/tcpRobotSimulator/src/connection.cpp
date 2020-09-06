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

#include "connection.h"

#include <QtNetwork/QTcpSocket>
#include <QtCore/QTimer>
#include <QtCore/QThread>

#include <QtCore/QDebug>

static const QString trikRuntimeVersion = "3.1.3";

static const int keepaliveTime = 3000;
static const int heartbeatTime = 5000;

using namespace tcpRobotSimulator;

Connection::Connection(Protocol connectionProtocol, Heartbeat useHeartbeat, const QString &configVersion)
	: mProtocol(connectionProtocol)
	, mUseHeartbeat(useHeartbeat == Heartbeat::use)
	, mConfigVersion(configVersion)
{
}

Connection::~Connection()
{
}

void Connection::init(const QHostAddress &ip, int port)
{
	mSocket = new QTcpSocket(this);

	connectSlots();

	initKeepalive();

	mSocket->connectToHost(ip, port);

	if (!mSocket->waitForConnected()) {
		doDisconnect();
	} else {
		if (mUseHeartbeat) {
			mKeepAliveTimer->start();
			mHeartbeatTimer->start();
		}
	}
}

void Connection::send(const QByteArray &data)
{
	if (mSocket->state() != QAbstractSocket::ConnectedState) {
		return;
	}

	if (mUseHeartbeat) {
		/// Reset keepalive timer to avoid spamming with keepalive packets.
		mKeepAliveTimer->start();
	}

	const QByteArray message = mProtocol == Protocol::messageLength
			? QByteArray::number(data.size()) + ':' + data
			: data + '\n';

	mSocket->write(message);
}

void Connection::init(int socketDescriptor)
{
	mSocket = new QTcpSocket(this);

	initKeepalive();

	if (!mSocket->setSocketDescriptor(socketDescriptor)) {
		return;
	}

	connectSlots();

	if (mUseHeartbeat) {
		mKeepAliveTimer->start();
		mHeartbeatTimer->start();
	}
}

void Connection::onReadyRead()
{
	if (!mSocket || !mSocket->isValid()) {
		return;
	}

	if (mUseHeartbeat) {
		/// Reset heartbeat timer, we received something, so connection is up.
		mHeartbeatTimer->start();
	}

	const QByteArray &data = mSocket->readAll();
	mBuffer.append(data);

	processBuffer();
}

void Connection::processBuffer()
{
	switch (mProtocol) {
	case Protocol::messageLength:
	{
		while (!mBuffer.isEmpty()) {
			if (mExpectedBytes == 0) {
				// Determining the length of a message.
				const int delimiterIndex = mBuffer.indexOf(':');
				if (delimiterIndex == -1) {
					// We did not receive full message length yet.
					return;
				} else {
					const QByteArray length = mBuffer.left(delimiterIndex);
					mBuffer = mBuffer.mid(delimiterIndex + 1);
					bool ok = false;
					mExpectedBytes = length.toInt(&ok);
					if (!ok) {
						mExpectedBytes = 0;
					}
				}
			} else {
				if (mBuffer.size() >= mExpectedBytes) {
					QByteArray const message = mBuffer.left(mExpectedBytes);
					mBuffer = mBuffer.mid(mExpectedBytes);

					handleIncomingData(message);

					mExpectedBytes = 0;
				} else {
					// We don't have all message yet.
					return;
				}
			}
		}
		break;
	}
	case Protocol::endOfLineSeparator:
	{
		if (mBuffer.contains('\n')) {
			const auto messages = mBuffer.split('\n');
			for (int i = 0; i < messages.size() - 1; ++i) {
				handleIncomingData(messages.at(i));
			}

			mBuffer = messages.last();
		}
		break;
	}
	}
}

void Connection::handleIncomingData(const QByteArray &data)
{
	if (data == "keepalive") {
		return;
	} if (data == "version") {
		mVersionRequestReceived = true;
		send(QString("version: " + trikRuntimeVersion).toUtf8());
	} else {
		processData(data);
	}
}

void Connection::onConnect()
{
	if (mUseHeartbeat) {
		mKeepAliveTimer->start();
		mHeartbeatTimer->start();
	}
}

void Connection::onDisconnect()
{
	doDisconnect();
}

void Connection::onError(QAbstractSocket::SocketError error)
{
	Q_UNUSED(error);
	doDisconnect();
}

void Connection::keepAlive()
{
	send("keepalive");
}

void Connection::onHeartbeatTimeout()
{
	/// We did not receive anything for some time, assuming connection is down and closing socket.
	mSocket->disconnectFromHost();
}

void Connection::connectSlots()
{
	connect(mSocket, &QTcpSocket::readyRead, this, &Connection::onReadyRead);
	connect(mSocket, &QTcpSocket::connected, this, &Connection::onConnect);
	connect(mSocket, &QTcpSocket::disconnected, this, &Connection::onDisconnect);
	connect(mSocket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::error)
			, this, &Connection::onError);
}

void Connection::doDisconnect()
{
	if (mDisconnectReported) {
		return;
	}

	mDisconnectReported = true;

	emit disconnected();

	thread()->quit();
}

void Connection::initKeepalive()
{
	if (mUseHeartbeat) {
		mKeepAliveTimer.reset(new QTimer);
		mHeartbeatTimer.reset(new QTimer);

		connect(mKeepAliveTimer.data(), &QTimer::timeout, this, &Connection::keepAlive);
		connect(mHeartbeatTimer.data(), &QTimer::timeout, this, &Connection::onHeartbeatTimeout);
		connect(this, &Connection::disconnected, mKeepAliveTimer.data(), &QTimer::stop);
		connect(this, &Connection::disconnected, mHeartbeatTimer.data(), &QTimer::stop);

		mKeepAliveTimer->setSingleShot(false);
		mHeartbeatTimer->setSingleShot(false);

		mKeepAliveTimer->setInterval(keepaliveTime);
		mHeartbeatTimer->setInterval(heartbeatTime);
	}
}

void Connection::processData(const QByteArray &data)
{
	const QString command = QString::fromUtf8(data.data());

	if (command.startsWith("keepalive")) {
		// Discard "keepalive" output.
		return;
	}

	if (command.startsWith("file:")) {
	} else if (command.startsWith("run:")) {
		mRunProgramRequestReceived = true;
		emit runProgramRequestReceivedSignal();
	} else if (command == "stop") {
	} else if (command.startsWith("direct:")) {
	} else if (command.startsWith("directScript:")) {
	} else if (command == "configVersion") {
		mConfigVersionRequestReceived = true;
		send(("configVersion: " + mConfigVersion).toUtf8());
	}
}

bool Connection::runProgramRequestReceived() const
{
	return mRunProgramRequestReceived;
}

bool Connection::configVersionRequestReceived() const
{
	return mConfigVersionRequestReceived;
}

bool Connection::versionRequestReceived() const
{
	return mVersionRequestReceived;
}
