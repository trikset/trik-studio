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

#include "twoDModel/engine/model/robotModel.h"

#include <qmath.h>
#include <QtCore/QtMath>
#include <QtGui/QTransform>

#include <qrutils/mathUtils/math.h>
#include <qrkernel/settingsManager.h>
#include <qrgui/plugins/toolPluginInterface/usedInterfaces/errorReporterInterface.h>

#include <kitBase/robotModel/robotParts/encoderSensor.h>
#include <kitBase/robotModel/robotParts/motor.h>
#include <kitBase/robotModel/robotParts/rangeSensor.h>

#include "twoDModel/engine/model/constants.h"
#include "twoDModel/engine/model/settings.h"
#include "twoDModel/engine/model/timeline.h"
#include "twoDModel/engine/model/worldModel.h"

#include "physics/physicsEngineBase.h"

#include "src/engine/items/startPosition.h"
#include "src/engine/items/wallItem.h"
#include "src/engine/items/ballItem.h"
#include "utils/abstractTimer.h"
#include "src/engine/view/scene/twoDModelScene.h"
#include "src/engine/view/scene/robotItem.h"

using namespace twoDModel::model;
using namespace kitBase::robotModel;
using namespace kitBase::robotModel::robotParts;

const int positionStampsCount = 50;
const qreal manualSpeed = 0.5;
const qreal eps = manualSpeed / 2;

RobotModel::RobotModel(robotModel::TwoDRobotModel &robotModel
		, const Settings &settings
		, QObject *parent)
	: QObject(parent)
	, mSettings(settings)
	, mRobotModel(robotModel)
	, mSensorsConfiguration(robotModel.robotId(), robotModel.size())
	, mMarker(Qt::transparent)
	, mPosStamps(positionStampsCount)
	, mStartPositionMarker(new items::StartPosition(info().size()))
{
	reinit();
}

RobotModel::~RobotModel() = default;

void RobotModel::reinit()
{
	mMotors.clear();
	mMarker = Qt::transparent;

	for (const Device * const device : mRobotModel.configuration().devices()) {
		if (device->deviceInfo().isA<robotParts::Motor>()) {
			initMotor(robotWheelDiameterInPx / 2, 0, 0, device->port(), false);
		}
	}

	mBeepTime = 0;
	mDeltaDegreesOfAngle = 0;
	mAcceleration = QPointF(0, 0);

	connect(&mRobotModel, &RobotModelInterface::moveManually, this, &RobotModel::moveCell, Qt::UniqueConnection);
	connect(&mRobotModel, &RobotModelInterface::turnManuallyOn, this, &RobotModel::turnOn, Qt::UniqueConnection);
	connect(&mRobotModel, &RobotModelInterface::drawManually, this, &RobotModel::drawInCell, Qt::UniqueConnection);
}

void RobotModel::moveCell(int n) {
	const int gridSize = qReal::SettingsManager::value("2dGridCellSize").toInt();
	auto shiftPos = QTransform().rotate(mAngle).map(QPointF(gridSize, 0));
	if (n < 0) shiftPos = -shiftPos;
	mIsRiding = true;
	mWaitPos = mPos + shiftPos * abs(n);
	mIsCollide = false;
}

void RobotModel::turnOn(qreal angle) {
	setRotation(rotation() + angle);
}

void RobotModel::drawInCell(const QColor &color, const QString& text)
{
	const auto penWidth = qReal::SettingsManager::value("GridWidth").toDouble() / 100;
	const auto gridSize = qReal::SettingsManager::value("2dGridCellSize").toInt();
	mWorldModel->prependRobotTrace(QPen(Qt::black, penWidth), QBrush(color), robotBoundingPath(false));
	if (text.isEmpty()) return;
	QPainterPath path;
	QFont font;
	font.setPixelSize(35);
	path.addText(robotBoundingPath(false).boundingRect().bottomLeft(), font, text);
	auto robotBR = robotBoundingPath(false).boundingRect();
	auto bR = path.boundingRect();
	path.translate(robotBR.left() - bR.left() + (gridSize - bR.width())/2
			, robotBR.bottom() - bR.bottom() + (bR.height() - gridSize)/2);
	mWorldModel->prependRobotTrace(QPen(Qt::white), QBrush(Qt::black), path);
}

void RobotModel::clear()
{
	reinit();
	setPosition(QPointF());
	setRotation(0);
	auto scene = dynamic_cast<twoDModel::view::TwoDModelScene *>(mStartPositionMarker->scene());
	scene->robot(*const_cast<RobotModel*>(this))->useCustomImage(false);
}

