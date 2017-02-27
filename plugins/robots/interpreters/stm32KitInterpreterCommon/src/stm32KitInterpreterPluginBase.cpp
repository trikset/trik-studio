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

#include "stm32KitInterpreterCommon/stm32KitInterpreterPluginBase.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>

#include <twoDModel/engine/twoDModelEngineFacade.h>
#include <qrkernel/settingsManager.h>
#include <qrkernel/settingsListener.h>

using namespace stm32;
using namespace qReal;

const Id robotDiagramType = Id("RobotsMetamodel", "RobotsDiagram", "RobotsDiagramNode");
const Id subprogramDiagramType = Id("RobotsMetamodel", "RobotsDiagram", "SubprogramDiagram");

Stm32KitInterpreterPluginBase::Stm32KitInterpreterPluginBase()
{
}

Stm32KitInterpreterPluginBase::~Stm32KitInterpreterPluginBase()
{
	if (mOwnsAdditionalPreferences) {
		delete mAdditionalPreferences;
	}

	if (mOwnsBlocksFactory) {
		delete mBlocksFactory;
	}
}

void Stm32KitInterpreterPluginBase::initKitInterpreterPluginBase
		(robotModel::Stm32RobotModelBase * const realRobotModel
		, robotModel::twoD::Stm32TwoDRobotModel * const twoDRobotModel
		, blocks::Stm32BlocksFactoryBase * const blocksFactory
		)
{
	mRealRobotModel.reset(realRobotModel);
	mTwoDRobotModel.reset(twoDRobotModel);
	mBlocksFactory = blocksFactory;

	const auto modelEngine = new twoDModel::engine::TwoDModelEngineFacade(*mTwoDRobotModel);

	mTwoDRobotModel->setEngine(modelEngine->engine());
	mTwoDModel.reset(modelEngine);

	mAdditionalPreferences = new Stm32AdditionalPreferences({ mRealRobotModel->name() });
}

void Stm32KitInterpreterPluginBase::init(const kitBase::KitPluginConfigurator &configurer)
{
	connect(&configurer.eventsForKitPlugin()
			, &kitBase::EventsForKitPluginInterface::robotModelChanged
			, [this](const QString &modelName) { mCurrentlySelectedModelName = modelName; });

	qReal::gui::MainWindowInterpretersInterface &interpretersInterface
			= configurer.qRealConfigurator().mainWindowInterpretersInterface();

	mTwoDModel->init(configurer.eventsForKitPlugin()
			, configurer.qRealConfigurator().systemEvents()
			, configurer.qRealConfigurator().logicalModelApi()
			, configurer.qRealConfigurator().controller()
			, interpretersInterface
			, configurer.qRealConfigurator().mainWindowDockInterface()
			, configurer.qRealConfigurator().projectManager()
			, configurer.interpreterControl());

	mRealRobotModel->setErrorReporter(*interpretersInterface.errorReporter());
	mTwoDRobotModel->setErrorReporter(*interpretersInterface.errorReporter());

	connect(mAdditionalPreferences, &Stm32AdditionalPreferences::settingsChanged
			, mRealRobotModel.data(), &robotModel::Stm32RobotModelBase::rereadSettings);

	connect(mAdditionalPreferences, &Stm32AdditionalPreferences::settingsChanged
			, mTwoDRobotModel.data(), &robotModel::twoD::Stm32TwoDRobotModel::rereadSettings);
}

QList<kitBase::robotModel::RobotModelInterface *> Stm32KitInterpreterPluginBase::robotModels()
{
	return {mRealRobotModel.data(), mTwoDRobotModel.data()};
}

kitBase::blocksBase::BlocksFactoryInterface *Stm32KitInterpreterPluginBase::blocksFactoryFor(
		const kitBase::robotModel::RobotModelInterface *model)
{
	Q_UNUSED(model);

	mOwnsBlocksFactory = false;
	return mBlocksFactory;
}

kitBase::robotModel::RobotModelInterface *Stm32KitInterpreterPluginBase::defaultRobotModel()
{
	return mTwoDRobotModel.data();
}

QList<kitBase::AdditionalPreferences *> Stm32KitInterpreterPluginBase::settingsWidgets()
{
	mOwnsAdditionalPreferences = false;
	return {mAdditionalPreferences};
}

QWidget *Stm32KitInterpreterPluginBase::quickPreferencesFor(const kitBase::robotModel::RobotModelInterface &model)
{
	return model.name().toLower().contains("twod")
			? nullptr
			: produceIpAddressConfigurer();
}

QList<qReal::ActionInfo> Stm32KitInterpreterPluginBase::customActions()
{
	return {};
}

QList<HotKeyActionInfo> Stm32KitInterpreterPluginBase::hotKeyActions()
{
	return {};
}

QString Stm32KitInterpreterPluginBase::defaultSettingsFile() const
{
	return ":/stm32DefaultSettings.ini";
}

QIcon Stm32KitInterpreterPluginBase::iconForFastSelector(
		const kitBase::robotModel::RobotModelInterface &robotModel) const
{
	return &robotModel == mRealRobotModel.data()
			? QIcon(":/icons/switch-real-stm32.svg")
			: &robotModel == mTwoDRobotModel.data()
					? QIcon(":/icons/switch-2d.svg")
					: QIcon();
}

kitBase::DevicesConfigurationProvider *Stm32KitInterpreterPluginBase::devicesConfigurationProvider()
{
	return &mTwoDModel->devicesConfigurationProvider();
}

QWidget *Stm32KitInterpreterPluginBase::produceIpAddressConfigurer()
{
	QLineEdit * const quickPreferences = new QLineEdit;
	quickPreferences->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	quickPreferences->setPlaceholderText(tr("Enter robot`s IP-address here..."));
	const auto updateQuickPreferences = [quickPreferences]() {
		const QString ip = qReal::SettingsManager::value("Stm32TcpServer").toString();
		if (quickPreferences->text() != ip) {
			quickPreferences->setText(ip);
		}
	};

	updateQuickPreferences();
	connect(mAdditionalPreferences, &Stm32AdditionalPreferences::settingsChanged, updateQuickPreferences);
	qReal::SettingsListener::listen("Stm32TcpServer", updateQuickPreferences, this);
	connect(quickPreferences, &QLineEdit::textChanged, [](const QString &text) {
		qReal::SettingsManager::setValue("Stm32TcpServer", text);
	});

	connect(this, &QObject::destroyed, [quickPreferences]() { delete quickPreferences; });
	return quickPreferences;
}
