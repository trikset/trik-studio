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

#include "robotItem.h"

#include "twoDModel/engine/model/constants.h"
#include "src/engine/items/startPosition.h"
#include <qrkernel/settingsManager.h>
#include <QtMath>
#include <QBuffer>
#include <QFileInfo>

using namespace twoDModel::view;
using namespace graphicsUtils;
using namespace twoDModel::model;
using namespace kitBase::robotModel::robotParts;

const int border = 0;
const int defaultTraceWidth = 6;

RobotItem::RobotItem(const QString &robotImageFileName, model::RobotModel &robotModel)
	: mImage(robotImageFileName, true)
	, mEmptyImage(new Image("", false))
	, mBeepItem(new BeepItem())
	, mRobotModel(robotModel)
{
	mCustomImages[No].reset(new Image(robotImageFileName, true));
	for (auto dir : {Left, Right, Up, Down}) {
		mCustomImages[dir] = mEmptyImage;
	}
	connect(&mRobotModel, &model::RobotModel::robotRided, this, &RobotItem::ride);
	connect(&mRobotModel, &model::RobotModel::positionChanged, this, &RobotItem::setPos);
	connect(&mRobotModel, &model::RobotModel::rotationChanged, this, &RobotItem::setRotation);
	connect(&mRobotModel, &model::RobotModel::playingSoundChanged, this, &RobotItem::setNeededBeep);

	connect(&mRobotModel.configuration(), &model::SensorsConfiguration::deviceRemoved, this, &RobotItem::removeSensor);
	connect(&mRobotModel.configuration(), &model::SensorsConfiguration::positionChanged
			, this, &RobotItem::updateSensorPosition);
	connect(&mRobotModel.configuration(), &model::SensorsConfiguration::rotationChanged
			, this, &RobotItem::updateSensorRotation);

	connect(&mRobotModel.info(), &twoDModel::robotModel::TwoDRobotModel::settingsChanged
			, this, &RobotItem::updateImage);

	setAcceptHoverEvents(true);
	setAcceptDrops(true);
	setZValue(ZValue::Robot);
	const QSizeF robotSize = mRobotModel.info().size();
	setX2(x1() + robotSize.width());
	setY2(y1() + robotSize.height());
	mMarkerPoint = QPointF((x1()+x2())/2, (y1()+y2())/2);  // Marker is situated under the robot
	// TODO: Use rotationCenter?
	// mMarkerPoint = mRobotModel.info().rotationCenter();
	QPen pen(this->pen());
	pen.setWidth(defaultTraceWidth);
	setPen(pen);

	setTransformOriginPoint(mRobotModel.info().robotCenter());
	mBeepItem->setParentItem(this);
	mBeepItem->setPos((robotSize.width() - beepWavesSize) / 2, (robotSize.height() - beepWavesSize) / 2);
	mBeepItem->setVisible(false);

	RotateItem::init();

	QHash<kitBase::robotModel::PortInfo, kitBase::robotModel::DeviceInfo> sensors = robotModel.info().specialDevices();
	for (const kitBase::robotModel::PortInfo &port : sensors.keys()) {
		const kitBase::robotModel::DeviceInfo device = sensors[port];
		SensorItem *sensorItem = new SensorItem(robotModel.configuration(), port
				, robotModel.info().sensorImagePath(device), robotModel.info().sensorImageRect(device));
		addSensor(port, sensorItem);

		const QPair<QPoint, qreal> configuration(robotModel.info().specialDeviceConfiguration(port));
		QPoint position(configuration.first.x() * boundingRect().width() / 2
				, configuration.first.y() * boundingRect().height() / 2);
		sensorItem->setPos(position + boundingRect().center());
		sensorItem->setRotation(configuration.second);
	}
	savePos();
}

RobotItem::Direction RobotItem::imageDirection()
{
	int fullAngle = static_cast<int>(rotation());
	auto dir = fullAngle % 360;
	if (dir < 0) dir += 360;
	dir += 45;
	dir /= 90;
	dir %= 4;
	return static_cast<Direction>(dir * 90);
}

