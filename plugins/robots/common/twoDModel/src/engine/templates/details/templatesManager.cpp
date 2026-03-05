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

#include "templatesManager.h"
#include "template.h"

using namespace twoDModel::templates::details;

static auto* sSystemLibraryNs = "ts:";
static auto* sUserLibraryNs = "u:";

void TemplatesManager::clearTemplates(bool system)
{
	if (system) {
		mSystemTemplates.clear();
		return;
	}

	mUserTemplates.clear();
}

void TemplatesManager::addTemplates(std::unordered_map<QString, XmlTemplate> &templates, bool isSystem)
{
	auto &targetMap = isSystem ? mSystemTemplates : mUserTemplates;
	const auto &prefix = isSystem ? sSystemLibraryNs : sUserLibraryNs;

	for (auto &&currentTemplate : templates) {
		auto finalKey = currentTemplate.first;
		if (!finalKey.startsWith(prefix)) {
			finalKey = prefix + finalKey;
		}
		targetMap.emplace(std::move(finalKey), std::move(currentTemplate.second));
	}
}


XmlTemplate* TemplatesManager::findTemplate(const QString &templateName)
{
	std::unordered_map<QString, XmlTemplate>* targetMap = nullptr;

	if (templateName.startsWith(sSystemLibraryNs)) {
		targetMap = &mSystemTemplates;
	} else if (templateName.startsWith(sUserLibraryNs)) {
		targetMap = &mUserTemplates;
	}

	if (!targetMap) {
		return nullptr;
	}

	auto it = targetMap->find(templateName);
	return (it != targetMap->end()) ? &it->second : nullptr;
}

bool TemplatesManager::isPotentialTemplate(const QString &name) const
{
	return name.startsWith(sSystemLibraryNs) || name.startsWith(sUserLibraryNs);
}
