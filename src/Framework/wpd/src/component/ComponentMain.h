
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
	void handleMiniMap(const config::WPD::sub::MiniMap& msg);
	void handleLocalPathPlan(const config::WPD::sub::LocalPathPlan& msg);
	void handlePosAttVel(const config::WPD::sub::PosAttVel& msg);
	void publishSpeed(config::WPD::pub::Speed& msg);
};
#endif /* COMPONENTMAIN_H_ */
