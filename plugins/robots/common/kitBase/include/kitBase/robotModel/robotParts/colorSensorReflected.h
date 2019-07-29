#pragma once

#include "colorSensor.h"

#include "kitBase/kitBaseDeclSpec.h"

namespace kitBase {
namespace robotModel {
namespace robotParts {

class ROBOTS_KIT_BASE_EXPORT ColorSensorReflected : public ColorSensor
{
	Q_OBJECT
	Q_CLASSINFO("name", "colorReflected")
	Q_CLASSINFO("friendlyName", tr("EV3 Color sensor (reflected)"))
	Q_CLASSINFO("simulated", "true")

public:
	ColorSensorReflected(const DeviceInfo &info, const PortInfo &port);
};

}
}
}
