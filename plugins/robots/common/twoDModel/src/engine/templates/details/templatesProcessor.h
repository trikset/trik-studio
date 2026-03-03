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

class TemplatesManager;

class TemplatesProcessor
{
public:
	TemplatesProcessor(const TemplatesProcessor&) = delete;
	TemplatesProcessor& operator=(const TemplatesProcessor&) = delete;
	TemplatesProcessor(TemplatesProcessor&&) noexcept = default;
	TemplatesProcessor& operator=(TemplatesProcessor&&) noexcept = default;
	virtual ~TemplatesProcessor() = default;
	TemplatesProcessor(details::TemplatesManager *manager) noexcept;

	/// Accepts xml as input using templates (<use> tags) as xml nodes. The function modifies the input
	/// xml element constraintsXml  by transforming the tree. Each <use> in this tree will be replaced by
	/// a sequence of xml nodes resulting from template expansion after parameter substitution and sending
	/// it to the Qt Xml parser. Template expansion is lazy, so any nodes nested in <use> templates will be
	/// disassembled in the following steps. Also, any cyclic links between templates are prohibited.
	/// As a result of the function, the input constraintsXml should get a form that
	/// is understandable by the Constraints Parser.
	bool substitute(const QDomElement &constraintsXml);

	/// Returns all errors received when inserting parameters into template bodies,
	/// which can later be displayed to the user from the ConsoleReporter interface or recorded in logs.
	QStringList errors() const;

	/// Clear all error messages
	void clear();
protected:
	using SubstitutionErrorCode = XmlTemplate::TemplateSubstitutionErrorCode;
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
	virtual void error(const QString& message,
				     int line,
				     const ExpansionContext &context,
				     SubstitutionErrorCode code);
private:
	struct ExpansionItem {
	    QDomElement mElement;
	    ExpansionContext mContext;
	};
	TemplatesManager *mManager;
	QStringList mErrors;
	QDomElement processTemplate(const QDomElement &elements, ExpansionContext& context);
};
}
}
}
