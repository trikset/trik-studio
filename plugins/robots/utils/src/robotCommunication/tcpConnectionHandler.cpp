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

#include "tcpConnectionHandler.h"

#include <QtNetwork/QHostAddress>

#include <qrkernel/logging.h>

#include <QNetworkProxy>

const int keepaliveTime = 3000;

using namespace utils::robotCommunication;

TcpConnectionHandler::TcpConnectionHandler(int port)
	: mKeepAliveTimer(new QTimer(this))
	, mPort(port)
{
	QObject::connect(&mSocket, &QTcpSocket::readyRead, this
		, &TcpConnectionHandler::onIncomingData, Qt::DirectConnection);

	QObject::connect(&mSocket, &QTcpSocket::disconnected
					 , mKeepAliveTimer, &QTimer::stop, Qt::DirectConnection);

	QObject::connect(mKeepAliveTimer, &QTimer::timeout, this
		, &TcpConnectionHandler::keepalive, Qt::DirectConnection);

	mKeepAliveTimer->setInterval(keepaliveTime);
	mKeepAliveTimer->setSingleShot(false);
}

TcpConnectionHandler::~TcpConnectionHandler()
{
	mSocket.disconnect(this); //otherwise DirectConnection from another thread can happen afer dtor
}

bool TcpConnectionHandler::connect(const QHostAddress &serverAddress)
{
	if (isConnected() || mSocket.state() == QTcpSocket::ConnectingState) {
		return true;
	}
	// Sometimes local proxy configuration is an issue
	// Try to avoid system proxy, because usually we are in local hetwork
	// But fallback to proxy if connnection failed
	mSocket.setProxy(QNetworkProxy::NoProxy);
	mSocket.connectToHost(serverAddress, static_cast<quint16>(mPort));
	auto result = mSocket.waitForConnected(3000);
	if (!result) {
		// QNetworkProxyFactory::systemProxyForQuery can run few seconds on Windows
		// We can make a reconnect attempt wihout quering proxies
		// However it will take (probably) additional 3000 ms for each case
		// when just an ip-address was wrong (or robot is turned off)
		// In case systemProxyForQuery takes more than 3000 ms,
		// this code can be updated to make a blind re-connection attempt
		// and just logging proxies after an attempt in case of a failure
		const QNetworkProxyQuery proxyQuery(serverAddress.toString(), mPort);
		const auto &tcpProxies = QNetworkProxyFactory::systemProxyForQuery(proxyQuery);
		if (!tcpProxies.isEmpty()
				&& (tcpProxies.size() != 1  || tcpProxies.first().type() != QNetworkProxy::NoProxy)) {
			QLOG_INFO() << "Proxies:" << tcpProxies;
			QLOG_INFO() << "Attempting to reconnect with an application default proxy";
			mSocket.setProxy(QNetworkProxy::DefaultProxy);
			mSocket.connectToHost(serverAddress, static_cast<quint16>(mPort));
			result = mSocket.waitForConnected(3000);
		}
	}

	if (!result) {
		QLOG_ERROR() << mSocket.errorString();
	} else {
		mKeepAliveTimer->start();
	}

	mBuffer.clear();
	mExpectedBytes = 0;

	return result;
}

bool TcpConnectionHandler::isConnected()
{
	return mSocket.state() == QTcpSocket::ConnectedState;
}

void TcpConnectionHandler::disconnect()
{
	if (isConnected()) {
		mSocket.disconnectFromHost();
		if (mSocket.state() != QAbstractSocket::UnconnectedState) {
			mSocket.waitForDisconnected(3000);
		}
	}
}

void TcpConnectionHandler::send(const QString &data)
{
	if (!isConnected()) {
		QLOG_ERROR() << "Attempting to send through unconnected socket";
		return;
	}

	QByteArray dataByteArray = data.toUtf8();
	dataByteArray = QByteArray::number(dataByteArray.size()) + ':' + dataByteArray;
	mSocket.write(dataByteArray);
	if (!mSocket.waitForBytesWritten(3000)) {
		QLOG_ERROR() << "Unable to send data" << data << "to" << mSocket.peerAddress();
	} else {
		/// Resetting keepalive timer since we already sent something to the other side.
		mKeepAliveTimer->start();
	}
}

void TcpConnectionHandler::onIncomingData()
{
	if (!mSocket.isValid()) {
		return;
	}

	const QByteArray &data = mSocket.readAll();
	mBuffer.append(data);

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
					QLOG_ERROR() << "Malformed message, can not determine message length from this:" << length;
					mExpectedBytes = 0;
				}
			}
		} else {
			if (mBuffer.size() >= mExpectedBytes) {
				const QByteArray message = mBuffer.left(mExpectedBytes);
				mBuffer = mBuffer.mid(mExpectedBytes);
				emit messageReceived(message);

				mExpectedBytes = 0;
			} else {
				// We don't have all message yet.
				return;
			}
		}
	}
}

void TcpConnectionHandler::keepalive()
{
	send("keepalive");
}
