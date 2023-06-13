/* Copyright 2007-2015 QReal Research Group
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

#include "xmlUtils.h"

#include <QtCore/QFile>
#include <QtCore/QDebug>

using namespace utils;

QDomDocument xmlUtils::loadDocument(const QString &fileName, QString *errorMessage, int *errorLine, int *errorColumn)
{
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly)) {
		qWarning() << "Cannot open" << fileName << "for reading";
		return QDomDocument();
	}

	QDomDocument doc;
	if (!doc.setContent(&file, false, errorMessage, errorLine, errorColumn)) {
		file.close();
		return QDomDocument();
	}

	file.close();
	return doc;
}

QDomDocument xmlUtils::loadDocumentWithConversion(const QString &loadFileName
		, QString *errorMessage, int *errorLine, int *errorColumn)
{
	const QDomDocument save = utils::xmlUtils::loadDocument(loadFileName, errorMessage, errorLine, errorColumn);
	if (errorMessage && !errorMessage->isEmpty()) {
		return save;
	}

	QDomElement root = save.firstChildElement("root");

	QDomElement oldRobot = root.firstChildElement("robots").firstChildElement("robot");
	if (oldRobot.hasAttribute("position") || oldRobot.hasAttribute("direction")
			|| !oldRobot.firstChildElement("startPosition").isNull()) {
		QDomElement world = root.firstChildElement("world");
		if (world.isNull()) {
			world = root.ownerDocument().createElement("world");
			root.appendChild(world);
		}

		QDomElement robot = world.ownerDocument().createElement("robot");
		robot.setAttribute("position", oldRobot.attribute("position", "0:0"));
		robot.setAttribute("direction", oldRobot.attribute("direction", "0"));
		robot.appendChild(oldRobot.firstChildElement("startPosition"));
		world.appendChild(robot);

		oldRobot.removeAttribute("position");
		oldRobot.removeAttribute("direction");
		// start position reparented automatically
	}

	return save;
}
