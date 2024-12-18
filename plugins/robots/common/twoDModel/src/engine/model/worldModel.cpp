/* Copyright 2012-2018 CyberTech Labs Ltd., Anna Deripaska
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

#include <QtGui/QTransform>
#include <QtCore/QStringList>
#include <QtCore/QUuid>

#include <qrgui/plugins/toolPluginInterface/usedInterfaces/errorReporterInterface.h>

#include "twoDModel/engine/model/constants.h"
#include "twoDModel/engine/model/worldModel.h"
#include "twoDModel/engine/model/image.h"
#include "twoDModel/engine/model/robotModel.h"

#include "src/engine/items/wallItem.h"
#include "src/engine/items/skittleItem.h"
#include "src/engine/items/ballItem.h"
#include "src/engine/items/colorFieldItem.h"
#include "src/engine/items/curveItem.h"
#include "src/engine/items/rectangleItem.h"
#include "src/engine/items/ellipseItem.h"
#include "src/engine/items/stylusItem.h"
#include "src/engine/items/imageItem.h"
#include "src/engine/items/commentItem.h"
#include "src/engine/items/regions/ellipseRegion.h"
#include "src/engine/items/regions/rectangularRegion.h"
#include "src/engine/items/regions/boundRegion.h"

using namespace twoDModel;
using namespace model;

//#define D2_MODEL_FRAMES_DEBUG

#ifdef D2_MODEL_FRAMES_DEBUG
#include <QtWidgets/QGraphicsPathItem>
QGraphicsPathItem *debugPath = nullptr;
#endif

WorldModel::WorldModel()
	: mXmlFactory(new QDomDocument)
	, mErrorReporter(nullptr)
{
}

WorldModel::~WorldModel() = default;

void WorldModel::init(qReal::ErrorReporterInterface &errorReporter)
{
	mErrorReporter = &errorReporter;
}

qreal WorldModel::pixelsInCm() const
{
	return twoDModel::pixelsInCm;
}

QVector<int> WorldModel::lidarReading(const QPointF &position, qreal direction, int maxDistance, qreal maxAngle) const
{
	QVector<int> res;
	const auto solidItemsPath = buildSolidItemsPath();
	auto angleAndRange = QPair<qreal, int>(1, maxDistance);
	for (int i = 0; i < maxAngle; i++) {
		auto laserPath = rangeSensorScanningRegion(position, direction + i, angleAndRange);
		const auto intersection = solidItemsPath.intersected(laserPath);
		int currentRangeInCm = INT_MAX;
		for (int j = 0; j < intersection.elementCount(); j++) {
			auto el = intersection.elementAt(j);
			if (el.type != QPainterPath::CurveToDataElement) {
				auto lenght = QLineF(position, QPointF(el)).length() / pixelsInCm();
				if (lenght < currentRangeInCm) {
					currentRangeInCm = static_cast<int>(lenght);
				}
			}
		}
		res.append(currentRangeInCm <= maxDistance ? currentRangeInCm : 0);
	}
	return res;
}

int WorldModel::rangeReading(const QPointF &position, qreal direction, int maxDistance, qreal maxAngle) const
{
	int maxRangeCms = maxDistance;
	int minRangeCms = 0;
	int currentRangeInCm = (minRangeCms + maxRangeCms) / 2;

	const QPainterPath path = buildSolidItemsPath();
	if (!checkRangeDistance(maxRangeCms, position, direction, maxAngle, path)) {
		return maxRangeCms;
	}

	for ( ; minRangeCms < maxRangeCms;
			currentRangeInCm = (minRangeCms + maxRangeCms) / 2)
	{
		if (checkRangeDistance(currentRangeInCm, position, direction, maxAngle, path)) {
			maxRangeCms = currentRangeInCm;
		} else {
			minRangeCms = currentRangeInCm + 1;
		}
	}

	return currentRangeInCm;
}

bool WorldModel::checkRangeDistance(const int distance, const QPointF &position
		, const qreal direction, const qreal scanningAngle, const QPainterPath &wallPath) const
{
	const QPainterPath rayPath = rangeSensorScanningRegion(position, direction
			, QPair<qreal,int>(scanningAngle, distance));
	return rayPath.intersects(wallPath);
}

QPainterPath WorldModel::rangeSensorScanningRegion(const QPointF &position, QPair<qreal,int> angleAndRange) const
{
	return rangeSensorScanningRegion(position, 0, angleAndRange);
}

QPainterPath WorldModel::rangeSensorScanningRegion(const QPointF &position, qreal direction
		, QPair<qreal,int> angleAndRange) const
{
	const qreal rayWidthDegrees = angleAndRange.first;
	const qreal rangeInPixels = angleAndRange.second * pixelsInCm();

	QPainterPath rayPath;
	rayPath.arcTo(QRectF(-rangeInPixels, -rangeInPixels, 2 * rangeInPixels, 2 * rangeInPixels)
			, -direction - rayWidthDegrees / 2, rayWidthDegrees);
	rayPath.closeSubpath();
	const QTransform sensorPositionTransform = QTransform().translate(position.x(), position.y());
	return sensorPositionTransform.map(rayPath);
}

bool WorldModel::checkCollision(const QPainterPath &path) const
{
#ifdef D2_MODEL_FRAMES_DEBUG
	delete debugPath;
	QPainterPath commonPath = buildSolidItemsPath();
	commonPath.addPath(path);
	debugPath = new QGraphicsPathItem(commonPath);
	debugPath->setBrush(Qt::red);
	debugPath->setPen(QPen(QColor(Qt::blue)));
	debugPath->setZValue(100);

	QGraphicsScene * const scene = mWalls.isEmpty()
			? (mColorFields.isEmpty() ? nullptr : mColorFields.first()->scene())
			: mWalls.first()->scene();

	if (scene) {
		scene->addItem(debugPath);
		scene->update();
	}
#endif

	return buildSolidItemsPath().intersects(path);
}

const QMap<QString, QSharedPointer<items::WallItem> > &WorldModel::walls() const
{
	return mWalls;
}

const QMap<QString, QSharedPointer<items::SkittleItem>> &WorldModel::skittles() const
{
	return mSkittles;
}

const QMap<QString, QSharedPointer<items::BallItem>> &WorldModel::balls() const
{
	return mBalls;
}

void WorldModel::addWall(const QSharedPointer<items::WallItem> &wall)
{
	const QString id = wall->id();
	if (mWalls.contains(id)) {
		mErrorReporter->addError(tr("Trying to add an item with a duplicate id: %1").arg(id));
		return; // probably better than having no way to delete those duplicate items on the scene
	}

	mWalls[id] = wall;
	mOrder[id] = mOrder.size();
	emit wallAdded(wall);
}

void WorldModel::removeWall(QSharedPointer<items::WallItem> wall)
{
	mWalls.remove(wall->id());
	emit itemRemoved(wall);
}

void WorldModel::addSkittle(const QSharedPointer<items::SkittleItem> &skittle)
{
	const QString id = skittle->id();
	if (mSkittles.contains(id)) {
		mErrorReporter->addError(tr("Trying to add an item with a duplicate id: %1").arg(id));
		return; // probably better than having no way to delete those duplicate items on the scene
	}

	mSkittles[id] = skittle;
	emit skittleAdded(skittle);
}

void WorldModel::removeSkittle(QSharedPointer<items::SkittleItem> skittle)
{
	mSkittles.remove(skittle->id());
	emit itemRemoved(skittle);
}

void WorldModel::addBall(const QSharedPointer<items::BallItem> &ball)
{
	const QString id = ball->id();
	if (mBalls.contains(id)) {
		mErrorReporter->addError(tr("Trying to add an item with a duplicate id: %1").arg(id));
		return; // probably better than having no way to delete those duplicate items on the scene
	}

	mBalls[id] = ball;
	emit ballAdded(ball);
}

void WorldModel::removeBall(QSharedPointer<items::BallItem> ball)
{
	mBalls.remove(ball->id());
	emit itemRemoved(ball);
}

void WorldModel::addComment(const QSharedPointer<items::CommentItem> &comment)
{
	const QString id = comment->id();
	if (mComments.contains(id)) {
		mErrorReporter->addError(tr("Trying to add an item with a duplicate id: %1").arg(id));
		return; // probably better than having no way to delete those duplicate items on the scene
	}

	mComments[id] = comment;
	emit commentAdded(comment);
}

void WorldModel::removeComment(QSharedPointer<items::CommentItem> comment)
{
	mComments.remove(comment->id());
	emit itemRemoved(comment);
}

const QMap<QString, QSharedPointer<items::ColorFieldItem>> &WorldModel::colorFields() const
{
	return mColorFields;
}

const QMap<QString, QSharedPointer<items::ImageItem>> &WorldModel::imageItems() const
{
	return mImageItems;
}

const QMap<QString, QSharedPointer<items::CommentItem> > &WorldModel::commentItems() const
{
	return mComments;
}

const QMap<QString, QSharedPointer<items::RegionItem>> &WorldModel::regions() const
{
	return mRegions;
}

const QList<QSharedPointer<QGraphicsPathItem> > &WorldModel::trace() const
{
	return mRobotTrace;
}

void WorldModel::addColorField(const QSharedPointer<items::ColorFieldItem> &colorField)
{
	const QString id = colorField->id();
	if (mColorFields.contains(id)) {
		mErrorReporter->addError(tr("Trying to add an item with a duplicate id: %1").arg(id));
		return;
	}

	mColorFields[id] = colorField;
	mOrder[id] = mOrder.size();
	emit colorItemAdded(colorField);
}

void WorldModel::removeColorField(QSharedPointer<items::ColorFieldItem> colorField)
{
	mColorFields.remove(colorField->id());
	emit itemRemoved(colorField);
}

void WorldModel::addImageItem(const QSharedPointer<items::ImageItem> &imageItem)
{
	const QString id = imageItem->id();
	if (mImageItems.contains(id)) {
		mErrorReporter->addError(tr("Trying to add an item with a duplicate id: %1").arg(id));
		return;
	}

	mImageItems[id] = imageItem;
	mImages[imageItem->image()->imageId()] = imageItem->image();
	mOrder[id] = mOrder.size();
	connect(&*imageItem, &items::ImageItem::internalImageChanged, this, &WorldModel::blobsChanged);
	connect(&*imageItem, &items::ImageItem::internalImageChanged, this, [this, id](){
			if (auto item = mImageItems.value(id))	{
				auto imageSize = item->image()->preferedSize();
				if (imageSize.height() == 0 || imageSize.width() == 0) {
					mErrorReporter->addWarning(tr("Incorrect image, please try anouther one"));
				}
			}
		});
	emit imageItemAdded(imageItem);
	emit blobsChanged();
}

void WorldModel::removeImageItem(QSharedPointer<items::ImageItem> imageItem)
{
	mImageItems.remove(imageItem->id());

	emit itemRemoved(imageItem);
	emit blobsChanged();
}

void WorldModel::setRobotModel(RobotModel * robotModel)
{
	mRobotModel = robotModel;
}

void WorldModel::clear()
{
	while (!mWalls.isEmpty()) {
		removeWall(mWalls.last());
	}

	while (!mSkittles.isEmpty()) {
		removeSkittle(mSkittles.last());
	}

	while (!mBalls.isEmpty()) {
		removeBall(mBalls.last());
	}

	while (!mColorFields.isEmpty()) {
		removeColorField(mColorFields.last());
	}

	while (!mImageItems.isEmpty()) {
		removeImageItem(mImageItems.last());
	}

	while (!mRegions.isEmpty()) {
		auto toRemove = mRegions.last();
		mRegions.remove(toRemove->id());
		emit itemRemoved(toRemove);
	}

	while (!mComments.isEmpty()) {
		auto toRemove = mComments.last();
		mComments.remove(toRemove->id());
		emit itemRemoved(toRemove);
	}

	if (mRobotModel) {
		mRobotModel->deserializeWorldModel(QDomElement());
	}

	mOrder.clear();

	mImages.clear();

	clearRobotTrace();

	emit blobsChanged();
}

void WorldModel::appendRobotTrace(const QPen &pen, const QPointF &begin, const QPointF &end)
{
	if (pen.color() == QColor(Qt::transparent)) {
		return;
	}
	if (mRobotTrace.isEmpty() || mRobotTrace.last()->pen() != pen) {
		auto path = QPainterPath(begin);
		path.lineTo(end);
		auto traceItem = QSharedPointer<QGraphicsPathItem>::create(path);
		traceItem->setPen(pen);
		traceItem->setZValue(graphicsUtils::AbstractItem::ZValue::Marker);
		emit robotTraceAppearedOrDisappeared(true);
		mRobotTrace << traceItem;
		emit traceItemAddedOrChanged(traceItem, false);
	} else {
		auto path = mRobotTrace.last()->path();
		path.moveTo(begin);
		path.lineTo(end);
		mRobotTrace.last()->setPath(path);
		emit traceItemAddedOrChanged(mRobotTrace.last(), true);
	}
}

void WorldModel::clearRobotTrace()
{
	while (!mRobotTrace.isEmpty()) {
		auto const toRemove = mRobotTrace.first();
		mRobotTrace.removeOne(toRemove);
		emit itemRemoved(toRemove);
	}

	emit robotTraceAppearedOrDisappeared(false);
}

QPainterPath WorldModel::buildSolidItemsPath() const
{
	/// @todo Maintain a cache for this.
	QPainterPath path;

	for (auto &&wall : mWalls) {
		path.addPath(wall->path());
	}

	for (auto &&skittle: mSkittles) {
		path.addPath(skittle->path());
	}

	for (auto &&ball: mBalls) {
		path.addPath(ball->path());
	}

	return path;
}

void WorldModel::serializeBackground(QDomElement &background, const QRect &rect, const Image * const img) const
{
	background.setAttribute("backgroundRect", QString("%1:%2:%3:%4").arg(
			QString::number(rect.x())
			, QString::number(rect.y())
			, QString::number(rect.width())
			, QString::number(rect.height())));

	const QString imageId = img ? img->imageId() : "";
	background.setAttribute("imageId", imageId);
}

QRectF WorldModel::deserializeRect(const QString &string) const
{
	const QStringList splittedStr = string.split(":");
	if (splittedStr.count() == 4) {
		const auto x = splittedStr[0].toDouble();
		const auto y = splittedStr[1].toDouble();
		const auto w = splittedStr[2].toDouble();
		const auto h = splittedStr[3].toDouble();
		return QRectF(x, y, w, h);
	}

	return QRectF();
}

QDomElement WorldModel::serializeWorld(QDomElement &parent) const
{
	QDomElement result = parent.ownerDocument().createElement("world");
	parent.appendChild(result);

	auto comparator = [&](const QString &id1, const QString &id2) { return mOrder[id1] < mOrder[id2]; };

	QDomElement walls = parent.ownerDocument().createElement("walls");
	result.appendChild(walls);
	QList<QString> wallsIds = mWalls.keys();
	std::sort(wallsIds.begin(), wallsIds.end(), comparator);
	for (const QString &wall : wallsIds) {
		mWalls[wall]->serialize(walls);
	}

	QDomElement skittles = parent.ownerDocument().createElement("skittles");
	result.appendChild(skittles);
	for (auto &&skittle : mSkittles) {
		skittle->serialize(skittles);
	}

	QDomElement balls = parent.ownerDocument().createElement("balls");
	result.appendChild(balls);
	for (auto &&ball : mBalls) {
		ball->serialize(balls);
	}

	QDomElement colorFields = parent.ownerDocument().createElement("colorFields");
	result.appendChild(colorFields);
	QList<QString> colorFieldsIds = mColorFields.keys();
	std::sort(colorFieldsIds.begin(), colorFieldsIds.end(), comparator);
	for (const QString &colorField : colorFieldsIds) {
		mColorFields[colorField]->serialize(colorFields);
	}

	QDomElement images = parent.ownerDocument().createElement("images");
	result.appendChild(images);
	QList<QString> imageIds = mImageItems.keys();
	std::sort(imageIds.begin(), imageIds.end(), comparator);
	for (const QString &image : imageIds) {
		mImageItems[image]->serialize(images);
	}

	QDomElement regions = parent.ownerDocument().createElement("regions");
	result.appendChild(regions);
	for (auto &&region : mRegions) {
		QDomElement regionElement = parent.ownerDocument().createElement("region");
		region->serialize(regionElement);
		regions.appendChild(regionElement);
	}

	// IKHON do we need mOrder? if yes, add mOrder to addComment
	QDomElement comments = parent.ownerDocument().createElement("comments");
	result.appendChild(comments);
	for (auto &&comment : mComments) {
		comment->serialize(comments);
	}

	if (mRobotModel) {
		mRobotModel->serializeWorldModel(parent);
	}

	// Robot trace saving is disabled

	return result;
}

QDomElement WorldModel::serializeBlobs(QDomElement &parent) const
{
	QDomElement result = parent.ownerDocument().createElement("blobs");
	QDomElement images = parent.ownerDocument().createElement("images");

	QList<QString> imageIds = mImageItems.keys();
	for (const QString &imageItem : imageIds) {
		QDomElement image = parent.ownerDocument().createElement("image");
		mImageItems[imageItem]->image()->serialize(image);
		images.appendChild(image);
	}

	if (!images.childNodes().isEmpty()) {
		result.appendChild(images);
		parent.appendChild(result);
	}

	return result;
}

QDomElement WorldModel::serializeItem(const QString &id) const
{
	if (auto item = qSharedPointerDynamicCast<graphicsUtils::AbstractItem>(findId(id))) {
		QDomElement temporalParent = mXmlFactory->createElement("temporalParent");
		return item->serialize(temporalParent);
	} else {
		return QDomElement();
	}
}

void WorldModel::deserialize(const QDomElement &element, const QDomElement &blobs)
{
	if (element.isNull()) {
		/// @todo Report error
		return;
	}

	clear();

	// blobs section
	if (!blobs.isNull()) {
		for (QDomElement imagesNode = blobs.firstChildElement("images"); !imagesNode.isNull()
				; imagesNode = imagesNode.nextSiblingElement("images")) {
			for (QDomElement imageNode = imagesNode.firstChildElement("image"); !imageNode.isNull()
					; imageNode = imageNode.nextSiblingElement("image")) {
				auto img = Image::deserialize(imageNode);
				mImages.insert(img->imageId(), img);
			}
		}
	}

	for (QDomElement backgroundNode = element.firstChildElement("background"); !backgroundNode.isNull()
			; backgroundNode = backgroundNode.nextSiblingElement("background")) {
		QString imageId = backgroundNode.attribute("imageId");
		const QRectF backgroundRect = deserializeRect(backgroundNode.attribute("backgroundRect"));
		if (backgroundRect.isNull()) {
			break;
		}
		if (!imageId.isEmpty()) {
			createImageItem(backgroundNode, true);
		} else {
			auto image = Image::deserialize(backgroundNode);
			mImages[image->imageId()] = image;
			createImageItem(backgroundNode, true);
		}
	}


	for (QDomElement traceNode = element.firstChildElement("trace"); !traceNode.isNull()
			; traceNode = traceNode.nextSiblingElement("trace")) {
		for (QDomElement segmentNode = traceNode.firstChildElement("segment"); !segmentNode.isNull()
				; segmentNode = segmentNode.nextSiblingElement("segment")) {
			const QPointF from(segmentNode.attribute("x1").toDouble(), segmentNode.attribute("y1").toDouble());
			const QPointF to(segmentNode.attribute("x2").toDouble(), segmentNode.attribute("y2").toDouble());
			QPen pen;
			pen.setColor(QColor(segmentNode.attribute("color")));
			pen.setWidth(segmentNode.attribute("width").toInt());
			appendRobotTrace(pen, from, to);
		}
	}

	for (QDomElement wallsNode = element.firstChildElement("walls"); !wallsNode.isNull()
			; wallsNode = wallsNode.nextSiblingElement("walls")) {
		for (QDomElement wallNode = wallsNode.firstChildElement("wall"); !wallNode.isNull()
				; wallNode = wallNode.nextSiblingElement("wall")) {
			createWall(wallNode);
		}
	}

	for (QDomElement skittlesNode = element.firstChildElement("skittles"); !skittlesNode.isNull()
			; skittlesNode = skittlesNode.nextSiblingElement("skittles")) {
		for (QDomElement skittleNode = skittlesNode.firstChildElement("skittle"); !skittleNode.isNull()
				; skittleNode = skittleNode.nextSiblingElement("skittle")) {
			createSkittle(skittleNode);
		}
	}

	for (QDomElement ballsNode = element.firstChildElement("balls"); !ballsNode.isNull()
			; ballsNode = ballsNode.nextSiblingElement("balls")) {
		for (QDomElement ballNode = ballsNode.firstChildElement("ball"); !ballNode.isNull()
				; ballNode = ballNode.nextSiblingElement("ball")) {
			createBall(ballNode);
		}
	}

	for (QDomElement colorFieldsNode = element.firstChildElement("colorFields"); !colorFieldsNode.isNull()
			; colorFieldsNode = colorFieldsNode.nextSiblingElement("colorFields")) {
		for (QDomElement elementNode = colorFieldsNode.firstChildElement(); !elementNode.isNull()
				; elementNode = elementNode.nextSiblingElement()) {
			createElement(elementNode);
		}
	}

	for (QDomElement commentsNode = element.firstChildElement("comments"); !commentsNode.isNull()
			; commentsNode = commentsNode.nextSiblingElement("comments")) {
		for (QDomElement elementNode = commentsNode.firstChildElement(); !elementNode.isNull()
				; elementNode = elementNode.nextSiblingElement()) {
			createComment(elementNode);
		}
	}

	for (QDomElement imagesNode = element.firstChildElement("images"); !imagesNode.isNull()
			; imagesNode = imagesNode.nextSiblingElement("images")) {
		for (QDomElement imageNode = imagesNode.firstChildElement("image"); !imageNode.isNull()
				; imageNode = imageNode.nextSiblingElement("image")) {
			if (imageNode.hasAttribute("path")) {
				auto img = Image::deserialize(imageNode);
				QString id = element.attribute("imageId");
				if (id.isNull()) {
					id = img->imageId();
					imageNode.setAttribute("imageId", id);
				}

				mImages.insert(id, img);
			}
			createImageItem(imageNode, imageNode.attribute("isBackground", "false") == "true");
		}
	}

	for (QDomElement regionNode = element.firstChildElement("regions").firstChildElement("region")
			; !regionNode.isNull()
			; regionNode = regionNode.nextSiblingElement("region"))
	{
		createRegion(regionNode);
	}

	if (mRobotModel) {
		mRobotModel->deserializeWorldModel(element);
	}
}

QSharedPointer<QGraphicsObject> WorldModel::findId(const QString &id) const
{
	if (id.isEmpty()) {
		return nullptr;
	}

	if (mWalls.contains(id)) {
		return mWalls[id];
	}

	if (mSkittles.contains(id)) {
		return mSkittles[id];
	}

	if (mBalls.contains(id)) {
		return mBalls[id];
	}

	if (mColorFields.contains(id)) {
		return mColorFields[id];
	}

	if (mImageItems.contains(id)) {
		return mImageItems[id];
	}

	if (mRegions.contains(id)) {
		return mRegions[id];
	}

	if (mComments.contains(id)) {
		return mComments[id];
	}

	return nullptr;
}

void WorldModel::createElement(const QDomElement &element)
{
	if (element.tagName() == "rectangle") {
		createRectangle(element);
	} else if (element.tagName() == "ellipse") {
		createEllipse(element);
	} else if (element.tagName() == "line") {
		createLine(element);
	} else if (element.tagName() == "cubicBezier") {
		createCubicBezier(element);
	} else if (element.tagName() == "stylus") {
		createStylus(element);
	} else if (element.tagName() == "image") {
		createImageItem(element, element.hasAttribute("background"));
	} else if (element.tagName() == "wall") {
		createWall(element);
	} else if (element.tagName() == "skittle") {
		createSkittle(element);
	} else if (element.tagName() == "ball") {
		createBall(element);
	} else if (element.tagName() == "region") {
		createRegion(element);
	} else if (element.tagName() == "comment") {
		createComment(element);
	}
}

void WorldModel::createWall(const QDomElement &element)
{
	auto wall = QSharedPointer<items::WallItem>::create(QPointF(), QPointF());
	wall->deserialize(element);
	addWall(wall);
}

void WorldModel::createSkittle(const QDomElement &element)
{
	auto skittle = QSharedPointer<items::SkittleItem>::create(QPointF());
	skittle->deserialize(element);
	addSkittle(skittle);
}

void WorldModel::createBall(const QDomElement &element)
{
	auto ball = QSharedPointer<items::BallItem>::create(QPointF());
	ball->deserialize(element);
	addBall(ball);
}

void WorldModel::createLine(const QDomElement &element)
{
	auto lineItem = QSharedPointer<items::LineItem>::create(QPointF(), QPointF());
	lineItem->deserialize(element);
	addColorField(lineItem);
}

void WorldModel::createRectangle(const QDomElement &element)
{
	auto rectangleItem = QSharedPointer<items::RectangleItem>::create(QPointF(), QPointF());
	rectangleItem->deserialize(element);
	addColorField(rectangleItem);
}

void WorldModel::createEllipse(const QDomElement &element)
{
	auto ellipseItem = QSharedPointer<items::EllipseItem>::create(QPointF(), QPointF());
	ellipseItem->deserialize(element);
	addColorField(ellipseItem);
}

void WorldModel::createCubicBezier(const QDomElement &element)
{
	auto curveItem = QSharedPointer<items::CurveItem>::create(QPointF(), QPointF());
	curveItem->deserialize(element);
	addColorField(curveItem);
}

void WorldModel::createStylus(const QDomElement &element)
{
	auto stylusItem = QSharedPointer<items::StylusItem>::create(0, 0);
	stylusItem->deserialize(element);
	addColorField(stylusItem);
}

void WorldModel::createComment(const QDomElement &element)
{
	auto commentItem = QSharedPointer<items::CommentItem>::create(QPointF(), QPointF());
	commentItem->deserialize(element);
	addComment(commentItem);
}

QSharedPointer<items::ImageItem> WorldModel::createImageItem(const QDomElement &element, bool background)
{
	auto imageId = element.attribute("imageId");
	auto image = mImages.value(imageId, nullptr);
	if (!image) {
		image.reset(new Image(imageId));
		mErrorReporter->addError(tr("Unknown image with imageId %1").arg(imageId));
	}
	auto imageItem = QSharedPointer<items::ImageItem>::create(image, QRect());
	imageItem->deserialize(element);
	imageItem->setBackgroundRole(background || element.attribute("isBackground") == "true");
	addImageItem(imageItem);

	return imageItem;
}

void WorldModel::createRegion(const QDomElement &element)
{
	const QString type = element.attribute("type", "ellipse").toLower();
	QSharedPointer<items::RegionItem> item;
	QSharedPointer<QGraphicsObject> boundItem;
	if (type == "ellipse") {
		item.reset(new items::EllipseRegion);
	} else if (type == "rectangle") {
		item.reset(new items::RectangularRegion);
	} else if (type == "bound") {
		auto id = element.attribute("boundItem");
		boundItem = findId(id);
		if (boundItem) {
			item.reset(new items::BoundRegion(*boundItem, id));
		} /// @todo: else report error
	}

	if (item) {
		item->deserialize(element);
		auto itemId = item->id();
		mRegions[itemId] = item;
		if (boundItem) {
			// Item itself will be deleted with its parent, see BoundRegion constructor.
			connect(&*item, &QObject::destroyed, this, [this, itemId]() { mRegions.remove(itemId); });
		}
		emit regionItemAdded(item);
	}
}

void WorldModel::removeItem(const QString &id)
{
	auto item = findId(id);
	if (auto wall = qSharedPointerDynamicCast<items::WallItem>(item)) {
		removeWall(wall);
	} else if (auto colorItem = qSharedPointerDynamicCast<items::ColorFieldItem>(item)) {
		removeColorField(colorItem);
	} else if (auto skittleItem = qSharedPointerDynamicCast<items::SkittleItem>(item)) {
		removeSkittle(skittleItem);
	} else if (auto ballItem = qSharedPointerDynamicCast<items::BallItem>(item)) {
		removeBall(ballItem);
	} else if (auto image = qSharedPointerDynamicCast<items::ImageItem>(item)) {
		removeImageItem(image);
	} else if (auto comment = qSharedPointerDynamicCast<items::CommentItem>(item)) {
		removeComment(comment);
	}
}
