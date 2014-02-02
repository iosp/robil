
/*
 * RosComm.cpp
 *
 *  Created on: Sunday, 02. February 2014 10:01AM
 *      Author: autogenerated
 */
#include <ros/ros.h>
#include <std_msgs/String.h>
#include "RosComm.h"
#include "../component/ComponentMain.h"
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>
#include "ParameterHandler.h"
RosComm::RosComm(ComponentMain* comp,int argc,char** argv)
	: _inited(init(argc, argv)), _comp(comp)
{
	_sub_Camera=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"VO","Camera","sub"), 10, &RosComm::CameraCallback,this));
	_sub_INS=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"VO","INS","sub"), 10, &RosComm::INSCallback,this));
	_sub_TF=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"VO","TF","sub"), 10, &RosComm::TFCallback,this));
	_pub_PosAttVel=ros::Publisher(_nh.advertise<config::VO::pub::PosAttVel>(fetchParam(&_nh,"VO","PosAttVel","pub"),10));
}
RosComm::~RosComm()
{
}
bool RosComm::init(int argc,char** argv){
	ros::init(argc,argv,"VO_node");
}


void RosComm::CameraCallback(const config::VO::sub::Camera::ConstPtr &msg)
{
	_comp->handleCamera(*msg);
}
	

void RosComm::INSCallback(const config::VO::sub::INS::ConstPtr &msg)
{
	_comp->handleINS(*msg);
}
	

void RosComm::TFCallback(const config::VO::sub::TF::ConstPtr &msg)
{
	_comp->handleTF(*msg);
}
	

void RosComm::publishPosAttVel( config::VO::pub::PosAttVel &msg)
{
	_pub_PosAttVel.publish(msg);
}
	
