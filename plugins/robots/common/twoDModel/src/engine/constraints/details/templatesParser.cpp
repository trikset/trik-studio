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

static QString getAllChildContent(const QDomElement& parentElement)
{
	if (!parentElement.hasChildNodes()) {
		return {};
	}

	QString result;
	QTextStream stream(&result);

	QDomNode child = parentElement.firstChild();
	while(!child.isNull()) {
		child.save(stream, 0);
		child = child.nextSibling();
	}
	return result;
}

QDomElement TemplatesParser::processTemplate(const QDomElement &elements, ExpansionContext& context)
{
	if (elements.tagName().toLower() != "use") {
		return elements;
	}

	auto &&templateName = elements.attribute("template");

	if (templateName.isEmpty()) {
		substituteError(QObject::tr(R"(The <use> tag must contain a "template" attribute)")
				, elements.lineNumber(), context);
		return {};
	}

	if (context.mMacrosInProgress.contains(templateName)) {
		substituteError(QObject::tr(
		    "Recursive template expansion detected: %1 -> %2")
		    .arg(context.mOrder.join(" -> "))
		    .arg(templateName), elements. lineNumber(), context);
		return {};
	}

	auto it = mTemplates.find(templateName);

	if (it == mTemplates.end()) {
		substituteError(tr(R"(The <use> tag contains a template=%1 attribute that is not the name of a declared template)")
				.arg(templateName), elements.lineNumber(), context);
		return {};
	}

	QHash<QString, QString> paramsForReplace;
	for (QDomElement element = elements.firstChildElement()
		; !element.isNull()
		; element = element.nextSiblingElement())
	{
		if (element.tagName().toLower() != "with") {
			substituteError(QObject::tr(
				R"(The <use> tag can only contain a child tag <with>)"),
				elements.lineNumber(), context);
			return {};
		}

		auto &&param = element.attribute("param");

		QString value;
		if (!param.isEmpty()) {
			value = getAllChildContent(element);
			paramsForReplace.insert(param, value);
		} else {
			auto &&attributes = element.attributes();
			for (int i = 0; i < attributes.length(); i++) {
				auto &&attr = attributes.item(i).toAttr();
				paramsForReplace.insert(attr.name(), attr.value());
			}
		}
	}

	auto &&xmlTemplate = it->second;
	auto &&stringResult = xmlTemplate.proccess(paramsForReplace);

	auto &&wrappedXml = QString("<root>%1</root>").arg(stringResult);
	QDomDocument result;
	QString errorMessage;
	int errorLine, errorColumn;
	result.setContent(wrappedXml, &errorMessage, &errorLine, &errorColumn);
	const auto &message = tr("After substituting the parameters for the template %1, it did not become a valid xml node")
			.arg(templateName);
	if (!result.setContent(wrappedXml, &errorMessage, &errorLine, &errorColumn)) {
		substituteError(QString("%1 %2").arg(message, errorMessage), errorLine, context);
		return {};
	}

	context.mOrder.append(templateName);
	context.mDepth++;
	context.mMacrosInProgress.insert(templateName);
	return result.documentElement();
}

bool TemplatesParser::transform(const QDomElement& constraintsXml) {
	std::stack<StackItem> elementStack;
	const auto &rootContext = ExpansionContext();
	auto&& child = constraintsXml.firstChildElement();

	while (!child.isNull()) {
		elementStack.push(StackItem{child, rootContext.fork()});
		child = child.nextSiblingElement();
	}

	while (!elementStack.empty()) {
		const auto& currentItem = elementStack.top();
		auto&& current = currentItem.mElement;
		auto context = currentItem.mContext;

		elementStack.pop();

		if (current.tagName() != "use") {
			auto&& child = current.firstChildElement();
			while (!child.isNull()) {
				elementStack.push(StackItem{child, context.fork()});
				child = child.nextSiblingElement();
			}
			continue;
		}

		auto&& currentContext = context.fork();
		auto&& replacement = processTemplate(current, currentContext);
		auto&& parent = current.parentNode().toElement();

		if (parent.isNull()) {
			continue;
		}

		auto&& nextSibling = current.nextSibling();

		if (replacement.isNull()) {
			parent.removeChild(current);
			return false;
		}

		parent.removeChild(current);

		auto&& replChild = replacement.firstChildElement();
		std::vector<StackItem> newlyInserted;

		while (!replChild.isNull()) {
			auto&& cloned = replChild.toElement();

			if (nextSibling.isNull()) {
				parent.appendChild(cloned);
			} else {
				parent.insertBefore(cloned, nextSibling);
			}

			newlyInserted.push_back(StackItem{cloned, currentContext});
			replChild = replChild.nextSiblingElement();
		}

		for (auto it = newlyInserted.rbegin(); it != newlyInserted.rend(); ++it) {
			elementStack.push(*it);
		}
	}
	return true;
}

