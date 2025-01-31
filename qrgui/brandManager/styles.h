/* Copyright 2007-2015 QReal Research Group
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

#include <QtWidgets/QApplication>
#include <QPalette>

#include <qrutils/inFile.h>
#include "fonts.h"

namespace qReal {

/// Manages all json stylesheets in system
class Styles
{
	Q_DISABLE_COPY(Styles)
public:
	explicit Styles(const Fonts &fonts)
		: mFonts(fonts)
	{
	}

	
	virtual ~Styles() = default;

	/// Returns json stylesheet for start tab background
	virtual QString startTabBackgroundStyle() const
	{
		return loadSystemPallete(utils::InFile::readAll(startTabBackgroundStylePath()));
	}

	/// Returns json stylesheet for start tab substrate background
	virtual QString startTabSubstrateBackgroundStyle() const
	{
		return loadSystemPallete(utils::InFile::readAll(startTabSubstrateBackgroundStylePath()));
	}

	/// Returns json stylesheet for start tab header background
	virtual QString startTabHeaderBackgroundStyle() const
	{
		return loadSystemPallete(utils::InFile::readAll(startTabHeaderBackgroundStylePath()));
	}

	/// Returns json stylesheet for recent projects section background on start tab
	virtual QString startTabRecentProjectsBackgroundStyle() const
	{
		return loadSystemPallete(utils::InFile::readAll(startTabRecentProjectsBackgroundStylePath()));
	}

	/// Returns json stylesheet for projects management section background on start tab
	virtual QString startTabProjectsManagementBackgroundStyle() const
	{
		return loadSystemPallete(utils::InFile::readAll(startTabProjectsManagementBackgroundStylePath()));
	}

	/// Returns json stylesheet for command buttons on start tab
	virtual QString startTabButtonStyle() const
	{
		return loadSystemPallete(utils::InFile::readAll(startTabButtonStylePath()));
	}

	/// Returns json stylesheet for styled text on start tab  of level 1 heading
	virtual QString startTabLabelLevel1Style() const
	{
		return loadSystemPallete(utils::InFile::readAll(startTabLabelLevel1StylePath()));
	}

	/// Returns json stylesheet for styled text on start tab of level 2 heading
	virtual QString startTabLabelLevel2Style() const
	{
		return loadSystemPallete(utils::InFile::readAll(startTabLabelLevel2StylePath()));
	}

	virtual QString splashscreenStyle() const
	{
		return loadSystemPallete(utils::InFile::readAll(splashscreenStylePath()));
	}

	QPalette loadPalette(const QString& pathToPalette) const;

protected:

	/// 
	QString loadSystemPallete(QString style) const {
		auto systemPalette(QApplication::palette());
		return style
		.replace("@@Window@@", systemPalette.color(QPalette::Window).name())
		.replace("@@Base@@", systemPalette.color(QPalette::Base).name())
		.replace("@@Font@@", mFonts.commandButtonsFont())
		.replace("@@Light@@", systemPalette.color(QPalette::Light).name())
		.replace("@@Highlight@@", systemPalette.color(QPalette::Highlight).name())
		.replace("@@Text@@", systemPalette.color(QPalette::Text).name());
	}

	/// Returns a path to a file with json stylesheet for start tab background
	virtual QString startTabBackgroundStylePath() const
	{
		return processUrl(":/styles/startTab/background.css");
	}

	/// Returns a path to a file with json stylesheet for start tab substrate background
	virtual QString startTabSubstrateBackgroundStylePath() const
	{
		return processUrl(":/styles/startTab/substrate.css");
	}

	/// Returns a path to a file with json stylesheet for start tab header background
	virtual QString startTabHeaderBackgroundStylePath() const
	{
		return processUrl(":/styles/startTab/header.css");
	}

	/// Returns a path to a file with json stylesheet for recent projects section background on start tab
	virtual QString startTabRecentProjectsBackgroundStylePath() const
	{
		return processUrl(":/styles/startTab/recentProjectsBackground.css");
	}

	/// Returns a path to a file with json stylesheet for projects management section background on start tab
	virtual QString startTabProjectsManagementBackgroundStylePath() const
	{
		return processUrl(":/styles/startTab/projectsManagementBackground.css");
	}

	/// Returns a path to a file with json stylesheet for command buttons on start tab
	virtual QString startTabButtonStylePath() const
	{
		return processUrl(":/styles/startTab/button.css");
	}

	/// Returns a path to a file with json stylesheet for styled text on start tab  of level 1 heading
	virtual QString startTabLabelLevel1StylePath() const
	{
		return processUrl(":/styles/startTab/labelLevel1.css");
	}

	/// Returns a path to a file with json stylesheet for styled text on start tab  of level 2 heading
	virtual QString startTabLabelLevel2StylePath() const
	{
		return processUrl(":/styles/startTab/labelLevel2.css");
	}

	virtual QString splashscreenStylePath() const
	{
		return processUrl(":/styles/splashscreen/splashscreen.css");
	}

	/// Returns either given url without modifications or transforms it into absolute disk location
	/// for more convenient styles debugging (modifications do not need rebuilds then)
	QString processUrl(const QString &resourceUrl) const
	{
		// TODO: uncomment one of the next scenarious

		// Scenario one: use it for releases
		return resourceUrl;

		// Scenario two: use it for debugging
		// QString choppedString = resourceUrl;
		// choppedString.remove(0, 1);
		// return PlatformInfo::applicationDirPath() + "/../../qrgui/brandManager" + choppedString;
	}

	const Fonts &mFonts;
};

}

// Implemented in .h file for correct linkage
