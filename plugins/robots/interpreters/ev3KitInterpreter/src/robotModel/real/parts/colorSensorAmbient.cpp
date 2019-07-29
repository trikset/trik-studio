#include "colorSensorAmbient.h"

#include <ev3Kit/communication/ev3DirectCommand.h>

const unsigned colorSensorResponseSize = 9;

using namespace ev3::robotModel::real::parts;
using namespace ev3::communication;
using namespace kitBase::robotModel;

ColorSensorAmbient::ColorSensorAmbient(const kitBase::robotModel::DeviceInfo &info
		, const kitBase::robotModel::PortInfo &port
		, utils::robotCommunication::RobotCommunicator &robotCommunicator)
	: kitBase::robotModel::robotParts::ColorSensorAmbient(info, port)
	, mImplementation(robotCommunicator, port)
	, mRobotCommunicator(robotCommunicator)
{
}

void ColorSensorAmbient::read()
{
	const QByteArray command = mImplementation.readyPercentCommand(mImplementation.lowLevelPort(), 1);
	QByteArray outputBuf;
	mRobotCommunicator.send(command, colorSensorResponseSize, outputBuf);
	emit newData(static_cast<int>(outputBuf.data()[5]));
}
