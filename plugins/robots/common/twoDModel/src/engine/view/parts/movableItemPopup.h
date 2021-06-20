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

#pragma once

#include <qrutils/graphicsUtils/itemPopup.h>

class QAbstractButton;
class QSpinBox;

namespace twoDModel {
namespace items {
class CubeItem;
}
namespace view {

/// A popup for MovableItem on 2D model scene.
/// Contains image`s path picker and button to reset image.
class MovableItemPopup : public graphicsUtils::ItemPopup
{
	Q_OBJECT

public:
	explicit MovableItemPopup(graphicsUtils::AbstractScene &scene, QWidget *parent = nullptr);

signals:
	/// Emitted when user changed cube image settings.
	void imageSettingsChanged();

private:
	bool suits(QGraphicsItem *item) override;

	void initWidget();
	QAbstractButton *initButton(const QString &icon, const QString &toolTip);
	QWidget *initRestoreButton();
	QWidget *initImagePicker();

	QAbstractButton *mRestoreButton {};  // Takes ownership
	QAbstractButton *mImagePicker{};  // Takes ownership
};

}
}
