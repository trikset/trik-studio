/* Copyright 2026 CyberTech Labs Ltd.
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

#include <QtWidgets/QWidget>
#include <qrutils/utilsDeclSpec.h>

namespace qReal {
namespace ui {

class QRUTILS_EXPORT ColorDialog : public QWidget
{
	Q_OBJECT
public:
	explicit ColorDialog(QWidget *parent = nullptr);

	void configure(const QString &settingsKey);

	/// Save the received options from the QColorDialog.
	void save();

	void restore();

	void setColor(const QColor &color);
private Q_SLOTS:
	void chooseColor();

private:
	QPixmap getColorPixMap() const;
	QColor mSavedColor;
	QString mSettingsKey;
};

}
}
