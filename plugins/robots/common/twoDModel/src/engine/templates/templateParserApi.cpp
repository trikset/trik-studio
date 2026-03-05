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

#include <QsLog.h>
#include <qrgui/plugins/toolPluginInterface/usedInterfaces/errorReporterInterface.h>
#include "templateParserApi.h"
#include "details/templatesParser.h"
#include "details/templatesManager.h"
#include "details/templatesProcessor.h"
#include <QFile>
#include <qrutils/xmlUtils.h>
#include <qrkernel/platformInfo.h>

using namespace twoDModel::templates;

TemplatesParserApi::~TemplatesParserApi() = default;

TemplatesParserApi::TemplatesParserApi(qReal::ErrorReporterInterface &errorReporter)
	: mManager(new details::TemplatesManager),
	  mParser(new details::TemplatesParser),
	  mProcessor(new details::TemplatesProcessor(mManager.get())),
	  mErrorReporter(errorReporter){}

void TemplatesParserApi::parseSystemTemplates()
{
	mParser->clear();
	mManager->clearTemplates(true);
	mParser->parseAllTemplatesFromDirectory(pathsToTemplates());
	mManager->addTemplates(mParser->currentTemplates(), true);
	reportTemplateParserErrors();
}

QString TemplatesParserApi::pathsToTemplates() const
{
	return qReal::PlatformInfo::invariantSettingsPath("pathToTemplates");
}

void TemplatesParserApi::parseTemplates(const QDomDocument &templatesXml)
{
	if (templatesXml.isNull()) {
		// The user did not provide templates
		return;
	}
	mParser->clear();
	mManager->clearTemplates(false);
	mParser->parseTemplates(templatesXml);
	mManager->addTemplates(mParser->currentTemplates(), false);
	reportTemplateParserErrors();
}

QHash<QString, QDomDocument> TemplatesParserApi::generateTemplatesFromDirectory(const QString &directory)
{
	mParser->clear();
	mManager->clearTemplates(false);
	auto &&result = mParser->parseAllTemplatesFromDirectory(directory);
	mManager->addTemplates(mParser->currentTemplates(), false);
	reportTemplateParserErrors();
	return result;
}

bool TemplatesParserApi::proccessTemplates(const QDomElement &constraintsXml)
{
	if (constraintsXml.isNull()) {
		// The user did not provide constraints
		return true;
	}

	mProcessor->clear();
	mProcessor->substitute(constraintsXml);
	reportTemplateSubstitutionErrors();

	QByteArray debugPath = qgetenv("TRIK_PREPROCESSOR_XML_OUTPUT");
	if (!debugPath.isEmpty()) {
		QFile file(QString::fromUtf8(debugPath));
		if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
			// OUTPUT --- only constraints
			QTextStream stream(&file);
			stream << utils::xmlUtils::ensureXmlFieldsOrder(
					  utils::xmlUtils::getTagContent(constraintsXml, true));
		}
	}

	const auto &errors = mProcessor->errors();
	return errors.isEmpty();
}

void TemplatesParserApi::reportTemplateSubstitutionErrors()
{
	for(auto &&error : mProcessor->errors()) {
		const QString fullMessage = QObject::tr("Error while template substitution: %1").arg(error);
		QLOG_ERROR() << fullMessage;
		mErrorReporter.addError(fullMessage);
	}
}

void TemplatesParserApi::reportTemplateParserErrors()
{
	for (auto &&error : mParser->errors()) {
		const QString fullMessage = QObject::tr("Error while parsing template: %1").arg(error);
		QLOG_ERROR() << fullMessage;
		mErrorReporter.addError(fullMessage);
	}
}
