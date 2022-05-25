/* Copyright 2014-2018 CyberTech Labs Ltd.
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

#include "trikKitInterpreterCommon/trikAdditionalPreferences.h"
#include "ui_trikAdditionalPreferences.h"

#include <QtWidgets/QStyle>

#include <QMessageBox>
#include <qrkernel/settingsManager.h>
#include <qrutils/widgets/qRealFileDialog.h>

using namespace trik;
using namespace qReal;

TrikAdditionalPreferences::TrikAdditionalPreferences(const QStringList &realRobotNames, QWidget *parent)
	: AdditionalPreferences(parent)
	, mUi(new Ui::TrikAdditionalPreferences)
	, mRealRobotNames(realRobotNames)
{
	mUi->setupUi(this);
	mUi->robotImagePicker->configure("trikRobot2DImage", tr("2D robot image:"));
	mUi->browseImagesPathButton->setIcon(style()->standardIcon(QStyle::SP_DirIcon));
	mUi->packImagesPushButton->setIcon(style()->standardIcon(QStyle::SP_DialogSaveButton));

	mUi->simulatedCameraFrame->setVisible(not mUi->realCameraCheckBox->isChecked());
	mUi->realCameraFrame->setVisible(mUi->realCameraCheckBox->isChecked());

	connect(mUi->realCameraCheckBox, &QCheckBox::clicked, this, [this](bool checked) {
		mUi->simulatedCameraFrame->setVisible(not checked);
		mUi->realCameraFrame->setVisible(checked);
	});

	connect(mUi->imagesFromProjectCheckBox, &QCheckBox::clicked, this, [this](bool checked) {
		mUi->imagesFromDiskFrame->setEnabled(not checked);
	});

	connect(mUi->browseImagesPathButton, &QPushButton::clicked, this, [this]() {
		const QString directoryName = utils::QRealFileDialog::getExistingDirectory("TrikSimulatedCameraImagesPath"
					, this, tr("Select Directory")).replace("\\", "/");
		mUi->imagesPathlineEdit->setText(directoryName);
		SettingsManager::setValue("TrikSimulatedCameraImagesPath", directoryName);
	});

	connect(mUi->packImagesPushButton, &QPushButton::clicked
			, this, &TrikAdditionalPreferences::packImagesToProjectClicked);

	connect(mUi->mailboxCheckBox, &QCheckBox::toggled, mUi->mailboxHullNumberLabel, &QLabel::setVisible);
	connect(mUi->mailboxCheckBox, &QCheckBox::toggled, mUi->mailboxHullNumber, &QLineEdit::setVisible);
}

TrikAdditionalPreferences::~TrikAdditionalPreferences()
{
	delete mUi;
}

void TrikAdditionalPreferences::save()
{
	SettingsManager::setValue("TrikTcpServer", mUi->tcpServerLineEdit->currentText());
	SettingsManager::setValue("TrikWebCameraReal", mUi->realCameraCheckBox->isChecked());
	SettingsManager::setValue("TrikSimulatedCameraImagesPath", mUi->imagesPathlineEdit->text());
	SettingsManager::setValue("TrikSimulatedCameraImagesFromProject", mUi->imagesFromProjectCheckBox->isChecked());
	SettingsManager::setValue("TrikWebCameraRealName", mUi->cameraNameLineEdit->text());
	SettingsManager::setValue("TRIK2DMailbox", mUi->mailboxCheckBox->isChecked());
	SettingsManager::setValue("TRIK2DHullNumber", mUi->mailboxHullNumber->text());
	SettingsManager::setValue("UnityTcpServer", mUi->unityTcpServerLineEdit->currentText());
	SettingsManager::setValue("UnitySendData", mUi->unitySendDataCheckBox->isChecked());
	mUi->robotImagePicker->save();

	if (mailboxSavedState != mUi->mailboxCheckBox->isChecked()) {
		QMessageBox::information(this, tr("Information"), tr("You should restart the program to apply changes"));
		mailboxSavedState = mUi->mailboxCheckBox->isChecked();
	}
	emit settingsChanged();
}

void TrikAdditionalPreferences::restoreSettings()
{
	const auto &addr = SettingsManager::value("TrikTcpServer").toString();
	if (mUi->tcpServerLineEdit->findText(addr) < 0) {
		mUi->tcpServerLineEdit->insertItem(0, addr);
	}
	mUi->tcpServerLineEdit->setCurrentText(addr);
	mUi->realCameraCheckBox->setChecked(SettingsManager::value("TrikWebCameraReal").toBool());
	mUi->imagesPathlineEdit->setText(SettingsManager::value("TrikSimulatedCameraImagesPath").toString());
	mUi->cameraNameLineEdit->setText(SettingsManager::value("TrikWebCameraRealName").toString());
	mUi->imagesFromProjectCheckBox->setChecked(SettingsManager::value("TrikSimulatedCameraImagesFromProject").toBool());
	mUi->simulatedCameraFrame->setVisible(not mUi->realCameraCheckBox->isChecked());
	mUi->realCameraFrame->setVisible(mUi->realCameraCheckBox->isChecked());
	mUi->mailboxCheckBox->setChecked(SettingsManager::value("TRIK2DMailbox").toBool());
	const auto &unityAddr = SettingsManager::value("UnityTcpServer").toString();
	mUi->unitySendDataCheckBox->setChecked(SettingsManager::value("UnitySendData").toBool());
	mUi->unityTcpServerLineEdit->insertItem(0, unityAddr);
	mUi->unityTcpServerLineEdit->setCurrentText(unityAddr);
	mailboxSavedState = mUi->mailboxCheckBox->isChecked();
	mUi->robotImagePicker->restore();
}

void TrikAdditionalPreferences::onRobotModelChanged(kitBase::robotModel::RobotModelInterface * const robotModel)
{
	const bool isReal = !robotModel->name().contains("TwoD");
	mUi->tcpSettingsGroupBox->setVisible(isReal);
	mUi->multimediaSettingsGroupBox->setVisible(not isReal);
}
