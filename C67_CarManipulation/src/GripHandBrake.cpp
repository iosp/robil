#ifndef __GRIPHANDBRAKE__HPP
#define __GRIPHANDBRAKE__HPP

#include <actionlib/server/simple_action_server.h>
#include <C0_RobilTask/RobilTask.h>
#include <C0_RobilTask/RobilTaskAction.h>


using namespace std;
using namespace C0_RobilTask;

// include added
#include <math.h>
#include <ros/ros.h>
#include <ros/subscribe_options.h>
#include <boost/thread.hpp>
#include <boost/algorithm/string.hpp>
#include <atlas_msgs/AtlasState.h>
#include <atlas_msgs/AtlasCommand.h>
#include <sandia_hand_msgs/SimpleGraspSrv.h>
#include "std_msgs/String.h"
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <C67_CarManipulation/FK.h>
#include <C67_CarManipulation/IK.h>
#include <C67_CarManipulation/Path.h>
#include <PoseController/hand_movement.h>
#include <std_srvs/Empty.h>
// end added

//variables added
static ros::Publisher pubAtlasCommand;
static atlas_msgs::AtlasCommand ac;
static atlas_msgs::AtlasState as;
static ros::ServiceClient sandia_client;
static ros::ServiceClient joint_client;
static ros::ServiceClient joint_start_client;
static ros::ServiceClient joint_stop_client;

static sandia_hand_msgs::SimpleGraspSrv sandia_srv;
static PoseController::hand_movement joint_srv;
static std_srvs::Empty joint_start_srv;
static std_srvs::Empty joint_stop_srv;
static boost::mutex mutex;
static ros::Time t0;
static const unsigned int numJoints = 28;

static RPY argTarget;
static bool callBackRun = false;
//end added

ostream& operator<<(ostream& o, std::vector<string>& s){
	for(size_t i=0;i<s.size()-1;i++)
		o<<s[i]<<',';
	if(s.size()!=0)
		return o<<s[s.size()-1];
	return o;
}

class GripHandBrakeServer: public RobilTask {
protected:
	enum Consts { Time = 8 };
	enum Errors { NoParams = 1, NoSolution = 2 , SandiaCallFail = 3, JointCallFail = 4};
	std::vector<string> params;
	int operation;
	int time;
	int retValue;
	string outputstr;
	
public:
	GripHandBrakeServer(std::string name, std::vector<string> par):
        RobilTask(name), params(par)
    {
		cout<<"params: "<<params<<endl;
		
//		time = -1;
//		if( find(params, "time=").size()>0 ){
//			time = cast<int>(value(params,"time="));
//		}
		time = (int)Time*1000;
		
		retValue = 0;
		if( find(params, "return=").size()>0 ){
			retValue = cast<int>(value(params,"return="));
		}
		
		outputstr="process...";
		if( find(params, "print=").size()>0 ){
			outputstr = value(params,"print=");
		}


    }

    bool exists(Arguments& args, std::string name){
		return args.find(name) != args.end();
	}
	
	std::string find(std::vector<string>& s, std::string key){
		for(size_t i=0;i<s.size();i++){
			if(s[i].find(key)==0) return s[i];
		}
		return "";
	}
	std::string value(std::vector<string>& s, std::string key){
		for(size_t i=0;i<s.size();i++){
			if(s[i].find(key)==0) return s[i].substr(s[i].find('=')+1);
		}
		return "";
	}
	template<class A> A cast(std::string name){
		std::stringstream n;n<<name;
		A a; n>>a;
		return a;
	}	
 
	template<class A> A cast(Arguments& args, std::string name){
		std::stringstream n;n<<args[name];
		A a; n>>a;
		return a;
	}

