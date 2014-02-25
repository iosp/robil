
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

void ComponentMain::handlePositionUpdate(const config::LOC::sub::PositionUpdate& msg)
{
	std::cout<< "LOC say:" << msg << std::endl;
}
	

void ComponentMain::handleGPS(const config::LOC::sub::GPS& msg)
{
	std::cout<< "LOC say:" << msg << std::endl;
}
	

void ComponentMain::handleINS(const config::LOC::sub::INS& msg)
{
	std::cout<< "LOC say:" << msg << std::endl;
}
	

void ComponentMain::handleVOOdometry(const config::LOC::sub::VOOdometry& msg)
{
	std::cout<< "LOC say:" << msg << std::endl;
}
	

void ComponentMain::publishLocation(config::LOC::pub::Location& msg)
{
	_roscomm->publishLocation(msg);
}
	

void ComponentMain::publishPerVelocity(config::LOC::pub::PerVelocity& msg)
{
	_roscomm->publishPerVelocity(msg);
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
