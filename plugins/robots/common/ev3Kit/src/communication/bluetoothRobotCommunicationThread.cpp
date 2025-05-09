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

#include "ev3Kit/communication/bluetoothRobotCommunicationThread.h"

#include <QtCore/QMetaType>
#include <QtCore/QTimer>
#include <QtCore/QThread>
#include <QtCore/QFileInfo>
#include <QtSerialPort/QSerialPort>
#include <qrkernel/settingsManager.h>

#include "ev3Kit/communication/commandConstants.h"
#include "ev3Kit/communication/ev3DirectCommand.h"

#include <QsLog.h>

const int keepAliveResponseSize = 5;
const int serialPortTimeoutMsec = 3000;

using namespace ev3::communication;

BluetoothRobotCommunicationThread::BluetoothRobotCommunicationThread()
	: mPort(nullptr)
	, mKeepAliveTimer(new QTimer(this))
{
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

	const bool result = send1(buffer);
	if (buffer.size() >= 5 && buffer[4] == enums::commandType::CommandTypeEnum::DIRECT_COMMAND_REPLY) {
		QByteArray const result = receive(responseSize);
		emit response(addressee, result);
	} else {
		emit response(addressee, QByteArray());
	}

	return result;
}

bool BluetoothRobotCommunicationThread::connect()
{
	if (mPort && mPort->isOpen()) {
		emit connected(true, QString());
		return true;
	}

	const QString portName = qReal::SettingsManager::value("Ev3BluetoothPortName").toString();
	mPort = new QSerialPort(portName, this);
	mPort->setBaudRate(QSerialPort::BaudRate::Baud9600);
	mPort->setFlowControl(QSerialPort::FlowControl::NoFlowControl);
	mPort->setParity(QSerialPort::Parity::NoParity);
	mPort->setDataBits(QSerialPort::DataBits::Data8);
	mPort->setStopBits(QSerialPort::StopBits::TwoStop);

	if( !mPort->open(QIODevice::ReadWrite)) {
		QLOG_ERROR() << "Failed to open actual port" << portName
			    << "with error" << mPort->error()
			    << "with error string" << mPort->errorString();
		emit connected(false, tr("Cannot open port ") + portName);
		return false;
	}

	// Sending "Keep alive" command to check connection.
	keepAlive();
	const QByteArray response = receive(keepAliveResponseSize);
	emit connected(!response.isEmpty(), QString());

	mKeepAliveTimer->moveToThread(this->thread());
	mKeepAliveTimer->disconnect();
	QObject::connect(mKeepAliveTimer, &QTimer::timeout, this, &BluetoothRobotCommunicationThread::checkForConnection);
	QObject::connect(this, &BluetoothRobotCommunicationThread::disconnected, mKeepAliveTimer, &QTimer::stop);
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
	Q_UNUSED(allow);
}

bool BluetoothRobotCommunicationThread::send(const QByteArray &buffer, int responseSize, QByteArray &outputBuffer)
{
	const bool result = send1(buffer);
	outputBuffer = receive(responseSize);
	return result;
}

bool BluetoothRobotCommunicationThread::send1(const QByteArray &buffer) const
{
	return mPort && (mPort->write(buffer) > 0) && mPort->waitForBytesWritten(serialPortTimeoutMsec);
}

QByteArray BluetoothRobotCommunicationThread::receive(int size) const
{
	if (!mPort || !mPort->waitForReadyRead(serialPortTimeoutMsec)) {
		return {};
	}
	return mPort->read(size);
}

void BluetoothRobotCommunicationThread::checkForConnection()
{
	if (!mPort || !mPort->isOpen()) {
		return;
	}

	keepAlive();
	const QByteArray response = receive(keepAliveResponseSize);

	if (response == QByteArray()) {
		emit disconnected();
	}
}

void BluetoothRobotCommunicationThread::keepAlive()
{
	QByteArray command = Ev3DirectCommand::formCommand(10, 0, 0, 0
			, enums::commandType::CommandTypeEnum::DIRECT_COMMAND_REPLY);
	int index = 7;
	Ev3DirectCommand::addOpcode(enums::opcode::OpcodeEnum::KEEP_ALIVE, command, index);
	Ev3DirectCommand::addByteParameter(10, command, index); // 10 - Number of minutes before entering sleep mode.
	if (!send1(command)) {
		QLOG_ERROR() << "Bluetooth: failed to send keep-alive";
	}
}
