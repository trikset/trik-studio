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

#include <QDir>
#include <qrutils/inFile.h>
#include "templatesParser.h"
#include "template.h"

using namespace twoDModel::templates::details;

XmlTemplate* TemplatesParser::findTemplate(const QString& name)
{
	auto &&it = mCurrentTemplates.find(name);
	if (it == mCurrentTemplates.end()) {
		return nullptr;
	}
	return &it->second;
}

bool TemplatesParser::parseTemplate(const QDomElement &templateElement)
{
	auto &&templateName = templateElement.attribute("name", "");
	if (templateName.isEmpty()) {
		error(QObject::tr(
			R"(The &lt;template&gt; tag was provided, but the required "name" attribute was missing.)"),
			templateElement.lineNumber(),
			ParserErrorCode::MissingTemplateNameAttribute,
			{});
		return false;
	}

	const auto* foundTemplate = findTemplate(templateName);
	if (foundTemplate) {
		error(QObject::tr("Redefinition a template %1 that already exists").arg(templateName),
			   templateElement.lineNumber(), ParserErrorCode::RedefinitionExistingTemplate, {});
		return false;
	}

	XmlTemplate xmlTemplate(templateName);
	xmlTemplate.processDeclaration(templateElement);

	const auto &errors = xmlTemplate.declarationErrors();
	for (auto &&declarationError: errors) {
		error(declarationError.error, declarationError.line, declarationError.errorCode, templateName);
	}
	if (!errors.isEmpty()) {
		return false;
	}
	mCurrentTemplates.emplace(templateName, std::move(xmlTemplate));
	return true;
}

QDomDocument TemplatesParser::parseTemplates(const QDomDocument &templatesDocument)
{
	auto &&templatesXml = templatesDocument.firstChildElement("templates");
	QDomDocument result;
	if (templatesXml.isNull()) {
		// not found
		return result;
	}

	QDomElement templatesContainer = result.createElement("templatesContainer");
	auto firstChildElement = templatesXml.firstChildElement();
	while (!firstChildElement.isNull()) {
		if (firstChildElement.tagName().toLower() != "template") {
			error(
				QObject::tr("the &lt;templates&gt; tag can only contain"
					    " the &lt;template&gt; tag as a child tag, actual %1")
				.arg(firstChildElement.tagName())
				, firstChildElement.lineNumber()
				, ParserErrorCode::TemplatesTagContaintsOnlyTemplate, {});
		} else if (!parseTemplate(firstChildElement)) {
			// already logged
		} else {
			templatesContainer.appendChild(firstChildElement.cloneNode());
		}
		firstChildElement = firstChildElement.nextSiblingElement();
	}
	result.appendChild(templatesContainer);
	return result;
}

QHash<QString, QDomDocument> TemplatesParser::parseAllTemplatesFromDirectory(const QString &dirPath)
{
	QDir xmlTemplateDir(dirPath);
	if (!xmlTemplateDir.exists()) {
		auto &&errorString = QString("Template library does not exist at path %1").arg(xmlTemplateDir.path());
		error(errorString, 0, ParserErrorCode::TemplateLibraryNotFound, {});
	}
	QHash<QString, QDomDocument> result;
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
		if (!templates.setContent(templateCode, &errorMessage, &errorLine)) {
			error(QString("%1 %2").arg(message, errorMessage),
				   errorLine, ParserErrorCode::QtXmlParserError, {});
			continue;
		}

		QDomDocument currentResult;
		QDomElement resultTemplates = currentResult.createElement("templates");

		const auto &parseResult = parseTemplates(templates).firstChildElement("templatesContainer");
		for (auto xmlTemplate = parseResult.firstChildElement("template"); !xmlTemplate.isNull()
				; xmlTemplate = xmlTemplate.nextSiblingElement("template")) {
			resultTemplates.appendChild(xmlTemplate.cloneNode());
		}
		currentResult.appendChild(resultTemplates);
		result[baseName] = currentResult;
	}

	return result;
}

void TemplatesParser::clear()
{
	mCurrentTemplates.clear();
	mErrors.clear();
}

std::unordered_map<QString, XmlTemplate> & TemplatesParser::currentTemplates()
{
	return mCurrentTemplates;
}

QStringList TemplatesParser::errors() const
{
	return mErrors;
}

void TemplatesParser::error(const QString& message, int line, ParserErrorCode code, const QString &currentTemplate)
{
	Q_UNUSED(code)
	QStringList messages = {message, QObject::tr("line %1").arg(line)};
	if (!currentTemplate.isEmpty()) {
		messages.append(QObject::tr("template %1").arg(currentTemplate));
	}
	const auto &finalMessage = messages.join(" ");
	mErrors << finalMessage;
}
