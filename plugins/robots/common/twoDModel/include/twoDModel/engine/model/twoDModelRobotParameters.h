#pragma once

#include <QObject>
#include "twoDModel/twoDModelDeclSpec.h"
#include "twoDModel/robotModel/twoDRobotModel.h"
#include <QPolygonF>

namespace twoDModel {
namespace model {

/// A class required to encapsulate the dynamic properties of the robot that change during configuration (mass, size, and so on)
/// That is, all requests required to obtain robot parameters using RobotModel::info() now use this class.
/// This complicates the architecture and leads to errors, so it may be worth extending this class to become a full proxy
/// class for twoDModel::robotModel::TwoDRobotModel and use it in all 2D-model classes.
class TWO_D_MODEL_EXPORT TwoDRobotModelParameters: public QObject
{
	Q_OBJECT
	Q_PROPERTY(qreal mass READ mass WRITE setMass)
	Q_PROPERTY(qreal friction READ friction WRITE setFriction)
	Q_PROPERTY(qreal restitution READ restitution WRITE setRestitution)
	Q_PROPERTY(qreal linearDamping READ linearDamping WRITE setLinearDamping)
	Q_PROPERTY(qreal angularDamping READ angularDamping WRITE setAngularDamping)
	Q_PROPERTY(QSizeF size READ size WRITE setSize)
	Q_PROPERTY(qreal wheelRestitution READ wheelRestitution WRITE setWheelRestitution)
	Q_PROPERTY(qreal wheelFriction READ wheelFriction WRITE setWheelFriction)
	Q_PROPERTY(qreal wheelMass READ wheelMass WRITE setWheelMass)
public:
	TwoDRobotModelParameters(const twoDModel::robotModel::TwoDRobotModel &twoDRobotModel, QObject *parent = nullptr);

	/// A function required to set default parameters (from twoDModel::robotModel::TwoDRobotModel) that are read-only.
	///  Useful when loading an empty project, when all robot parameters should have a default value, or
	/// when the corresponding fields are missing during deserialization.
	void reinit();

	bool propertyChanged(const char *propertyName) const;

	/// Recalculate the collision polygon based on the current size of the robot.
	QPolygonF collidingPolygon() const;

	/// Set the mass for the robot.
	void setMass(const qreal mass);

	/// Set the mass for the robot wheel.
	void setWheelMass(const qreal mass);

	/// Get the mass for the robot wheel.
	qreal wheelMass() const;

	/// Set the restitution coefficient for the robot's wheel.
	void setWheelRestitution(const qreal restitution);

	/// Get the restitution coefficient for the robot's wheel.
	qreal wheelRestitution() const;

	/// Set the friction coefficient for the robot's wheel.
	void setWheelFriction(const qreal friction);

	/// Get the friction coefficient for the robot's wheel.
	qreal wheelFriction() const;

	/// Set robot size.
	void setSize(QSizeF size);

	/// Set the friction coefficient for the robot.
	void setFriction(const qreal friction);

	/// Set the restitution coefficient for the robot.
	void setRestitution(const qreal restitution);

	/// Set the linear damping coefficient for the robot.
	void setLinearDamping(const qreal linearDamping);

	/// Set the angular damping coefficient for the robot.
	void setAngularDamping(const qreal angularDamping);

	/// Get the mass of the robot.
	qreal mass() const;

	/// Get the friction coefficient for the robot.
	qreal friction() const;

	/// Get the restitution coefficient for the robot.
	qreal restitution() const;

	/// Get the angular damping coefficient for the robot.
	qreal angularDamping() const;

	/// Get the linear damping coefficient for the robot.
	qreal linearDamping() const;

	/// Get robot size.
	QSizeF size() const;

	/// Get wheel diameter.
	qreal wheelDiameter() const;

	/// Get robot center.
	QPointF robotCenter() const;

	/// Get one percent of the angular velocity of the robot.
	qreal onePercentAngularVelocity() const;

	/// Get wheels positions.
	QList<QPointF> wheelsPosition() const;

	/// Get robot rotation center.
	QPointF rotationCenter() const;

	/// Get robot track.
	qreal robotTrack() const;
Q_SIGNALS:
	void robotParamChanged();
private:
	const twoDModel::robotModel::TwoDRobotModel &mRobotModel;
	qreal mWidth;
	qreal mHeight;
	qreal mMass;
	qreal mFriction;
	qreal mRestitution;
	qreal mLinearDamping;
	qreal mAngularDamping;
	qreal mWheelRestitution;
	qreal mWheelFriction;
	qreal mWheelMass;

};

}
}
