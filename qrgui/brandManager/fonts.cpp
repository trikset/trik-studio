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

#include "fonts.h"

#include <QtCore/QFile>
#include <QtCore/QVariant>
#include <QtGui/QFontDatabase>

#include <qrkernel/settingsManager.h>

#include <QsLog.h>

using namespace qReal;

Fonts::Fonts()
{
	for (const auto &fontPath : bundledFonts()) {
		registerFontFile(fontPath);
	}
}

QFont Fonts::sceneLabelsFont() const
{
	return font(FontRole::SceneLabels);
}

QFont Fonts::codeEditorFont() const
{
	return font(FontRole::CodeEditor);
}

QFont Fonts::uiFont() const
{
	return font(FontRole::Ui);
}

QFont Fonts::font(FontRole role) const
{
	const auto config = roleConfig(role);
	auto families = familiesForRole(role, config);
	const auto selectedFamily = explicitFamily(role);
	const auto userFont = userFontAttributes(config);

	const auto parsingFamily = selectedFamily.isEmpty() ? families.first() : selectedFamily;

	QFont result = defaultFont(role);
	bool parsed = false;

	if (!userFont.isEmpty()) {
		QFont userFontObject;
		parsed = userFontObject.fromString(parsingFamily + ',' + userFont);
		if (parsed) {
			result = userFontObject;
		}
	}

	if (!parsed && role == FontRole::SceneLabels && legacyCustomFontEnabled()) {
		// Preserve the size and style chosen in the old "custom font" dialog.
		QFont legacy;
		parsed = legacy.fromString(variantToCommaString(SettingsManager::value("CurrentFont")));
		if (parsed) {
			result = legacy;
		}
	}

	if (!selectedFamily.isEmpty()) {
		families.removeAll(selectedFamily);
		families.prepend(selectedFamily);
	}

	applyRoleTraits(result, role);
	applyFamilies(result, families);
	return result;
}

QFont Fonts::defaultFont(FontRole role) const
{
	const auto config = roleConfig(role);
	auto families = familiesForRole(role, config);
	const auto defaultFont = defaultFontAttributes(config);
	const auto &parsingFamily = families.first();

	QFont result;
	if (!defaultFont.isEmpty()) {
		result.fromString(parsingFamily + ',' + defaultFont);
	}

	applyRoleTraits(result, role);

	applyFamilies(result, families);
	return result;
}

bool Fonts::hasUserFont(FontRole role) const
{
	const auto config = roleConfig(role);
	const auto family = SettingsManager::value(config.userFamilyKey()).toString().trimmed();
	if (!family.isEmpty() || !userFontAttributes(config).isEmpty()) {
		return true;
	}

	if (role == FontRole::SceneLabels) {
		return legacyCustomFontEnabled()
		       && !variantToCommaString(SettingsManager::value("CurrentFont")).trimmed().isEmpty();
	}

	return false;
}

void Fonts::setUserFont(FontRole role, const QFont &font) const
{
	const auto config = roleConfig(role);
	const auto description = font.toString();
	SettingsManager::setValue(config.userFamilyKey(), font.family());
	SettingsManager::setValue(config.userFontKey(), description.section(',', 1));

	if (role == FontRole::SceneLabels) {
		SettingsManager::setValue(config.useCustomFontKey(), true);
	}
}

void Fonts::clearUserFont(FontRole role) const
{
	const auto config = roleConfig(role);
	SettingsManager::setValue(config.userFamilyKey(), QString());
	SettingsManager::setValue(config.userFontKey(), QString());

	if (role == FontRole::SceneLabels) {
		SettingsManager::setValue(config.useCustomFontKey(), false);
	}
}

QStringList Fonts::fontSettingsKeys(FontRole role)
{
	const auto config = roleConfig(role);
	QStringList keys = {
		config.familiesKey(),
		config.userFamilyKey(),
		config.userFontKey(),
		config.defaultFontKey(),
	};

	if (role == FontRole::SceneLabels) {
		keys << config.useCustomFontKey();
	}

	return keys;
}

QStringList Fonts::bundledFonts() const
{
	return {
		":/fonts/Pfennig.ttf",
		":/fonts/DejaVuSansMono.ttf",
		":/fonts/CascadiaMono-Regular.ttf",
		":/fonts/CascadiaMono-Bold.ttf",
		":/fonts/CascadiaMono-Italic.ttf",
		":/fonts/CascadiaMono-BoldItalic.ttf",
	};
}

QString Fonts::RoleConfig::familiesKey() const
{
	return group + "/Families";
}

QString Fonts::RoleConfig::userFamilyKey() const
{
	return group + "/UserFamily";
}

QString Fonts::RoleConfig::userFontKey() const
{
	return group + "/UserFont";
}

QString Fonts::RoleConfig::defaultFontKey() const
{
	return group + "/DefaultFont";
}

