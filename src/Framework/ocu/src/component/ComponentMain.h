
/*
 * ComponentMain.h
 *
 *  Created on: Sunday, 02. February 2014 10:01AM
 *      Author: autogenerated
 */
#ifndef COMPONENTMAIN_H_
#define COMPONENTMAIN_H_
#include <std_msgs/String.h>
#include <ParameterTypes.h>
class RosComm;
class ComponentMain {
	RosComm* _roscomm;
public:
	ComponentMain(int argc,char** argv);
	virtual ~ComponentMain();
	void handlePosAttVel(const config::OCU::sub::PosAttVel& msg);
	void handleStatusData(const config::OCU::sub::StatusData& msg);
	void handleMissionStatus(const config::OCU::sub::MissionStatus& msg);
	void handleMap(const config::OCU::sub::Map& msg);
	void handleLocalPathPlan(const config::OCU::sub::LocalPathPlan& msg);
	void handleIEDDetectionEvent(const config::OCU::sub::IEDDetectionEvent& msg);
	void handleIEDLocation(const config::OCU::sub::IEDLocation& msg);
	void publishPositionUpdate(config::OCU::pub::PositionUpdate& msg);
	void publishMissionPlan(config::OCU::pub::MissionPlan& msg);
	void publishTeleoperation(config::OCU::pub::Teleoperation& msg);
	void publishIEDDetectionEvent(config::OCU::pub::IEDDetectionEvent& msg);
	void publishIEDLocation(config::OCU::pub::IEDLocation& msg);
};
#endif /* COMPONENTMAIN_H_ */
