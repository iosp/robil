#ifndef __PICKUP__HPP
#define __PICKUP__HPP

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
#include "FK.h"
#include "IK.h"
#include "Path.h"
#include "Trace.h"
#include <C23_dFind/perceptionTransform.h>
#include <C23_ObjectRecognition/C23_orient.h>
// end added

//variables added
static ros::Publisher pubAtlasCommand;
static atlas_msgs::AtlasCommand ac;
static atlas_msgs::AtlasState as;
static ros::ServiceClient sandia_client, perception_transform_cli_;
static sandia_hand_msgs::SimpleGraspSrv sandia_srv;
static C23_dFind::perceptionTransform perception_srv_msg;
static ros::ServiceClient c23client;
static boost::mutex mutex;
static boost::mutex send_mutex;
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


void update_comand(){
	boost::mutex::scoped_lock l(send_mutex);
//	sandia_srv.request.grasp.name = "cylindrical";
//	sandia_srv.request.grasp.closed_amount = 0.0;
	if (!sandia_client.call(sandia_srv))
	{
//		ROS_INFO("%s: Sandia Hand Service Call Failed!", _name.c_str());
//		retValue  = SandiaCallFail;
//		return TaskResult(retValue, "ERROR");
	}
}


class PickUpServer: public RobilTask {
protected:
	enum Consts { Time = 7 };
	enum Errors { NoParams = 1, NoSolution = 2 , SandiaCallFail = 3};
	std::vector<string> params;
	int operation;
	int time;
	int retValue;
	string outputstr;


public:
	PickUpServer(std::string name, std::vector<string> par):
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
		pPathPoints points(origin,goal,pointsNum,StartEnd);

