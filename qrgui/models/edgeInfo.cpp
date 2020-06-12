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

#include "edgeInfo.h"
#include <QMimeData>
#include <qrkernel/settingsManager.h>
#include <qrkernel/definitions.h>
#include <qrgui/plugins/toolPluginInterface/usedInterfaces/logicalModelAssistInterface.h>
#include <qrgui/plugins/toolPluginInterface/usedInterfaces/graphicalModelAssistInterface.h>

using namespace qReal;

EdgeInfo::EdgeInfo(const Id &graphicalId
		, const Id &logicalId
		, LogicalModelAssistInterface &logicalModel
		, GraphicalModelAssistInterface &graphicalModel)
	: EdgeInfo(graphicalId, logicalId, logicalModel.parent(logicalId), graphicalModel.parent(graphicalId)
			, graphicalModel.fromPort(graphicalId), graphicalModel.toPort(graphicalId)
			, graphicalModel.configuration(graphicalId), static_cast<int>(
					stringToShape(graphicalModel.graphicalRepoApi().property(graphicalId, "linkShape").toString())))
{
	setSrcId(graphicalModel.from(graphicalId));
	setDstId(graphicalModel.to(graphicalId));

	const QMap<QString, QVariant> properties = graphicalModel.properties(logicalId);
	for (const QString &property : properties.keys()) {
		if (property != "from" && property != "to") {
			mInfo.setLogicalProperty(property, properties[property]);
		}
	}

	mInfo.setGraphicalProperty("position", graphicalModel.position(graphicalId));
}

EdgeInfo::EdgeInfo(const Id &id
		, const Id &logicalId
		, const Id &logicalParent
		, const Id &graphicalParent
		, qreal portFrom
		, qreal portTo
		, const QPolygon &configuration
		, int shapeType
		)
	: mInfo(id, logicalId, logicalParent, graphicalParent, {}, {}, Id(), true)
	, mPortFrom(portFrom)
	, mPortTo(portTo)
	, mConfiguration(configuration)
	, mShapeType(shapeType)
{
}

QString EdgeInfo::shapeToString(LinkShape shapeType)
{
	switch (shapeType) {
	case LinkShape::broken:
		return "broken";
	case LinkShape::curve:
		return "curve";
	case LinkShape::square:
		return "square";
	}

	return "broken";
}

LinkShape EdgeInfo::stringToShape(const QString &string)
{
	if (string == "broken") {
		return LinkShape::broken;
	} else if (string == "square") {
		return LinkShape::square;
	} else if (string == "curve") {
		return LinkShape::curve;
	} else {
		return static_cast<LinkShape>(SettingsManager::value("LineType").toInt());
	}
}

QDataStream &EdgeInfo::serialize(QDataStream &out) const
{
	return mInfo.serialize(out) << mSrcId << mDstId << mPortFrom << mPortTo << mConfiguration << mShapeType;
}

QDataStream &EdgeInfo::deserialize(QDataStream &in)
{
	return mInfo.deserialize(in) >> mSrcId >> mDstId >> mPortFrom >> mPortTo >> mConfiguration >> mShapeType;
}

bool EdgeInfo::equals(const EdgeInfo &other) const
{
	const EdgeInfo *otherEdge = dynamic_cast<const EdgeInfo *>(&other);
	if (!otherEdge) {
		return false;
	}

	return mInfo.equals(other.getInfo())
			&& mSrcId == otherEdge->mSrcId
			&& mDstId == otherEdge->mDstId
			&& mPortFrom == otherEdge->mPortFrom
			&& mPortTo == otherEdge->mPortTo
			&& mConfiguration == otherEdge->mConfiguration;
}

QMimeData *EdgeInfo::mimeData() const
{
	return mInfo.mimeData();
}

ElementInfo EdgeInfo::fromMimeData(const QMimeData *mimeData)
{
	auto data = mimeData->data(DEFAULT_MIME_TYPE);
	QDataStream inStream(&data, QIODevice::ReadOnly);

	ElementInfo result;
	inStream >> result;
	return result;
}

