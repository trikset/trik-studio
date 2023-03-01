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

#include <QtCore/QPoint>
#include <QtCore/QList>
#include <QtCore/QPair>
#include <QtGui/QPainterPath>
#include <QtGui/QPolygon>
#include <QtWidgets/QGraphicsPathItem>
#include <QtXml/QDomDocument>

#include "twoDModel/engine/model/image.h"
#include "twoDModel/twoDModelDeclSpec.h"

class QGraphicsItem;

namespace qReal {
class ErrorReporterInterface;
}

namespace twoDModel {
namespace items {
class WallItem;
class CubeItem;
class BallItem;
class MovableItem;
class ColorFieldItem;
class ImageItem;
class RegionItem;
class CommentItem;
}

namespace model {

class RobotModel;

class TWO_D_MODEL_EXPORT WorldModel : public QObject
{
	Q_OBJECT

public:
	WorldModel();
	~WorldModel();

	void init(qReal::ErrorReporterInterface &errorReporter);

	/// Returns a number of pixels in 1 cm. This value may change, pixelsInCmChanged() signal will then be emitted.
	qreal pixelsInCm() const;

	/// Measures the distance between robot and wall
	Q_INVOKABLE int rangeReading(const QPointF &position, qreal direction, int maxDistance, qreal maxAngle) const;

	/// Measures the distance between robot and solid object for each angle in maxAngle and maxDistance scanning region
	Q_INVOKABLE QVector<int> lidarReading(const QPointF &position, qreal direction
			, int maxDistance, qreal maxAngle) const;

	/// Returns area which is seen by sonar sensor.
	QPainterPath rangeSensorScanningRegion(const QPointF &position, qreal direction,
			QPair<qreal,int> angleAndRange) const;

	/// Returns area which is seen by sonar sensor with zero rotation.
	QPainterPath rangeSensorScanningRegion(const QPointF &position, QPair<qreal,int> angleAndRange) const;

	/// Checks if the given path intersects some wall.
	bool checkCollision(const QPainterPath &path) const;

	/// Returns a set of walls in the world model. Result is mapping of wall ids to walls themselves.
	const QMap<QString, QSharedPointer<items::WallItem>> &walls() const;

	/// Returns a set of all movable items in the world model. Result is mapping of ids to items themselves.
	const QMap<QString, QSharedPointer<items::MovableItem>> &movables() const;

	/// Returns a set of color field items in the world model. Result is mapping of field ids to fields themselves.
	const QMap<QString, QSharedPointer<items::ColorFieldItem>> &colorFields() const;

	/// Returns a set of region items in the world model. Result is mapping of field ids to regions themselves.
	const QMap<QString, QSharedPointer<items::RegionItem>> &regions() const;

	/// Returns a list of image items in the world model.
	const QMap<QString, QSharedPointer<items::ImageItem>> &imageItems() const;

	/// Returns a set of comments in the world model. Result is mapping of comments ids to comments themselves.
	const QMap<QString, QSharedPointer<items::CommentItem>> &commentItems() const;

	/// Returns a list of trace items on the floor.
	const QList<QSharedPointer<QGraphicsPathItem>> &trace() const;

	/// Appends \a wall into world model.
	void addWall(const QSharedPointer<items::WallItem> &wall);

	/// Removes \a wall from the world model.
	void removeWall(QSharedPointer<items::WallItem> wall);

	/// Appends \a movable into world model.
	void addMovable(const QSharedPointer<items::MovableItem> &movable);

	/// Removes \a movable from the world model.
	void removeMovable(QSharedPointer<items::MovableItem> movable);

	/// Appends \a comment into world model.
	void addComment(const QSharedPointer<items::CommentItem> &comment);

	/// Removes \a comment from the world model.
	void removeComment(QSharedPointer<items::CommentItem> comment);

	/// Appends colored item \a colorField into the world model.
	void addColorField(const QSharedPointer<items::ColorFieldItem> &colorField);

	/// Removes colored item \a colorField form the world model.
	void removeColorField(QSharedPointer<items::ColorFieldItem> colorField);

	/// Adds image item into 2D model.
	void addImageItem(const QSharedPointer<items::ImageItem> &imageItem);

	/// Removes image item from 2D model.
	void removeImageItem(QSharedPointer<items::ImageItem> imageItem);

	/// Sets using robot model
	void setRobotModel(RobotModel * robotModel);

	/// Removes all walls, colored items, regions and robot traces from the world model.
	void clear();

	/// Appends one more segment of the given to the robot`s trace.
	void appendRobotTrace(const QPen &pen, const QPointF &begin, const QPointF &end);

	/// Prepends full path to the robot`s trace.
	void prependRobotTrace(const QPen &pen, const QBrush &brush, const QPainterPath &path);

	/// Removes all the segments from the current robot`s trace.
	void clearRobotTrace();

	/// Saves world to XML.
	QDomElement serializeWorld(QDomElement &parent) const;

	/// Saves blobs to XML.
	QDomElement serializeBlobs(QDomElement &parent) const;