RobotModel::Wheel *RobotModel::initMotor(int radius, int speed, uint64_t degrees, const PortInfo &port, bool isUsed)
{
	auto *motor = new Wheel();
	motor->radius = radius;
	motor->speed = speed;
	motor->degrees = degrees;
	motor->isUsed = isUsed;
	motor->breakMode = true;
	if (degrees == 0) {
		motor->activeTimeType = DoInf;
	} else {
		motor->activeTimeType = DoByLimit;
	}

	mMotors[port].reset(motor);

	/// @todo We need some mechanism to set correspondence between motors and encoders. In NXT motors and encoders are
	///       physically plugged into one port, so we can find corresponding port by name. But in TRIK encoders can be
	///       connected differently.
	for (const Device * const device : mRobotModel.configuration().devices()) {
		if (device->deviceInfo().isA<EncoderSensor>()
				&& (device->port().name() == port.name() || device->port().nameAliases().contains(port.name())))
		{
			mMotorToEncoderPortMap[port] = device->port();
			mTurnoverEngines[mMotorToEncoderPortMap[port]] = 0;
		}
	}

	return motor;
}

void RobotModel::playSound(int timeInMs)
{
	mBeepTime = qMax(mBeepTime, timeInMs);
}

void RobotModel::setNewMotor(int speed, uint degrees, const PortInfo &port, bool breakMode)
{
	mMotors[port]->speed = mathUtils::Math::truncateToInterval(-100, 100, speed);
	mMotors[port]->degrees = degrees;
	mMotors[port]->isUsed = true;
	mMotors[port]->breakMode = breakMode;
	if (degrees) {
		mMotors[port]->activeTimeType = DoByLimit;
	} else {
		mMotors[port]->activeTimeType = DoInf;
	}
}

void RobotModel::countMotorTurnover()
{
	for (auto &&motor : mMotors) {
		const PortInfo &port = mMotors.key(motor);
		const qreal degrees = Timeline::timeInterval * motor->spoiledSpeed * mRobotModel.onePercentAngularVelocity();
		const qreal actualDegrees = mPhysicsEngine->isRobotStuck() ? -degrees : degrees;
		mTurnoverEngines[mMotorToEncoderPortMap[port]] += actualDegrees;
		if (motor->isUsed && (motor->activeTimeType == DoByLimit)
				&& (mTurnoverEngines[mMotorToEncoderPortMap[port]] >= motor->degrees))
		{
			motor->speed = 0;
			motor->activeTimeType = End;
		}
	}
}

int RobotModel::readEncoder(const PortInfo &port) const
{
	return mTurnoverEngines[port];
}

void RobotModel::resetEncoder(const PortInfo &port)
{
	mTurnoverEngines[port] = 0;
}

SensorsConfiguration &RobotModel::configuration()
{
	return mSensorsConfiguration;
}

const RobotModel::Wheel &RobotModel::leftWheel() const
{
	return *mMotors[mWheelsToMotorPortsMap[left]];
}

const RobotModel::Wheel &RobotModel::rightWheel() const
{
	return *mMotors[mWheelsToMotorPortsMap[right]];
}

twoDModel::robotModel::TwoDRobotModel &RobotModel::info() const
{
	return mRobotModel;
}

void RobotModel::stopRobot()
{
	mBeepTime = 0;
	mRobotModel.displayWidget()->reset();
	mIsFirstAngleStamp = true;
	mPosStamps.clear();
	emit playingSoundChanged(false);
	for (auto &&engine : mMotors) {
		engine->speed = 0;
		engine->breakMode = true;
	}
	mIsRiding = false;
}

void RobotModel::countBeep()
{
	if (mBeepTime > 0) {
		emit playingSoundChanged(true);
		mBeepTime -= Timeline::timeInterval;
	} else {
		emit playingSoundChanged(false);
	}
}

void RobotModel::countSpeedAndAcceleration()
{
	if (mIsFirstAngleStamp) {
		mAngleStampPrevious = mAngle;
		mIsFirstAngleStamp = false;
	} else {
		// Convert to millidegress per second
		mDeltaDegreesOfAngle = (mAngle - mAngleStampPrevious) * 1000 / Timeline::timeInterval;
		mAngleStampPrevious = mAngle;
	}

	if (mPosStamps.size() >= positionStampsCount) {
		mPosStamps.dequeue();
	}

	mPosStamps.enqueue(mPos);
	mAcceleration = averageAcceleration();
}

