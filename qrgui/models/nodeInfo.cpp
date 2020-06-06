/* Copyright 2015-2016 Dmitry Mordvinov
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

#include "nodeInfo.h"

#include <qrkernel/definitions.h>
#include <qrgui/plugins/toolPluginInterface/usedInterfaces/logicalModelAssistInterface.h>
#include <qrgui/plugins/toolPluginInterface/usedInterfaces/graphicalModelAssistInterface.h>

using namespace qReal;

NodeInfo::NodeInfo()
{
}

NodeInfo::NodeInfo(const Id &graphicalId
		, const Id &logicalId
		, LogicalModelAssistInterface &logicalModel
		, GraphicalModelAssistInterface &graphicalModel)
	: NodeInfo(graphicalId, logicalId, logicalModel.parent(logicalId), graphicalModel.parent(graphicalId)
			,graphicalModel.properties(logicalId) , graphicalModel.properties(graphicalId)
			, logicalModel.logicalRepoApi().outgoingExplosion(logicalId))
{
	setGraphicalProperty("links", IdListHelper::toVariant(IdList()));
	setGraphicalProperty("position", graphicalModel.position(graphicalId));
}

NodeInfo::NodeInfo(const Id &id
		, const Id &logicalId
		, const Id &logicalParent
		, const Id &graphicalParent
		, const QMap<QString, QVariant> &logicalProperties
		, const QMap<QString, QVariant> &graphicalProperties
		, const Id &explosionTarget)
	: mInfo(id, logicalId, graphicalParent, logicalParent
			, logicalProperties, graphicalProperties, explosionTarget, false)
{
}

QDataStream &NodeInfo::serialize(QDataStream &out) const
{
	return mInfo.serialize(out);
}

QDataStream &NodeInfo::deserialize(QDataStream &in)
{
	return mInfo.deserialize(in);
}


QMimeData *NodeInfo::mimeData() const
{
	return mInfo.mimeData();
}

ElementInfo NodeInfo::fromMimeData(const QMimeData *mimeData)
{
	auto data = mimeData->data(DEFAULT_MIME_TYPE);
	QDataStream inStream(&data, QIODevice::ReadOnly);

	ElementInfo result;
	inStream >> result;
	return result;
}

bool NodeInfo::isEdge() const
{
	return mInfo.isEdge();
}

Id NodeInfo::parent() const
{
	return mInfo.parent();
}

QString NodeInfo::name() const
{
	return mInfo.name();
}

QPointF NodeInfo::position() const
{
	return mInfo.position();
}

Id NodeInfo::newId()
{
	return mInfo.newId();
}

Id NodeInfo::newLogicalId()
{
	return mInfo.newLogicalId();
}

void NodeInfo::setPos(const QPointF &position)
{
	return mInfo.setPos(position);
}

const Id &NodeInfo::explosionTarget() const
{
	return mInfo.explosionTarget();
}

const Id &NodeInfo::id() const
{
	return mInfo.id();
}

const Id &NodeInfo::logicalId() const
{
	return mInfo.logicalId();
}

void NodeInfo::setLogicalId(const Id &id)
{
	mInfo.setLogicalId(id);
}

const Id &NodeInfo::logicalParent() const
{
	return mInfo.logicalParent();
}

void NodeInfo::setLogicalParent(const Id &parent)
{
	mInfo.setLogicalParent(parent);
}

const Id &NodeInfo::graphicalParent() const
{
	return mInfo.graphicalParent();
}

void NodeInfo::setGraphicalParent(const Id &parent)
{
	mInfo.setGraphicalParent(parent);
}

const QList<QString> NodeInfo::logicalProperties() const
{
	return mInfo.logicalProperties();
}

QVariant NodeInfo::logicalProperty(const QString &propertyName) const
{
	return mInfo.logicalProperty(propertyName);
}

void NodeInfo::setLogicalProperty(const QString &propertyName, const QVariant &propertyValue)
{
	mInfo.setLogicalProperty(propertyName, propertyValue);
}

void NodeInfo::setAllLogicalProperties(const QMap<QString, QVariant> &logicalProperties)
{
	mInfo.setAllGraphicalProperties(logicalProperties);
}

const QList<QString> NodeInfo::graphicalProperties() const
{
	return mInfo.graphicalProperties();
}

QVariant NodeInfo::graphicalProperty(const QString &propertyName) const
{
	return mInfo.graphicalProperty(propertyName);
}

void NodeInfo::setGraphicalProperty(const QString &propertyName, const QVariant &propertyValue)
{
	return mInfo.setGraphicalProperty(propertyName, propertyValue);
}

void NodeInfo::setAllGraphicalProperties(const QMap<QString, QVariant> &graphicalProperties)
{
	mInfo.setAllLogicalProperties(graphicalProperties);
}

ElementInfo NodeInfo::getInfo() const
{
	return mInfo;
}

QDataStream &operator<< (QDataStream &out, const NodeInfo &data)
{
	return data.serialize(out);
}

QDataStream &operator>> (QDataStream &in, NodeInfo &data)
{
	return data.deserialize(in);
}

bool operator== (const NodeInfo &first, const NodeInfo &second)
{
	return first.getInfo().equals(second.getInfo());
}
