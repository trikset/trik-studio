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

#include <src/engine/constraints/details/template.h>
#include <src/engine/constraints/details/templatesParser.h>
#include <gmock/gmock.h>

namespace qrTest {

// clazy:excludeall=function-args-by-value

class XmlTemplateMock : public twoDModel::constraints::details::XmlTemplate
{
public:
	using XmlTemplate::XmlTemplate;
	MOCK_METHOD(void, addDeclarationError,
		    (const QString&, int, TemplateParseErrorCode), (override));
	MOCK_METHOD(void, mockAddSubstitutionError,
			(const QString&, int, TemplateSubstitutionErrorCode));
	void addSubstitutionError(const QString& message, int line,
				TemplateSubstitutionErrorCode code) override
	{
	    XmlTemplate::addSubstitutionError(message, line, code);
	    mockAddSubstitutionError(message, line, code);
	}
};

class XmlTemplateParserMock : public twoDModel::constraints::details::TemplatesParser
{
public:
	using TemplatesParser::TemplatesParser;
	using ExpansionContext = TemplatesParser::ExpansionContext;
	MOCK_METHOD(void, parseError,
		    (const QString&, int, ParserErrorCode, const QString&), (override));
	MOCK_METHOD(void, substituteError,
		    (const QString&, int, const ExpansionContext &, SubstitutionErrorCode), (override));
};
}

// clazy:enable
