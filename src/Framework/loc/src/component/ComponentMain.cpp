
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

void ComponentMain::handlePosAttVel(config::LOC::sub::PosAttVel& msg)
{
	std::cout<< "LOC say:" << msg.data << std::endl;
}
	

void ComponentMain::handlePositionUpdate(config::LOC::sub::PositionUpdate& msg)
{
	std::cout<< "LOC say:" << msg.data << std::endl;
}
	

void ComponentMain::publishPosAttVel(config::LOC::pub::PosAttVel& msg)
{
	_roscomm->publishPosAttVel(msg);
}
	
