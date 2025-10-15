#include "twoDColorSensorFull.h"
#include "twoDModel/engine/twoDModelEngineInterface.h"
#include "twoDModel/engine/model/constants.h"
#include <QColor>

using namespace ev3::robotModel::twoD::parts;
using namespace kitBase::robotModel;

ColorSensorFull::ColorSensorFull(const kitBase::robotModel::DeviceInfo &info
		, const kitBase::robotModel::PortInfo &port
		, twoDModel::engine::TwoDModelEngineInterface &engine)
	: kitBase::robotModel::robotParts::ColorSensorFull(info, port)
	, mEngine(engine)
{
}

void ColorSensorFull::read()
{
	const auto &color = mEngine.readColorSensor(port());
	Q_UNUSED(color);
	setLastData(0);
	/*
	 * Implement color recognition for ev3 that will take into account brown
	 */
}
