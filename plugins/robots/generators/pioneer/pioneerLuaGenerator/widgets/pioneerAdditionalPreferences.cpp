/* Copyright 2017 QReal Research Group
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

#include "pioneerAdditionalPreferences.h"
#include "ui_pioneerAdditionalPreferences.h"

#include <QtWidgets/QFileDialog>

#include <qrkernel/settingsManager.h>
#include <pioneerKit/constants.h>

using namespace pioneer;
using namespace pioneer::lua;
using namespace qReal;

PioneerAdditionalPreferences::PioneerAdditionalPreferences(QWidget *parent)
	: AdditionalPreferences(parent)
	, mUi(new Ui::PioneerAdditionalPreferences)
{
	mUi->setupUi(this);
	mUi->baseStationModeComboBox->addItems({"usb", "wifi"});

	restoreSettings();
}

PioneerAdditionalPreferences::~PioneerAdditionalPreferences()
{
	delete mUi;
}

void PioneerAdditionalPreferences::save()
{
	SettingsManager::setValue(settings::pioneerBaseStationIP, mUi->baseStationIpComboBox->currentText());
	SettingsManager::setValue(settings::pioneerBaseStationPort, mUi->baseStationPortComboBox->currentText());
	SettingsManager::setValue(settings::pioneerBaseStationMode, mUi->baseStationModeComboBox->currentText());

	emit settingsChanged();
}

void PioneerAdditionalPreferences::updateComboBox(QComboBox *selector, QString settings)
{
	const auto &value = SettingsManager::value(settings).toString();
	if (selector->findText(value) < 0) {
		selector->insertItem(0, value);
	}
	selector->setCurrentText(value);
}
void PioneerAdditionalPreferences::restoreSettings()
{
	updateComboBox(mUi->baseStationIpComboBox, settings::pioneerBaseStationIP);
	updateComboBox(mUi->baseStationPortComboBox, settings::pioneerBaseStationPort);
	updateComboBox(mUi->baseStationModeComboBox, settings::pioneerBaseStationMode);
}

void PioneerAdditionalPreferences::onRobotModelChanged(kitBase::robotModel::RobotModelInterface * const robotModel)
{
	Q_UNUSED(robotModel);
}
