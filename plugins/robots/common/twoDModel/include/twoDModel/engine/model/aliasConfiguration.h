#pragma once
#include "twoDModel/twoDModelDeclSpec.h"
#include <kitBase/robotModel/portInfo.h>
#include <QDomElement>

namespace twoDModel {

namespace robotModel {
class TwoDRobotModel;
}

namespace model {

/// For different KITs, such as the EV3 and TRIK twoDModel, many things are expressed through the same
/// entities. For example, both models have two wheels with a motor and an encoder attached to them,
/// as well as sensors with a common interface, and so on. Despite the fact that these sensors or other
/// devices have common interfaces (which are ultimately inherited from the ScalarSensor or VectorSensor
/// class or the Device class), it is necessary to write new code due to the difference in entity names
/// for different KITs. In constraints, this happens, for example, when accessing objects through event chains,
/// such as robot1.M4 or robot1.A. Ports already have alias semantics, but the ability to configure ports from the
/// UI, check their availability, and more complicates the situation. The hash function for ports in containers
/// also only considers the name and direction. It is proposed to solve the problem at the worldModel.xml level.
class TWO_D_MODEL_EXPORT AliasConfiguration
{
	Q_DISABLE_COPY_MOVE(AliasConfiguration)
public:
	explicit AliasConfiguration(twoDModel::robotModel::TwoDRobotModel &robotModel);
	~AliasConfiguration() = default;
	void serialize(QDomElement &element) const;
	void deserialize(const QDomElement &element);

	/// Alias is a port property, so if the user changes the device on the port, it should not affect
	/// the list of aliases specified in WorldModel.xml
	/// User aliases cannot have a name that is already occupied by another port,
	/// to avoid ambiguous situations that may arise when debugging programs
	QStringList getAliases(const kitBase::robotModel::PortInfo &portInfo) const;

	/// It is necessary for the correct serialization of devices in the 2D model. The fact is that the
	/// classes that store information about devices and ports use hash functions for the port that take into account
	/// only the name and direction of the port, and the information about the alises is lost. For example, a widget
	/// for selecting a motor for the left and right wheels that has default values or a sensor configurator.
	/// At the same time, they are responsible for serialization.
	kitBase::robotModel::PortInfo createFromPort(const kitBase::robotModel::PortInfo &port) const;

	/// needSerialize: At the moment, information about custom sensors and wheels remains in their blocks in WorldModel.xml,
	/// but this class is still responsible for storing aliases.
	void addAliases(const kitBase::robotModel::PortInfo &portInfo, bool needSerialize = false);
private:
	struct AliasInfo {
		QStringList mNames{};
		bool mNeedSerliaze {};
	};

	twoDModel::robotModel::TwoDRobotModel &mRobotModel;
	QHash<kitBase::robotModel::PortInfo, AliasInfo> mAllowedAliases;
};
}
}