bool TemplatesParser::parse(const QDomElement &templatesXml)
{
	QDomDocument newDoc;
	auto &&importedNode = newDoc.importNode(templatesXml, true).toElement();
	newDoc.appendChild(importedNode);

	const auto& templatesXmlString = newDoc.toString();
	QDomDocument templatesXmlDocument;
	QString errorMessage;
	int errorLine, errorColumn;

	if (!templatesXmlDocument.setContent(templatesXmlString, &errorMessage, &errorLine, &errorColumn)) {
		return false;
	}

	auto firstChildElement = templatesXmlDocument
			.firstChildElement("templates")
			.firstChildElement();

	while (!firstChildElement.isNull()) {
		if (firstChildElement.tagName().toLower() != "template") {
			parseError(QObject::tr(R"(the <templates>; tag can only contain the <template>; tag as a child tag)")
				   , firstChildElement.lineNumber(), firstChildElement.columnNumber());
			return false;
		}

		if (!parseTemplate(firstChildElement)) {
			return false;
		}

		firstChildElement = firstChildElement.nextSiblingElement();
	}

	return true;
}


TemplatesParser::TemplatesParser():
	mLibraryName("xml-templates") {}

void TemplatesParser::parseSystemTemplates()
{
	QDir xmlTemplateDir(pathsToTemplates());

	if (!xmlTemplateDir.exists()) {
		auto &&errorString = QString("System template library does not exist at path %1").arg(pathsToTemplates());
		QLOG_ERROR() << errorString;
		parseError(errorString, 0, 0);
	}

	QStringList filters = {"*.xml"};
	QStringList files = xmlTemplateDir.entryList(filters, QDir::Files);

	for (auto &&fileName : files) {
		auto &&filePath = xmlTemplateDir.filePath(fileName);
		QFileInfo fileInfo(filePath);
		auto &&baseName = fileInfo.baseName();

		if (mTemplates.find(baseName) != mTemplates.end()) {
			continue;
		}

		auto &&templateCode = utils::InFile::readAll(filePath);

		QDomDocument templates;
		QString errorMessage;
		int errorLine, errorColumn;

		const auto &&message = QString("Error parsing a system template from a file %1 with").arg(baseName);
		if (!templateCode.isEmpty() && !templates.setContent(templateCode, &errorMessage, &errorLine, &errorColumn)) {
			parseError(QString("%1 %2").arg(message, errorMessage), errorLine, errorColumn);
			continue;
		}

		auto &&templatesXml = templates.firstChildElement("templates");
		if (templatesXml.isNull()) {
			parseTemplate(templates.firstChildElement("template"));
			return;
		}

		parse(templatesXml);
	}
}

QString TemplatesParser::pathsToTemplates() const
{
	return { ":/" + mLibraryName + "/templates" };
}

