
/*
 * ComponentMain.h
 *
 *  Created on: Tuesday, 25. February 2014 12:20PM
 *      Author: autogenerated
 */
#ifndef COMPONENTMAIN_H_
#define COMPONENTMAIN_H_
#include <std_msgs/String.h>
#include <ParameterTypes.h>
#include <tf/tf.h>
class RosComm;
class ComponentMain {
	RosComm* _roscomm;
public:
	ComponentMain(int argc,char** argv);
	virtual ~ComponentMain();
	void handleIEDLocation(const config::SMME::sub::IEDLocation& msg);
	void handleAssignNavTask(const config::SMME::sub::AssignNavTask& msg);
	void handleAssignManTask(const config::SMME::sub::AssignManTask& msg);
	void handleAssignMission(const config::SMME::sub::AssignMission& msg);
	void handleBladePosition(const config::SMME::sub::BladePosition& msg);
	void handleLocation(const config::SMME::sub::Location& msg);
	void publishGlobalPath(config::SMME::pub::GlobalPath& msg);
	void publishWorkSeqData(config::SMME::pub::WorkSeqData& msg);
	void publishMissionAcceptance(config::SMME::pub::MissionAcceptance& msg);
	void publishTransform(const tf::Transform& _tf, std::string srcFrame, std::string distFrame);
	tf::StampedTransform getLastTrasform(std::string srcFrame, std::string distFrame);
	void publishDiagnostic(const diagnostic_msgs::DiagnosticStatus& _report);
	void publishDiagnostic(const std_msgs::Header& header, const diagnostic_msgs::DiagnosticStatus& _report);
};
#endif /* COMPONENTMAIN_H_ */
