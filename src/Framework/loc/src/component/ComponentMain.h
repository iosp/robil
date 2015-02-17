
/*
 * ComponentMain.h
 *
 *  Created on: Thursday, 27. February 2014 12:29PM
 *      Author: autogenerated
 */
#ifndef COMPONENTMAIN_H_
#define COMPONENTMAIN_H_
#include <std_msgs/String.h>
#include <ParameterTypes.h>
#include <tf/tf.h>
#include "ekf_class.h"
#include "noiseless_estimator.h"
#include <boost/thread.hpp>
class RosComm;
//class ComponentMain;
class ComponentMain {
	RosComm* _roscomm;
public:
	ComponentMain(int argc,char** argv);
	virtual ~ComponentMain();
	static void performEstimation();
	void handlePositionUpdate(const config::LOC::sub::PositionUpdate& msg);
	void setSteeringInput(double msg);
	void setThrottleInput(double msg);
	void handleGPS(const config::LOC::sub::GPS& msg);
	void handleINS(const config::LOC::sub::INS& msg);
	void handleVOOdometry(const config::LOC::sub::VOOdometry& msg);
	void handleGpsSpeed(const config::LOC::sub::PerGpsSpeed& msg);
	void publishLocation(config::LOC::pub::Location& msg);
	void publishPerVelocity(config::LOC::pub::PerVelocity& msg);
	void publishTransform(const tf::Transform& _tf, std::string srcFrame, std::string distFrame);
	tf::StampedTransform getLastTrasform(std::string srcFrame, std::string distFrame);
	void publishDiagnostic(const diagnostic_msgs::DiagnosticStatus& _report);
	void publishDiagnostic(const std_msgs::Header& header, const diagnostic_msgs::DiagnosticStatus& _report);
private:
  ekf _estimator;
  Observer _observer;
  boost::thread* _estimation_thread;
  static ComponentMain *_this;
};
#endif /* COMPONENTMAIN_H_ */
