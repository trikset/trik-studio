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

#include <QtCore/QString>
#include <QtCore/QVector>
#include <QtGui/QFont>

#include "qrgui/brandManager/brandManagerDeclSpec.h"
#include "qrgui/brandManager/fonts.h"

namespace qReal {

/// Holds the per-role font settings editing state between UI actions and the
/// moment they are persisted. The UI only renders the state and forwards user
/// choices; this class owns pending font descriptions and writes them through
/// the Fonts API.
class QRGUI_BRAND_MANAGER_EXPORT FontSettingsManager
{
	Q_DISABLE_COPY(FontSettingsManager)
public:
	explicit FontSettingsManager(const Fonts *fonts);

	/// Roles shown in the settings UI, in display order.
	static QVector<FontRole> roles();

	/// Reloads the state from the current settings.
	void reload();

	/// Returns the font that should be shown for the role, taking pending
	/// edits into account.
	QFont displayedFont(FontRole role) const;

	/// Returns true when the role has a custom font (pending or saved).
	bool isCustom(FontRole role) const;

	/// Stages the given font for the role.
	void setFont(FontRole role, const QFont &font);

	/// Stages the default font for the role.
	void resetFont(FontRole role);

	/// Returns true when the role has unsaved changes.
	bool isChanged(FontRole role) const;

	/// Returns true when any role has unsaved changes.
	bool hasChanges() const;

	/// Writes the staged state through the Fonts API.
	void save();

private:
	struct RoleState {
		bool custom = false;
		bool initialCustom = false;
		QString pendingDescription;
		QString initialDescription;

		bool isChanged() const;
	};

	static int indexOf(FontRole role);
	RoleState &state(FontRole role);
	const RoleState &state(FontRole role) const;

	const Fonts *mFonts;
	QVector<RoleState> mStates;
};

}
