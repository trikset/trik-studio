/* Copyright 2017 QReal Research Group
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

#include <QtCore/QHash>
#include <QtCore/QString>

#include <qrkernel/ids.h>

namespace generatorBase {

/// Class that stores and produces human-readable labels for goto statements.
class ReadableLabelManager
{
public:
	/// Returns existing or generates new label for a node with given id.
	/// For new ids label starts with given prefix or uses node type.
	QString labelFor(const qReal::Id &id, const QString &prefix = "");

	/// Clears all stored labels.
	void reinit();

private:
	/// Makes given string CAPS_WITH_UNDERSCORES.
	static QString beautify(const QString &label);

	QHash<QString, int> mNodeTypesCount;
	QHash<qReal::Id, QString> mLabels;
};

}
