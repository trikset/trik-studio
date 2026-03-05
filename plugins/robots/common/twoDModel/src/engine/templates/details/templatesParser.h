/* Copyright 2025 CyberTech Labs Ltd.
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

class TemplatesParser
{
public:
	TemplatesParser(const TemplatesParser&) = delete;
	TemplatesParser& operator=(const TemplatesParser&) = delete;
	TemplatesParser(TemplatesParser&&) noexcept = default;
	TemplatesParser& operator=(TemplatesParser&&) noexcept = default;
	virtual ~TemplatesParser() = default;
	TemplatesParser() noexcept = default;

	/// It is used to parse all templates from the directory. Thus, each xml file in the directory will
	/// be examined, and each file will search for the top-level template or templates tag.
	/// In the future, this function should be used to allow the user to specify a directory with
	/// their own templates.
	QHash<QString, QDomDocument> parseAllTemplatesFromDirectory(const QString &dirPath);

	/// Returns all errors received when parsing template definitions,
	/// which can later be displayed to the user from the ConsoleReporter interface or recorded in logs.
	QStringList errors() const;

	/// Clear all error messages
	void clear();

	std::unordered_map<QString, XmlTemplate> &currentTemplates();

	QDomDocument parseTemplates(const QDomDocument &templatesDocument);
protected:
	using ParserErrorCode = XmlTemplate::TemplateParseErrorCode;
	virtual void error(const QString& message, int line, ParserErrorCode code,
						const QString &currentTemplate);
private:
	/// Parsing a separate template and checking the uniqueness of its name.
	/// If a user overrides a library template, an error should be thrown.
	bool parseTemplate(const QDomElement &templateElement);

	XmlTemplate* findTemplate(const QString& name);
	std::unordered_map<QString, XmlTemplate> mCurrentTemplates;
	QStringList mErrors;
};
}
}
}