	void Move(IkSolution origin, IkSolution goal, double sec, int pointsNum)
	{
		pPathPoints points = pPathPoints(origin, goal, pointsNum);

		for (int i=0; i<pointsNum; i++)
		{
			// ros::spinOnce();


			joint_srv.request.l_arm_usy = ac.position[q4l];
			joint_srv.request.l_arm_shx = ac.position[q5l];
			joint_srv.request.l_arm_ely = ac.position[q6l];
			joint_srv.request.l_arm_elx = ac.position[q7l];
			joint_srv.request.l_arm_uwy = ac.position[q8l];
			joint_srv.request.l_arm_mwx = ac.position[q9l];
			joint_srv.request.r_arm_usy = points.pArray[i]._q4;
			joint_srv.request.r_arm_shx = points.pArray[i]._q5;
			joint_srv.request.r_arm_ely = points.pArray[i]._q6;
			joint_srv.request.r_arm_elx = points.pArray[i]._q7;
			joint_srv.request.r_arm_uwy = points.pArray[i]._q8;
			joint_srv.request.r_arm_mwx = points.pArray[i]._q9;

			//ROS_INFO("");
			//std::cout << i <<": ";
			//points.Array[i].Print();

			if (!joint_client.call(joint_srv))
			{
				ROS_INFO("%s: Joint Service Call Failed!", _name.c_str());
				retValue  = JointCallFail;
				//return TaskResult(retValue, "ERROR");
			}

			//pubAtlasCommand.publish(ac);

			ros::Duration(sec/pointsNum).sleep();

		}
	}
    
