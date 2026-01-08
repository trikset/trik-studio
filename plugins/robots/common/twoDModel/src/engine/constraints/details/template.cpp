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

#include "template.h"
#include <QHash>
#include <QObject>
#include <QTextStream>
#include <QRegularExpression>
#include <QSet>
#include <QsLog.h>

using namespace twoDModel::constraints::details;

XmlTemplate::XmlTemplate(const QString &id) noexcept:
	mId(id) {};

namespace {

QString getAllChildContent(const QDomElement& parentElement)
{
	QString result;
	QTextStream stream(&result);

	auto &&child = parentElement.firstChild();
	while(!child.isNull()) {
		child.save(stream, 0);
		child = child.nextSibling();
	}
	return result;
}

}

void XmlTemplate::processContent(const QDomElement &contentDecl)
{
	auto &&content = contentDecl.firstChild();
	if(!content.isCDATASection()) {
		addDeclarationError(QObject::tr(
			R"(Currently, this method of setting &lt;content&gt; tag for the template %1 is not supported.)")
			   .arg(mId), contentDecl.lineNumber(), TemplateParseErrorCode::ContentFormatNotSuppoted);
		return;
	}

	mText = content.toCDATASection().data();
	// Searching for the use of #{} in the body of a template with undeclared parameters will be used as a warning.
	static const QRegularExpression paramRegex("#\\{([^}]+)\\}");
	auto offset = 0;
	QRegularExpressionMatch match;
	while ((match = paramRegex.match(mText, offset)).hasMatch()) {
		auto &&fullMatch = match.captured(0);
		auto &&paramName = match.captured(1);
		auto &&paramIt = mParameters.find(paramName);

		if (paramIt == mParameters.end()) {
			auto &&startPos = match.capturedStart(0);
			addDeclarationError(QObject::tr(
				"When defining the template %1,"
				" the syntax %2 was used to substitute an"
				" offset %3 for an undeclared parameter %4.")
				.arg(mId, fullMatch, QString(startPos), paramName),
				contentDecl.lineNumber(), TemplateParseErrorCode::UseSpecialSyntaxForUndeclaredParam);
		}
		offset = match.capturedEnd();
	}
}

void XmlTemplate::processParams(const QDomElement &params)
{
	auto &&firstParamDecl = params.firstChildElement("param");
	while (!firstParamDecl.isNull()) {
		if (firstParamDecl.tagName() != "param") {
			addDeclarationError(QObject::tr(R"(the &lt;params&gt; tag can only contain the &lt;param&gt; tag as a child tag for template %1,
					actual tag is &lt;%2&gt;)")
				   .arg(mId, firstParamDecl.tagName()), firstParamDecl.lineNumber(), TemplateParseErrorCode::ParamsTagContainOnlyParam);
			return;
		}

		auto &&paramName = firstParamDecl.attribute("name");

		if (paramName.isEmpty()) {
			addDeclarationError(QObject::tr(
				R"(The &lt;param&gt; tag of template %1 was provided, but the required "name" attribute was missing.)")
				   .arg(mId), firstParamDecl.lineNumber(), TemplateParseErrorCode::MissingParamNameAttribute);
			return;
		}

		auto hasDefaultValue = true;
		auto &&defaultValue = firstParamDecl.attribute("default");
		if (!firstParamDecl.hasAttribute("default")) {
			if (firstParamDecl.hasChildNodes()) {
				defaultValue = getAllChildContent(firstParamDecl);
			} else {
				hasDefaultValue = false;
			}
		}

		mOrder.push_back(paramName);
		mParameters.insert(paramName, TemplateParamInfo(paramName, defaultValue, hasDefaultValue));
		firstParamDecl = firstParamDecl.nextSiblingElement();
	}
}

void XmlTemplate::clear()
{
	mDeclarationErrors.clear();
	mSubstitutionErrors.clear();
}


QStringList XmlTemplate::substitutionErrors() const
{
	return mSubstitutionErrors;
}

QStringList XmlTemplate::declarationErrors() const
{
	return mDeclarationErrors;
}

