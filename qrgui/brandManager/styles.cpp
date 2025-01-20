/* Copyright 2007-2015 QReal Research Group
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *	 http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

#include "styles.h"

#include <QApplication>
#include <QSettings>
#include <QPalette>
#include <QColor>

using namespace qReal;

QPalette Styles::loadPalette(QString pathToPalette) const {
	QSettings settings(pathToPalette, QSettings::IniFormat);
	QPalette palette;

	const QMap<QString, QPalette::ColorRole> colorRoles = {
		{"Window", QPalette::Window},
		{"WindowText", QPalette::WindowText},
		{"Base", QPalette::Base},
		{"AlternateBase", QPalette::AlternateBase},
		{"ToolTipBase", QPalette::ToolTipBase},
		{"ToolTipText", QPalette::ToolTipText},
		{"Text", QPalette::Text},
		{"Dark", QPalette::Dark},
		{"Shadow", QPalette::Shadow},
		{"Button", QPalette::Button},
		{"ButtonText", QPalette::ButtonText},
		{"BrightText", QPalette::BrightText},
		{"Link", QPalette::Link},
		{"Highlight", QPalette::Highlight},
		{"HighlightedText", QPalette::HighlightedText}
	};

	for (const auto &group : {"PaletteActive", "PaletteDisabled"}) {
		QPalette::ColorGroup colorGroup = (QString(group) == "PaletteDisabled") ? QPalette::Disabled : QPalette::Active;

		for (auto it = colorRoles.begin(); it != colorRoles.end(); ++it) {
			QStringList rgb = settings.value(QString(group) + "/" + it.key()).toStringList();
			if (!rgb.isEmpty()) {
				QColor color(rgb[0].toInt(), rgb[1].toInt(), rgb[2].toInt());
				palette.setColor(colorGroup, it.value(), color);
			}
		}
	}

	return palette;
}
