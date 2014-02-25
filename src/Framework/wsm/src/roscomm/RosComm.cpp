
/*
 * RosComm.cpp
 *
 *  Created on: Tuesday, 25. February 2014 12:20PM
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
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
RosComm::RosComm(ComponentMain* comp,int argc,char** argv)
	: _inited(init(argc, argv)), _comp(comp)
{
	_sub_WorkSeqData=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"WSM","WorkSeqData","sub"), 10, &RosComm::WorkSeqDataCallback,this));
	_sub_BladePosition=ros::Subscriber(_nh.subscribe(fetchParam(&_nh,"WSM","BladePosition","sub"), 10, &RosComm::BladePositionCallback,this));
	_pub_WSMVelocity=ros::Publisher(_nh.advertise<config::WSM::pub::WSMVelocity>(fetchParam(&_nh,"WSM","WSMVelocity","pub"),10));
	_pub_BladePositionCommand=ros::Publisher(_nh.advertise<config::WSM::pub::BladePositionCommand>(fetchParam(&_nh,"WSM","BladePositionCommand","pub"),10));
	_pub_diagnostic=ros::Publisher(_nh.advertise<diagnostic_msgs::DiagnosticArray>("/diagnostics",100));
	_maintains.add_thread(new boost::thread(boost::bind(&RosComm::heartbeat,this)));
}
RosComm::~RosComm()
{
}
bool RosComm::init(int argc,char** argv){
	ros::init(argc,argv,"WSM_node");
	return true;
}


void RosComm::WorkSeqDataCallback(const config::WSM::sub::WorkSeqData::ConstPtr &msg)
{
	_comp->handleWorkSeqData(*msg);
}
	

void RosComm::BladePositionCallback(const config::WSM::sub::BladePosition::ConstPtr &msg)
{
	_comp->handleBladePosition(*msg);
}
	

void RosComm::publishWSMVelocity( config::WSM::pub::WSMVelocity &msg)
{
	_pub_WSMVelocity.publish(msg);
}
	

void RosComm::publishBladePositionCommand( config::WSM::pub::BladePositionCommand &msg)
{
	_pub_BladePositionCommand.publish(msg);
}
	
void RosComm::publishTransform(const tf::Transform& _tf, std::string srcFrame, std::string distFrame){
	static tf::TransformBroadcaster br;
	br.sendTransform(tf::StampedTransform(_tf, ros::Time::now(), srcFrame, distFrame));
}
tf::StampedTransform RosComm::getLastTrasform(std::string srcFrame, std::string distFrame){
	tf::StampedTransform _tf;
	static tf::TransformListener listener;
	try {
	    listener.waitForTransform(distFrame, srcFrame, ros::Time(0), ros::Duration(10.0) );
	    listener.lookupTransform(distFrame, srcFrame, ros::Time(0), _tf);
	} catch (tf::TransformException& ex) {
	    ROS_ERROR("%s",ex.what());
	}
	return _tf;
}
void RosComm::publishDiagnostic(const diagnostic_msgs::DiagnosticStatus& _report){
	diagnostic_msgs::DiagnosticArray msg;
	msg.status.push_back(_report);
	_pub_diagnostic.publish(msg);
}
void RosComm::publishDiagnostic(const std_msgs::Header& header, const diagnostic_msgs::DiagnosticStatus& _report){
	diagnostic_msgs::DiagnosticArray msg;
	msg.header = header;
	msg.status.push_back(_report);
	_pub_diagnostic.publish(msg);
}
void RosComm::heartbeat(){
	using namespace boost::posix_time;
	ros::Publisher _pub = _nh.advertise<std_msgs::String>("/heartbeat", 10);
	double hz = HEARTBEAT_FREQUANCY;
	while(ros::ok()){
		boost::system_time stop_time = boost::get_system_time() + milliseconds((1/hz)*1000);
		std_msgs::String msg;
		msg.data = "WSM";
		_pub.publish(msg);
	    boost::this_thread::sleep(stop_time);
	}
}
