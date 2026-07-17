/* Copyright 2007-2016 QReal Research Group, Yurii Litvinov
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

#include "graphicType.h"

#include <QList>

namespace qrmc {
class MetaCompiler;

class NodeType : public GraphicType
{
public:
	NodeType(const Diagram &diagram, const qrRepo::LogicalRepoApi &api, const qReal::Id &id,
		const QString &targetDirectory);
	Type *clone() const override;
	~NodeType() override;

	bool init(const QString &context) override;

	void print() override;

	QString generateIsNodeOrEdge(const QString &lineTemplate) const override;
	QString generateNodeClass(const QString &classTemplate) override;
	QString generateEdgeClass(const QString &classTemplate) const override;
	QString generateResourceLine(const QString &resourceTemplate) const override;

private:
	void generateContainerStuff(QString &classTemplate) const;
	void generateContextMenuItems(QString &classTemplate, MetaCompiler *compiler) const;
	QString loadBoolProperty(const qReal::Id &id, const QString &property) const;
	QString loadIntProperty(const qReal::Id &id, const QString &property) const;
	QString loadIntVectorProperty(const qReal::Id &id, const QString &property) const;
};
}
