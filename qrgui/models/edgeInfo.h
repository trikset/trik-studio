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

#pragma once

#include <QtGui/QPolygon>

#include <metaMetaModel/linkShape.h>

#include "modelsDeclSpec.h"
#include "elementInfo.h"

namespace qReal {

/// Container for convenient storing edge element data for passing it into methods with just one parameter.
class QRGUI_MODELS_EXPORT EdgeInfo
{
public:
	EdgeInfo() = default;

	EdgeInfo(const Id &graphicalId
			, const Id &logicalId
			, LogicalModelAssistInterface &logicalModel
			, GraphicalModelAssistInterface &graphicalModel);

	EdgeInfo(const Id &id
			, const Id &logicalId
			, const Id &logicalParent
			, const Id &graphicalParent
			, qreal portFrom
			, qreal portTo
			, const QPolygon &configuration
			, int shapeType
	);

	QDataStream &serialize(QDataStream &out) const;

	QDataStream &deserialize(QDataStream &in);

	bool equals(const EdgeInfo &other) const;

	QMimeData *mimeData() const;

	static ElementInfo fromMimeData(const QMimeData *mimeData);

	bool isEdge() const;

	Id parent() const;

	QString name() const;

	QPointF position() const;

	Id newId();

	Id newLogicalId();

	void setPos(const QPointF &position);

	const Id &explosionTarget() const;

	const Id &id() const;

	const Id &logicalId() const;

	void setLogicalId(const Id &id);

	const Id &logicalParent() const;

	void setLogicalParent(const Id &parent);

	const Id &graphicalParent() const;

	void setGraphicalParent(const Id &parent);

	const QList<QString> logicalProperties() const;

	QVariant logicalProperty(const QString &propertyName) const;

	void setLogicalProperty(const QString &propertyName, const QVariant &propertyValue);

	void setAllLogicalProperties(const QMap<QString, QVariant> &logicalProperties);

	const QList<QString> graphicalProperties() const;

	QVariant graphicalProperty(const QString &propertyName) const;

	void setGraphicalProperty(const QString &propertyName, const QVariant &propertyValue);

	void setAllGraphicalProperties(const QMap<QString, QVariant> &graphicalProperties);


	/// @return String representation of shapeType
	static QString shapeToString(LinkShape shapeType);

	/// @return LinkShape represented by string; return linkShape::unset if string is incorrect
	static LinkShape stringToShape(const QString &string);

	/// Places fields into graphical and logical properties map, returns new ElementInfo instance.
	ElementInfo convertToSimpleInfo() const;

	/// Returns Id of a source of an edge.
	const Id &srcId() const;

	/// Returns Id of a destination of an edge.
	const Id &dstId() const;

	/// Sets Id of a source of an edge.
	void setSrcId(const Id &id);

	/// Sets Id of a destination of an edge.
	void setDstId(const Id &id);

	/// Gets element info of an edge.
	ElementInfo getInfo() const;

private:
	ElementInfo mInfo {true};
	Id mSrcId;
	Id mDstId;

	qreal mPortFrom = 0.0;
	qreal mPortTo = 0.0;

	QPolygon mConfiguration;
	int mShapeType = 0;
};

}

QRGUI_MODELS_EXPORT QDataStream &operator<< (QDataStream &out, const qReal::EdgeInfo &data);
QRGUI_MODELS_EXPORT QDataStream &operator>> (QDataStream &in, qReal::EdgeInfo &data);
QRGUI_MODELS_EXPORT bool operator== (const qReal::EdgeInfo &first, const qReal::EdgeInfo &second);
