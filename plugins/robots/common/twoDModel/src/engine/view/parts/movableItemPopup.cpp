/* Copyright 2021 CyberTech Labs Ltd.
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

#include "movableItemPopup.h"

#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QCheckBox>

#include <qrkernel/settingsManager.h>
#include <qrkernel/platformInfo.h>
#include <qrutils/widgets/qRealFileDialog.h>
#include <qrutils/graphicsUtils/abstractScene.h>
#include <qrutils/widgets/qRealMessageBox.h>

#include <src/engine/items/cubeItem.h>

using namespace twoDModel::view;

MovableItemPopup::MovableItemPopup(graphicsUtils::AbstractScene &scene, QWidget *parent)
	: ItemPopup(scene, parent)
{
	initWidget();
}

bool MovableItemPopup::suits(QGraphicsItem *item)
{
	return dynamic_cast<items::MovableItem *>(item) != nullptr;
}

void MovableItemPopup::initWidget()
{
	QGridLayout * const layout = new QGridLayout(this);
	layout->addWidget(initImagePicker(), 0, 0);
	layout->addWidget(initRestoreButton(), 0, 1);

	updateDueToLayout();
}

QWidget *MovableItemPopup::initRestoreButton()
{
	mRestoreButton = initButton(":/icons/2d_restore.png", tr("Restore default image"));
	connect(mRestoreButton, &QAbstractButton::clicked, this, [=]() {
		for (auto item : mCurrentItems) {
			dynamic_cast<items::MovableItem *>(item)->resetImage();
		}
		emit imageSettingsChanged();
	});
	return mRestoreButton;
}

QAbstractButton *MovableItemPopup::initButton(const QString &icon, const QString &toolTip)
{
	QPushButton * const result = new QPushButton(QIcon(icon), QString(), this);
	result->setToolTip(toolTip);
	result->setFlat(true);
	result->setFixedSize(24, 24);
	return result;
}

QWidget *MovableItemPopup::initImagePicker()
{
	mImagePicker = initButton(":/icons/2d_training.svg", "Change cube image");

	connect(mImagePicker, &QPushButton::clicked, this, [=]() {
		const QString loadFileName = utils::QRealFileDialog::getOpenFileName("2DSelectMovableImage"
				, mScene.views().first()
				, tr("Select image")
				, qReal::PlatformInfo::invariantSettingsPath("pathToImages") + "/.."
				, tr("Graphics (*.*)"));
		if (loadFileName.isEmpty()) {
			return;
		}

		QSharedPointer<model::Image> img(new model::Image(loadFileName, true));
		for (auto item : mCurrentItems) {
			dynamic_cast<items::MovableItem *>(item)->resetImage(img);
		}
		emit imageSettingsChanged();
	});

	return mImagePicker;
}
