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

#pragma once

#include <QtGui/QColor>

#include <stm32Kit/robotModel/parts/stm32Led.h>
#include <twoDModel/engine/twoDModelEngineInterface.h>

#include "stm32KitInterpreterCommon/declSpec.h"

namespace stm32 {
namespace robotModel {
namespace twoD {
namespace parts {

class ROBOTS_STM32_KIT_INTERPRETER_COMMON_EXPORT TwoDLed : public robotModel::parts::Stm32Led
{
	Q_OBJECT
	Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)

public:
	TwoDLed(const kitBase::robotModel::DeviceInfo &info
			, const kitBase::robotModel::PortInfo &port
			, twoDModel::engine::TwoDModelEngineInterface &engine);

	/// Returns the current color of led emulator in 2D model.
	QColor color() const;

	/// Sets the \a color of led emulator in 2D model.
	void setColor(const QColor &color);

	/// Sets the \a color of led emulator in 2D model.
	/// If "off" passed then led becomes gray.
	void setColor(const QString &color) override;

signals:
	/// Emitted when led color has changed.
	/// @warning This signal will not be emitted on led color chage right before or right after the interpretation.
	/// It notifies only about led`s color modification by led block.
	void colorChanged(const QColor &color);

private:
	twoDModel::engine::TwoDModelEngineInterface &mEngine;
};

}
}
}
}