		for (int i=0; i<pointsNum; i++)
		{
			// ros::spinOnce();


			ac.position[q4r] = points.pArray[i]._q4;
			ac.position[q5r] = points.pArray[i]._q5;
			ac.position[q6r] = points.pArray[i]._q6;
			ac.position[q7r] = points.pArray[i]._q7;
			ac.position[q8r] = points.pArray[i]._q8;
			ac.position[q9r] = points.pArray[i]._q9;
			//Move neck
			ac.position[3]=0.7;

			//ROS_INFO("");
			//std::cout << i <<": ";
			//points.Array[i].Print();

			pubAtlasCommand.publish(ac);

			ros::Duration(sec/pointsNum).sleep();

		}
	}

	void lMove(IkSolution origin, IkSolution goal, double sec, int pointsNum)
		{
			pPathPoints points(origin,goal,pointsNum,StartEnd);

			for (int i=0; i<pointsNum; i++)
			{
				// ros::spinOnce();


				ac.position[q4l] = points.pArray[i]._q4;
				ac.position[q5l] = points.pArray[i]._q5;
				ac.position[q6l] = points.pArray[i]._q6;
				ac.position[q7l] = points.pArray[i]._q7;
				ac.position[q8l] = points.pArray[i]._q8;
				ac.position[q9l] = points.pArray[i]._q9;

				//ROS_INFO("");
				//std::cout << i <<": ";
				//points.Array[i].Print();

				pubAtlasCommand.publish(ac);

				ros::Duration(sec/pointsNum).sleep();

			}
		}

	bool getObjectData(string target, double *x, double *y, double *z, double *R, double *P, double *Y) {
	    C23_ObjectRecognition::C23_orient c23srv;
	    c23srv.request.target = target;

	    ROS_INFO("Calling C23 perception service");
	    if(c23client.call(c23srv))
	    {
	        *x = c23srv.response.x;
	        *y = c23srv.response.y;
	        *z = c23srv.response.z;
	        *R = c23srv.response.R;
	        *P = c23srv.response.P;
	        *Y = c23srv.response.Y;

	        ROS_INFO("Received data from majd: x= %f , y= %f , z= %f",*x ,*y ,*z );
	        //cout << "Received data from majd: " << c23srv.response.x << "," << c23srv.response.y << "," << c23srv.response.z << endl;
	        return true;
	    }
	    else
	    {
	    	ROS_INFO("No Message From Majd" );

	    }
	    return false;

	}

	//Move the three back angles
	void MoveBack(IkSolution origin, IkSolution goal, double sec, int pointsNum)
		{
			pPathPoints points(origin,goal,pointsNum);
			ROS_INFO("Moving back of the robot to target position");
			for (int i=0; i<pointsNum; i++)
			{

				ac.position[q1] = points.pArray[i].m_q[0];
				ac.position[q2] = points.pArray[i].m_q[1];
				ac.position[q3] = points.pArray[i].m_q[2];

				pubAtlasCommand.publish(ac);

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

		argTarget = RPY(0.0 ,0.0 ,0.0,M_PI,0.0,0.0);	//Reverse

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

//		if (!exists(args,"operation"))
//		{
//			ROS_INFO("%s: No operation Defined!", _name.c_str());
//			retValue  = NoParams;
//			return TaskResult(retValue, "ERROR");
//		}

		//open hand
		{boost::mutex::scoped_lock l(send_mutex);
			sandia_srv.request.grasp.name = "cylindrical";
			sandia_srv.request.grasp.closed_amount = 0.0;
		}
//		if (!sandia_client.call(sandia_srv))
//		{
//			ROS_INFO("%s: Sandia Hand Service Call Failed!", _name.c_str());
//			retValue  = SandiaCallFail;
//			return TaskResult(retValue, "ERROR");
//		}


		ROS_INFO("%s: Target Operation %d - %s", _name.c_str(), operation, (operation == 1? "Forward": "Reverse"));

		while(time >= 0) {

			if(isPreempt()){

				return TaskResult::Preempted();
			}

//			if(outputstr!="no_print"){
//				ROS_INFO("%s: %s", _name.c_str(), outputstr.c_str());
//			}
//--------------------------------------------------------------------------------------
			if(callBackRun)
			{
				ROS_INFO("Call Back Entered.");

				//RPY destination = RPY(0.46,-0.071,-0.1,-3.14,0.5,1.442);
				//Matrix DestM = destination.FromRPY();







				//current angles of the right arm
				IkSolution IkCurrent = IkSolution(as.position[q4r], as.position[q5r], as.position[q6r], as.position[q7r],
									as.position[q8r], as.position[q9r]);
				Move(IkCurrent,IkCurrent,1,10);

				//current angles of the left arm
				IkSolution IkCurrentL = IkSolution(as.position[q4l], as.position[q5l], as.position[q6l], as.position[q7l],
													as.position[q8l], as.position[q9l]);

				//grasp position from perception
				string target = "Firehose";
				getObjectData(target,&(argTarget.x), &(argTarget.y), &(argTarget.z), &(argTarget.R), &(argTarget.P), &(argTarget.Y));
				//since no solution from perception yet, we override it
				ROS_INFO("Hose from perception: x=%f, y=%f, z=%f, R=%f, P=%f, Y=%f", argTarget.x, argTarget.y, argTarget.z, argTarget.R, argTarget.P, argTarget.Y);
				RPY Origin=RPY(0.52, -0.072657, 0.217362, -3.135264, 0, 1.460349); //Origin=RPY(0.52, -0.072657, 0.217362, -3.135264, 0, 1.460349)
				argTarget=TraceAB(Origin,argTarget);
//				argTarget.x += Origin.x;
//				argTarget.y += Origin.y;
//				argTarget.z += Origin.z;
//				argTarget.R += Origin.R;
//				argTarget.P += Origin.P;
//				argTarget.Y += Origin.Y;
				//argTarget=RPY(0.46,-0.071,-0.2,-3.14,0.0,1.442);
				ROS_INFO("Hose After Matric Multiply: x=%f, y=%f, z=%f, R=%f, P=%f, Y=%f", argTarget.x, argTarget.y, argTarget.z, argTarget.R, argTarget.P, argTarget.Y);
				//Back movement from current to desired:
				double current_q1=as.position[q1]; //lbz
				double current_q2=as.position[q2]; //mby
				double current_q3=as.position[q3]; //ubx
				double desired_q1=0.0;
				double desired_q2=0.0;
				double desired_q3=0.0;

				//move the back
				IkSolution current_back=IkSolution(current_q1, current_q2, current_q3,0,0,0);
				ROS_INFO("current_back: q1=%f, q2=%f, q3=%f", current_q1, current_q2, current_q3);
				IkSolution target_back=IkSolution(desired_q1,desired_q2,desired_q3,0,0,0);
				MoveBack(current_back , target_back , 2 , 100);

				// Find the IK solution for the next solution of the arm
				RPY arm_offset=RPY(0,0,0,0,0,0); //the offset between the perception point and the desired grasp point
				// the target position for the arm

				//Multiply the transformation matrices from argTarget to arm_offset
				RPY arm_target = TraceAngle(argTarget,arm_offset,0.0);
				arm_target.z += 0.15;
				ROS_INFO("here1");
				IkSolution IkNext0 = rScanRPY(desired_q1,desired_q2,desired_q3, arm_target,0.01);
				arm_target.z -= 0.18;
				ROS_INFO("here2");
				IkSolution IkNext = rScanRPY(desired_q1,desired_q2,desired_q3, arm_target,0.01);
				arm_target.z += 0.2;
				arm_target.x += 0.0;
				arm_target.R += 0.5;
				ROS_INFO("here3");
				IkSolution IkNext2 = rScanRPY(desired_q1,desired_q2,desired_q3, arm_target,0.01);
				ROS_INFO("here4");
//				arm_target.z -= 0.15;
//				arm_target.R += 1.57;
//				arm_target.Y = -arm_target.Y;
//				IkSolution IkNextL = lScanRPY(desired_q1,desired_q2,desired_q3, arm_target,0.01);

				if ((!IkNext0.valid)||(!IkNext.valid)||(!IkNext2.valid)){
					ROS_INFO("%s: No Solution!", _name.c_str());
					retValue  = NoSolution;
					//return TaskResult(retValue, "ERROR");
				}
				{boost::mutex::scoped_lock l(send_mutex);
							sandia_srv.request.grasp.name = "cylindrical";
							sandia_srv.request.grasp.closed_amount = 0.37;
						}

				ros::Duration(1).sleep();
				Move(IkCurrent, IkNext0, 3.0, 100);
				ROS_INFO("here5");
				ros::Duration(1).sleep();
				Move(IkNext0, IkNext, 3.0, 100);
				ROS_INFO("here6");
				ros::Duration(2).sleep();
				//close hand
				{boost::mutex::scoped_lock l(send_mutex);
							sandia_srv.request.grasp.name = "cylindrical";
							sandia_srv.request.grasp.closed_amount = 1.0;
						}
				ros::Duration(2).sleep();
				Move(IkNext, IkNext2, 5.0, 100);
				ROS_INFO("here7");
/* Move left arm
				ros::Duration(2).sleep();
				lMove(IkCurrentL, IkNextL, 5.0, 100);
*/
				/*
				ros::Duration(1).sleep();
				IkSolution target_back1=IkSolution(2.5,desired_q2,desired_q3,0,0,0);
				MoveBack(target_back , target_back1 , 5 , 100);

				ros::Duration(1).sleep();
				IkSolution target_back2=IkSolution(0.0,desired_q2,desired_q3,0,0,0);
				MoveBack(target_back1 , target_back2 , 5 , 100);
*/
				time -= 2000 ;
				ROS_INFO("%s: Finish movement", _name.c_str());
				break;
			}
			ros::Duration(0.1).sleep();
			//sleep(100);
			time -= 100 ;
		}
   //--------------------------------------------------------------------

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

		for (unsigned int i = 0; i < numJoint
		ros::Time last_ros_time_;
		bool wait = true;
		ws; i++)
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
			if (((j>=q4r)&&(j<=q9r))||((j>=q4l)&&(j<=q9l))||((j>=q1)&&(j<=q3)))
				ac.k_effort[j]  = 255;
			//std::cout << state[j] << " ";
		}
		ac.k_effort[3]  = 255;
	}


  // uncomment to simulate state filtering
  // usleep(1000);

}



