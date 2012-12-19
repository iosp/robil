#include <QImage>
#include "C11_Node.h"

//void C11_Node::viewImage(const sensor_msgs::ImageConstPtr& msg);
IC11_Node_Subscriber* C11_Node::pIC11_Node_Subscriber;

C11_Node::C11_Node(IC11_Node_Subscriber* subscriber)
{
	pIC11_Node_Subscriber = subscriber;
}

C11_Node::C11_Node(int argc, char** argv, IC11_Node_Subscriber* subscriber ):
       init_argc(argc),
       init_argv(argv)
{
	pIC11_Node_Subscriber = subscriber;
}

C11_Node::~C11_Node() {
	delete it_;
	delete nh_;
    if(ros::isStarted()) {
      ros::shutdown(); // explicitly needed since we use ros::start();
      ros::waitForShutdown();
    }
        wait();
}

bool C11_Node::proccess(C11_OperatorControl::C11::Request  &req,
    C11_OperatorControl::C11::Response &res )
          {
                  ROS_INFO("recived request, tying to fetch data\n");

                  return true;
          }

bool C11_Node::init() {
        ros::init(init_argc,init_argv,"C11_OperatorControl");
        if ( ! ros::master::check() ) {
                return false;
        }

        nh_ = new ros::NodeHandle();
		service = nh_->advertiseService("C11", &C11_Node::proccess, this); //Specifying what to do when a service is requested
		if ( ! ros::master::check() ) {
				return false;
		}

		it_ = new image_transport::ImageTransport(*nh_);
		panoramic_image= it_->subscribe("C21/smallPanorama",1,&viewImage);

		status_subscriber = nh_->subscribe("c11_stt",1000,&StatusMessageCallback);


        start();
 //       ros::start(); // explicitly needed since our nodehandle is going out of scope.
        return true;
}

void C11_Node::run() {
        ros::Rate loop_rate(1);
        int count = 0;
        while ( ros::ok() ) {


                ros::spinOnce();
                loop_rate.sleep();
                ++count;
        }
        std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
        Q_EMIT rosShutdown(); // used to signal the gui for a shutdown (useful to roslaunch)
}

void C11_Node::viewImage(const sensor_msgs::ImageConstPtr& msg)
{
	std::cout << "Step1" << std::endl;
	if(msg->width > 1 && msg->height > 1)
	{
		QImage myImage(msg->data.data(), msg->width, msg->height, QImage::Format_RGB888);
		pIC11_Node_Subscriber->OnImgReceived(myImage);
	}
	std::cout << "Image received." << std::endl;
	std::cout << "Image width: "<< msg->width << std::endl;
	std::cout << "Image height: "<< msg->height << std::endl;
}

void C11_Node::StatusMessageCallback(const C11_Agent::C34C11_STTConstPtr)
{

}

/*int main(int argc, char **argv)
{
  ros::init(argc, argv, "C11_OperatorControl");
  C11_Node my_node();
  while(ros::ok()){
	  ros::spin();
  }
  return 0;
}*/

