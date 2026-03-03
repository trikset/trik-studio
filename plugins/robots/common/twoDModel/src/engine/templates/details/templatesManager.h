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

#include <QDomElement>
#include <QSet>
#include <unordered_map>
#include "template.h"

namespace twoDModel {
namespace templates {
namespace details {

class TemplatesManager
{
public:
	TemplatesManager(const TemplatesManager&) = delete;
	TemplatesManager& operator=(const TemplatesManager&) = delete;
	TemplatesManager(TemplatesManager&&) noexcept = default;
	TemplatesManager& operator=(TemplatesManager&&) noexcept = default;
	TemplatesManager() noexcept = default;
	void addTemplates(std::unordered_map<QString, XmlTemplate> &templates, bool isSystem);
	void clearTemplates(bool system);
	XmlTemplate* findTemplate(const QString &templateName);
	bool isPotentialTemplate(const QString &name) const;
private:
	std::unordered_map<QString, XmlTemplate> mSystemTemplates;
	std::unordered_map<QString, XmlTemplate> mUserTemplates;
};
}
}
}
