#pragma once

#include "colorSensor.h"

#include "kitBase/kitBaseDeclSpec.h"

namespace kitBase {
namespace robotModel {
namespace robotParts {

class ROBOTS_KIT_BASE_EXPORT ColorSensorAmbient : public ColorSensor
{
	Q_OBJECT
	Q_CLASSINFO("name", "colorAmbient")
	Q_CLASSINFO("friendlyName", tr("EV3 Color sensor (ambient)"))
	Q_CLASSINFO("simulated", "true")

public:
	ColorSensorAmbient(const DeviceInfo &info, const PortInfo &port);
};

}
}
}
