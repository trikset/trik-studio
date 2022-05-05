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
#include <QtNetwork/QNetworkProxy>
#include "connectionToVizualizator.h"
#include <qrkernel/settingsManager.h>
#include <qrkernel/settingsListener.h>

/// Connection to Unity to send frames, run/stop/restart signals
ConnectionToVizualizator::ConnectionToVizualizator()
//ConnectionToVizualizator::ConnectionToVizualizator(QString ip, int port)
//	: Ip(ip)
//	, Port(port)
{
	setIp(qReal::SettingsManager::value("UnityTcpServer").toString());
	sendData = qReal::SettingsManager::value("UnitySendData").toBool();
	qReal::SettingsListener::listen("UnitySendData", [this](bool send){
		sendData = send;
	}, this);
	qReal::SettingsListener::listen("UnityTcpServer", [this](){
		setIp(qReal::SettingsManager::value(("UnityTcpServer")).toString());
		if (sendData){
			connectToHost();
		}
	}, this);
}

ConnectionToVizualizator::~ConnectionToVizualizator()
{
	reset();
	keepaliveTimer->deleteLater();
	socket->deleteLater();
}

void ConnectionToVizualizator::init()
{
	keepaliveTimer = new QTimer();
	socket = new QTcpSocket();
	qRegisterMetaType<QAbstractSocket::SocketState>();
	connect(keepaliveTimer, &QTimer::timeout, this, [this]() { write("keepalive \n"); } );
	connect(socket, &QTcpSocket::readyRead, this, &ConnectionToVizualizator::onReadyRead);
}

bool ConnectionToVizualizator::isConnected() const
{
	return socket->state() == QTcpSocket::ConnectedState;
}

void ConnectionToVizualizator::write(const QString &data)
{
	if (sendData)
	{
		socket->write(data.toLatin1().data());
	}
}

void ConnectionToVizualizator::onReadyRead()
{
	const QByteArray &data = socket->readAll();
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
	if (!keepaliveTimer->isActive())
		return;
	keepaliveTimer->stop();
	socket->disconnectFromHost();
}

quint16 ConnectionToVizualizator::getPort() const
{
	return Port;
}

QString ConnectionToVizualizator::getIp() const
{
	return Ip;
}

void ConnectionToVizualizator::setPort(const quint16 &value)
{
	Port = value;
}

void ConnectionToVizualizator::setIp(const QString &value)
{
	Ip = value;
}

void ConnectionToVizualizator::connectToHost()
{
	if (sendData)
	{
		reset();
		constexpr auto timeout = 3 * 1000;
		QEventLoop loop;
		QTimer::singleShot(timeout, &loop, &QEventLoop::quit);
		connect(socket, &QTcpSocket::connected, &loop, &QEventLoop::quit);
		connect(socket
				, static_cast<void(QTcpSocket::*)(QAbstractSocket::SocketError)>(&QTcpSocket::error)
				, &loop
				, [&loop](QAbstractSocket::SocketError) { loop.quit(); });
		socket->setProxy(QNetworkProxy::NoProxy);
		socket->connectToHost(Ip, Port);
		loop.exec();

		if (socket->state() == QTcpSocket::ConnectedState) {
			keepaliveTimer->start(3000);
		} else {
			socket->abort();
		}
	}
}

void ConnectionToVizualizator::disconnectFromHost()
{
	if (isConnected()) {
		socket->disconnectFromHost();
		if (socket->state() != QAbstractSocket::UnconnectedState) {
			socket->waitForDisconnected(3000);
		}
	}
}

bool ConnectionToVizualizator::isSendingData()
{
	return sendData;
}
