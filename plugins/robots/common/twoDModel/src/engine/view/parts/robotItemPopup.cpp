/* Copyright 2015 QReal Research Group, Dmitry Mordvinov
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

#include "robotItemPopup.h"

#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QCheckBox>

#include <qrkernel/settingsManager.h>
#include <qrkernel/platformInfo.h>
#include <qrutils/widgets/qRealFileDialog.h>
#include <qrutils/graphicsUtils/abstractScene.h>

#include "src/engine/view/scene/robotItem.h"

using namespace twoDModel::view;

RobotItemPopup::RobotItemPopup(graphicsUtils::AbstractScene &scene, QWidget *parent)
	: ItemPopup(scene, parent)
{
	initWidget();
}

RobotItemPopup::~RobotItemPopup()
{
}

bool RobotItemPopup::suits(QGraphicsItem *item)
{
	return dynamic_cast<RobotItem *>(item) != nullptr;
}

bool RobotItemPopup::attachTo(QGraphicsItem *item)
{
	mCurrentItem = dynamic_cast<RobotItem *>(item);
	mSpinBox->setValue(mCurrentItem->pen().width());

	const bool followingEnabled = qReal::SettingsManager::value("2dFollowingRobot").toBool();
	mFollowButton->setChecked(followingEnabled);

	mUseImageButton->setChecked(mCurrentItem->usedCustomImage());
	mImagePicker->setVisible(mCurrentItem->usedCustomImage());
	return true;
}

bool RobotItemPopup::attachTo(const QList<QGraphicsItem *> &items)
{
	Q_UNUSED(items)
	return false;
}

void RobotItemPopup::initWidget()
{
	QGridLayout * const layout = new QGridLayout(this);
	layout->addWidget(initFollowButton(), 0, 0);
	layout->addWidget(initReturnButton(), 0, 1);
	layout->addWidget(initImagePicker(), 1, 1);
	layout->addWidget(initSaveImageButton(), 1, 0, Qt::AlignCenter);
	layout->addWidget(initSpinBox(), 2, 0, 1, 2);

	updateDueToLayout();
}

QWidget *RobotItemPopup::initFollowButton()
{
	mFollowButton = initButton(":/icons/2d_target.png", QString());
	mFollowButton->setCheckable(true);
	connect(mFollowButton, &QAbstractButton::toggled, this, &RobotItemPopup::followingChanged);
	connect(mFollowButton, &QAbstractButton::toggled, this, [=](bool enabled) {
		mFollowButton->setToolTip(tr("Camera folowing robot: %1")
				.arg(enabled ? tr("enabled") : tr("disabled")));
	});
	return mFollowButton;
}

QWidget *RobotItemPopup::initReturnButton()
{
	mReturnButton = initButton(":/icons/2d_robot_back.png", tr("Return robot to the initial position"));
	connect(mReturnButton, &QAbstractButton::clicked, this, &RobotItemPopup::restoreRobotPositionClicked);
	return mReturnButton;
}

QAbstractButton *RobotItemPopup::initButton(const QString &icon, const QString &toolTip)
{
	QPushButton * const result = new QPushButton(QIcon(icon), QString(), this);
	result->setToolTip(toolTip);
	result->setFlat(true);
	result->setFixedSize(24, 24);
	return result;
}

QWidget *RobotItemPopup::initSpinBox()
{
	mSpinBox = new QSpinBox(this);
	mSpinBox->setRange(1, 30);
	mSpinBox->setToolTip(tr("Marker thickness"));
	QPalette spinBoxPalette;
	spinBoxPalette.setColor(QPalette::Window, Qt::transparent);
	spinBoxPalette.setColor(QPalette::Base, Qt::transparent);
	mSpinBox->setPalette(spinBoxPalette);
	connect(mSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, [=](int value) {
		mCurrentItem->setPenWidth(value);
	});

	return mSpinBox;
}

QWidget *RobotItemPopup::initImagePicker()
{
	mImagePicker = initButton(":/icons/2d_training.svg", "Change the robot image");

	connect(mImagePicker, &QPushButton::clicked, this, [=]() {
		const QString loadFileName = utils::QRealFileDialog::getOpenFileName("2DSelectRobotImage", mScene.views().first()
				, tr("Select image")
				, qReal::PlatformInfo::invariantSettingsPath("pathToImages") + "/.."
				, tr("Graphics (*.*)"));
		if (loadFileName.isEmpty()) {
			return;
		}

		mCurrentItem->setCustomImage(loadFileName);
		emit imageSettingsChanged();
	});

	return mImagePicker;
}

QWidget *RobotItemPopup::initSaveImageButton()
{
	mUseImageButton = new QCheckBox(this);
	mUseImageButton->setToolTip(tr("Use custom robot image"));
	mUseImageButton->setFixedSize(25, 25);
	connect(mUseImageButton, &QAbstractButton::toggled, this, [=](bool useImage){
		mImagePicker->setVisible(useImage);
		emit propertyChanged({mCurrentItem->id()}, "customImage", useImage);
	});

	return mUseImageButton;
}
