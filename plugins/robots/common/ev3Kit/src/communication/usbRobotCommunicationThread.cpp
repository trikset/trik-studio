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

#include "ev3Kit/communication/usbRobotCommunicationThread.h"

#include <QtCore/QTimer>
#include <QtCore/QThread>

#if defined(Q_OS_LINUX)
#include <errno.h>
#include "plugins/robots/thirdparty/hidapi/linux/hid.c"
static int hidapi_lasterror() { return errno; }
#elif defined(Q_OS_WIN)
#include <errhandlingapi.h>
static int hidapi_lasterror() { return GetLastError(); }
#include "plugins/robots/thirdparty/hidapi/windows/hid.c"
#elif defined(Q_OS_MAC)
#include <errno.h>
#include "plugins/robots/thirdparty/hidapi/mac/hid.c"
static int hidapi_lasterror() { return errno; }
#endif

#include <qrkernel/logging.h>

#include "ev3Kit/communication/ev3DirectCommand.h"
#include "ev3Kit/communication/commandConstants.h"

static const int EV3_VID = 0x0694;
static const int EV3_PID = 0x0005;
static const int EV3_USB_TIMEOUT = 2000;
static const int EV3_INTERFACE_NUMBER = 0;
static const int EV3_CONFIGURATION_NB = 1;
static const int EV3_EP_OUT = 0x01;
static const int EV3_EP_IN = 0x81;
static const int EV3_PACKET_SIZE = 0x400;
static const int MAX_DEBUG_LEVEL = 3;

using namespace ev3::communication;

UsbRobotCommunicationThread::UsbRobotCommunicationThread()
	: mHandle(nullptr)
	, mKeepAliveTimer((this))
{
}

UsbRobotCommunicationThread::~UsbRobotCommunicationThread()
{
	disconnect();
}

bool UsbRobotCommunicationThread::send(QObject *addressee, const QByteArray &buffer, int responseSize)
{
	if (!mHandle) {
		emit response(addressee, QByteArray());
		return false;
	}

	const bool result = send1(buffer);
	if (buffer.size() >= 5 && buffer[4] == enums::commandType::CommandTypeEnum::DIRECT_COMMAND_REPLY) {
		const QByteArray result = receive(responseSize);
		emit response(addressee, result);
	} else {
		emit response(addressee, QByteArray());
	}

	return result;
}

bool UsbRobotCommunicationThread::connect()
{
	if (mHandle) {
		QLOG_INFO() << "EV3USB" << "Handle reused";
		emit connected(true, QString());
		return true;
	}

	{
		// it is not necessary but logs are extremely useful
		QLOG_INFO() << "hidapi devices:";
		hid_device_info *devs = hid_enumerate(0x0, 0x0);
		for(hid_device_info *cur_dev = devs; cur_dev; cur_dev = cur_dev->next) {
			QLOG_INFO() << qSetFieldWidth(4) << right << qSetPadChar('0')  << hex << uppercasebase
						<< cur_dev->vendor_id
						<< qSetFieldWidth(4) << right << qSetPadChar('0')  << hex << uppercasebase
						<< cur_dev->product_id
						<< reset << cur_dev->path
						<< QString::fromWCharArray(cur_dev->serial_number)
						<< QString::fromWCharArray(cur_dev->manufacturer_string)
						<< QString::fromWCharArray(cur_dev->product_string);
		}
		hid_free_enumeration(devs);
	}

	mHandle = hid_open(EV3_VID, EV3_PID, nullptr);
	if (!mHandle) {
		QLOG_ERROR() << "hid_open failed for "
				<< QString::number(EV3_VID) << QString::number(EV3_PID);
		emit connected(false, tr("Cannot find EV3 device. Check robot connected and turned on and try again."));
		return false;
	}

	emit connected(true, QString());
	mKeepAliveTimer.disconnect();
	QObject::connect(&mKeepAliveTimer, SIGNAL(timeout()), this, SLOT(checkForConnection()), Qt::UniqueConnection);
	mKeepAliveTimer.start(3000);
	return true;
}

void UsbRobotCommunicationThread::reconnect()
{
	connect();
}

void UsbRobotCommunicationThread::disconnect()
{
	if (mHandle) {
		hid_close(mHandle);
		mHandle = nullptr;
		hid_exit();
	}

	mKeepAliveTimer.stop();
	emit disconnected();
}

void UsbRobotCommunicationThread::allowLongJobs(bool allow)
{
	Q_UNUSED(allow);
}

void UsbRobotCommunicationThread::checkForConnection()
{
	if (!mHandle) {
		return;
	}

	// Sending "Keep alive" command to check connection.
	QByteArray command;
	command.resize(10);
	command[0] = 8;
	command[1] = 0;
	command[2] = (++mMessageCounter);
	command[3] = mMessageCounter >> 8;
	command[4] = enums::commandType::CommandTypeEnum::DIRECT_COMMAND_NO_REPLY;
	command[5] = 0;
	command[6] = 0;
	command[7] = enums::opcode::OpcodeEnum::KEEP_ALIVE;
	command[8] = enums::argumentSize::ArgumentSizeEnum::BYTE;
	command[9] = 10; //Number of minutes before entering sleep mode.

	if (!send1(command)) {
		QLOG_ERROR() << "EV3USB" << "Connection lost";
		hid_close(mHandle);
		mHandle = nullptr;
		emit disconnected();
		mKeepAliveTimer.stop();
	}
}

bool UsbRobotCommunicationThread::send(const QByteArray &buffer, int responseSize, QByteArray &outputBuffer)
{
	auto ok = send1(buffer);
	if (ok)
		outputBuffer = receive(responseSize);
	return ok;
}

bool UsbRobotCommunicationThread::send1(const QByteArray &buf) const
{
	if (!mHandle)
		return false;

	auto buffer = buf;
	buffer.prepend({'\0'});
	auto n = hid_write(mHandle, reinterpret_cast<const uint8_t*>(buffer.data()), buffer.size());
	auto ok = n >= buffer.size();
	if (!ok) {
		QLOG_ERROR() << "EV3USB" << "Failed hid_write with" << n
					 << "bytes written of" << buffer.size() << ", errno =" << hidapi_lasterror();
	}

	return ok;
}

QByteArray UsbRobotCommunicationThread::receive(int size) const
{
	// It's strange, but regardless of kind of response, it must have size = 1024 (EV3_PACKET_SIZE)
	// If we set another size(For example, response[10]), program will throw error.
	uchar response[EV3_PACKET_SIZE] {0, };
	size_t bufSize = sizeof(response)/sizeof (response[0]);
//	response[0] = 0;
//	response[1] = EV3_EP_IN;
//	auto n = hid_write(mHandle, response, bufSize);
//	if (n != bufSize) {
//		QLOG_ERROR() << "EV3USB" << "Failed hid_write with errno =" << errno;
//	}

	auto n = hid_read(mHandle, response, bufSize);
	if ( n <= 0) {
		QLOG_ERROR() << "EV3USB" << "Failed hid_read with" << n << ", errno = " << errno;
	}
	auto resultSize = qMin(EV3_PACKET_SIZE, size);
	QByteArray result(qMin(resultSize, n), '\0');
	for (int i = 0; i < result.size(); ++i) {
		result[i] = response[i];
	}

	return result;
}
