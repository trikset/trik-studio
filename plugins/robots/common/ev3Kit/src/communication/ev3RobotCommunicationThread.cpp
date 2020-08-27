/* Copyright 2015 CyberTech Labs Ltd.
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

#include "ev3Kit/communication/ev3RobotCommunicationThread.h"

#include <QtCore/QFileInfo>

#include "ev3Kit/communication/commandConstants.h"
#include "ev3Kit/communication/ev3DirectCommand.h"
#include "QsLog.h"

static constexpr uchar EV3_SYSTEM_COMMAND_REPLY =             0x01;    //  System command, reply required
static constexpr uchar EV3_SYSTEM_COMMAND_NO_REPLY =          0x81;    //  System command, reply not required
static constexpr uchar EV3_BEGIN_DOWNLOAD =                   0x92;    //  Begin file down load
static constexpr uchar EV3_CONTINUE_DOWNLOAD =                0x93;    //  Continue file down load
static constexpr uchar EV3_DELETE_FILE =                      0x9C;    //  Remove file
static constexpr uchar EV3_SYSTEM_REPLY =                     0x03;    //  System command reply
static constexpr uchar EV3_SYSTEM_REPLY_ERROR =               0x05;    //  System command reply error
static constexpr uchar EV3_DELETE_FILE_RESPONSE_SIZE =        8;
static constexpr uchar EV3_BEGIN_DOWNLOAD_RESPONSE_SIZE =     8;
static constexpr uchar EV3_CONTINUE_DOWNLOAD_RESPONSE_SIZE =  8;
static constexpr uchar EV3_SYSTEM_COMMAND_REPLY_SUCCESS =  0x00;
static constexpr uchar EV3_CONTINUE_DOWNLAD_STATUS_EOF =      0x08;

using namespace ev3::communication;

Ev3RobotCommunicationThread::~Ev3RobotCommunicationThread()
{
}

static inline QString char2hex (char c)
{
	return QString("0x%1").arg(static_cast<uint8_t>(c), 2, 16, QLatin1Char('0'));
}

QString Ev3RobotCommunicationThread::uploadFile(const QString &sourceFile, const QString &targetDir)
{
	const QFileInfo fileInfo(sourceFile);
	// A path to file on the remote device.
	const QString devicePath = targetDir + "/" + fileInfo.fileName();

	auto filenameLength = fileInfo.fileName().length();
	if (filenameLength > EV3_MAX_ALLOWED_FILENAME_LENGTH) {
		emit errorOccured(tr("EV3 limits filename length to %1 characters, "
				"but you have %2, please, rename your project.").arg(EV3_MAX_ALLOWED_FILENAME_LENGTH)
				.arg(filenameLength));
		return QString();
	}

	QFile file(sourceFile);
	if (!file.open(QIODevice::ReadOnly)) {
		QLOG_ERROR() << "Failed to open" << sourceFile;
		return QString();
	}

	QByteArray data = file.readAll();
	file.close();
	const int chunkSize = 960; // have no idea why 960...


// uncomment it if it will be needed
// remove previous file
//	const int cmdDeleteSize = 6 + devicePath.size();
//	QByteArray commandDelete(cmdDeleteSize, 0);
//	commandDelete[0] = cmdDeleteSize & 0xFF;
//	commandDelete[1] = (cmdDeleteSize >> 8) & 0xFF ;
//	commandDelete[2] = 0x02;
//	commandDelete[3] = 0x00;
//	commandDelete[4] = SYSTEM_COMMAND_REPLY;
//	commandDelete[5] = DELETE_FILE;
//	int index0 = 6;
//	for (int i = 0; i < devicePath.size(); ++i) {
//		commandDelete[index0++] = devicePath.at(i).toLatin1();
//	}

//	commandDelete[index0] = 0x00;

//	send1(commandDelete);
//	QByteArray commandDeleteResponse = receive(DELETE_FILE_RESPONSE_SIZE);

	// start downloading
	const int cmdBeginSize = 11 + devicePath.size();
	QByteArray commandBegin(cmdBeginSize, 0);
	commandBegin[0] = charOf(cmdBeginSize - 2);
	commandBegin[1] = charOf((cmdBeginSize - 2) >> 8) ;
	commandBegin[2] = charOf(++mMessageCounter);
	commandBegin[3] = charOf(mMessageCounter >> 8);
	commandBegin[4] = charOf(EV3_SYSTEM_COMMAND_REPLY);
	commandBegin[5] = charOf(EV3_BEGIN_DOWNLOAD);
	commandBegin[6] = charOf(data.size());
	commandBegin[7] = charOf(data.size() >> 8);
	commandBegin[8] = charOf(data.size() >> 16);
	commandBegin[9] = charOf(data.size() >> 24);
	int index = 10;
	for (int i = 0; i < devicePath.size(); ++i) {
		commandBegin[index++] = devicePath.at(i).toLatin1();
	}

	commandBegin[index] = 0x00;

	if (!send1(commandBegin)) {
		QLOG_ERROR() << "EV3USB" << "Failed to start program upload to robot";
		return QString();
	}

	QByteArray commandBeginResponse = receive(EV3_BEGIN_DOWNLOAD_RESPONSE_SIZE);

	if (commandBeginResponse.at(4) == EV3_SYSTEM_REPLY_ERROR) {
		QLOG_ERROR() << "EV3USB"
						<< "Reply to cmd" << char2hex(commandBeginResponse.at(5))
						<< "msg#" << (static_cast<uint32_t>(commandBeginResponse.at(3)) << 8)
										+ static_cast<uint32_t>(static_cast<uint8_t>(commandBeginResponse.at(2)))
						<< "status" << char2hex(commandBeginResponse.at(6));
		if (commandBeginResponse.size() > 7) {
			QLOG_INFO() << "EV3USB" << "Reply additional:"
						<< commandBeginResponse.right(commandBeginResponse.size()-7).toHex();
		}

		return QString();
	}

	char handle = commandBeginResponse.at(7);
	int sizeSent = 0;
	while (sizeSent < data.size()) {
		const int sizeToSend = qMin(chunkSize, data.size() - sizeSent);
		const int cmdContinueSize = 7 + sizeToSend;
		QByteArray commandContinue(cmdContinueSize, 0);
		commandContinue[0] = charOf(cmdContinueSize - 2);
		commandContinue[1] = charOf((cmdContinueSize - 2) >> 8);
		commandContinue[2] = charOf(++mMessageCounter);
		commandContinue[3] = charOf(mMessageCounter >> 8);
		commandContinue[4] = charOf(EV3_SYSTEM_COMMAND_REPLY);
		commandContinue[5] = charOf(EV3_CONTINUE_DOWNLOAD);
		commandContinue[6] = handle;
		for (int i = 0; i < sizeToSend; ++i) {
			commandContinue[7 + i] = data.at(sizeSent++);
		}

		if (!send1(commandContinue)) {
			QLOG_ERROR() << "EV3USB" << QString("Failed to send program data to robot bytes %1..%2")
					.arg(sizeSent-sizeToSend).arg(sizeSent-1);
			return QString();
		}

		QByteArray commandContinueResponse = receive(EV3_CONTINUE_DOWNLOAD_RESPONSE_SIZE);
		if (commandContinueResponse.at(4) == EV3_SYSTEM_REPLY_ERROR) {
			QLOG_ERROR() << "EV3USB"
							<< "Reply to cmd" << char2hex(commandContinueResponse.at(5))
							<< "msg#" << (static_cast<uint32_t>(commandContinueResponse.at(3)) << 8)
							   + static_cast<uint32_t>(static_cast<uint8_t>(commandContinueResponse.at(2)))
							<< "status" << char2hex(commandContinueResponse.at(6));
			if (commandContinueResponse.size() > 7) {
				QLOG_INFO() << "EV3USB" << "Reply additional:"
							<< commandContinueResponse.right(commandContinueResponse.size()-7).toHex();
			}
			return QString();
		}
	}

	QLOG_INFO() << "File uploaded" << devicePath;
	return devicePath;
}

bool Ev3RobotCommunicationThread::runProgram(const QString &pathOnRobot)
{
	QByteArray command = Ev3DirectCommand::formCommand(21 + pathOnRobot.size(), ++mMessageCounter, 0x08, 0
			, enums::commandType::CommandTypeEnum::DIRECT_COMMAND_NO_REPLY);
	int index = 7;
	command[index++] = charOf(0xC0);  // opFILE            Opcode file related
	command[index++] = charOf(0x08);
	command[index++] = charOf(0x82);  // LC0(LOAD_IMAGE)   Command encoded as single byte constant
	command[index++] = charOf(0x01);  // LC2(USER_SLOT)    User slot (1 = program slot) encoded as single constant byte
	command[index++] = charOf(0x00);
	command[index++] = charOf(0x84);  // LCS               Encoding: String to follow (zero terminated)

	for (int i = 0; i < pathOnRobot.size(); ++i) {
		command[index++] = pathOnRobot.at(i).toLatin1();
	}

	command[index++] = 0x00;  // Zero termination of string above
	command[index++] = 0x60;  // GV0(0), Return Image Size at Global Var offset 0. Offset encoded as single byte
	command[index++] = 0x64;  // GV0(4), Return Address of image at Global Var offset 4. Offset encoded as single byte
	command[index++] = 0x03;  // opPROGRAM_START Opcode
	command[index++] = 0x01;
	command[index++] = 0x60;  // GV0(0), Size of image at Global Var offset 0.
	command[index++] = 0x64;  // GV0(4), Address of image at Global Var offset 4
	command[index++] = 0x00;  // LC0(0), Debug mode (0 = normal) encoded as single byte constant

	auto res = send1(command);
	if (!res) {
		QLOG_ERROR() << "Program run failed";
	}

	return res;
}

void Ev3RobotCommunicationThread::stopProgram()
{
	QByteArray command = Ev3DirectCommand::formCommand(9, ++mMessageCounter, 0, 0
			, enums::commandType::CommandTypeEnum::DIRECT_COMMAND_NO_REPLY);
	command[7] = 0x02;  // opPROGRAM_STOP Opcode
	command[8] = 0x01;  // LC0(USER_SLOT), User slot = 1 (program slot)
	if (!send1(command)) {
		QLOG_ERROR() << "EV3USB" << "Failed to stop program";
	}
}
