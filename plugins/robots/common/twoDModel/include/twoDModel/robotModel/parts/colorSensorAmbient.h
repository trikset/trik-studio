#pragma once

#include <kitBase/robotModel/robotParts/colorSensorAmbient.h>

#include "twoDModel/twoDModelDeclSpec.h"

namespace twoDModel {

namespace engine {
class TwoDModelEngineInterface;
}

namespace robotModel {
namespace parts {

class TWO_D_MODEL_EXPORT ColorSensorAmbient : public kitBase::robotModel::robotParts::ColorSensorAmbient
{
	Q_OBJECT
	Q_CLASSINFO("friendlyName", tr("Color sensor EV3 (ambient)"))

public:
	ColorSensorAmbient(const kitBase::robotModel::DeviceInfo &info
			, const kitBase::robotModel::PortInfo &port
			, engine::TwoDModelEngineInterface &engine);

	void read();

private:
	engine::TwoDModelEngineInterface &mEngine;
};

}
}
}
