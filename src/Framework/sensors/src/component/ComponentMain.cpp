
/*
 * ComponentMain.cpp
 *
 *  Created on: Tuesday, 25. February 2014 12:20PM
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


void ComponentMain::publishSensorINS(config::SENSORS::pub::SensorINS& msg)
{
	_roscomm->publishSensorINS(msg);
}
	

void ComponentMain::publishSensorGPS(config::SENSORS::pub::SensorGPS& msg)
{
	_roscomm->publishSensorGPS(msg);
}
	

void ComponentMain::publishSensorCamL(config::SENSORS::pub::SensorCamL& msg)
{
	_roscomm->publishSensorCamL(msg);
}
	

void ComponentMain::publishSensorCamR(config::SENSORS::pub::SensorCamR& msg)
{
	_roscomm->publishSensorCamR(msg);
}
	

void ComponentMain::publishSensorWire(config::SENSORS::pub::SensorWire& msg)
{
	_roscomm->publishSensorWire(msg);
}
	

void ComponentMain::publishSensorSICK(config::SENSORS::pub::SensorSICK& msg)
{
	_roscomm->publishSensorSICK(msg);
}
	

void ComponentMain::publishSensorIBEO1(config::SENSORS::pub::SensorIBEO1& msg)
{
	_roscomm->publishSensorIBEO1(msg);
}
	

void ComponentMain::publishSensorIBEO2(config::SENSORS::pub::SensorIBEO2& msg)
{
	_roscomm->publishSensorIBEO2(msg);
}
	

void ComponentMain::publishSensorIBEO3(config::SENSORS::pub::SensorIBEO3& msg)
{
	_roscomm->publishSensorIBEO3(msg);
}
	

void ComponentMain::publishSensorIBEO4(config::SENSORS::pub::SensorIBEO4& msg)
{
	_roscomm->publishSensorIBEO4(msg);
}
	
void ComponentMain::publishTransform(const tf::Transform& _tf, std::string srcFrame, std::string distFrame){
	_roscomm->publishTransform(_tf, srcFrame, distFrame);
}
tf::StampedTransform ComponentMain::getLastTrasform(std::string srcFrame, std::string distFrame){
	return _roscomm->getLastTrasform(srcFrame, distFrame);
}
void ComponentMain::publishDiagnostic(const diagnostic_msgs::DiagnosticStatus& _report){
	_roscomm->publishDiagnostic(_report);
}
void ComponentMain::publishDiagnostic(const std_msgs::Header& header, const diagnostic_msgs::DiagnosticStatus& _report){
	_roscomm->publishDiagnostic(header, _report);
}
