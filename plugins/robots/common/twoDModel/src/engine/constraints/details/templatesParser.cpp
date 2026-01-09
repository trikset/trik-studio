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

#include "templatesParser.h"
#include "template.h"
#include <unordered_set>
#include <QRegularExpression>
#include <stack>
#include <QsLog.h>
#include <QDir>
#include <qrutils/inFile.h>

using namespace twoDModel::constraints::details;

XmlTemplate* TemplatesParser::findTemplate(const QString& name)
{
	auto &&systemIt = mSystemTemplates.find(name);
	if (systemIt == mSystemTemplates.end()) {
		auto &&it = mTemplates.find(name);
		if (it == mTemplates.end()) {
			return nullptr;
		}
		return &it->second;
	}
	return &systemIt->second;

}
bool TemplatesParser::parseTemplate(const QDomElement &templateElement)
{
	auto &&templateName = templateElement.attribute("name", "");
	if (templateName.isEmpty()) {
		parseError(QObject::tr(R"(The &lt;template&gt; tag was provided,
				but the required "name" attribute was missing.)"),
				templateElement.lineNumber(),
				ParserErrorCode::MissingTemplateNameAttribute);
		return false;
	}

	const auto* foundTemplate = findTemplate(templateName);
	if (foundTemplate) {
		parseError(QObject::tr("Redefinition a template %1 that already exists").arg(templateName),
			   templateElement.lineNumber(), ParserErrorCode::RedefinitionExistingTemplate);
		return false;
	}

	XmlTemplate xmlTemplate(templateName);
	xmlTemplate.processDeclaration(templateElement);

	const auto &errors = xmlTemplate.declarationErrors();
	for (auto &&declarationError: errors) {
		mParsingErrors << declarationError;
	}
	if (!errors.isEmpty()) {
		return false;
	}
	mTemplates.emplace(templateName, std::move(xmlTemplate));
	return true;
}

bool TemplatesParser::parseTemplates(const QDomElement &templatesXml)
{
	auto firstChildElement = templatesXml.firstChildElement();

	while (!firstChildElement.isNull()) {
		if (firstChildElement.tagName().toLower() != "template") {
			parseError(QObject::tr(R"(the &lt;templates&gt; tag can only
					contain the &lt;template&gt; tag as a child tag)")
					, firstChildElement.lineNumber()
					, ParserErrorCode::TemplatesTagContaintsOnlyTemplate);
			return false;
		}

		if (!parseTemplate(firstChildElement)) {
			return false;
		}

		firstChildElement = firstChildElement.nextSiblingElement();
	}

	return true;
}

void TemplatesParser::parseAllTemplatesFromDirectory(const QString &dirPath)
{
	QDir xmlTemplateDir(dirPath);
	if (!xmlTemplateDir.exists()) {
		auto &&errorString = QString("Template library does not exist at path %1").arg(xmlTemplateDir.path());
		parseError(errorString, 0, ParserErrorCode::TemplateLibraryNotFound);
	}

	QStringList filters = {"*.xml"};
	QStringList files = xmlTemplateDir.entryList(filters, QDir::Files);

	for (auto &&fileName : files) {
		auto &&filePath = xmlTemplateDir.filePath(fileName);

		QFileInfo fileInfo(filePath);
		auto &&baseName = fileInfo.baseName();
		auto &&templateCode = utils::InFile::readAll(filePath);

		QDomDocument templates;
		QString errorMessage;
		int errorLine;

		const auto &&message = QString("Error parsing template from a file %1 with").arg(baseName);
		if (!templateCode.isEmpty() && !templates.setContent(templateCode, &errorMessage, &errorLine)) {
			parseError(QString("%1 %2").arg(message, errorMessage), errorLine, ParserErrorCode::QtXmlParserError);
			continue;
		}

		auto &&templatesXml = templates.firstChildElement("templates");
		if (templatesXml.isNull()) {
			parseTemplate(templates.firstChildElement("template"));
			return;
		}

		parseTemplates(templatesXml);
	}
}

QString TemplatesParser::pathsToTemplates() const
{
	return { ":/" + mLibraryName + "/templates" };
}

void TemplatesParser::parseSystemTemplates()
{
	clear();
	parseAllTemplatesFromDirectory(pathsToTemplates());
	mSystemTemplates = std::move(mTemplates);
	mTemplates.clear();
}