int main(int argc, char **argv)
{
	if(argc<0) return 1;
	std::string tname ("PickUp");

	if(tname=="-h" || tname=="--help"){
		cout<<"PickUp Server"<<endl;
		cout<<"Syntax: PickUpServer [ARG1=VALUE] [ARG2=VALUE] ..."<<endl;
		cout<<"Arguments:"<<endl;
		//cout<<"    time=INTEGER    : time (in mS) for task running. if -1, wait forever"<<endl;
		cout<<"    return=INTEGER  : return value of task: 0 is OK, -1 is PLAN, 0< is a ERROR CODE "<<endl;
		cout<<"    print=STRING    : print progress text. default is 'process...' and 'no_print' suppress printing."<<endl;
		return 0;
	}

	stringstream snodename; snodename<<"PickUpServerNode_"<<time(NULL);
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
	//perception_transform_cli_ = nh_.serviceClient<C23_dFind::perceptionTransform>("perceptionTransform");

	//Perception client
	c23client = rosnode->serviceClient<C23_ObjectRecognition::C23_orient>("/C23/C66");

	ROS_INFO("create task");


	std::vector<string> params;
	if(argc>1){
		for(int i=1; i<argc; i++){
			params.push_back(argv[i]);
		}
	}
	if(argc == 1) params.push_back("No Parameters");
	PickUpServer task(tname, params);

	//ros::spin();
	ros::Rate r(2);
	while(ros::ok()){
		update_comand();
		r.sleep();
		ros::spinOnce();
	}

	return 0;
}
