/* Copyright 2025 CyberTech Labs Ltd.
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

#include "dirPicker.h"
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStyle>

#include <qrkernel/settingsManager.h>
#include <qrutils/widgets/qRealFileDialog.h>

using namespace qReal::ui;


DirPicker::DirPicker(QWidget *parent)
	: QWidget(parent)
	, mLabel(new QLabel(this))
	, mPathEditor(new QLineEdit(this))
{
	auto *button = new QPushButton(style()->standardIcon(QStyle::SP_DirIcon), tr("Browse..."), this);
	auto *layout = new QHBoxLayout(this);
	layout->addWidget(mLabel);
	layout->addWidget(mPathEditor);
	layout->addWidget(button);
	connect(button, &QPushButton::clicked, this, &DirPicker::pick);
}

void DirPicker::configure(const QString &settingsKey,
			  const QString &title,
			  const QString &dialogId,
			  const QString &dialogTittle)
{
	mDialogId = dialogId;
	mDialogTittle = dialogTittle;
	mSettingsKey = settingsKey;
	mLabel->setText(title);
}

bool DirPicker::isSavedDirExist()
{
	return QDir(SettingsManager::value(mSettingsKey).toString()).exists();
}

void DirPicker::save() const
{
	if (!mPathEditor->text().isEmpty() && !mSettingsKey.isEmpty()) {
		SettingsManager::setValue(mSettingsKey, mPathEditor->text());
	}
}

void DirPicker::restore()
{
	if (!mSettingsKey.isEmpty()) {
		mPathEditor->setText(SettingsManager::value(mSettingsKey).toString());
	}
}

void DirPicker::pick()
{
	const auto dirPath = utils::QRealFileDialog::getExistingDirectory(mDialogId, this
			, mDialogTittle).replace("\\", "/");
	SettingsManager::setValue(mSettingsKey, dirPath);
	mPathEditor->setText(dirPath);
}
