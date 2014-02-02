
/*
 * ComponentMain.cpp
 *
 *  Created on: Sunday, 02. February 2014 10:01AM
 *      Author: autogenerated
 */
#include "ComponentMain.h"
#include "../roscomm/RosComm.h"
ComponentMain::ComponentMain(int argc,char** argv)
{
	_roscomm = new RosComm(this,argc, argv);
}
ComponentMain::~ComponentMain() {
	if(_roscomm) delete _roscomm; _roscomm=0;
}


void ComponentMain::publishSensor_SICK(config::SENSORS::pub::Sensor_SICK& msg)
{
	_roscomm->publishSensor_SICK(msg);
}
	

void ComponentMain::publishSensor_IBEO(config::SENSORS::pub::Sensor_IBEO& msg)
{
	_roscomm->publishSensor_IBEO(msg);
}
	

void ComponentMain::publishSensor_CAM_R(config::SENSORS::pub::Sensor_CAM_R& msg)
{
	_roscomm->publishSensor_CAM_R(msg);
}
	

void ComponentMain::publishSensor_CAM_L(config::SENSORS::pub::Sensor_CAM_L& msg)
{
	_roscomm->publishSensor_CAM_L(msg);
}
	

void ComponentMain::publishSensor_WIRE(config::SENSORS::pub::Sensor_WIRE& msg)
{
	_roscomm->publishSensor_WIRE(msg);
}
	

void ComponentMain::publishSensor_GPS(config::SENSORS::pub::Sensor_GPS& msg)
{
	_roscomm->publishSensor_GPS(msg);
}
	

void ComponentMain::publishSensor_INS(config::SENSORS::pub::Sensor_INS& msg)
{
	_roscomm->publishSensor_INS(msg);
}
	
