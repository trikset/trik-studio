/* Copyright 2022 Lada Egorova
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

#include <QEventLoop>
#include <QsLog.h>
#include "connectionToVisualizer.h"
#include <qrkernel/settingsManager.h>
#include <qrkernel/settingsListener.h>

using namespace twoDModel::trajectory;

/// Connection to Unity to send frames, run/stop/restart signals
ConnectionToVisualizer::ConnectionToVisualizer()
//ConnectionToVisualizer::ConnectionToVisualizer(QString ip, int port)
//	: mIp(ip)
//	, mPort(port)
{
	setIp(qReal::SettingsManager::value("UnityTcpServer").toString());
	mSendData = qReal::SettingsManager::value("UnitySendData").toBool();
	qReal::SettingsListener::listen("UnitySendData", [this](bool send){
		mSendData = send;
	}, this);
	qReal::SettingsListener::listen("UnityTcpServer", [this](){
		setIp(qReal::SettingsManager::value(("UnityTcpServer")).toString());
		if (mSendData){
			connectToHost();
		}
	}, this);
}

ConnectionToVisualizer::~ConnectionToVisualizer()
{
	reset();
	mKeepaliveTimer->deleteLater();
	mSocket->deleteLater();
}

void ConnectionToVisualizer::init()
{
	mKeepaliveTimer = new QTimer();
	mSocket = new QTcpSocket();
	qRegisterMetaType<QAbstractSocket::SocketState>();
	connect(mKeepaliveTimer, &QTimer::timeout, this, [this]() { write("keepalive \n"); } );
	connect(mSocket, &QTcpSocket::readyRead, this, &ConnectionToVisualizer::onReadyRead);
}

bool ConnectionToVisualizer::isConnected() const
{
	return mSocket->state() == QTcpSocket::ConnectedState;
}

void ConnectionToVisualizer::write(const QString &data)
{
	int result = 0;
	if (mSendData)
	{
		if (result == mSocket->write(data.toLatin1().data()) != 0){
			QLOG_ERROR() << "Exception occured when sending data";
		}
	}
}

void ConnectionToVisualizer::onReadyRead()
{
	const QByteArray &data = mSocket->readAll();
	mBuffer = data;
	if (mBuffer == "Stop") {
		emit stopRequested();
	}
	else if (mBuffer == "Run") {
		emit runRequested();
	}
	else if (mBuffer == "Restart") {
		emit restartRequested();
	}
}

void ConnectionToVisualizer::stopPressed()
{
	write("Stop");
}

void ConnectionToVisualizer::startPressed()
{
	write("Run");
}

void ConnectionToVisualizer::restartPressed()
{
	write("Restart");
}

void ConnectionToVisualizer::reset()
{
	if (!mKeepaliveTimer->isActive())
		return;
	mKeepaliveTimer->stop();
	mSocket->disconnectFromHost();
}

quint16 ConnectionToVisualizer::getPort() const
{
	return mPort;
}

QString ConnectionToVisualizer::getIp() const
{
	return mIp;
}

void ConnectionToVisualizer::setPort(const quint16 &value)
{
	mPort = value;
}

void ConnectionToVisualizer::setIp(const QString &value)
{
	mIp = value;
}

void ConnectionToVisualizer::connectToHost()
{
	if (mSendData)
	{
		reset();
		constexpr auto timeout = 3000;
		QEventLoop loop;
		QTimer::singleShot(timeout, &loop, &QEventLoop::quit);
		connect(mSocket, &QTcpSocket::connected, &loop, &QEventLoop::quit);
		connect(mSocket
				, static_cast<void(QTcpSocket::*)(QAbstractSocket::SocketError)>(&QTcpSocket::error)
				, &loop
				, [&loop](QAbstractSocket::SocketError) { loop.quit(); });
		mSocket->setProxy(QNetworkProxy::NoProxy);
		mSocket->connectToHost(mIp, mPort);
		loop.exec();

		if (mSocket->state() == QTcpSocket::ConnectedState) {
			mKeepaliveTimer->start(3000);
		} else {
			mSocket->abort();
		}
	}
}

void ConnectionToVisualizer::disconnectFromHost()
{
	if (isConnected()) {
		mSocket->disconnectFromHost();
		if (mSocket->state() != QAbstractSocket::UnconnectedState) {
			mSocket->waitForDisconnected(3000);
		}
	}
}

bool ConnectionToVisualizer::isSendingData()
{
	return mSendData;
}
//}
