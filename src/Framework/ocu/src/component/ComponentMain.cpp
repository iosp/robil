
/*
 * ComponentMain.cpp
 *
 *  Created on: Thursday, 30. January 2014 03:54PM
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

void ComponentMain::handlePosAttVel(config::OCU::sub::PosAttVel& msg)
{
	std::cout<< "OCU say:" << msg.data << std::endl;
}
	

void ComponentMain::handleTeleoperation(config::OCU::sub::Teleoperation& msg)
{
	std::cout<< "OCU say:" << msg.data << std::endl;
}
	

void ComponentMain::handleStatusData(config::OCU::sub::StatusData& msg)
{
	std::cout<< "OCU say:" << msg.data << std::endl;
}
	

void ComponentMain::handleMissionStatus(config::OCU::sub::MissionStatus& msg)
{
	std::cout<< "OCU say:" << msg.data << std::endl;
}
	

void ComponentMain::handleMap(config::OCU::sub::Map& msg)
{
	std::cout<< "OCU say:" << msg.data << std::endl;
}
	

void ComponentMain::handleLocalPathPlan(config::OCU::sub::LocalPathPlan& msg)
{
	std::cout<< "OCU say:" << msg.data << std::endl;
}
	

void ComponentMain::handleIEDDetectionEvent(config::OCU::sub::IEDDetectionEvent& msg)
{
	std::cout<< "OCU say:" << msg.data << std::endl;
}
	

void ComponentMain::handleIEDLocation(config::OCU::sub::IEDLocation& msg)
{
	std::cout<< "OCU say:" << msg.data << std::endl;
}
	

void ComponentMain::publishPositionUpdate(config::OCU::pub::PositionUpdate& msg)
{
	_roscomm->publishPositionUpdate(msg);
}
	

void ComponentMain::publishMissionPlan(config::OCU::pub::MissionPlan& msg)
{
	_roscomm->publishMissionPlan(msg);
}
	

void ComponentMain::publishTeleoperation(config::OCU::pub::Teleoperation& msg)
{
	_roscomm->publishTeleoperation(msg);
}
	

void ComponentMain::publishIEDDetectionEvent(config::OCU::pub::IEDDetectionEvent& msg)
{
	_roscomm->publishIEDDetectionEvent(msg);
}
	

void ComponentMain::publishIEDLocation(config::OCU::pub::IEDLocation& msg)
{
	_roscomm->publishIEDLocation(msg);
}
	
