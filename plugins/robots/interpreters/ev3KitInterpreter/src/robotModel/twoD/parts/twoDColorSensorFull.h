#pragma once

#include <kitBase/robotModel/robotParts/colorSensorFull.h>

namespace twoDModel {
namespace engine {
class TwoDModelEngineInterface;
}
}

namespace ev3 {
namespace robotModel {
namespace twoD {
namespace parts {
class ColorSensorFull : public kitBase::robotModel::robotParts::ColorSensorFull
{
	Q_OBJECT
public:
	ColorSensorFull(const kitBase::robotModel::DeviceInfo &info
			, const kitBase::robotModel::PortInfo &port
			, twoDModel::engine::TwoDModelEngineInterface &engine);

	void read();

private:
	twoDModel::engine::TwoDModelEngineInterface &mEngine;
};

}
}
}
}