void RobotItem::drawItem(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	Q_UNUSED(option)
	Q_UNUSED(widget)
	painter->setRenderHint(QPainter::Antialiasing);
	painter->setRenderHint(QPainter::SmoothPixmapTransform);
	auto rect = RectangleImpl::boundingRect(x1(), y1(), x2(), y2(), 0).toRect();
	if (mIsCustomImage) {
		if (mIsRotatingImage) {
			painter->save();
			// We actually use knowledge that left-top of rect is (0,0)
			if (mCustomImages[imageDirection()] && mCustomImages[imageDirection()]->isValid()) {
				mLastDirection = imageDirection();
			}
			painter->translate(rect.right()/2, rect.bottom()/2);
			painter->rotate(-rotation());
			painter->translate(-rect.right()/2, -rect.bottom()/2);
			mCustomImages[mLastDirection]->draw(*painter, rect);
			painter->restore();
		} else {
			mCustomImages[No]->draw(*painter, rect);
		}
	} else {
		mImage.draw(*painter, rect);
	}
}

void RobotItem::drawExtractionForItem(QPainter* painter)
{
	painter->setPen(QPen(Qt::blue));
	painter->drawRect(QRectF(QPointF(x1(), y1()), QPointF(x2(), y2())));
}

QRectF RobotItem::boundingRect() const
{
	return RectangleImpl::boundingRect(x1(), y1(), x2(), y2(), border);
}

QRectF RobotItem::calcNecessaryBoundingRect() const
{
	return boundingRect().adjusted(border, border, -border, -border);
}

void RobotItem::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
	emit mousePressed();
	AbstractItem::mousePressEvent(event);

	if (editable()) {
		mRobotModel.onRobotLiftedFromGround();
		mDragStart = mRobotModel.position();
	}
}

void RobotItem::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{
	AbstractItem::mouseMoveEvent(event);
}

void RobotItem::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{
	AbstractItem::mouseReleaseEvent(event);
	if (editable()) {
		onLanded();
	}
}

void RobotItem::onLanded()
{
	mRobotModel.onRobotReturnedOnGround();
	emit changedPosition(this);
}

void RobotItem::resizeItem(QGraphicsSceneMouseEvent *event)
{
	Q_UNUSED(event)
	QGraphicsItem::setPos(mRobotModel.alignToGrid(pos()));
	update();
}

QDomElement RobotItem::serialize(QDomElement &parent) const
{
	QDomElement result = RotateItem::serialize(parent);
	result.setTagName("robot");
	result.setAttribute("position", QString::number(x()) + ":" + QString::number(y()));
	result.setAttribute("direction", QString::number(rotation()));

	return result;
}

void RobotItem::deserializeImage(const QDomElement &element) {
	const QDomElement image = element.firstChildElement("robotImage");
	// Need for old saves
	if (!image.isNull()) {
		mCustomImages[No] = Image::deserialize(image);
		useCustomImage(true);
		mIsRotatingImage = false;
	} else {
		const QDomElement images = element.firstChildElement("robotImages");
		if (images.isNull()) {
			return;
		}
		for (QDomElement image = images.firstChildElement(); !image.isNull()
				; image = image.nextSiblingElement()) {
			Direction dir = static_cast<Direction>(image.attribute("direction").toInt());
			mCustomImages[dir] = Image::deserialize(image);
		}
		for (const auto dir : {Right, Up, Left, Down}) {
			if (mCustomImages[dir].isNull()){
				mCustomImages[dir] = mEmptyImage;
			} else if (mCustomImages[Right]->isValid()) {
				mIsRotatingImage = true;
			}
		}
		useCustomImage(true);
	}
}

