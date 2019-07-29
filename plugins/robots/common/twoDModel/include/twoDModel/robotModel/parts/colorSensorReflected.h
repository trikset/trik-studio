#pragma once

#include <kitBase/robotModel/robotParts/colorSensorReflected.h>

#include "twoDModel/twoDModelDeclSpec.h"

namespace twoDModel {

namespace engine {
class TwoDModelEngineInterface;
}

namespace robotModel {
namespace parts {

class TWO_D_MODEL_EXPORT ColorSensorReflected : public kitBase::robotModel::robotParts::ColorSensorReflected
{
	Q_OBJECT
	Q_CLASSINFO("friendlyName", tr("EV3 Color sensor (reflected)"))

public:
	ColorSensorReflected(const kitBase::robotModel::DeviceInfo &info
			, const kitBase::robotModel::PortInfo &port
			, engine::TwoDModelEngineInterface &engine);

	void read();

private:
	engine::TwoDModelEngineInterface &mEngine;
};

}
}
}
