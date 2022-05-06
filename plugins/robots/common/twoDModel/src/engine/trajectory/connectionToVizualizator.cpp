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
#include "connectionToVizualizator.h"
#include <qrkernel/settingsManager.h>
#include <qrkernel/settingsListener.h>

//namespace trajectory {
/// Connection to Unity to send frames, run/stop/restart signals
ConnectionToVizualizator::ConnectionToVizualizator()
//ConnectionToVizualizator::ConnectionToVizualizator(QString ip, int port)
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

ConnectionToVizualizator::~ConnectionToVizualizator()
{
	reset();
	mKeepaliveTimer->deleteLater();
	mSocket->deleteLater();
}

void ConnectionToVizualizator::init()
{
	mKeepaliveTimer = new QTimer();
	mSocket = new QTcpSocket();
	qRegisterMetaType<QAbstractSocket::SocketState>();
	connect(mKeepaliveTimer, &QTimer::timeout, this, [this]() { write("keepalive \n"); } );
	connect(mSocket, &QTcpSocket::readyRead, this, &ConnectionToVizualizator::onReadyRead);
}

bool ConnectionToVizualizator::isConnected() const
{
	return mSocket->state() == QTcpSocket::ConnectedState;
}

void ConnectionToVizualizator::write(const QString &data)
{
	if (mSendData)
	{
		mSocket->write(data.toLatin1().data());
	}
}

void ConnectionToVizualizator::onReadyRead()
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

void ConnectionToVizualizator::stopPressed()
{
	write("Stop");
}

void ConnectionToVizualizator::startPressed()
{
	write("Run");
}

void ConnectionToVizualizator::restartPressed()
{
	write("Restart");
}

void ConnectionToVizualizator::reset()
{
	if (!mKeepaliveTimer->isActive())
		return;
	mKeepaliveTimer->stop();
	mSocket->disconnectFromHost();
}

quint16 ConnectionToVizualizator::getPort() const
{
	return mPort;
}

QString ConnectionToVizualizator::getIp() const
{
	return mIp;
}

void ConnectionToVizualizator::setPort(const quint16 &value)
{
	mPort = value;
}

void ConnectionToVizualizator::setIp(const QString &value)
{
	mIp = value;
}

void ConnectionToVizualizator::connectToHost()
{
	if (mSendData)
	{
		reset();
		constexpr auto timeout = 3 * 1000;
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

void ConnectionToVizualizator::disconnectFromHost()
{
	if (isConnected()) {
		mSocket->disconnectFromHost();
		if (mSocket->state() != QAbstractSocket::UnconnectedState) {
			mSocket->waitForDisconnected(3000);
		}
	}
}

bool ConnectionToVizualizator::isSendingData()
{
	return mSendData;
}
//}
