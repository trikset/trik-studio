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

#include "fontSettingsManager.h"

#include <algorithm>

#include <QtGlobal>

using namespace qReal;

FontSettingsManager::FontSettingsManager(const Fonts *fonts)
	: mFonts(fonts)
{
	Q_ASSERT(mFonts);
	reload();
}

QVector<FontRole> FontSettingsManager::roles()
{
	return {
		FontRole::SceneLabels,
		FontRole::CodeEditor,
		FontRole::Ui,
	};
}

void FontSettingsManager::reload()
{
	mStates.clear();
	for (const auto role : roles()) {
		RoleState state;
		state.custom = mFonts->hasUserFont(role);
		state.pendingDescription = state.custom ? mFonts->font(role).toString() : QString();
		state.initialCustom = state.custom;
		state.initialDescription = state.pendingDescription;
		mStates.append(state);
	}
}

QFont FontSettingsManager::displayedFont(FontRole role) const
{
	const auto &roleState = state(role);
	if (roleState.custom && !roleState.pendingDescription.isEmpty()) {
		QFont font;
		font.fromString(roleState.pendingDescription);
		return font;
	}

	return mFonts->defaultFont(role);
}

bool FontSettingsManager::isCustom(FontRole role) const
{
	return state(role).custom;
}

void FontSettingsManager::setFont(FontRole role, const QFont &font)
{
	auto &roleState = state(role);
	roleState.pendingDescription = font.toString();
	roleState.custom = true;
}

void FontSettingsManager::resetFont(FontRole role)
{
	auto &roleState = state(role);
	roleState.custom = false;
	roleState.pendingDescription.clear();
}

bool FontSettingsManager::RoleState::isChanged() const
{
	return custom != initialCustom || pendingDescription != initialDescription;
}

bool FontSettingsManager::isChanged(FontRole role) const
{
	return state(role).isChanged();
}

bool FontSettingsManager::hasChanges() const
{
	return std::any_of(mStates.cbegin(), mStates.cend(), [](const RoleState &state) { return state.isChanged(); });
}

void FontSettingsManager::save()
{
	const auto allRoles = roles();
	for (int index = 0; index < mStates.size(); ++index) {
		auto &roleState = mStates[index];
		if (!roleState.isChanged()) {
			continue;
		}

		const auto role = allRoles.at(index);
		const auto hasCustomFont = roleState.custom && !roleState.pendingDescription.isEmpty();

		if (hasCustomFont) {
			QFont font;
			font.fromString(roleState.pendingDescription);
			mFonts->setUserFont(role, font);
		} else {
			mFonts->clearUserFont(role);
		}

		roleState.custom = hasCustomFont;
		roleState.initialCustom = hasCustomFont;
		roleState.initialDescription = roleState.pendingDescription;
	}
}

int FontSettingsManager::indexOf(FontRole role)
{
	return roles().indexOf(role);
}

FontSettingsManager::RoleState &FontSettingsManager::state(FontRole role)
{
	const auto index = indexOf(role);
	Q_ASSERT(index >= 0);
	Q_ASSERT(index < mStates.size());
	return mStates[index];
}

const FontSettingsManager::RoleState &FontSettingsManager::state(FontRole role) const
{
	const auto index = indexOf(role);
	Q_ASSERT(index >= 0);
	Q_ASSERT(index < mStates.size());
	return mStates[index];
}