    TaskResult task(const string& name, const string& uid, Arguments& args) {
		int time = this->time;
		// initiate return value
		retValue = 0;
		// get status data again
		callBackRun  = false;
		if( exists(args,"operation") ){
			operation = cast<int>(args["operation"]);
		}
		if (operation != 1)
			argTarget = RPY(.53 ,-.23 ,0.12,M_PI,0,0.3);	//Engage
		else
			argTarget = RPY(.35 ,-.23 ,0.05,M_PI,0,0.3);	//Release

		if( exists(args,"x") ){
			argTarget.x = cast<double>(args["x"]);
		}
		if( exists(args,"dx") ){
			argTarget.x += cast<double>(args["dx"]);
		}
		if( exists(args,"y") ){
			argTarget.y = cast<double>(args["y"]);
		}
		if( exists(args,"dy") ){
			argTarget.y += cast<double>(args["dy"]);
		}
		if( exists(args,"z") ){
			argTarget.z = cast<double>(args["z"]);
		}
		if( exists(args,"dz") ){
			argTarget.z += cast<double>(args["dz"]);
		}
		if( exists(args,"R") ){
			argTarget.R = cast<double>(args["R"]);
		}
		if( exists(args,"P") ){
			argTarget.P = cast<double>(args["P"]);
		}
		if( exists(args,"Y") ){
			argTarget.Y = cast<double>(args["Y"]);
		}

		if (!exists(args,"operation"))
		{
			ROS_INFO("%s: No operation Defined!", _name.c_str());
			retValue  = NoParams;
			return TaskResult(retValue, "ERROR");
		}


		ROS_INFO("%s: Target Operation %d - %s", _name.c_str(), operation, (operation == 1? "Release": "Engage"));

		while(time >= 0) {
			
			if(isPreempt()){
				
				return TaskResult::Preempted();
			}
			
//			if(outputstr!="no_print"){
//				ROS_INFO("%s: %s", _name.c_str(), outputstr.c_str());
//			}

			if(callBackRun)
			{
				ROS_INFO("Call Back Entered.");
				IkSolution IkCurrent = IkSolution(as.position[q4r], as.position[q5r], as.position[q6r], as.position[q7r],
									as.position[q8r], as.position[q9r]);
				if (operation != 1) // Engage
				{
					//open hand
					//sandia_srv.request.grasp.name = "cylindrical";
					sandia_srv.request.grasp.name = "prismatic";
					sandia_srv.request.grasp.closed_amount = 0.0;
					if (!sandia_client.call(sandia_srv))
					{
						ROS_INFO("%s: Sandia Hand Service Call Failed!", _name.c_str());
						retValue  = SandiaCallFail;
						return TaskResult(retValue, "ERROR");
					}
					//back in 12 centimeter
					argTarget.z += 0.12;
					IkSolution IkNext = rScanRPY(as.position[q1], as.position[q2], as.position[q3], argTarget,0.01);
					//back to origin
					argTarget.z -= 0.12;
					IkSolution IkNext2 = rScanRPY(as.position[q1], as.position[q2], as.position[q3], argTarget,0.01);
					//end position
					argTarget.x -= 0.12;
					argTarget.z -= 0.08;
					IkSolution IkNext3 = rScanRPY(as.position[q1], as.position[q2], as.position[q3], argTarget,0.01);
					//move out hand
					argTarget.z += 0.20;
					IkSolution IkNext4 = rScanRPY(as.position[q1], as.position[q2], as.position[q3], argTarget,0.01);

					if ((!IkNext.valid)||(!IkNext2.valid)||(!IkNext3.valid)||(!IkNext4.valid)){
						ROS_INFO("%s: No Solution!", _name.c_str());
						retValue  = NoSolution;
						return TaskResult(retValue, "ERROR");
					}
					// move near target
					Move(IkCurrent, IkNext, 2.0, 100);
					ros::Duration(1).sleep();
					Move(IkNext, IkNext2, 1.0, 50);
					sandia_srv.request.grasp.name = "cylindrical";
					sandia_srv.request.grasp.closed_amount = 1.0;
					if (!sandia_client.call(sandia_srv))
					{
						ROS_INFO("%s: Sandia Hand Service Call Failed!", _name.c_str());
						retValue  = SandiaCallFail;
						return TaskResult(retValue, "ERROR");
					}
					Move(IkNext2, IkNext3, 1.0, 50);
					Move(IkNext3, IkNext4, 1.0, 50);

					time -= 6000 ;
				}
				else
				{
					//close hand
					sandia_srv.request.grasp.name = "cylindrical";
					sandia_srv.request.grasp.closed_amount = 1.0;
					if (!sandia_client.call(sandia_srv))
					{
						ROS_INFO("%s: Sandia Hand Service Call Failed!", _name.c_str());
						retValue  = SandiaCallFail;
						return TaskResult(retValue, "ERROR");
					}
					//back in 12 centimeter
					argTarget.z += 0.05;
					IkSolution IkNext = rScanRPY(as.position[q1], as.position[q2], as.position[q3], argTarget,0.01);
					//back to origin
					argTarget.z -= 0.05;
					IkSolution IkNext2 = rScanRPY(as.position[q1], as.position[q2], as.position[q3], argTarget,0.01);
					//end position
					argTarget.x += 0.14;
					argTarget.z += 0.04;
					IkSolution IkNext3 = rScanRPY(as.position[q1], as.position[q2], as.position[q3], argTarget,0.01);
					//move out hand
					argTarget.z += 0.20;
					IkSolution IkNext4 = rScanRPY(as.position[q1], as.position[q2], as.position[q3], argTarget,0.01);

					if ((!IkNext.valid)||(!IkNext2.valid)||(!IkNext3.valid)||(!IkNext4.valid)){
						ROS_INFO("%s: No Solution!", _name.c_str());
						retValue  = NoSolution;
						return TaskResult(retValue, "ERROR");
					}
					// move near target
					Move(IkCurrent, IkNext, 2.0, 100);
					ros::Duration(1).sleep();
					Move(IkNext, IkNext2, 1.0, 50);
					Move(IkNext2, IkNext3, 2.0, 50);
					Move(IkNext3, IkNext4, 1.0, 50);

					time -= 7000 ;
				}
				ROS_INFO("%s: Finish movement", _name.c_str());
				break;
			}
			ros::Duration(0.1).sleep();
			//sleep(100);
			time -= 100 ;
		}
                
        
        //return TaskResult::Preempted();
        if( retValue > 0 ){
			return TaskResult(retValue, "ERROR");
		}
        return TaskResult(SUCCESS, "OK");
    }

};

#endif


#include "ros/ros.h"