void RobotItem::serializeImage(QDomElement &parent) const {
	QDomElement imgParent = parent.ownerDocument().createElement("robotImages");
	for (const auto key : mCustomImages.keys()) {
		if (mCustomImages[key] && mCustomImages[key]->isValid()){
			QDomElement img = imgParent.ownerDocument().createElement("robotImage");
			img.setAttribute("direction", key);
			imgParent.appendChild(img);
			mCustomImages[key]->serialize(img);
		}
	}
	parent.appendChild(imgParent);
}

void RobotItem::deserialize(const QDomElement &element)
{
	const QString positionStr = element.attribute("position", "0:0");
	const QStringList splittedStr = positionStr.split(":");
	const qreal x = static_cast<qreal>(splittedStr[0].toDouble());
	const qreal y = static_cast<qreal>(splittedStr[1].toDouble());
	setPos(QPointF(x, y));

	setRotation(element.attribute("direction", "0").toDouble());
}

QMap<kitBase::robotModel::PortInfo, SensorItem *> const &RobotItem::sensors() const
{
	return mSensors;
}

void RobotItem::setPos(const QPointF &newPos)
{
	QGraphicsItem::setPos(newPos);
}

void RobotItem::setRotation(qreal rotation)
{
	QGraphicsItem::setRotation(rotation);
}

void RobotItem::ride(const QPointF &newPos, qreal rotation)
{
	const QPointF oldMarker = mapToScene(mMarkerPoint);
	setPos(newPos);
	setRotation(rotation);
	const QPointF newMarker = mapToScene(mMarkerPoint);
	QPen pen;
	pen.setColor(mRobotModel.markerColor());
	pen.setWidth(this->pen().width());
	emit drawTrace(pen, oldMarker, newMarker);
}

void RobotItem::addSensor(const kitBase::robotModel::PortInfo &port, SensorItem *sensor)
{
	mSensors[port] = sensor;
	sensor->setParentItem(this);

	sensor->setPos(mRobotModel.configuration().position(port));
	sensor->setRotation(mRobotModel.configuration().direction(port));
	emit sensorAdded(sensor);
}

void RobotItem::removeSensor(const kitBase::robotModel::PortInfo &port)
{
	if (!mSensors.contains(port) || !mSensors.value(port)) {
		return;
	}

	auto sensor = mSensors[port];
	scene()->removeItem(sensor);
	mSensors[port] = nullptr;
	delete sensor;
	// Only pointer itself, not the pointee can be used after deletion
	emit sensorRemoved(sensor);

}

void RobotItem::updateSensorPosition(const kitBase::robotModel::PortInfo &port)
{
	if (mSensors[port]) {
		mSensors[port]->setPos(mRobotModel.configuration().position(port));
		emit sensorUpdated(mSensors[port]);
	}
}

void RobotItem::updateSensorRotation(const kitBase::robotModel::PortInfo &port)
{
	if (mSensors[port]) {
		mSensors[port]->setRotation(mRobotModel.configuration().direction(port));
		emit sensorUpdated(mSensors[port]);
	}
}

void RobotItem::setNeededBeep(bool isNeededBeep)
{
	mBeepItem->setVisible(isNeededBeep);
}

bool RobotItem::setCustomImage(const QStringList &robotImageFileNames) {
	if (robotImageFileNames.size() == 1) {
		mIsCustomImage = true;
		mIsRotatingImage = false;
		mCustomImages[No]->loadFrom(robotImageFileNames[0]);
	} else if (robotImageFileNames.size() <= 4) {
		QMap<Direction, QSharedPointer<model::Image>> oldImages;
		for (auto && key : mCustomImages.keys()) {
			oldImages[key] = mCustomImages[key];
			mCustomImages[key].reset();
		}
		for (auto && fileName : robotImageFileNames) {
			auto fileBaseName = QFileInfo(fileName).baseName().toLower();
			auto newImage = new Image(fileName, true);
			if (fileBaseName.endsWith("up")) {
				mCustomImages[Up].reset(newImage);
			} else if (fileBaseName.endsWith("down")) {
				mCustomImages[Down].reset(newImage);
			} else if (fileBaseName.endsWith("right")) {
				mCustomImages[Right].reset(newImage);
			} else if (fileBaseName.endsWith("left")) {
				mCustomImages[Left].reset(newImage);
			}
		}
		auto success = false;
		for (auto && key : mCustomImages.keys()) {
			if (!mCustomImages[key]) {
				mCustomImages[key] = mEmptyImage;
			} else if (mCustomImages[key]->isValid()) {
				success = true;
			}
		}
		if (success) {
			mIsCustomImage = true;
			mIsRotatingImage = true;
		} else {
			for (auto && key : oldImages.keys()) {
				mCustomImages[key] = oldImages[key];
			}
			return false;
		}
	} else {
		return false;
	}
	update();
	return true;
}

