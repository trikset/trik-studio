/* Copyright 2015 CyberTech Labs Ltd.
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

#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QFile>

#include <qrrepo/repoApi.h>

#include <QFileInfo>

const QString description = QObject::tr("Patcher for save files, replaces world model "
		"with contents of a given XML world model");

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);
	QCoreApplication::setApplicationName("Patcher");
	QCoreApplication::setApplicationVersion("2.0");

	QCommandLineParser parser;
	parser.setApplicationDescription(description);
	parser.addHelpOption();
	parser.addVersionOption();
	parser.addPositionalArgument("save-file", QObject::tr("TRIK Studio save file to be patched."));

	QCommandLineOption patchField("f", QObject::tr("XML file with prepared 2D model field."), "field.xml");
	parser.addOption(patchField);
	QCommandLineOption patchScript("s", QObject::tr("Script file to be patched into save file."), "script.js");
	parser.addOption(patchScript);

	parser.process(app);

	const QStringList positionalArgs = parser.positionalArguments();
	if (positionalArgs.size() != 1) {
		parser.showHelp();
	}

	const auto &saveFile = positionalArgs[0];
	qrRepo::RepoApi repo(saveFile);

	if (parser.isSet(patchField)) {
		const auto &field = parser.value(patchField);
		QFile fieldFile(field);
		if (!fieldFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
			return 1;
		}

		/// Explicitly convert to QString
		const QString &fieldContents = fieldFile.readAll();

		repo.setMetaInformation("worldModel", fieldContents);
		fieldFile.close();
	}


	if (parser.isSet(patchScript)) {
		const auto &script = parser.value(patchScript);
		if (!script.isEmpty()) {
			QFile scriptFile(script);
			if (!scriptFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
				return 1;
			}

			/// Explicitly convert to QString
			const QString &scriptContent = scriptFile.readAll();
			repo.setMetaInformation("activeCode", scriptContent);

			repo.setMetaInformation("activeCodeLanguageExtension", QFileInfo(scriptFile).suffix().toLower());

			scriptFile.close();
		}
	}

	if (!repo.saveAll()) {
		return -1;
	}

	return 0;
}