QPointF RobotModel::averageAcceleration() const
{
	/// Some arcane formula that produces natural-looking results for some reason (with correct accelerometerConstant,
	/// since mPosStamps.size() as a divisor is obviously wrong here).
	/// Maybe it will be better to actually count average.

	return mPosStamps.size() < 2 ? QPointF() : (mPosStamps.size() < 4
			? (mPosStamps.tail() - mPosStamps.head()) / mPosStamps.size()
			: (mPosStamps.tail() - mPosStamps.nthFromTail(1)
					- mPosStamps.nthFromHead(1) + mPosStamps.head()) / mPosStamps.size());
}

QPointF RobotModel::robotCenter() const
{
	return mPos + mRobotModel.robotCenter();
}

QTransform RobotModel::robotsTransform() const
{
	const QRectF boundingRect(QPointF(), mRobotModel.size());
	const QPointF realRotatePoint = QPointF(boundingRect.width() / 2, boundingRect.height() / 2);
	const QPointF translationToZero = -realRotatePoint - boundingRect.topLeft();
	const QPointF finalTranslation = mPos + realRotatePoint + boundingRect.topLeft();
	return QTransform().translate(finalTranslation.x(), finalTranslation.y())
			.rotate(mAngle).translate(translationToZero.x(), translationToZero.y());
}

QPainterPath RobotModel::sensorBoundingPath(const PortInfo &port) const
{
	if (mSensorsConfiguration.type(port).isNull() || !mSensorsConfiguration.type(port).simulated())
	{
		return QPainterPath();
	}
	const QPointF sensorPos = mSensorsConfiguration.position(port);
	QPainterPath tempSensorPath;
	tempSensorPath.addRect(sensorRect(port, sensorPos));
	const QTransform transformSensor = QTransform()
			.translate(sensorPos.x(), sensorPos.y())        // /\  And going back again
			.rotate(mSensorsConfiguration.direction(port))  // ||  Then rotating
			.translate(-sensorPos.x(), -sensorPos.y());     // ||  First translating to zero
	return transformSensor.map(tempSensorPath);
}

QPainterPath RobotModel::robotBoundingPath(const bool withSensors) const
{
	QPainterPath path;
	const QRectF boundingRect(QPointF(), mRobotModel.size());
	path.addRect(boundingRect);

	if (withSensors) {
		for (const PortInfo &port : mRobotModel.configurablePorts()){
			path.addPath(sensorBoundingPath(port));
		}
	}

	return robotsTransform().map(path);
}

void RobotModel::setPhysicalEngine(physics::PhysicsEngineBase &engine)
{
	mPhysicsEngine = &engine;
}

void RobotModel::setWorldModel(WorldModel &worldModel)
{
	mWorldModel = &worldModel;
}

QRectF RobotModel::sensorRect(const PortInfo &port, const QPointF sensorPos) const
{
	if (!mSensorsConfiguration.type(port).isNull()) {
		auto device = mSensorsConfiguration.type(port);
		const QSizeF size = mRobotModel.sensorImageRect(mSensorsConfiguration.type(port)).size();
		// We don't need part with radiating waves from range sensor in bounding rect of sensor
		if (device.isA<robotParts::RangeSensor>()) {
			return QRectF(sensorPos.x() - size.width()/2, sensorPos.y() - size.height()/2
					, size.width()/2, size.height());
		}
		return QRectF(sensorPos - QPointF(size.width() / 2, size.height() / 2), size);
	}

	return QRectF();
}

QColor RobotModel::markerColor() const
{
	return mMarker;
}

void RobotModel::markerDown(const QColor &color)
{
	mMarker = color;
}

void RobotModel::markerUp()
{
	mMarker = Qt::transparent;
}

QVector<int> RobotModel::accelerometerReading() const
{
	return {static_cast<int>(mAcceleration.x() * accelerometerConstant)
				, static_cast<int>(mAcceleration.y() * accelerometerConstant)
				, g};
}

QVector<int> RobotModel::gyroscopeReading() const
{
	return {static_cast<int>(mDeltaDegreesOfAngle * 1000)
		, static_cast<int>((mAngle - mGyroAngle) * 1000)};
}

QVector<int> RobotModel::gyroscopeCalibrate()
{
	mGyroAngle = mAngle;
	return gyroscopeReading();
}