void RobotItem::useCustomImage(bool isUsed) {
	mIsCustomImage = isUsed;
	update();
}

bool RobotItem::usedCustomImage() {
	return mIsCustomImage;
}

QVariant RobotItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
	if (change == ItemPositionHasChanged) {
		mRobotModel.setPosition(value.value<QPointF>());
	}

	if (change == ItemRotationHasChanged) {
		mRobotModel.setRotation(value.toReal());
	}

	return RotateItem::itemChange(change, value);
}

void RobotItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
	QGraphicsItem::contextMenuEvent(event);
}

void RobotItem::recoverDragStartPosition()
{
	mRobotModel.setPosition(mDragStart);
	emit recoverRobotPosition(mDragStart);
}

RobotModel &RobotItem::robotModel()
{
	return mRobotModel;
}

void RobotItem::returnToStartPosition()
{
	mRobotModel.onRobotLiftedFromGround();
	mRobotModel.setRotation(mRobotModel.startPositionMarker()->rotation());
	// Here we want the center of the robot to be the position of the marker.
	const QPointF shiftFromPicture = mapFromScene(pos());
	const QPointF markerPos = mRobotModel.startPositionMarker()->scenePos();
	const QPointF shiftToCenter = mapToScene(QPointF()) - mapToScene(boundingRect().center() - shiftFromPicture);
	mRobotModel.setPosition(markerPos + shiftToCenter);
	mRobotModel.onRobotReturnedOnGround();

	emit recoverRobotPosition(markerPos + shiftToCenter);
}

QPolygonF RobotItem::collidingPolygon() const
{
	return mRobotModel.info().collidingPolygon();
}

qreal RobotItem::mass() const
{
	return mRobotModel.info().mass();
}

qreal RobotItem::friction() const
{
	return mRobotModel.info().friction();
}

twoDModel::items::SolidItem::BodyType RobotItem::bodyType() const
{
	return BodyType::DYNAMIC;
}

void RobotItem::BeepItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option
		, QWidget *widget)
{
	Q_UNUSED(option)
	Q_UNUSED(widget)

	drawBeep(painter);
}

QRectF RobotItem::BeepItem::boundingRect() const
{
	return QRectF(0, 0, beepWavesSize, beepWavesSize);
}

void RobotItem::BeepItem::drawBeep(QPainter *painter)
{
	const QPointF center(beepWavesSize / 2, beepWavesSize / 2);

	drawBeepArcs(painter, center, 40);
	drawBeepArcs(painter, center, 50);
	drawBeepArcs(painter, center, 60);
}

void RobotItem::BeepItem::drawBeepArcs(QPainter *painter, const QPointF &center, qreal radius)
{
	painter->save();
	QPen pen;
	pen.setColor(Qt::red);
	pen.setWidth(3);
	painter->setPen(pen);
	const qreal diameter = radius + radius;
	QRectF rect(center.x() - radius, center.y() - radius, diameter, diameter);
	painter->drawArc(rect, 45 * 16, 90 * 16);
	painter->drawArc(rect, 225 * 16, 90 * 16);
	painter->restore();
}

void RobotItem::updateImage()
{
	mImage.loadFrom(mRobotModel.info().robotImage());
}
