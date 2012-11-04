/**************************************************************************************
 * This is a template for the c51_carOperation module for the robil project
 * The c51_carOperation module goal is to provide the car operation
 * using the data received from the vision capability modules
 * There is no actual input/output at this time, this goes according to the current milestone
 * set at the robil management meeting
 * 
 **************************************************************************************/

#include "ros/ros.h"
#include "c51_carOperation/C51.h"

/**
 * this class represent the C51_Node,
 * it subscribe to two camera/image topics and provide the path
 **/
class C51_Node{

public:

	/**
	 * constructor, initializes the ROS node, subscribe it to the given topics and instruct it to provide the service
	 * @param left_camera the left camera image topic
	 * @param right_camera the right camera image topic
	 */
	  C51_Node()
	  {
		service = nh_.advertiseService("C51", &C51_Node::proccess, this); //Specifying what to do when a service is requested
		ROS_INFO("service on\n");
	  }


	  /**
	   * The call back function executed when a service is requested
	   * it must return true in order to work properly
	   * @param req the request message, generated by the node requesting the service
	   * @param res the response message, generated by the service node when a service is requested
	   */
	  bool proccess(c51_carOperation::C51::Request  &req,
			c51_carOperation::C51::Response &res )
	  {
		  ROS_INFO("recived request, tying to fetch data\n");

		  return true;
	  }


private:
  ros::NodeHandle nh_;
  ros::ServiceServer service;
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "c51_carOperation");
  C51_Node my_node();
  while(ros::ok()){
	  ros::spin();
  }
  return 0;
}