	/// Saves all information about the item with \a id into XML element. Item then can be recreated from
	/// this specification using createElement(QDomElement) method.
	QDomElement serializeItem(const QString &id) const;

	/// Restores world model XML specification.
	/// @param element Root element of the world model XML specification.
	/// @param blobs Root element of the blobs XML specification.
	void deserialize(const QDomElement &element, const QDomElement &blobs);

	/// Searches on the scene item with the given id. Returns nullptr if not found.
	QSharedPointer<QGraphicsObject> findId(const QString &id) const;

	/// Creates element from serialized XML specification.
	void createElement(const QDomElement &element);

	/// Creates wall item described by \a element in the world model.
	void createWall(const QDomElement &element);

	/// Creates movabel item described by \a element in the world model.
	void createMovable(const QDomElement &element);

	/// Creates cube item described by \a element in the world model.
	QSharedPointer<items::CubeItem> createCube(const QDomElement &element);

	/// Creates ball item described by \a element in the world model.
	QSharedPointer<items::BallItem> createBall(const QDomElement &element);

	/// Creates line colored item described by \a element in the world model.
	void createLine(const QDomElement &element);

	/// Creates rectangular colored item described by \a element in the world model.
	void createRectangle(const QDomElement &element);

	/// Creates ellipse colored item described by \a element in the world model.
	void createEllipse(const QDomElement &element);

	/// Creates cubic bezier colored item described by \a element in the world model.
	void createCubicBezier(const QDomElement &element);

	/// Creates stylus colored item described by \a element in the world model.
	void createStylus(const QDomElement &element);

	/// Creates comment item described by \a element in the world model.
	void createComment(const QDomElement &element);

	/// Creates image item described by \a element in the world model.
	QSharedPointer<items::ImageItem> createImageItem(const QDomElement &element, bool background=false);

	/// Creates region item described by \a element in the world model.
	void createRegion(const QDomElement &element);

	/// Removes item with the \a id from the world model.
	void removeItem(const QString &id);

	qReal::ErrorReporterInterface* errorReporter();

signals:
	/// Emitted when current metrics system conversion constant has changed.
	void pixelsInCmChanged(qreal newValue);

	/// Emitted each time when model is appended with some new wall.
	void wallAdded(const QSharedPointer<items::WallItem> &item);

	/// Emitted each time when model is appended with some new movable item.
	void movableAdded(const QSharedPointer<items::MovableItem> &item);

	/// Emitted each time when model is appended with some new color field item.
	void commentAdded(const QSharedPointer<items::CommentItem> &item);

	/// Emitted each time when model is appended with some new color field item.
	void colorItemAdded(const QSharedPointer<items::ColorFieldItem> &item);

	/// Emitted each time when model is appended with some new color field item.
	void imageItemAdded(const QSharedPointer<items::ImageItem> &item);

	/// Emitted each time when model is appended with some new item.
	void regionItemAdded(const QSharedPointer<items::RegionItem> &item);

	/// Emitted each time when model is appended with some new item.
	void traceItemAddedOrChanged(const QSharedPointer<QGraphicsPathItem> &item, bool justChanged);

	/// Emitted each time when some item was removed from the 2D model world.
	void itemRemoved(const QSharedPointer<QGraphicsItem> &item);

	/// Emitted when robot trace is non-empty any more or was cleared from the floor.
	void robotTraceAppearedOrDisappeared(bool appeared);

	/// Emitted when blobs information changed.
	void blobsChanged();

	/// Emitted each time when imageItem with background created.
	void backgroundImageItemAdded(items::ImageItem *item);

private:
	/// Returns true if ray intersects some wall.
	bool checkRangeDistance(const int distance, const QPointF &position
			, const qreal direction, const qreal scanningAngle, const QPainterPath &wallPath) const;
	QPainterPath buildSolidItemsPath() const;

	void serializeBackground(QDomElement &background, const QRect &rect, const Image * const img) const;
	QRectF deserializeRect(const QString &string) const;

	QMap<QString, QSharedPointer<items::WallItem>> mWalls;
	QMap<QString, QSharedPointer<items::MovableItem>> mMovables;
	QMap<QString, QSharedPointer<items::ColorFieldItem>> mColorFields;
	QMap<QString, QSharedPointer<items::ImageItem>> mImageItems;
	QMap<QString, QSharedPointer<items::RegionItem>> mRegions;
	QMap<QString, QSharedPointer<model::Image>> mImages;
	QMap<QString, QSharedPointer<items::CommentItem>> mComments;
	RobotModel * mRobotModel {}; // Doesn't take ownership
	QMap<QString, int> mOrder;
	QList<QSharedPointer<QGraphicsPathItem>> mRobotTrace;
	QRect mBackgroundRect;
	QScopedPointer<QDomDocument> mXmlFactory;
	qReal::ErrorReporterInterface *mErrorReporter;  // Doesn`t take ownership.
};

}
}

Q_DECLARE_METATYPE(QGraphicsPathItem *)