QString Fonts::RoleConfig::useCustomFontKey() const
{
	return group + "/UseCustomFont";
}

Fonts::RoleConfig Fonts::roleConfig(FontRole role)
{
	switch (role) {
	case FontRole::CodeEditor:
		return {"Fonts/CodeEditor", "Cascadia Mono,DejaVu Sans Mono"};
	case FontRole::Ui:
		return {"Fonts/Ui", "Segoe UI"};
	case FontRole::SceneLabels:
	default:
		return {"Fonts/SceneLabels", "Cascadia Mono,Pfennig"};
	}
}

QString Fonts::explicitFamily(FontRole role)
{
	const auto config = roleConfig(role);
	auto userPreferredFamily = SettingsManager::value(config.userFamilyKey()).toString().trimmed();

	// Backward compatibility with the legacy config flags. CustomFont enabled the old
	// custom font mode for scene labels, and CurrentFont stored the chosen font as a
	// QFont::toString() value. The fallback below is used only when there is no new
	// Fonts/SceneLabels/UserFamily or Fonts/SceneLabels/UserFont value.
	if (!userPreferredFamily.isEmpty() || role != FontRole::SceneLabels || !legacyCustomFontEnabled()
		|| !userFontAttributes(config).isEmpty()) {
		return userPreferredFamily;
	}

	QFont legacy;
	legacy.fromString(variantToCommaString(SettingsManager::value("CurrentFont")));
	return legacy.family().trimmed();
}

bool Fonts::legacyCustomFontEnabled()
{
	const auto useCustomFont = SettingsManager::value(roleConfig(FontRole::SceneLabels).useCustomFontKey());
	if (useCustomFont.isValid() && !useCustomFont.toString().isEmpty()) {
		return useCustomFont.toBool();
	}

	return SettingsManager::value("CustomFont").toBool();
}

QString Fonts::userFontAttributes(const RoleConfig &config)
{
	return variantToCommaString(SettingsManager::value(config.userFontKey())).trimmed();
}

QString Fonts::defaultFontAttributes(const RoleConfig &config)
{
	return variantToCommaString(SettingsManager::value(config.defaultFontKey())).trimmed();
}

QStringList Fonts::familiesFromSettings(const RoleConfig &config)
{
	const auto familiesValue = SettingsManager::value(config.familiesKey());
	auto parts = variantToFamilies(familiesValue);
	if (parts.isEmpty()) {
		QLOG_DEBUG() << "No font families are configured for" << config.group
			     << "- using default:" << config.defaultFamilies;
		parts = variantToFamilies(config.defaultFamilies);
	}

	QStringList result;
	for (const auto &part : parts) {
		const auto trimmed = part.trimmed();
		if (!trimmed.isEmpty()) {
			result << trimmed;
		}
	}

	return result;
}

QStringList Fonts::familiesForRole(FontRole role, const RoleConfig &config)
{
	auto families = familiesFromSettings(config);
	if (families.isEmpty()) {
		families << systemFamily(role);
	}

	return families;
}

QStringList Fonts::variantToFamilies(const QVariant &value)
{
	if (value.type() == QVariant::StringList) {
		return value.toStringList();
	}

	return value.toString().split(',', Qt::SkipEmptyParts);
}

QString Fonts::variantToCommaString(const QVariant &value)
{
	if (value.type() == QVariant::StringList) {
		return value.toStringList().join(',');
	}

	return value.toString();
}

QString Fonts::systemFamily(FontRole role)
{
	return QFontDatabase::systemFont(
		role == FontRole::CodeEditor ? QFontDatabase::FixedFont : QFontDatabase::GeneralFont)
	        .family();
}

void Fonts::applyRoleTraits(QFont &font, FontRole role)
{
	if (role == FontRole::CodeEditor) {
		font.setFixedPitch(true);
	}
}

void Fonts::applyFamilies(QFont &font, const QStringList &families)
{
	if (families.isEmpty()) {
		return;
	}

	font.setFamilies(families);
	// setFamilies() keeps family() untouched, so keep both representations
	// consistent: family() is the preferred family, families() is the fallback
	// chain used by Qt's font matching.
	font.setFamily(families.first());
}

void Fonts::registerFontFile(const QString &path)
{
	if (path.isEmpty()) {
		QLOG_WARN() << "Font registration skipped: empty font path";
		return;
	}

	if (!QFile::exists(path)) {
		QLOG_WARN() << "Font file is missing, skipping registration:" << path;
		return;
	}

	const auto fontId = QFontDatabase::addApplicationFont(path);
	if (fontId == -1) {
		QLOG_WARN() << "Failed to register font:" << path;
		return;
	}

	QLOG_DEBUG() << "Registered font:" << path << "families:" << QFontDatabase::applicationFontFamilies(fontId);
}