bool TemplatesParser::
parseTemplate(const QDomElement &templateElement)
{
	auto &&templateName = templateElement.attribute("name", "");
	if (templateName.isEmpty()) {
		parseError(QObject::tr(R"(The <template> tag was provided, but the required "name" attribute was missing.)"),
			   templateElement.lineNumber(), templateElement.columnNumber());
		return false;
	}

	auto &&it = mTemplates.find(templateName);

	if (it != mTemplates.end()) {
		parseError(QObject::tr("Redefinition a template %1 that already exists").arg(it->first),
			   templateElement.lineNumber(), templateElement.columnNumber());
		return false;
	}

	auto &&params = templateElement.firstChildElement("params");
	std::unordered_map<QString, QString> templateParams;

	if (!params.isNull()) {
		auto &&firstParamDecl = params.firstChildElement("param");
		while (!firstParamDecl.isNull()) {
			if (firstParamDecl.tagName() != "param") {
				parseError(QObject::tr(R"(the <params> tag can only contain the <param> tag as a child tag for template %1)")
					   .arg(templateName), firstParamDecl.lineNumber(), firstParamDecl.columnNumber());
				return false;
			}

			auto &&paramName = firstParamDecl.attribute("name");

			if (paramName.isEmpty()) {
				parseError(QObject::tr(
					R"(The <param> tag of template %1 was provided, but the required "name" attribute was missing.)")
					   .arg(templateName), firstParamDecl.lineNumber(), firstParamDecl.columnNumber());
				return false;
			}

			auto &&defaultValue = firstParamDecl.attribute("default");
			if (defaultValue.isEmpty()) {
				defaultValue = getAllChildContent(firstParamDecl);
			}

			templateParams.emplace(std::move(paramName), std::move(defaultValue));
			firstParamDecl = firstParamDecl.nextSiblingElement();
		}
	}

	auto &&contentDecl = templateElement.firstChildElement("content");

	if (contentDecl.isNull()) {
		parseError(QObject::tr(
			R"(The <template> of template %1 tag was provided, but the required child tag <content> was missing.)")
			   .arg(templateName), templateElement.lineNumber(), templateElement.columnNumber());
		return false;
	}

	auto &&content = contentDecl.firstChild();
	if(!content.isCDATASection()) {
		parseError(QObject::tr(
			R"(Currently, this method of setting <content> tag for the template %1 is not supported.)")
			   .arg(templateName), contentDecl.lineNumber(), contentDecl.columnNumber());
		return false;
	}

	auto &&text = content.toCDATASection().data();
	static const QRegularExpression paramRegex("#\\{([^}]+)\\}");
	auto offset = 0;
	QRegularExpressionMatch match;

	auto &&xmlTemplate = XmlTemplate(templateName, text);

	while ((match = paramRegex.match(text, offset)).hasMatch()) {
		auto &&fullMatch = match.captured(0);
		auto &&paramName = match.captured(1);

		auto &&paramIt = templateParams.find(paramName);

		if (paramIt == templateParams.end()) {
			auto &&startPos = match.capturedStart(0);
			parseError(QObject::tr(
				"When defining the template %1,"
				" the syntax %2 was used to substitute an"
				" offset %3 for an undeclared parameter %4.")
				.arg(templateName, fullMatch, QString(startPos), paramName),
				contentDecl.lineNumber(), contentDecl.columnNumber());
			return false;
		}
		xmlTemplate.emplaceParam(match.capturedStart(), fullMatch.length(), paramName, paramIt->second);
		offset = match.capturedEnd();
	}

	mTemplates.emplace(templateName, std::move(xmlTemplate));
	return true;
}

void TemplatesParser::clear()
{
	mTemplates.clear();
	mParsingErrors.clear();
	mSubstituionErrors.clear();
}

void TemplatesParser::parseError(const QString& message, int line, int column)
{
	QLOG_ERROR() << message + QObject::tr("line:column %1:%2").arg(line, column);
	mParsingErrors << message + QObject::tr("line:column %1:%2").arg(line, column);
}

void TemplatesParser::substituteError(const QString& message, int line, const ExpansionContext &context)
{
	QLOG_ERROR() << message
			+ QObject::tr(", line %1").arg(line)
		     << tr(R"(Substitution chain: %1.)").arg(context.mOrder.join(" -> "));
	mSubstituionErrors << message
			      + QObject::tr(", line %1").arg(line)
			   << tr(R"(Substitution chain: %1.)").arg(context.mOrder.join(" -> "));

}

QStringList TemplatesParser::parsingErrors() const
{
	return mParsingErrors;
}

QStringList TemplatesParser::substituionErrors() const
{
	return mSubstituionErrors;
}
