#ifndef _C11_PUSH_SERVER_H_
#define _C11_PUSH_SERVER_H_

//tasks dependencies
#include <actionlib/server/simple_action_server.h>
#include <C0_RobilTask/RobilTask.h>
#include <C0_RobilTask/RobilTaskAction.h>
#include <C0_RobilTask/StringOperations.h>
#include "C21_VisionAndLidar/C21_Pan.h"
#include "C21_VisionAndLidar/C21_Pic.h"
//#include <cstdlib>
#include <sensor_msgs/image_encodings.h>
#include <image_transport/image_transport.h>
#include "C22_GroundRecognitionAndMapping/C22.h"
#include "C10_Common/push_img.h"
#include "C10_Common/push_occupancy_grid.h"

using namespace std;
using namespace C0_RobilTask;

class PushHMIServer:public RobilTask{


public:
	PushHMIServer(string name = "/PushHMI"):
    	RobilTask(name)
    {

    }

	TaskResult panoramic_image_task()
	{
		ros::ServiceClient c21Client = _node.serviceClient<C21_VisionAndLidar::C21_Pic>("C21/Pic");

		C21_VisionAndLidar::C21_Pic srv21;
		srv21.request.req.cmd=C21_VisionAndLidar::C21_PICTURE::LEFT;
		if (!c21Client.call(srv21))
		{
			ROS_ERROR("couldn't get a picture, exiting\n");
			return TaskResult::FAULT();
		}

		ros::ServiceClient c11Client = _node.serviceClient<C10_Common::push_img>("C11/push_img");

		C10_Common::push_img srv11;

		srv11.request.IMG = srv21.response.res;

		if (!c11Client.call(srv11))
		{
			ROS_ERROR("couldn't get a C11 reply, exiting\n");
			return TaskResult::FAULT();

		}

		 if (srv11.response.ACK.mes != 1) {
			ROS_ERROR("C11 ack is fault, exiting\n");
			return TaskResult::FAULT();
		 }

		 return TaskResult::SUCCESS ();
	}

	TaskResult occupancy_grid_task()
	{
		ros::ServiceClient c22Client = _node.serviceClient<C22_GroundRecognitionAndMapping::C22>("C22");
		C22_GroundRecognitionAndMapping::C22 srv22;
		if (!c22Client.call(srv22))
		{
			ROS_ERROR("couldn't get a occupancy grid, exiting\n");
			return TaskResult::FAULT();
		}
		ros::ServiceClient c11Client = _node.serviceClient<C10_Common::push_occupancy_grid>("C11/push_occupancy_grid");

		C10_Common::push_occupancy_grid srv11;

		srv11.request.OGD = srv22.response.drivingPath;
		if (!c11Client.call(srv11))
		{
			ROS_ERROR("couldn't get a C11 reply, exiting\n");
			return TaskResult::FAULT();

		}

		 if (srv11.response.ACK.mes != 1) {
			ROS_ERROR("C11 ack is fault, exiting\n");
			return TaskResult::FAULT();
		 }

		return TaskResult::SUCCESS ();
	}

    TaskResult task(const string& name, const string& uid, Arguments& args){

    	ROS_INFO("C11_Agent: PushHMI called!\n");
    	if(!args.empty())
    	{
    		ROS_INFO("%s: %s\n","data",args["data"].data());
    		string str = args["data"];
    		if(!str.empty())
    		{
    			if(str == "panoramic_image")
    			{
    				ROS_INFO("panoramic_image BINGO");
    				return panoramic_image_task();
    			}
    			else if(str == "occupancy_grid")
				{
    				ROS_INFO("occupancy_grid BINGO");
    				return occupancy_grid_task();
				}
    		}
    	}
    	return TaskResult::FAULT();
    }
};


#endif //_C11_PUSH_SERVER_