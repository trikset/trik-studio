#include "twoDModel/robotModel/parts/colorSensorAmbient.h"

#include "twoDModel/engine/twoDModelEngineInterface.h"

using namespace twoDModel::robotModel::parts;
using namespace kitBase::robotModel;

ColorSensorAmbient::ColorSensorAmbient(const kitBase::robotModel::DeviceInfo &info
		, const kitBase::robotModel::PortInfo &port
		, engine::TwoDModelEngineInterface &engine)
	: kitBase::robotModel::robotParts::ColorSensorAmbient(info, port)
	, mEngine(engine)
{
}

void ColorSensorAmbient::read()
{
	emit newData(mEngine.readColorSensor(port()));
}
