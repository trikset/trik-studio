#include "twoDModel/robotModel/parts/colorSensorReflected.h"

#include "twoDModel/engine/twoDModelEngineInterface.h"

using namespace twoDModel::robotModel::parts;
using namespace kitBase::robotModel;

ColorSensorReflected::ColorSensorReflected(const kitBase::robotModel::DeviceInfo &info
		, const kitBase::robotModel::PortInfo &port
		, engine::TwoDModelEngineInterface &engine)
	: kitBase::robotModel::robotParts::ColorSensorReflected(info, port)
	, mEngine(engine)
{
}

void ColorSensorReflected::read()
{
	emit newData(mEngine.readColorSensor(port()));
}
