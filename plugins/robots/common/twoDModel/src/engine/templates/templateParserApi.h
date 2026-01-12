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

#include <memory>
#include <QDomElement>

namespace qReal {
class ErrorReporterInterface;
}

namespace twoDModel {
namespace templates {

namespace details {
class TemplatesParser;
}

class TemplatesParserApi
{
public:
	TemplatesParserApi(const TemplatesParserApi&) = delete;
	TemplatesParserApi& operator=(const TemplatesParserApi&) = delete;
	TemplatesParserApi(TemplatesParserApi&&) = delete;
	TemplatesParserApi& operator=(TemplatesParserApi&&) = delete;
	explicit TemplatesParserApi(qReal::ErrorReporterInterface &errorReporter);
	~TemplatesParserApi();

	QDomDocument generateTemplatesFromDirectory(const QString &directory);
	bool proccessTemplates(const QDomElement &constraintsXml);
	void parseSystemTemplates();
	void parseTemplates(const QDomDocument &templatesXml);
private:
	void reportTemplateParserErrors();
	void reportTemplateSubstitutionErrors();

	std::unique_ptr<details::TemplatesParser> mTemplatesParser;
	qReal::ErrorReporterInterface &mErrorReporter;
};
}
}