QRectF RobotModel::aheadRect() const {
	auto gridSize = qReal::SettingsManager::value("2dGridCellSize").toInt();
	return QRectF(0, eps, eps, gridSize - 2 * eps);
}

void RobotModel::nextStep()
{
	// Changing position quietly, they must not be caught by UI here.
	// No physics for simple robot
//	mPos += mPhysicsEngine->positionShift(*this).toPointF();
//	mAngle += mPhysicsEngine->rotation(*this);
	if (mIsRiding) {
		auto oneStep = qReal::SettingsManager::value("2dGridCellSize").toInt();
		const auto &delta = mWaitPos - mPos;
		const auto &direction = QTransform().rotate(mAngle).map(QPointF(1, 0));
		auto && ahead = aheadRect();
		if (delta.x() * direction.x() + delta.y() * direction.y() > 0) {
			ahead.translate(oneStep, 0);
		} else {
			ahead.translate(-ahead.width(), 0);
			oneStep = -oneStep;
		}
		items::MovableItem *needToMove;
		QMap<items::MovableItem*, bool> movedItems;
		do {
			needToMove = nullptr;
			const auto &aheadPolygon = robotsTransform().map(ahead);
			for (auto &&movable : mWorldModel->movables()) {
				const auto movablePolygon = movable->mapToScene(movable->boundingRect());
				if (movablePolygon.intersects(aheadPolygon) && !movedItems.contains(movable.data())) {
					needToMove = movable.data();
					movedItems[needToMove] = true;
					break;
				}
			}
			ahead.translate(oneStep, 0);
		} while (needToMove);

		const auto lenSquare = QPointF::dotProduct(delta, delta);
		const auto oldPos = mPos;

		if (lenSquare <= manualSpeed * manualSpeed) {
			mPos = mWaitPos;
			mIsRiding = false;
			emit mRobotModel.endManual(!mIsCollide);
		} else {
			const auto unitVector = delta / qSqrt(lenSquare);
			QLineF moveLine(QPointF(), (movedItems.size() + 0.5) * abs(oneStep) * unitVector);
			moveLine.translate(robotCenter());
			for (auto &&wall : mWorldModel->walls()) {
				auto wallLine = QLineF(wall->begin(), wall->end());
				if (moveLine.intersect(wallLine, nullptr) == QLineF::BoundedIntersection) {
					mIsCollide = true;
					mIsRiding = false;
					mPos = alignToGrid(mPos);
					emit mRobotModel.endManual(!mIsCollide);
					break;
				}
			}
			if (mIsRiding) {
				mPos += manualSpeed * unitVector;
			}
		}

		for (auto &&item : movedItems.keys(true)) {
			item->setPos(item->pos() + mPos - oldPos);
		}
	} else {
		emit mRobotModel.endManual(true);
	}
	emit positionRecalculated(mPos, mAngle);
}

void RobotModel::recalculateParams()
{
	// Do nothing until robot gets back on the ground
	if (!mIsOnTheGround || !mPhysicsEngine) {
		return;
	}

	// No motors on simple model
//	auto calculateMotorOutput = [&](WheelEnum wheel) {
//		const PortInfo &port = mWheelsToMotorPortsMap.value(wheel, PortInfo());
//		if (!port.isValid() || port.name() == "None") {
//			return;
//		}

//		Wheel * const engine = mMotors.value(port, nullptr);
//		if (!engine) {
//			return;
//		}

//		engine->spoiledSpeed = mSettings.realisticMotors() ? varySpeed(engine->speed) : engine->speed;
//	};

//	calculateMotorOutput(left);
//	calculateMotorOutput(right);

	nextStep();
//	countSpeedAndAcceleration();
//	countMotorTurnover();
	countBeep();
}

void RobotModel::nextFragment()
{
	if (!mIsOnTheGround) {
		return;
	}

	emit robotRided(mPos, mAngle);
}

QPointF RobotModel::position() const
{
	return mPos;
}

void RobotModel::setPosition(const QPointF &newPos)
{
	if (newPos != mPos) {
		mPos = newPos;
		emit positionChanged(newPos);
	}
}

qreal RobotModel::rotation() const
{
	return mAngle;
}

void RobotModel::setRotation(qreal angle)
{
	if (!mathUtils::Math::eq(mAngle, angle)) {
		mAngle = angle;
		emit rotationChanged(angle);
	}
}

