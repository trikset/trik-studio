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
#include <QDomElement>

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

	QCommandLineOption patchField("f", QObject::tr("XML file with prepared 2D model field. "
							"Both world and robot configurations (position + ports) will be patched."), "field.xml");
	parser.addOption(patchField);
	QCommandLineOption patchScript("s", QObject::tr("Script file to be patched into save file."), "script.js");
	parser.addOption(patchScript);
	QCommandLineOption patchWorld("w", QObject::tr("XML file with prepared 2D model field. "
										"Only world configurations will be patched."), "field.xml");
	parser.addOption(patchWorld);

	QCommandLineOption patchWorldAndPosition("wp", QObject::tr("XML file with prepared 2D model field. "
										"Only world configurations and robot position will be patched."), "field.xml");
	parser.addOption(patchWorldAndPosition);

	QCommandLineOption putRobotOnStart("rrp", QObject::tr("Reset robot position to start position"));
	parser.addOption(putRobotOnStart);

	parser.process(app);

	const QStringList positionalArgs = parser.positionalArguments();
	if (positionalArgs.size() != 1) {
		parser.showHelp();
	}

	const auto &saveFile = positionalArgs[0];
	qrRepo::RepoApi repo(saveFile);

	// Check that from three booleans (-f/-w/--wp options) at least two of them are not true at the same time
	if (parser.isSet(patchField) + parser.isSet(patchWorld) + parser.isSet(patchWorldAndPosition) > 1) {
		return 2;
	}

	if (parser.isSet(patchField)) {
		const auto &field = parser.value(patchField);
		QFile fieldFile(field);
		if (!fieldFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
			return 1;
		}

		/// Explicitly convert to QString
		const QString &fieldContents = fieldFile.readAll();

		repo.setMetaInformation("worldModel", fieldContents);
	}

	if (parser.isSet(patchWorld)) {
		const auto &field = parser.value(patchWorld);
		QFile fieldFile(field);
		if (!fieldFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
			return 1;
		}

		QDomDocument newWorld;
		newWorld.setContent(&fieldFile);
		QDomDocument prevWorld;
		prevWorld.setContent(repo.metaInformation("worldModel").toString());

		newWorld.documentElement().replaceChild(
					prevWorld.documentElement().firstChildElement("robots"),
					newWorld.documentElement().firstChildElement("robots"));

		QString newWorldStr;
		QTextStream stream(&newWorldStr);
		newWorld.save(stream, 4);
		repo.setMetaInformation("worldModel", newWorldStr);
	}

	if (parser.isSet(patchWorldAndPosition)) {
		const auto &field = parser.value(patchWorldAndPosition);
		QFile fieldFile(field);
		if (!fieldFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
			return 1;
		}

		QDomDocument newWorld;
		newWorld.setContent(&fieldFile);
		QDomDocument prevWorld;
		prevWorld.setContent(repo.metaInformation("worldModel").toString());

		// Logic below is the same as in context menu "Load world without robot configuration..."
		// Copied from "TwoDModelWidget::loadWorldModelWithoutRobot"
		auto saveRobot = prevWorld.documentElement().firstChildElement("robots").firstChildElement("robot");
		auto currentRobot = newWorld.documentElement().firstChildElement("robots").firstChildElement("robot");

		saveRobot.replaceChild(currentRobot.firstChildElement("sensors"), saveRobot.firstChildElement("sensors"));
		saveRobot.replaceChild(currentRobot.firstChildElement("wheels"), saveRobot.firstChildElement("wheels"));
		saveRobot.setAttribute("id", currentRobot.attribute("id"));

		QString newWorldStr;
		QTextStream stream(&newWorldStr);
		newWorld.save(stream, 4);
		repo.setMetaInformation("worldModel", newWorldStr);
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

	if (parser.isSet(putRobotOnStart)) {
		QDomDocument world;
		world.setContent(repo.metaInformation("worldModel").toString());
		auto robot = world.documentElement().firstChildElement("robots").firstChildElement("robot");
		auto start = robot.firstChildElement("startPosition");
		robot.setAttribute("direction", start.attribute("direction"));
		auto x = start.attribute("x").toDouble() - 25;
		auto y = start.attribute("y").toDouble() - 25;
		robot.setAttribute("position", QString::number(x) + ":" + QString::number(y));
		repo.setMetaInformation("worldModel", world.toString(4));
	}

	if (!repo.saveAll()) {
		return -1;
	}

	return 0;
}
