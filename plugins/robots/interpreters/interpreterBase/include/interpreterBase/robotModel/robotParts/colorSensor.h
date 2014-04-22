#pragma once

#include "scalarSensor.h"
#include "interpreterBase/interpreterBaseDeclSpec.h"

namespace interpreterBase {
namespace robotModel {
namespace robotParts {

class ROBOTS_INTERPRETER_BASE_EXPORT ColorSensor : public ScalarSensor
{
	Q_OBJECT
	Q_CLASSINFO("name", "color")
	Q_CLASSINFO("friendlyName", tr("Color sensor"))

public:
	ColorSensor(DeviceInfo const &info, PortInfo const &port);
};

}
}
}
