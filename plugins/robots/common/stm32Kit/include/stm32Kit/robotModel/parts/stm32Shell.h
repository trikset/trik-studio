/* Copyright 2013-2016 CyberTech Labs Ltd.
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

#pragma once

#include <kitBase/robotModel/robotParts/shell.h>

namespace stm32 {
namespace robotModel {
namespace parts {

/// Executes shell commands on STM32 controller
class Stm32Shell : public kitBase::robotModel::robotParts::Shell
{
	Q_OBJECT

public:
	/// Constructor, takes device type info and port on which this motor is configured.
	Stm32Shell(const kitBase::robotModel::DeviceInfo &info
			, const kitBase::robotModel::PortInfo &port);
	virtual ~Stm32Shell();

	/// Run current command in the stm32
	virtual void runCommand(const QString &command) = 0;

	/// Evaluates the given code on native runtime language.
	virtual void runCode(const QString &code) = 0;

	/// Force stm32 say the text
	virtual void say(const QString &text) = 0;

	/// Writes the text to a given file
	virtual void writeToFile(const QString &filePath, const QString &text) = 0;

	/// Removes a given file
	virtual void removeFile(const QString &filePath) = 0;

	/// Sends all data from a given file and send it via fileContents() signal.
	virtual void readFile(const QString &filePath) = 0;

	/// Enables video streaming on the robot.
	virtual void initVideoStreaming(int qual, bool grayscale) = 0;
};

}
}
}
