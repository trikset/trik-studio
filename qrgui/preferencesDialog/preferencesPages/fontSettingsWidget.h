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

#include <QtCore/QVector>
#include <QtWidgets/QWidget>

#include <qrgui/brandManager/fontSettingsManager.h>

class QFrame;
class QGridLayout;
class QLabel;
class QPushButton;
class QToolButton;

/// @file
///
/// Font settings editor widget.
///
/// The widget is a single collapsible "Fonts" section. Every font role is a
/// row with the role title, the current font description and the two action
/// buttons. The section is built from ordinary widgets and layouts, so Qt
/// keeps its geometry correct without any view, item model or delegate.
///
/// The widget only renders the state. Pending edits and persistence are owned
/// by FontSettingsManager, so the UI layer stays free of font settings logic.

/// Edits fonts of all application roles as a collapsible section.
class FontSettingsWidget : public QWidget
{
	Q_OBJECT

public:
	/// Creates the widget and loads the initial state from settings.
	explicit FontSettingsWidget(QWidget *parent = nullptr);

	/// Reloads the state from settings, discarding pending changes.
	void reload();

	/// Returns true when at least one role has unsaved changes.
	bool hasChanges() const;

	/// Writes the staged changes through FontSettingsManager.
	void save();

protected:
	/// Retranslates the widget on language change.
	void changeEvent(QEvent *e) override;

private:
	/// Widgets of one font role row.
	struct RoleRow {
		qReal::FontRole role = qReal::FontRole::SceneLabels;
		QLabel *title = nullptr;
		QLabel *description = nullptr;
		QPushButton *chooseButton = nullptr;
		QPushButton *resetButton = nullptr;
	};

	/// Builds the collapsible section header and its content container.
	void setupUi();

	/// Creates one row with action buttons for every supported font role.
	void setupRoleRows();

	/// Opens the font dialog and stages the selected font for the row.
	void chooseFont(int row);

	/// Stages the default font for the row.
	void resetFont(int row);

	/// Updates the font description of one role row.
	void updateRow(int row);

	/// Updates the font descriptions of all role rows.
	void updateAllRows();

	/// Retranslates all user-visible strings.
	void retranslate();

	/// Returns the resolved font currently displayed for the role.
	QFont displayedFont(qReal::FontRole role) const;

	/// Returns a human readable description of the font.
	QString fontDescription(const QFont &font) const;

	/// Returns the display name of the role.
	QString roleTitle(qReal::FontRole role) const;

	/// Pending font settings state.
	qReal::FontSettingsManager mFontSettings;

	/// The header button that expands or collapses the section.
	QToolButton *mHeader = nullptr;

	/// The container with the role rows.
	QFrame *mContent = nullptr;

	/// The layout that holds the role rows.
	QGridLayout *mRolesLayout = nullptr;

	/// Widgets of the role rows, in FontSettingsManager::roles() order.
	QVector<RoleRow> mRows;
};