void XmlTemplate::processDeclaration(const QDomElement &templateDeclaration)
{
	clear();
	auto &&params = templateDeclaration.firstChildElement("params");

	if (!params.isNull()) {
		processParams(params);
	}

	if (!mDeclarationErrors.isEmpty()) {
		return;
	}

	auto &&contentDecl = templateDeclaration.firstChildElement("content");
	if (contentDecl.isNull()) {
		addDeclarationError(QObject::tr(
			R"(The &lt;template&gt; of template %1 tag was provided, but the required child tag &lt;content&gt; was missing.)")
			   .arg(mId), templateDeclaration.lineNumber(), TemplateParseErrorCode::MissingContentTag);
		return;
	}
	processContent(contentDecl);
}

bool XmlTemplate::validateParam(const QDomNode &with, const QString &param)
{
	auto it = mParameters.find(param);
	if (it == mParameters.end()) {
		addSubstitutionError(QObject::tr(
			R"(The using an undeclared parameter %1 for template %2)").arg(param, mId),
			with.lineNumber(), TemplateSubstitutionErrorCode::UseUndeclaredParam);
		return false;
	}
	return true;
}

void XmlTemplate::parseParams(const QDomElement &paramTag, QHash<QString, QString> &paramsForReplace, bool fromTemplate)
{
	auto &&attributes = paramTag.attributes();
	for (int i = 0; i < attributes.length(); i++) {
		auto &&attr = attributes.item(i).toAttr();
		auto &&currentParamName = attr.name();
		if (fromTemplate && currentParamName == "template") {
			continue;
		}
		if (validateParam(paramTag, currentParamName)){
			paramsForReplace.insert(currentParamName, attr.value());
		}
	}
}

void XmlTemplate::parseWith(const QDomElement &with, QHash<QString, QString> &paramsForReplace)
{
	if (with.tagName().toLower() != "with") {
		addSubstitutionError(QObject::tr(
			R"(The &lt;use&gt; tag can only contain a child tag &lt;with&gt;)"),
			with.lineNumber(), TemplateSubstitutionErrorCode::UseTagContainsOnlyWithTag);
		return;
	}

	QString value;
	auto hasParam = with.hasAttribute("param");
	if (!hasParam) {
		parseParams(with, paramsForReplace);
	} else {
		auto &&param = with.attribute("param");
		paramsForReplace.insert(param, getAllChildContent(with));
	}

}

QString XmlTemplate::substitute(const QDomElement &templateUsage)
{
	clear();
	QHash<QString, QString> paramsForReplace;
	parseParams(templateUsage, paramsForReplace, true);
	for (QDomElement element = templateUsage.firstChildElement()
		; !element.isNull()
		; element = element.nextSiblingElement())
	{
		parseWith(element, paramsForReplace);
	}

	if (!mSubstitutionErrors.isEmpty()) {
		return {};
	}

	auto result = mText;
	for (auto it = mOrder.rbegin(), end = mOrder.rend(); it != end; ++it) {
		auto value = paramsForReplace.find(*it);
		auto declaredParam = mParameters.find(*it).value();
		if (value == paramsForReplace.end()) {
			if (!declaredParam.mHasDefaultValue) {
				addSubstitutionError(
				QObject::tr("The parameter %1 of template %2 has no default value and was not explicitly specified by the user")
						.arg(*it, mId), templateUsage.lineNumber(), TemplateSubstitutionErrorCode::MissingReqiuredParam);
				continue;
			}
			substitute(*it, declaredParam.mDefaultValue, result);
			continue;
		}
		substitute(*it, value.value(), result);
	}
	return result;
}

void XmlTemplate::substitute(const QString& name, const QString& value, QString &result)
{

	result.replace("#{" + name + "}", value);
}

void XmlTemplate::addDeclarationError(const QString& message, int lineNumber, TemplateParseErrorCode code)
{
	Q_UNUSED(code)
	QLOG_ERROR() << message + " " + QString("line %1 relative template declaration").arg(lineNumber);
	mDeclarationErrors << message + " " + QObject::tr("line %1 relative template declaration").arg(lineNumber);
}

void XmlTemplate::addSubstitutionError(const QString& message, int lineNumber, TemplateSubstitutionErrorCode code)
{
	Q_UNUSED(code)
	QLOG_ERROR() << message + " " + QString("line relative template body %1").arg(lineNumber);
	mSubstitutionErrors << message + " " + QObject::tr("line %1 relative body of template %2")
							.arg(QString::number(lineNumber), mId);
}
