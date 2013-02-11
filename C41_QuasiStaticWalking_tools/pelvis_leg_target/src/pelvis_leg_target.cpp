#include <ros/ros.h>
#include <pelvis_leg_target/pelvis_leg_target.h>
#include <tf/transform_listener.h>
#include <move_pelvis/move_pelvis.h>

class move_to_leg{
private:
	ros::NodeHandle nh_;
	tf::TransformListener listener;
	ros::ServiceClient move_pelvis_client;
	ros::ServiceServer srv_server;

public:
	move_to_leg(){
		move_pelvis_client = nh_.serviceClient<move_pelvis::move_pelvis>("move_pelvis");
		srv_server = nh_.advertiseService("pelvis_leg_target",&move_to_leg::srv_CB,this);
	}


	~move_to_leg(){
	}

	bool srv_CB(pelvis_leg_target::pelvis_leg_targetRequest &req,pelvis_leg_target::pelvis_leg_targetResponse &res){
		tf::StampedTransform transform;
		try {
			listener.waitForTransform("/pelvis",req.leg,ros::Time(0),ros::Duration(0.2));
			listener.lookupTransform("/pelvis",req.leg,ros::Time(0),transform);
		} catch (tf::TransformException &ex) {
			ROS_ERROR("%s",ex.what());
		}
		move_pelvis::move_pelvis move_pelvis_srv;

		move_pelvis_srv.request.PositionDestination.x=transform.getOrigin().x();
		move_pelvis_srv.request.PositionDestination.y=transform.getOrigin().y();
		move_pelvis_srv.request.PositionDestination.z=0;
		move_pelvis_srv.request.LinkToMove = "pelvis";
		move_pelvis_srv.request.AngleDestination.x=0;move_pelvis_srv.request.AngleDestination.y=0;move_pelvis_srv.request.AngleDestination.z=0;
		ROS_INFO("Sending pelvis to relative x,y,z: %f,%f,%f",move_pelvis_srv.request.PositionDestination.x,move_pelvis_srv.request.PositionDestination.y,move_pelvis_srv.request.PositionDestination.z);
		move_pelvis_client.call(move_pelvis_srv);
		res.SUCCESS=move_pelvis_srv.response.success;
		return true;
	}

};

int main(int argc, char **argv) {
	ros::init(argc, argv, "pelvis_leg_target");
	move_to_leg *move_to_leg_obj = new move_to_leg();
	ROS_INFO("ready");
	ros::spin();
	return 0;
}