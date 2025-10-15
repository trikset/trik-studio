#include "twoDColorSensorFull.h"
#include "twoDModel/engine/twoDModelEngineInterface.h"
#include "twoDModel/engine/model/constants.h"
#include <QColor>

using namespace nxt::robotModel::twoD::parts;
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
	auto resColor = 0xFF000000;
	const auto clearRed = twoDModel::red - twoDModel::black;
	const auto clearGreen = twoDModel::green - twoDModel::black;
	const auto clearBlue = twoDModel::blue - twoDModel::black;

	if (color.red() > 200) {
		resColor += clearRed;
	} else if (color.red() > 100) {
		resColor += clearRed / 2;
	}
	if (color.green() > 150) {
		resColor += clearGreen;
	} else if (color.green() > 75) {
		resColor += clearGreen / 2;
	}
	if (color.blue() > 200) {
		resColor += clearBlue;
	} else if (color.blue() > 100) {
		resColor += clearBlue / 2;
	}
	int reading;
	switch (resColor) {
	case (twoDModel::black):
		reading = 1;
		break;
	case (twoDModel::red):
		reading = 5;
		break;
	case (twoDModel::green):
		reading = 3;
		break;
	case (twoDModel::blue) :
		reading = 2;
		break;
	case (twoDModel::yellow):
		reading = 4;
		break;
	case (twoDModel::white):
		reading = 6;
		break;
	case (twoDModel::cyan):
		reading = 7;
		break;
	case (twoDModel::magenta):
		reading = 8;
		break;
	default:
		reading = 0;
	}

	setLastData(reading);
}
