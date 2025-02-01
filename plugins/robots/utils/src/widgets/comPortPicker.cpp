/* Copyright 2015 CyberTech Labs Ltd.
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

#include <QtSerialPort/QSerialPortInfo>
#include "utils/widgets/comPortPicker.h"

#include <qrkernel/settingsManager.h>
#include <qrkernel/settingsListener.h>

using namespace qReal::ui;

ComPortPicker::ComPortPicker(const QString &key, QObject *parent)
	: QComboBox(nullptr)
	, mSettingsKey(key)
{
	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	setEditable(true);
	populate(*this, mSettingsKey);
	SettingsListener::listen(mSettingsKey, [=](const QString &port) { setCurrentText(port); }, parent);
	connect(this, &QComboBox::currentTextChanged, this, &ComPortPicker::onPortNameChanged);
}

void ComPortPicker::populate(QComboBox &box, const QString &settingsKey)
{
	auto ports = QSerialPortInfo::availablePorts();
	const QString defaultPortName = SettingsManager::value(settingsKey).toString();
	box.clear();

	for (auto &&info : ports) {
		const QRegExp portNameRegexp("COM\\d+", Qt::CaseInsensitive);
		if (portNameRegexp.indexIn(info.portName()) != -1) {
			const QString portName = portNameRegexp.cap();
			box.addItem(portName);
		}
	}

	const int defaultIndex = box.findText(defaultPortName);
	if (defaultIndex != -1) {
		box.setCurrentIndex(defaultIndex);
	} else if (box.isEditable()) {
		box.setCurrentText(defaultPortName);
	}
}

void ComPortPicker::onPortNameChanged(const QString &newPort)
{
	SettingsManager::setValue(mSettingsKey, newPort);
}
