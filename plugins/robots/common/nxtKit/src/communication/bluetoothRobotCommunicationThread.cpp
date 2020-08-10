/* Copyright 2012-2015 QReal Research Group
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

#include "nxtKit/communication/bluetoothRobotCommunicationThread.h"

#include <QtCore/QMetaType>
#include <QtCore/QTimer>
#include <QtCore/QThread>
#include <QEventLoop>
#include <ctime>

#include <qrkernel/settingsManager.h>
#include <plugins/robots/thirdparty/qextserialport/src/qextserialport.h>

#include "nxtKit/communication/nxtCommandConstants.h"

const int keepAliveResponseSize = 9;
const int getFirmwareVersionResponseSize = 9;

using namespace nxt::communication;

BluetoothRobotCommunicationThread::BluetoothRobotCommunicationThread()
	: mPort(nullptr)
	, mKeepAliveTimer(new QTimer(this))
{
	QObject::connect(mKeepAliveTimer, &QTimer::timeout, this, &BluetoothRobotCommunicationThread::checkForConnection);
	QObject::connect(this, &BluetoothRobotCommunicationThread::disconnected, mKeepAliveTimer, &QTimer::stop);
}

BluetoothRobotCommunicationThread::~BluetoothRobotCommunicationThread()
{
	disconnect();
}

bool BluetoothRobotCommunicationThread::send(QObject *addressee, const QByteArray &buffer, int responseSize)
{
	if (!mPort) {
		emit response(addressee, QByteArray());
		return false;
	}

	const bool result = send(buffer);
	if (buffer.size() >= 3 && buffer[2] == enums::errorCode::success) {
		const QByteArray result = receive(responseSize);
		emit response(addressee, result);
	} else {
		emit response(addressee, QByteArray());
	}

	return result;
}

bool BluetoothRobotCommunicationThread::connect()
{
	if (mPort) {
		disconnect();
		QEventLoop l;
		QTimer::singleShot(1000, &l, &QEventLoop::quit);
		l.exec();
	}

	const QString portName = qReal::SettingsManager::value("NxtBluetoothPortName").toString();
	mPort = new QextSerialPort(portName, QextSerialPort::Polling);
	mPort->setBaudRate(BAUD9600);
	mPort->setFlowControl(FLOW_OFF);
	mPort->setParity(PAR_NONE);
	mPort->setDataBits(DATA_8);
	mPort->setStopBits(STOP_2);
	mPort->setTimeout(3000);

	mPort->open(QIODevice::ReadWrite | QIODevice::Unbuffered);

	// Sending "Get firmware version" system command to check connection.
	QByteArray command(4, 0);
	command[0] = 0x02;  //command length
	command[1] = 0x00;
	command[2] = 0x01;
	command[3] = 0x88;

	send(command);
	const QByteArray response = receive(getFirmwareVersionResponseSize);
	emit connected(!response.isEmpty(), QString());

	mKeepAliveTimer->start(500);

	return !response.isEmpty();
}

void BluetoothRobotCommunicationThread::reconnect()
{
	connect();
}

void BluetoothRobotCommunicationThread::disconnect()
{
	delete mPort;
	mPort = nullptr;
	emit disconnected();
}

void BluetoothRobotCommunicationThread::allowLongJobs(bool allow)
{
	Q_UNUSED(allow)
}

bool BluetoothRobotCommunicationThread::send(const QByteArray &buffer, int responseSize, QByteArray &outputBuffer)
{
	const bool result = send(buffer);
	outputBuffer = receive(responseSize);
	return result;
}

bool BluetoothRobotCommunicationThread::send(const QByteArray &buffer) const
{
	return mPort->write(buffer) > 0;
}

QByteArray BluetoothRobotCommunicationThread::receive(int size) const
{
	return mPort->read(size);
}

void BluetoothRobotCommunicationThread::checkForConnection()
{
	if (!mPort || !mPort->isOpen()) {
		return;
	}

	QByteArray command(4, 0);
	command[0] = 0x02;
	command[1] = 0x00;

	command[2] = enums::telegramType::directCommandResponseRequired;
	command[3] = enums::commandCode::KEEPALIVE;

	send(command);

	const QByteArray response = receive(keepAliveResponseSize);

	if (response == QByteArray()) {
		emit disconnected();
	}
}
