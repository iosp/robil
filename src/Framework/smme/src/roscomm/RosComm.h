
/*
 * RosComm.h
 *
 *  Created on: Sunday, 02. February 2014 10:15AM
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
class ComponentMain;
class RosComm {
  bool _inited;
  ComponentMain   * _comp;
  ros::NodeHandle _nh;
	ros::Subscriber _sub_IEDDetectionEvent;
	ros::Subscriber _sub_IEDLocation;
	ros::Subscriber _sub_MissionPlan;
	ros::Subscriber _sub_StatusData;
	ros::Publisher  _pub_MissionStatus;
	ros::Publisher  _pub_MissionGlobalPath;
	ros::Publisher  _pub_IEDPosAtt;
	ros::Publisher  _pub_ExecuteWorkSequenceCommand;

  bool init(int argc,char** argv);
public:
	RosComm(ComponentMain* comp,int argc,char** argv);
	virtual ~RosComm();
	void IEDDetectionEventCallback(const config::SMME::sub::IEDDetectionEvent::ConstPtr &msg);
	void IEDLocationCallback(const config::SMME::sub::IEDLocation::ConstPtr &msg);
	void MissionPlanCallback(const config::SMME::sub::MissionPlan::ConstPtr &msg);
	void StatusDataCallback(const config::SMME::sub::StatusData::ConstPtr &msg);
	void publishMissionStatus( config::SMME::pub::MissionStatus &msg);
	void publishMissionGlobalPath( config::SMME::pub::MissionGlobalPath &msg);
	void publishIEDPosAtt( config::SMME::pub::IEDPosAtt &msg);
	void publishExecuteWorkSequenceCommand( config::SMME::pub::ExecuteWorkSequenceCommand &msg);

};
#endif /* ROSCOMM_H_ */