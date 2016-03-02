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

#pragma once

#include <qrkernel/ids.h>
#include <qrgraph/node.h>

#include "metaMetaModel/labelProperties.h"

namespace qReal {

class Metamodel;
class NodeElementType;
class EdgeElementType;

typedef QPair<QPair<qReal::Id, qReal::Id>, QPair<bool, qReal::Id> > PossibleEdge;
typedef QPair<QPair<QString, QString>, QPair<bool, QString> > StringPossibleEdge;

typedef QPair<bool, qReal::Id> PossibleEdgeType;
typedef QPair<qReal::Id, qReal::Id> ElementPair;

/// Describes type of elements that can be instantiated on scene.
/// The metamodel of some visual language is a number of such types associated each with other with some relations
/// (for example relation of generalization, relation of explosion, relation of containment, etc).
/// Metamodel thus is ordered multigraph where nodes are types of elements.
/// This fact is noted with inheriting ElementType from qrgraph::Node.
class ElementType : public qrgraph::Node
{
public:
	/// Casts this instance to node element type. If this is not node then assertion fault will be generated.
	const NodeElementType &toNode() const;

	/// Casts this instance to edge element type. If this is not edge then assertion fault will be generated.
	const EdgeElementType &toEdge() const;

	/// Returns true if this instance describes node element type.
	virtual bool isNode() const = 0;

	/// Returns the internal name if this element. This name can be used for element() part of qReal::Id and should
	/// not be shown to user.
	virtual QString name() const = 0;

	/// Returns the localized name assigned to instances of this type by default.
	virtual QString friendlyName() const = 0;

	/// Returns localized string describing this type. This string can be shown to user.
	virtual QString description() const = 0;

	/// Returns the internal name of the diagram this element belongs to.
	/// This name can be used for diagram() part of qReal::Id and should not be shown to user.
	virtual QString diagram() const = 0;

	/// Update shape of an element. Does nothing in case of generated editors, used by metamodel interpreter.
	/// @todo: Get rid of this shit now!
	virtual void updateRendererContent(const QString &shape);

	/// Returns a list of all labels on instances of this type.
	virtual QList<LabelProperties> labels() const = 0;

	/// Returns a list of custom logical properties of this element.
	virtual QStringList propertyNames() const = 0;

	/// Returns a lost of reference properties of this element.
	/// Reference properties are those whoose value is another element.
	virtual QStringList referenceProperties() const = 0;

	/// Returns a type name of a property with the given \a name.
	virtual QString propertyType(const QString &name) const = 0;

	/// Returns a string representation of a value assigned to \a property by default.
	virtual QString propertyDefaultValue(const QString &property) const = 0;

	/// Returns true if this element type generalizes \a parent. Distant
	virtual bool isParent(const ElementType &parent) const = 0;

	/// Returns localized string describing some \a property. This string can be shown to user.
	virtual QString propertyDescription(const QString &property) const = 0;

	/// Returns localized name of some \a property. The resulting string can be shown to user.
	virtual QString propertyDisplayedName(const QString &property) const = 0;

protected:
	/// @param metamodel Metamodel that owns this element.
	explicit ElementType(Metamodel &metamodel);
};

}
