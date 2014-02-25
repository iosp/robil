
/*
 * RosComm.h
 *
 *  Created on: Tuesday, 25. February 2014 12:20PM
 *      Author: autogenerated
 */
#ifndef ROSCOMM_H_
#define ROSCOMM_H_
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>
#include <ParameterTypes.h>
#include <tf/tf.h>
#include <boost/thread.hpp>
class ComponentMain;
class RosComm {
  bool _inited;
  ComponentMain   * _comp;
  ros::NodeHandle _nh;
  ros::Publisher _pub_diagnostic;
  boost::thread_group _maintains;
	ros::Subscriber _sub_CustomIED;
	ros::Subscriber _sub_LocalPath;
	ros::Publisher  _pub_IEDLocation;

  bool init(int argc,char** argv);
public:
	RosComm(ComponentMain* comp,int argc,char** argv);
	virtual ~RosComm();
	void CustomIEDCallback(const config::IEDSIM::sub::CustomIED::ConstPtr &msg);
	void LocalPathCallback(const config::IEDSIM::sub::LocalPath::ConstPtr &msg);
	void publishIEDLocation( config::IEDSIM::pub::IEDLocation &msg);

	void publishTransform(const tf::Transform& _tf, std::string srcFrame, std::string distFrame);
	tf::StampedTransform getLastTrasform(std::string srcFrame, std::string distFrame);
	void publishDiagnostic(const diagnostic_msgs::DiagnosticStatus& _report);
	void publishDiagnostic(const std_msgs::Header& header, const diagnostic_msgs::DiagnosticStatus& _report);
	void heartbeat();
};
#endif /* ROSCOMM_H_ */
