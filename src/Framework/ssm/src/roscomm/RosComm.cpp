
/*
 * RosComm.cpp
 *
 *  Created on: Thursday, 30. January 2014 03:54PM
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
{
  ros::init(argc,argv,"PP_node");
  _comp=comp;
	_sub_Map=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"SSM","MissionStatus","sub"), 10, &RosComm::MissionStatusCallback,this));
	_pub_StatusData=ros::Publisher(_nh.advertise<config::SSM::pub::StatusData>(fetchParam(&_nh,"SSM","StatusData","pub"),10));
}
RosComm::~RosComm()
{
}

void RosComm::MissionStatusCallback(const config::SSM::sub::MissionStatus::ConstPtr &msg)
{
	_comp->handleMissionStatus(*msg);
}
	

void RosComm::publishStatusData( config::SSM::pub::StatusData &msg)
{
	_pub_StatusData.publish(msg);
}
	
