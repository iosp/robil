
/*
 * ComponentMain.cpp
 *
 *  Created on: Sunday, 02. February 2014 10:15AM
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

void ComponentMain::handleSensor_WIRE(const config::SE_R2U::sub::Sensor_WIRE& msg)
{
	std::cout<< "SE_R2U say:" << msg << std::endl;
}
	

void ComponentMain::handleSensor_INS(const config::SE_R2U::sub::Sensor_INS& msg)
{
	std::cout<< "SE_R2U say:" << msg << std::endl;
}
	

void ComponentMain::handleSensor_GPS(const config::SE_R2U::sub::Sensor_GPS& msg)
{
	std::cout<< "SE_R2U say:" << msg << std::endl;
}
	
