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

	/// The copy constructor and the move constructor of QString are marked as noexcept.
	TemplatesParser() noexcept: mLibraryName("xml-templates") {}

	/// System templates are also set via xml and embedded in the binary,
	/// but they must also be accessible to the user for viewing.
	void parseSystemTemplates();

	/// It is used to parse all templates from the directory. Thus, each xml file in the directory will
	/// be examined, and each file will search for the top-level template or templates tag.
	/// In the future, this function should be used to allow the user to specify a directory with
	/// their own templates.
	QDomDocument parseAllTemplatesFromDirectory(const QString &dirPath);

	/// Accepts xml as input using templates (<use> tags) as xml nodes. The function modifies the input
	/// xml element constraintsXml  by transforming the tree. Each <use> in this tree will be replaced by
	/// a sequence of xml nodes resulting from template expansion after parameter substitution and sending
	/// it to the Qt Xml parser. Template expansion is lazy, so any nodes nested in <use> templates will be
	/// disassembled in the following steps. Also, any cyclic links between templates are prohibited.
	/// As a result of the function, the input constraintsXml should get a form that
	/// is understandable by the Constraints Parser.
	bool substitute(const QDomElement &constraintsXml);

	/// Returns all errors received when parsing template definitions,
	/// which can later be displayed to the user from the ConsoleReporter interface or recorded in logs.
	QStringList parsingErrors() const;

	/// Returns all errors received when inserting parameters into template bodies,
	/// which can later be displayed to the user from the ConsoleReporter interface or recorded in logs.
	QStringList substituionErrors() const;

	/// Clear all error messages
	void clear();

	QDomDocument parseTemplates(const QDomDocument &templatesDocument);
protected:
	using ParserErrorCode = XmlTemplate::TemplateParseErrorCode;
	using SubstitutionErrorCode = XmlTemplate::TemplateSubstitutionErrorCode;

	/// The path to the system template library.
	virtual QString pathsToTemplates() const;
	virtual void parseError(const QString& message, int line, ParserErrorCode code,
						const QString &currentTemplate);

	/// During template disclosure, it is necessary to prevent cyclic references to other templates,
	/// as well as to have a sufficiently detailed diagnosis (disclosure chains) in case of errors in
	/// parsing template bodies, since the same template may be incorrect depending on the parameters
	/// provided by the user through template chains.
	struct ExpansionContext {
		QSet<QString> mMacrosInProgress;
		QStringList mOrder;
		uint32_t mDepth {};

		ExpansionContext fork() const {
			auto newCtx = ExpansionContext();
			newCtx.mMacrosInProgress = mMacrosInProgress;
			newCtx.mOrder = mOrder;
			newCtx.mDepth = mDepth;
			return newCtx;
		}
	};
	virtual void substituteError(const QString& message,
				     int line,
				     const ExpansionContext &context,
				     SubstitutionErrorCode code);
private:

	/// Parsing a separate template and checking the uniqueness of its name.
	/// If a user overrides a library template, an error should be thrown.
	bool parseTemplate(const QDomElement &templateElement);

	XmlTemplate* findTemplate(const QString& name);

	struct ExpansionItem {
	    QDomElement mElement;
	    ExpansionContext mContext;
	};

	QString mLibraryName;
	std::unordered_map<QString, XmlTemplate> mTemplates;
	std::unordered_map<QString, XmlTemplate> mSystemTemplates;
	QStringList mParsingErrors;
	QStringList mSubstituionErrors;
	QDomElement processTemplate(const QDomElement &elements, ExpansionContext& context);
};
}
}
}
