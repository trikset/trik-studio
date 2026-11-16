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

#include <QtCore/QPair>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtCore/QVector>
#include <QtGui/QFont>

#include "qrgui/brandManager/brandManagerDeclSpec.h"

namespace qReal {

/// @file
///
/// Font resolution model.
///
/// Fonts are resolved per role (see FontRole). Every role is described by a
/// settings group `Fonts/<Role>` with the following optional keys:
///
///   * `Families`    - ordered fallback chain of font families, separated by
///                     commas. QSettings may already parse it into a
///                     QStringList, both forms are accepted.
///   * `UserFamily`  - a single family explicitly selected by the user. When
///                     set, it is prepended to the chain and the chain is kept
///                     as a fallback.
///   * `UserFont`    - serialized QFont attributes without the family, i.e. the
///                     QFont::toString() suffix starting from the point size
///                     (`12,-1,5,75,0,0,0,0,0`). It is concatenated with the
///                     selected family before QFont::fromString() is called.
///   * `DefaultFont` - the same format as `UserFont`, but holds the built-in
///                     baseline attributes. It is only read from the default
///                     settings and is used when `UserFont` is not set.
/// @todo Replace this opaque `QFont::toString()` suffix with readable
///       per-property settings (size, weight, style, ...) and a dedicated
///       parser. The current form is a temporary workaround that keeps the
///       existing behavior without growing the code much.
///
/// Built-in defaults:
///
///   * SceneLabels: Cascadia Mono, Pfennig, 11 pt;
///   * CodeEditor:  Cascadia Mono, DejaVu Sans Mono, 9 pt;
///   * Ui:          Segoe UI, system size.
///
/// The resolution performed by font() is:
///
///   1. explicit family (`UserFamily`, or the legacy `CurrentFont` for
///      SceneLabels) is moved to the front of the chain;
///   2. `UserFont` attributes, when set, are applied to a QFont parsed
///      together with the selected family; otherwise the default attributes
///      are used;
///   3. the `Families` chain from settings is used, or the built-in default
///      chain when the setting is empty;
///   4. if the resulting chain is empty, the system font for the role is used;
///   5. Qt picks the first available family and substitutes its own final
///      fallback if none of the families exist.
///
/// Bundled fonts (Pfennig, DejaVu Sans Mono, Cascadia Mono) are registered as
/// application fonts at startup and are ordinary candidates in the chains.
/// User provided fonts are expected to be installed in the operating system
/// and are picked up by Qt together with the system ones.
///
/// Legacy note: `CustomFont`/`CurrentFont` used to affect SceneLabels only.
/// They are still read for compatibility when the new
/// `Fonts/SceneLabels/UseCustomFont` key is absent. `UseCustomFont` is the new
/// switch for the custom font mode; `CurrentFont` holds a QFont::toString()
/// value, so the chosen size and style are preserved.

/// Logical purposes for which the application asks for a font.
enum class FontRole {
	/// Inline labels on the diagram scene.
	SceneLabels,
	/// Monospace font of the source code editor.
	CodeEditor,
	/// Regular user interface text.
	Ui
};

/// Manages the fonts used by the application.
class QRGUI_BRAND_MANAGER_EXPORT Fonts
{
	Q_DISABLE_COPY(Fonts)
public:
	/// Registers bundled font files as application fonts.
	Fonts();

	virtual ~Fonts() = default;

	/// Returns font for inline labels on scene.
	QFont sceneLabelsFont() const;

	/// Returns monospace font for the source code editor.
	QFont codeEditorFont() const;

	/// Returns regular font for the user interface.
	QFont uiFont() const;

	/// Returns a font resolved for the given role.
	/// See the file-level documentation for the resolution rules.
	QFont font(FontRole role) const;

	/// Returns the built-in font of the role without user overrides.
	QFont defaultFont(FontRole role) const;

	/// Returns true when the role has a custom font configured.
	bool hasUserFont(FontRole role) const;

	/// Stores the given font as the custom font of the role.
	/// This method changes application settings, not the Fonts object itself.
	void setUserFont(FontRole role, const QFont &font) const;

	/// Removes the custom font of the role so the built-in default is used.
	/// This method changes application settings, not the Fonts object itself.
	void clearUserFont(FontRole role) const;

	/// Returns settings keys whose changes affect the resolved font of the role.
	static QStringList fontSettingsKeys(FontRole role);

private:
	/// Per-role configuration. Settings keys are derived from `group`.
	struct RoleConfig {
		QString group;
		QString defaultFamilies;

		QString familiesKey() const;
		QString userFamilyKey() const;
		QString userFontKey() const;
		QString defaultFontKey() const;
		QString useCustomFontKey() const;
	};

	/// Returns the configuration of the given role.
	static RoleConfig roleConfig(FontRole role);

	/// Returns all font files bundled into the application resources as
	/// (path, family) pairs. The order does not matter: a family is matched by
	/// its name, and styles of the same family are matched by the QFont
	/// properties (weight, style).
	virtual QVector<QPair<QString, QString>> bundledFonts() const;

	/// Returns the family explicitly selected by the user, if any.
	/// Falls back to the legacy `CurrentFont` for SceneLabels.
	static QString explicitFamily(FontRole role);

	/// Returns true when the custom font mode is enabled. Prefers the new
	/// `Fonts/SceneLabels/UseCustomFont` key and falls back to the legacy
	/// `CustomFont` flag for old configurations.
	static bool legacyCustomFontEnabled();

	/// Returns serialized QFont attributes (without the family) selected by
	/// the user, or an empty string.
	static QString userFontAttributes(const RoleConfig &config);

	/// Returns built-in serialized QFont attributes (without the family) of
	/// the role, or an empty string.
	static QString defaultFontAttributes(const RoleConfig &config);

	/// Returns the ordered family chain of the role, or its default chain.
	static QStringList familiesFromSettings(const RoleConfig &config);

	/// Returns the ordered family chain of the role, falling back to the
	/// system family when no chain is configured.
	static QStringList familiesForRole(FontRole role, const RoleConfig &config);

	/// Converts a settings value into a list of families. A comma separated
	/// string and an already parsed QStringList are both supported.
	static QStringList variantToFamilies(const QVariant &value);

	/// Converts a settings value into a comma separated string. QSettings may
	/// parse comma separated values into a QStringList, so both forms are
	/// supported.
	static QString variantToCommaString(const QVariant &value);

	/// Returns the system font family for the role's kind of text.
	static QString systemFamily(FontRole role);

	/// Applies role-specific traits that are independent of the family chain.
	static void applyRoleTraits(QFont &font, FontRole role);

	/// Applies an ordered family chain to the font.
	static void applyFamilies(QFont &font, const QStringList &families);

	/// Registers a single font file. Missing files are logged and ignored.
	static void registerFontFile(const QString &path);
};

}
