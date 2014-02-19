
/*
 * ComponentMain.h
 *
 *  Created on: Wednesday, 19. February 2014 02:34PM
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
	void handleWPDVelocity(const config::LLC::sub::WPDVelocity& msg);
	void handleWSMVelocity(const config::LLC::sub::WSMVelocity& msg);
	void handleBladePositionCommand(const config::LLC::sub::BladePositionCommand& msg);
	void handlePerVelocity(const config::LLC::sub::PerVelocity& msg);
	void handleLocation(const config::LLC::sub::Location& msg);
	void publishEffortsTh(config::LLC::pub::EffortsTh& msg);
	void publishEffortsSt(config::LLC::pub::EffortsSt& msg);
	void publishEffortsJn(config::LLC::pub::EffortsJn& msg);
	void publishTransform(const tf::Transform& _tf, std::string srcFrame, std::string distFrame);
	tf::StampedTransform getLastTrasform(std::string srcFrame, std::string distFrame);
	void publishDiagnostic(const diagnostic_msgs::DiagnosticStatus& _report);
	void publishDiagnostic(const std_msgs::Header& header, const diagnostic_msgs::DiagnosticStatus& _report);
};
#endif /* COMPONENTMAIN_H_ */
