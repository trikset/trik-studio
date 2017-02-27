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

#include <QtCore/QScopedPointer>

#include <kitBase/kitPluginInterface.h>
#include <twoDModel/robotModel/twoDRobotModel.h>
#include <twoDModel/engine/twoDModelControlInterface.h>

#include <stm32Kit/blocks/stm32BlocksFactoryBase.h>
#include <stm32Kit/robotModel/stm32RobotModelBase.h>

#include "robotModel/twoD/stm32TwoDRobotModel.h"
#include "stm32AdditionalPreferences.h"

#include "declSpec.h"

namespace stm32 {

class ROBOTS_STM32_KIT_INTERPRETER_COMMON_EXPORT Stm32KitInterpreterPluginBase
		: public QObject, public kitBase::KitPluginInterface
{
	Q_OBJECT
	Q_INTERFACES(kitBase::KitPluginInterface)

public:
	Stm32KitInterpreterPluginBase();
	~Stm32KitInterpreterPluginBase() override;

	void init(const kitBase::KitPluginConfigurator &configurer) override;

	QList<kitBase::robotModel::RobotModelInterface *> robotModels() override;

	kitBase::robotModel::RobotModelInterface *defaultRobotModel() override;

	kitBase::blocksBase::BlocksFactoryInterface *blocksFactoryFor(
			const kitBase::robotModel::RobotModelInterface *model) override;

	QList<kitBase::AdditionalPreferences *> settingsWidgets() override;

	QWidget *quickPreferencesFor(const kitBase::robotModel::RobotModelInterface &model) override;

	QString defaultSettingsFile() const override;

	QIcon iconForFastSelector(const kitBase::robotModel::RobotModelInterface &robotModel) const override;

	kitBase::DevicesConfigurationProvider * devicesConfigurationProvider() override;

	QList<qReal::ActionInfo> customActions() override;

	QList<qReal::HotKeyActionInfo> hotKeyActions() override;

private slots:
	QWidget *produceIpAddressConfigurer();  // Transfers ownership

protected:
	/// Takes ownership over all supplied pointers.
	void initKitInterpreterPluginBase(
			robotModel::Stm32RobotModelBase * const realRobotModel
			, robotModel::twoD::Stm32TwoDRobotModel * const twoDRobotModel
			, blocks::Stm32BlocksFactoryBase * const blocksFactory
			);

private:
	QScopedPointer<twoDModel::TwoDModelControlInterface> mTwoDModel;
	QScopedPointer<robotModel::Stm32RobotModelBase> mRealRobotModel;
	QScopedPointer<robotModel::twoD::Stm32TwoDRobotModel> mTwoDRobotModel;

	/// @todo Use shared pointers instead of this sh~.
	/// Ownership depends on mOwnsBlocksFactory flag.
	blocks::Stm32BlocksFactoryBase *mBlocksFactory = nullptr;
	bool mOwnsBlocksFactory = true;

	/// Ownership depends on mOwnsAdditionalPreferences flag.
	Stm32AdditionalPreferences *mAdditionalPreferences = nullptr;
	bool mOwnsAdditionalPreferences = true;

	kitBase::InterpreterControlInterface *mInterpreterControl;  // Does not have ownership.
	QString mCurrentlySelectedModelName;
};

}