qreal RobotModel::x() const
{
	return mPos.x();
}

qreal RobotModel::y() const
{
	return mPos.y();
}

bool RobotModel::onTheGround() const
{
	return mIsOnTheGround;
}

QDomElement RobotModel::serialize(QDomElement &parent) const
{
	QDomElement robot = parent.ownerDocument().createElement("robot");
	parent.appendChild(robot);
	robot.setAttribute("id", mRobotModel.robotId());
	robot.setAttribute("position", QString::number(mPos.x()) + ":" + QString::number(mPos.y()));
	robot.setAttribute("direction", QString::number(mAngle));

	mSensorsConfiguration.serialize(robot);
	mStartPositionMarker->serialize(robot);
	serializeWheels(robot);

	auto scene = dynamic_cast<twoDModel::view::TwoDModelScene *>(mStartPositionMarker->scene());
	auto robotItem = scene->robot(*const_cast<RobotModel*>(this));
	if (robotItem->usedCustomImage()) {
		robotItem->serializeImage(robot);
	}
	return robot;
}

void RobotModel::deserialize(const QDomElement &robotElement)
{
	const QString positionStr = robotElement.attribute("position", "0:0");
	const QStringList splittedStr = positionStr.split(":");
	const qreal x = static_cast<qreal>(splittedStr[0].toDouble());
	const qreal y = static_cast<qreal>(splittedStr[1].toDouble());
	onRobotReturnedOnGround();
	setPosition(QPointF(x, y));
	setRotation(robotElement.attribute("direction", "0").toDouble());
	mStartPositionMarker->deserializeCompatibly(robotElement);
	deserializeWheels(robotElement);
	emit deserialized(QPointF(x, y), robotElement.attribute("direction", "0").toDouble());

	auto scene = dynamic_cast<twoDModel::view::TwoDModelScene *>(mStartPositionMarker->scene());
	auto robotItem = scene->robot(*const_cast<RobotModel*>(this));
	robotItem->deserializeImage(robotElement);

	nextFragment();
}

void RobotModel::onRobotLiftedFromGround()
{
	mLiftedPos = mPos;
	mIsOnTheGround = false;
}

void RobotModel::onRobotReturnedOnGround()
{
	mWaitPos += alignToGrid(mPos - mLiftedPos);
	mIsOnTheGround = true;
}

void RobotModel::setMotorPortOnWheel(WheelEnum wheel, const kitBase::robotModel::PortInfo &port)
{
	if (mWheelsToMotorPortsMap[wheel] != port) {
		mWheelsToMotorPortsMap[wheel] = port;
		emit wheelOnPortChanged(wheel, port);
	}
}

int RobotModel::varySpeed(const int speed) const
{
	const qreal ran = mathUtils::Math::gaussianNoise(varySpeedDispersion);
	return mathUtils::Math::truncateToInterval(-100, 100, round(speed * (1 + ran)));
}

void RobotModel::serializeWheels(QDomElement &robotElement) const
{
	QDomElement wheels = robotElement.ownerDocument().createElement("wheels");
	wheels.setAttribute("left", mWheelsToMotorPortsMap[WheelEnum::left].toString());
	wheels.setAttribute("right", mWheelsToMotorPortsMap[WheelEnum::right].toString());
	robotElement.appendChild(wheels);
}

void RobotModel::deserializeWheels(const QDomElement &robotElement)
{
	const QDomElement wheels = robotElement.firstChildElement("wheels");
	if (wheels.isNull()) {
		return;
	}

	setMotorPortOnWheel(WheelEnum::left, PortInfo::fromString(wheels.attribute("left")));
	setMotorPortOnWheel(WheelEnum::right, PortInfo::fromString(wheels.attribute("right")));
}

twoDModel::items::StartPosition *RobotModel::startPositionMarker()
{
	return mStartPositionMarker;
}

QPointF RobotModel::alignToGrid(QPointF pos) const
{
	return QPointF(roundPos(pos.x()), roundPos(pos.y()));
}

qreal RobotModel::roundPos(qreal pos) const {
	auto gridSize = qReal::SettingsManager::value("2dGridCellSize").toInt();
	auto roundedPos = pos - fmod(pos, gridSize);
	auto roundedPos2 = roundedPos + ((pos > 0) ? gridSize : -gridSize);
	if (qAbs(roundedPos - pos) > qAbs(roundedPos2 - pos)) {
		return roundedPos2;
	}
	return roundedPos;
}
