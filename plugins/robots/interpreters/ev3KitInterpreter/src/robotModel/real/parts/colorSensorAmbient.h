#pragma once

#pragma once

#include <kitBase/robotModel/robotParts/colorSensorAmbient.h>
#include <utils/robotCommunication/robotCommunicator.h>

#include "ev3InputDevice.h"

namespace ev3 {
namespace robotModel {
namespace real {
namespace parts {

class ColorSensorAmbient : public kitBase::robotModel::robotParts::ColorSensorAmbient
{
	Q_OBJECT
public:
	ColorSensorAmbient(const kitBase::robotModel::DeviceInfo &info
			, const kitBase::robotModel::PortInfo &port
			, utils::robotCommunication::RobotCommunicator &robotCommunicator);

	void read() override;

private:
	Ev3InputDevice mImplementation;
	utils::robotCommunication::RobotCommunicator &mRobotCommunicator;
};

}
}
}
}