bool EdgeInfo::isEdge() const
{
	return mInfo.isEdge();
}

Id EdgeInfo::parent() const
{
	return mInfo.parent();
}

QString EdgeInfo::name() const
{
	return mInfo.name();
}

QPointF EdgeInfo::position() const
{
	return mInfo.position();
}

Id EdgeInfo::newId()
{
	return mInfo.newId();
}

Id EdgeInfo::newLogicalId()
{
	return mInfo.newLogicalId();
}

void EdgeInfo::setPos(const QPointF &position)
{
	return mInfo.setPos(position);
}

const Id &EdgeInfo::explosionTarget() const
{
	return mInfo.explosionTarget();
}

const Id &EdgeInfo::id() const
{
	return mInfo.id();
}

const Id &EdgeInfo::logicalId() const
{
	return mInfo.logicalId();
}

void EdgeInfo::setLogicalId(const Id &id)
{
	mInfo.setLogicalId(id);
}

const Id &EdgeInfo::logicalParent() const
{
	return mInfo.logicalParent();
}

void EdgeInfo::setLogicalParent(const Id &parent)
{
	mInfo.setLogicalParent(parent);
}

const Id &EdgeInfo::graphicalParent() const
{
	return mInfo.graphicalParent();
}

void EdgeInfo::setGraphicalParent(const Id &parent)
{
	mInfo.setGraphicalParent(parent);
}

const QList<QString> EdgeInfo::logicalProperties() const
{
	return mInfo.logicalProperties();
}

QVariant EdgeInfo::logicalProperty(const QString &propertyName) const
{
	return mInfo.logicalProperty(propertyName);
}

void EdgeInfo::setLogicalProperty(const QString &propertyName, const QVariant &propertyValue)
{
	mInfo.setLogicalProperty(propertyName, propertyValue);
}

void EdgeInfo::setAllLogicalProperties(const QMap<QString, QVariant> &logicalProperties)
{
	mInfo.setAllGraphicalProperties(logicalProperties);
}

const QList<QString> EdgeInfo::graphicalProperties() const
{
	return mInfo.graphicalProperties();
}

QVariant EdgeInfo::graphicalProperty(const QString &propertyName) const
{
	return mInfo.graphicalProperty(propertyName);
}

void EdgeInfo::setGraphicalProperty(const QString &propertyName, const QVariant &propertyValue)
{
	return mInfo.setGraphicalProperty(propertyName, propertyValue);
}

void EdgeInfo::setAllGraphicalProperties(const QMap<QString, QVariant> &graphicalProperties)
{
	mInfo.setAllLogicalProperties(graphicalProperties);
}

QDataStream &operator<< (QDataStream &out, const EdgeInfo &data)
{
	return data.serialize(out);
}

QDataStream &operator>> (QDataStream &in, EdgeInfo &data)
{
	return data.deserialize(in);
}

bool operator== (const EdgeInfo &first, const EdgeInfo &second)
{
	return first.equals(second);
}

ElementInfo EdgeInfo::convertToSimpleInfo() const
{
	ElementInfo element(mInfo);
	element.setGraphicalProperty("configuration", mConfiguration);
	element.setGraphicalProperty("linkShape", mShapeType);

	element.setGraphicalProperty("from", mSrcId.toVariant());
	element.setGraphicalProperty("to", mDstId.toVariant());

	element.setGraphicalProperty("fromPort", mPortFrom);
	element.setGraphicalProperty("toPort", mPortTo);

	return element;
}

const Id &EdgeInfo::srcId() const
{
	return mSrcId;
}

const Id &EdgeInfo::dstId() const
{
	return mDstId;
}

void EdgeInfo::setSrcId(const Id &id)
{
	mSrcId = id;
}

void EdgeInfo::setDstId(const Id &id)
{
	mDstId = id;
}

ElementInfo EdgeInfo::getInfo() const
{
	return mInfo;
}
