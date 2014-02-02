
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

void ComponentMain::handleSensor_SICK(const config::SE_R2RS::sub::Sensor_SICK& msg)
{
	std::cout<< "SE_R2RS say:" << msg << std::endl;
}
	

void ComponentMain::handleSensor_IBEO(const config::SE_R2RS::sub::Sensor_IBEO& msg)
{
	std::cout<< "SE_R2RS say:" << msg << std::endl;
}
	

void ComponentMain::handleSensor_CAM_R(const config::SE_R2RS::sub::Sensor_CAM_R& msg)
{
	std::cout<< "SE_R2RS say:" << msg << std::endl;
}
	

void ComponentMain::handleSensor_CAM_L(const config::SE_R2RS::sub::Sensor_CAM_L& msg)
{
	std::cout<< "SE_R2RS say:" << msg << std::endl;
}
	

