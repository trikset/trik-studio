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

#include <QObject>
#include <QDomElement>
#include <QSet>
#include <unordered_map>
#include <memory>
#include "template.h"

namespace twoDModel {
namespace constraints {
namespace details {

class XmlTemplate;

class TemplatesParser: public QObject {
	Q_OBJECT
	Q_DISABLE_COPY_MOVE(TemplatesParser)
public:
	TemplatesParser();
	bool parse(const QDomElement &templatesXml);
	void parseSystemTemplates();
	void clear();
	bool transform(const QDomElement &constraintsXml);
	QStringList parsingErrors() const;
	QStringList substituionErrors() const;
private:
	void parseError(const QString& message, int line, int column);
	bool parseTemplate(const QDomElement &templateElement);
	QString pathsToTemplates() const;
	QString mLibraryName;
	std::unordered_map<QString, XmlTemplate> mTemplates;
	QStringList mParsingErrors;
	QStringList mSubstituionErrors;

	struct ExpansionContext {
	    QSet<QString> mMacrosInProgress;
	    QStringList mOrder;
	    uint16_t mDepth {};

	    ExpansionContext fork() const {
		auto newCtx = ExpansionContext();
		newCtx.mMacrosInProgress = mMacrosInProgress;
		newCtx.mOrder = mOrder;
		newCtx.mDepth = mDepth;
		return newCtx;
	    }

	    void push(const QString& macroName) {
		mMacrosInProgress.insert(macroName);
		mOrder.append(macroName);
		mDepth++;
	    }
	};

	struct StackItem {
	    QDomElement mElement;
	    ExpansionContext mContext;
	};

	void substituteError(const QString& message, int line, const ExpansionContext &context);
	std::pair<uint16_t, uint16_t> relativeErrorLineRelativeParent(uint16_t line, uint16_t column, const ExpansionContext &context);
	QDomElement processTemplate(const QDomElement &elements, ExpansionContext& context);
};
}
}
}
