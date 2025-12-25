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
#include <QXmlStreamReader>

using namespace utils;

QDomDocument xmlUtils::loadDocument(const QString &fileName, QString *errorMessage, int *errorLine, int *errorColumn)
{
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly)) {
		qWarning() << "Cannot open" << fileName << "for reading";
		return {};
	}

	QDomDocument doc;
	if (!doc.setContent(&file, false, errorMessage, errorLine, errorColumn)) {
		file.close();
		return {};
	}

	file.close();
	return doc;
}

QString xmlUtils::ensureXmlFieldsOrder(const QString &xmlInput)
{
	if (xmlInput.isEmpty()) {
		return {};
	}

	QXmlStreamReader reader(xmlInput);
	QString result;
	QXmlStreamWriter writer(&result);
	writer.setAutoFormatting(false);
	writer.setAutoFormattingIndent(4);
	bool first = true;

	while (!reader.atEnd() && !reader.hasError()) {
		auto token = reader.readNext();

		switch (token) {
		case QXmlStreamReader::StartElement: {
			writer.writeStartElement(reader.name().toString());
			if (first) {
				writer.setAutoFormatting(true);
				first = false;
			}
			QMap<QString, QString> sortedAttrs;
			for (auto &&attr : reader.attributes()) {
				sortedAttrs.insert(attr.name().toString(), attr.value().toString());
			}

			for (auto it = sortedAttrs.constBegin(); it != sortedAttrs.constEnd(); ++it) {
				writer.writeAttribute(it.key(), it.value());
			}
			break;
		}

		case QXmlStreamReader::EndElement:
			writer.writeEndElement();
			break;

		case QXmlStreamReader::Characters:
			if (!reader.isWhitespace()) {
				writer.writeCharacters(reader.text().toString());
			}
			break;

		case QXmlStreamReader::Comment:
			writer.writeComment(reader.text().toString());
			break;

		default:
			break;
		}
	}

	if (reader.hasError()) {
		return xmlInput;
	}

	return result;
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
