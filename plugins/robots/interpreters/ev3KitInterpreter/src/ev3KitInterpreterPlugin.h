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

#include <kitBase/kitPluginInterface.h>
#include <ev3Kit/blocks/ev3BlocksFactory.h>

#include "ev3AdditionalPreferences.h"
#include "robotModel/real/realRobotModel.h"


namespace ev3 {

class Ev3KitInterpreterPlugin : public QObject, public kitBase::KitPluginInterface
{
	Q_OBJECT
	Q_INTERFACES(kitBase::KitPluginInterface)
	Q_PLUGIN_METADATA(IID "ev3.Ev3KitInterpreterPlugin")

public:
	Ev3KitInterpreterPlugin();

	QString kitId() const override;

	QString friendlyKitName() const override;

	QList<kitBase::robotModel::RobotModelInterface *> robotModels() override;

	kitBase::blocksBase::BlocksFactoryInterface *blocksFactoryFor(
			const kitBase::robotModel::RobotModelInterface *model) override;

	// Transfers ownership.
	QList<kitBase::AdditionalPreferences *> settingsWidgets() override;

	QList<qReal::ActionInfo> customActions() override;

	QList<qReal::HotKeyActionInfo> hotKeyActions() override;

	QIcon iconForFastSelector(const kitBase::robotModel::RobotModelInterface &robotModel) const override;

private:
	robotModel::real::RealRobotModel mRealRobotModel;
	Ev3AdditionalPreferences *mAdditionalPreferences = nullptr;  // Transfers ownership
	blocks::Ev3BlocksFactory *mBlocksFactory = nullptr;  // Transfers ownership

};

}
