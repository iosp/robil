
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
	_sub_Sensor_SICK=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"PER","Sensor_SICK","sub"), 10, &RosComm::Sensor_SICKCallback,this));
	_sub_Sensor_IBEO=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"PER","Sensor_IBEO","sub"), 10, &RosComm::Sensor_IBEOCallback,this));
	_sub_Sensor_CAM_R=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"PER","Sensor_CAM_R","sub"), 10, &RosComm::Sensor_CAM_RCallback,this));
	_sub_Sensor_CAM_L=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"PER","Sensor_CAM_L","sub"), 10, &RosComm::Sensor_CAM_LCallback,this));
	_sub_Sensor_WIRE=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"PER","Sensor_WIRE","sub"), 10, &RosComm::Sensor_WIRECallback,this));
	_sub_Sensor_GPS=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"PER","Sensor_GPS","sub"), 10, &RosComm::Sensor_GPSCallback,this));
	_sub_Sensor_INS=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"PER","Sensor_INS","sub"), 10, &RosComm::Sensor_INSCallback,this));
	_pub_WiresLengths=ros::Publisher(_nh.advertise<config::PER::pub::WiresLengths>(fetchParam(&_nh,"PER","WiresLengths","pub"),10));
	_pub_Camera=ros::Publisher(_nh.advertise<config::PER::pub::Camera>(fetchParam(&_nh,"PER","Camera","pub"),10));
	_pub_Laser=ros::Publisher(_nh.advertise<config::PER::pub::Laser>(fetchParam(&_nh,"PER","Laser","pub"),10));
	_pub_INS=ros::Publisher(_nh.advertise<config::PER::pub::INS>(fetchParam(&_nh,"PER","INS","pub"),10));
	_pub_GPS=ros::Publisher(_nh.advertise<config::PER::pub::GPS>(fetchParam(&_nh,"PER","GPS","pub"),10));
	_pub_TF=ros::Publisher(_nh.advertise<config::PER::pub::TF>(fetchParam(&_nh,"PER","TF","pub"),10));
}
RosComm::~RosComm()
{
}
bool RosComm::init(int argc,char** argv){
	ros::init(argc,argv,"PER_node");
}


void RosComm::Sensor_SICKCallback(const config::PER::sub::Sensor_SICK::ConstPtr &msg)
{
	_comp->handleSensor_SICK(*msg);
}
	

void RosComm::Sensor_IBEOCallback(const config::PER::sub::Sensor_IBEO::ConstPtr &msg)
{
	_comp->handleSensor_IBEO(*msg);
}
	

void RosComm::Sensor_CAM_RCallback(const config::PER::sub::Sensor_CAM_R::ConstPtr &msg)
{
	_comp->handleSensor_CAM_R(*msg);
}
	

void RosComm::Sensor_CAM_LCallback(const config::PER::sub::Sensor_CAM_L::ConstPtr &msg)
{
	_comp->handleSensor_CAM_L(*msg);
}
	

void RosComm::Sensor_WIRECallback(const config::PER::sub::Sensor_WIRE::ConstPtr &msg)
{
	_comp->handleSensor_WIRE(*msg);
}
	

void RosComm::Sensor_GPSCallback(const config::PER::sub::Sensor_GPS::ConstPtr &msg)
{
	_comp->handleSensor_GPS(*msg);
}
	

void RosComm::Sensor_INSCallback(const config::PER::sub::Sensor_INS::ConstPtr &msg)
{
	_comp->handleSensor_INS(*msg);
}
	

void RosComm::publishWiresLengths( config::PER::pub::WiresLengths &msg)
{
	_pub_WiresLengths.publish(msg);
}
	

void RosComm::publishCamera( config::PER::pub::Camera &msg)
{
	_pub_Camera.publish(msg);
}
	

void RosComm::publishLaser( config::PER::pub::Laser &msg)
{
	_pub_Laser.publish(msg);
}
	

void RosComm::publishINS( config::PER::pub::INS &msg)
{
	_pub_INS.publish(msg);
}
	

void RosComm::publishGPS( config::PER::pub::GPS &msg)
{
	_pub_GPS.publish(msg);
}
	

void RosComm::publishTF( config::PER::pub::TF &msg)
{
	_pub_TF.publish(msg);
}
	