QDomElement TemplatesParser::processTemplate(const QDomElement &elements, ExpansionContext& context)
{
	auto &&templateName = elements.attribute("template");

	if (templateName.isEmpty()) {
		substituteError(QObject::tr(R"(The &lt;use&gt; tag must contain a "template" attribute)")
				, elements.lineNumber(), context, SubstitutionErrorCode::UseTagContainsTemplateAttr);
		return {};
	}

	if (context.mMacrosInProgress.contains(templateName)) {
		substituteError(QObject::tr(
			"Recursive template expansion detected: %1 -> %2")
			.arg(context.mOrder.join(" -> "), templateName), elements.lineNumber(),
			context, SubstitutionErrorCode::RecursiveTemplateExpansion);
		return {};
	}

	auto *foundTemplate = findTemplate(templateName);

	if (!foundTemplate) {
		substituteError(QObject::tr(R"(The &lt;use&gt; tag contains a template=%1 attribute
				that is not the name of a declared template)")
				.arg(templateName), elements.lineNumber(), context,
				SubstitutionErrorCode::UseUndeclaredTemplate);
		return {};
	}

	auto &xmlTemplate = *foundTemplate;
	auto substitutionResult = xmlTemplate.substitute(elements);
	const auto &errors = xmlTemplate.substitutionErrors();
	for (auto &&substitutionError: errors) {
		mSubstituionErrors << substitutionError;
	}
	if (!errors.isEmpty()) {
		return {};
	}

	auto &&wrappedXml = QString("<root>%1</root>").arg(substitutionResult);
	QDomDocument result;
	QString errorMessage;
	int errorLine;
	const auto &message =
		QObject::tr("After substituting the parameters for"
			    " the template %1, it did not become a valid xml node").arg(templateName);
	if (!result.setContent(wrappedXml, &errorMessage, &errorLine)) {
		substituteError(QString("%1 %2").arg(message, errorMessage), errorLine, context,
				SubstitutionErrorCode::QtXmlParserError);
		return {};
	}

	context.mOrder.append(templateName);
	context.mDepth++;
	context.mMacrosInProgress.insert(templateName);
	return result.documentElement();
}

bool TemplatesParser::substitute(const QDomElement& constraintsXml) {
	std::stack<ExpansionItem> elementStack;
	const auto &rootContext = ExpansionContext();
	auto&& child = constraintsXml.firstChildElement();

	while (!child.isNull()) {
		elementStack.push(ExpansionItem{child, rootContext.fork()});
		child = child.nextSiblingElement();
	}

	while (!elementStack.empty()) {
		auto currentItem = std::move(elementStack.top());
		auto&& current = currentItem.mElement;
		auto&& context = currentItem.mContext;

		elementStack.pop();

		// If the current node is not equal to use, we just want to process its children later.
		if (current.tagName() != "use") {
			auto&& child = current.firstChildElement();
			while (!child.isNull()) {
				elementStack.push(ExpansionItem{child, context.fork()});
				child = child.nextSiblingElement();
			}
			continue;
		}

		// If it is a <use> node, we want to replace it with a template definition.
		auto&& currentContext = context.fork();
		auto&& replacement = processTemplate(current, currentContext);
		auto&& parent = current.parentNode().toElement();

		auto&& nextSibling = current.nextSibling();

		// If the substitution is unsuccessful, we do not process the subtree,
		// the user will see an error message.
		if (replacement.isNull()) {
			parent.removeChild(current);
			return false;
		}

		// Otherwise, we replace the use tag with a sequence of received nodes,
		// the last of these nodes must have the next node as the node being replaced.
		parent.removeChild(current);

		auto &&replChild = replacement.firstChildElement();
		std::vector<ExpansionItem> newlyInserted;

		while (!replChild.isNull()) {
			auto &&next = replChild.nextSiblingElement();
			auto &&cloned = replChild.toElement();
			if (nextSibling.isNull()) {
				parent.appendChild(cloned);
			} else {
				parent.insertBefore(cloned, nextSibling);
			}

			newlyInserted.push_back(ExpansionItem{cloned, currentContext});
			replChild = next;
		}

		for (auto it = newlyInserted.rbegin(); it != newlyInserted.rend(); ++it) {
			elementStack.push(*it);
		}
	}
	return true;
}


void TemplatesParser::clear()
{
	mTemplates.clear();
	mParsingErrors.clear();
	mSubstituionErrors.clear();
}

QStringList TemplatesParser::parsingErrors() const
{
	return mParsingErrors;
}

QStringList TemplatesParser::substituionErrors() const
{
	return mSubstituionErrors;
}

void TemplatesParser::parseError(const QString& message, int line, ParserErrorCode code)
{
	Q_UNUSED(code)
	const auto &final =  message + " " + QObject::tr("line %1").arg(line);
	QLOG_ERROR() << final;
	mParsingErrors << final;
}

void TemplatesParser::substituteError(const QString& message, int line,
				      const ExpansionContext &context, SubstitutionErrorCode code)
{
	Q_UNUSED(code)
	const auto &final = message + " " + QObject::tr("line %1").arg(line);
	const auto &substitutionChain = QObject::tr(R"(Substitution chain: %1.)").arg(context.mOrder.join(" -> "));
	QLOG_ERROR() << final << substitutionChain;
	mSubstituionErrors << final << substitutionChain;
}