//functions added
void SetAtlasState(const atlas_msgs::AtlasState::ConstPtr &_as)
{


	if (callBackRun == false)
	{
		callBackRun = true;

		static ros::Time startTime = ros::Time::now();
		t0 = startTime;

		// lock to copy incoming AtlasState
		{
			boost::mutex::scoped_lock lock(mutex);
			as = *_as;
		}

		ac.header.stamp = as.header.stamp;


		// set cout presentation
//		std::cout.precision(6);
//		std::cout.setf (std::ios::fixed , std::ios::floatfield );
//		// print current state
//		std::cout << "Current Position:\n";
//		IkSolution IkCurrent = IkSolution(as.position[q4r],as.position[q5r],
//			as.position[q6r],	as.position[q7r], as.position[q8r], as.position[q9r]);
//		IkCurrent.Print();
//		RPY rCurrent = rPose(as.position[q1], as.position[q2],as.position[q3],IkCurrent);
//		rCurrent.Print();
//
//		// print target
//		if (use_arg)
//		{
//			std::cout << "Target:\n";
//			argTarget.Print();
//		}

		for (unsigned int i = 0; i < numJoints; i++)
		{
			ac.kp_position[i] = as.kp_position[i];
			ac.ki_position[i] = as.ki_position[i];
			ac.kd_position[i] = as.kd_position[i];
			ac.i_effort_min[i] = as.i_effort_min[i];
			ac.i_effort_max[i] = as.i_effort_max[i];

			ac.velocity[i] = 0;
			ac.effort[i] = 0;
			ac.kp_velocity[i] = 0;

		}

		// assign current joint angles
		for (unsigned int j=0; j<numJoints; j++)
		{
			ac.position[j] = as.position[j];
			ac.k_effort[j]  = 255;
			//std::cout << state[j] << " ";
		}
	}


  // uncomment to simulate state filtering
  // usleep(1000);

}

int main(int argc, char **argv)
{
	if(argc<0) return 1;
	std::string tname ("GripHandBrake");
	
	if(tname=="-h" || tname=="--help"){
		cout<<"GripHandBrake Server"<<endl;
		cout<<"Syntax: GripHandBrakeServer [ARG1=VALUE] [ARG2=VALUE] ..."<<endl;
		cout<<"Arguments:"<<endl;
		//cout<<"    time=INTEGER    : time (in mS) for task running. if -1, wait forever"<<endl;
		cout<<"    return=INTEGER  : return value of task: 0 is OK, -1 is PLAN, 0< is a ERROR CODE "<<endl;
		cout<<"    print=STRING    : print progress text. default is 'process...' and 'no_print' suppress printing."<<endl;
		return 0;
	}
	
	stringstream snodename; snodename<<"GripHandBrakeServerNode_"<<time(NULL);
	ROS_INFO("Start %s", snodename.str().c_str());
	
	ros::init(argc, argv, snodename.str().c_str());
	//ros::NodeHandle node;
	// add initializations
	ros::NodeHandle* rosnode = new ros::NodeHandle();

	ros::Time last_ros_time_;
	bool wait = true;
	while (wait)
	{
		last_ros_time_ = ros::Time::now();
		if (last_ros_time_.toSec() > 0)
		wait = false;
	}

	unsigned int n = numJoints;
	ac.position.resize(n);
	ac.k_effort.resize(n);
	ac.velocity.resize(n);
	ac.effort.resize(n);
	ac.kp_position.resize(n);
	ac.ki_position.resize(n);
	ac.kd_position.resize(n);
	ac.kp_velocity.resize(n);
	ac.i_effort_min.resize(n);
	ac.i_effort_max.resize(n);


	// ros topic subscribtions
	ros::SubscribeOptions atlasStateSo =
		ros::SubscribeOptions::create <atlas_msgs::AtlasState> (
		"/atlas/atlas_state", 100, SetAtlasState,
		ros::VoidPtr(), rosnode->getCallbackQueue());

	atlasStateSo.transport_hints = ros::TransportHints().reliable().tcpNoDelay(true);
	  ros::Subscriber subAtlasState = rosnode->subscribe(atlasStateSo);

	// ros topic publisher
	pubAtlasCommand = rosnode->advertise<atlas_msgs::AtlasCommand>(
		"/atlas/atlas_command", 100, true);
	//end additions
	
	//Sandia client
	sandia_client = rosnode->serviceClient<sandia_hand_msgs::SimpleGraspSrv>("/sandia_hands/r_hand/simple_grasp");

	joint_start_client = rosnode->serviceClient<std_srvs::Empty>("/PoseController/start");
	joint_client = rosnode->serviceClient<PoseController::hand_movement>("/PoseController/hand_movement");
	joint_start_client.call(joint_start_srv);
	if (!joint_start_client.call(joint_start_srv))
	{
		ROS_INFO("Fail calling Joint Server");
		return 1;
	}

	ROS_INFO("create task");
	

	std::vector<string> params;
	if(argc>1){
		for(int i=1; i<argc; i++){
			params.push_back(argv[i]);
		}
	}
	if(argc == 1) params.push_back("No Parameters");
	GripHandBrakeServer task(tname, params);

	ros::spin();

	return 0;
}
