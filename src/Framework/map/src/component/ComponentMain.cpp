
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

void ComponentMain::handleBladePosition(const config::MAP::sub::BladePosition& msg)
{
	std::cout<< "MAP say:" << msg << std::endl;
}
	

void ComponentMain::handlePosAttVel(const config::MAP::sub::PosAttVel& msg)
{
	std::cout<< "MAP say:" << msg << std::endl;
}
	

void ComponentMain::handleLaser(const config::MAP::sub::Laser& msg)
{
	std::cout<< "MAP say:" << msg << std::endl;
}
	

void ComponentMain::handleCamera(const config::MAP::sub::Camera& msg)
{
	std::cout<< "MAP say:" << msg << std::endl;
}
	

void ComponentMain::publishMap(config::MAP::pub::Map& msg)
{
	_roscomm->publishMap(msg);
}
	

void ComponentMain::publishMiniMap(config::MAP::pub::MiniMap& msg)
{
	_roscomm->publishMiniMap(msg);
}
	