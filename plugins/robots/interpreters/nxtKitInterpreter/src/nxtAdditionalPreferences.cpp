/* Copyright 2014-2016 QReal Research Group
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

#include "nxtAdditionalPreferences.h"
#include "ui_nxtAdditionalPreferences.h"
#include <qrkernel/settingsManager.h>
#include <utils/widgets/comPortPicker.h>
#include "QsLog.h"
#include <QOperatingSystemVersion>
#include <qrkernel/platformInfo.h>

using namespace nxt;
using namespace qReal;

NxtAdditionalPreferences::NxtAdditionalPreferences(const QString &realRobotName, QWidget *parent)
	: AdditionalPreferences(parent)
	, mUi(new Ui::NxtAdditionalPreferences)
	, mBluetoothRobotName(realRobotName)
{
	mUi->setupUi(this);
	mUi->robotImagePicker->configure("nxtRobot2DImage", tr("2D robot image:"));
	if (PlatformInfo::osType()  == "linux") {
		mUi->compilerPicker->configure("pathToArmNoneEabi", tr("Path to arm-none-eabi:"));
		setTextOnGeneratorLabel();
	}
	else {
		mUi->generatorSettingsGroupBox->setVisible(false);
	}
	connect(mUi->manualComPortCheckbox, &QCheckBox::toggled
			, this, &NxtAdditionalPreferences::manualComPortCheckboxChecked);
}

NxtAdditionalPreferences::~NxtAdditionalPreferences()
{
	delete mUi;
}

void NxtAdditionalPreferences::setColorOnGeneratorLabel(QColor color){
	QPalette palette = mUi->generatorLabel->palette();
	palette.setColor(mUi->generatorLabel->foregroundRole(), color);
	mUi->generatorLabel->setPalette(palette);
}

void NxtAdditionalPreferences::setTextOnGeneratorLabel(){
	if (!mUi->compilerPicker->isSavedDirExist()){
		mUi->generatorLabel->setText(tr("WARNING: Current directory doesn't exist. \nOpen "
										"<a href=\"https://help.trikset.com/nxt/run-upload-programs\">link</a>"
										" for instructions"));
		mUi->generatorLabel->setTextFormat(Qt::RichText);
		mUi->generatorLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
		mUi->generatorLabel->setOpenExternalLinks(true);
		setColorOnGeneratorLabel(QColor("red"));
	}
	else {
	mUi->generatorLabel->setText("Current directory exist.");
	setColorOnGeneratorLabel(QColor("black"));
	}
}

void NxtAdditionalPreferences::save()
{
	SettingsManager::setValue("NxtBluetoothPortName", selectedPortName());
	SettingsManager::setValue("NxtManualComPortCheckboxChecked", mUi->manualComPortCheckbox->isChecked());
	mUi->robotImagePicker->save();
	mUi->compilerPicker->save();
	setTextOnGeneratorLabel();
	emit settingsChanged();
}

void NxtAdditionalPreferences::restoreSettings()
{
	ui::ComPortPicker::populate(*mUi->comPortComboBox, "NxtBluetoothPortName");
	mUi->robotImagePicker->restore();
	mUi->compilerPicker->restore();
	setTextOnGeneratorLabel();

	if (mUi->comPortComboBox->count() == 0) {
		mUi->comPortComboBox->hide();
		mUi->comPortLabel->hide();
		mUi->manualComPortCheckbox->hide();
		mUi->noComPortsFoundLabel->show();
		mUi->directInputComPortLabel->show();
		mUi->directInputComPortLineEdit->show();
		mUi->directInputComPortLineEdit->setText(SettingsManager::value("NxtBluetoothPortName").toString());
	} else {
		mUi->comPortComboBox->show();
		mUi->comPortLabel->show();
		mUi->manualComPortCheckbox->show();
		mUi->directInputComPortLabel->hide();
		mUi->directInputComPortLineEdit->hide();
		mUi->noComPortsFoundLabel->hide();
		mUi->manualComPortCheckbox->setChecked(false);
		mUi->manualComPortCheckbox->setChecked(SettingsManager::value("NxtManualComPortCheckboxChecked").toBool());
	}
}

void NxtAdditionalPreferences::onRobotModelChanged(kitBase::robotModel::RobotModelInterface * const robotModel)
{
	QLOG_DEBUG() << robotModel->name();
	mUi->bluetoothSettingsGroupBox->setVisible(robotModel->name() == mBluetoothRobotName);
	if (PlatformInfo::osType()  == "linux") {
		mUi->generatorSettingsGroupBox->setVisible(robotModel->name() == "NxtOsekCGeneratorRobotModel");
	}
}

void NxtAdditionalPreferences::manualComPortCheckboxChecked(bool state)
{
	const QString defaultPortName = SettingsManager::value("NxtBluetoothPortName").toString();

	if (state) {
		mUi->comPortComboBox->hide();
		mUi->comPortLabel->hide();
		mUi->directInputComPortLabel->show();
		mUi->directInputComPortLineEdit->show();
		mUi->directInputComPortLineEdit->setText(defaultPortName);
	} else {
		mUi->comPortComboBox->show();
		mUi->comPortLabel->show();
		mUi->directInputComPortLabel->hide();
		mUi->directInputComPortLineEdit->hide();
		mUi->noComPortsFoundLabel->hide();
	}
}

QString NxtAdditionalPreferences::selectedPortName() const
{
	return mUi->comPortComboBox->isVisible()
			? mUi->comPortComboBox->currentText()
			: mUi->directInputComPortLineEdit->text();
}
