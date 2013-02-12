#include <QImage>
#include <cv_bridge/cv_bridge.h>
#include <opencv/highgui.h>
#include "C11_Node.h"

//void C11_Node::viewImage(const sensor_msgs::ImageConstPtr& msg);
IC11_Node_Subscriber* C11_Node::pIC11_Node_Subscriber;

C11_Node::C11_Node(IC11_Node_Subscriber* subscriber)
{
	pIC11_Node_Subscriber = subscriber;
	img_counter = 0;
}

C11_Node::C11_Node(int argc, char** argv, IC11_Node_Subscriber* subscriber ):
       init_argc(argc),
       init_argv(argv)
{
	pIC11_Node_Subscriber = subscriber;
	img_counter = 0;
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

//		it_ = new image_transport::ImageTransport(*nh_);
//		panoramic_image= it_->subscribe("C21/smallPanorama",1,&viewImage);

		//status_subscriber = nh_->subscribe("c11_stt",1000,&StatusMessageCallback);

		c11_push_img =	nh_->advertiseService("C11/push_img", &C11_Node::push_img_proccess, this);
		c11_push_occupancy_grid = nh_->advertiseService("C11/push_occupancy_grid", &C11_Node::push_occupancy_grid_proccess, this);
		LoadMissionClient = nh_->serviceClient<C10_Common::mission_selection>("MissionSelection");


        start();
        img_counter = 0;
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
	std::cout << "Image received." << std::endl;
	std::cout << "Image width: "<< msg->width << std::endl;
	std::cout << "Image height: "<< msg->height << std::endl;
	std::cout << "Image step: "<< msg->step << std::endl;
	if(msg->width > 1 && msg->height > 1)
	{
		QImage myImage(msg->data.data(), msg->width, msg->height, msg->step, QImage::Format_RGB888);
		pIC11_Node_Subscriber->OnImgReceived(myImage);
	}

}

//void C11_Node::StatusMessageCallback(const C11_Agent::C34C11_STTConstPtr)
//{
//
//}

bool C11_Node::push_img_proccess(C10_Common::push_img::Request  &req,
		C10_Common::push_img::Response &res )
{
	std::cout << "Step1" << std::endl;
	std::cout << "Image received." << std::endl;
	std::cout << "Image width: "<< req.IMG.width << std::endl;
	std::cout << "Image height: "<< req.IMG.height << std::endl;
	std::cout << "Image step: "<< req.IMG.step << std::endl;
	if(req.IMG.width > 1 && req.IMG.height > 1)
	{
		//QImage myImage(req.IMG.data.data(), req.IMG.width, req.IMG.height, req.IMG.step, QImage::Format_RGB888);
		//pIC11_Node_Subscriber->OnImgReceived(myImage);
		cv_bridge::CvImagePtr pan;
		try
		{
		  pan = cv_bridge::toCvCopy(req.IMG,enc::RGB8);
		}
		catch (cv_bridge::Exception& e)
		{
		  ROS_ERROR("cv_bridge exception: %s", e.what());
		  return false;
		}
//		cv::imshow("Image",pan->image);
		std::string imgName;
		std::stringstream out;
		out << "img"<< img_counter << std::endl;
		imgName = out.str();
		imgName.append(".jpg");
		cv::imwrite(imgName,pan->image);
		pIC11_Node_Subscriber->OnImgReceived(imgName);
		img_counter++;
		res.ACK.mes = 1;
		return true;
	}
	else
	{
		res.ACK.mes = 0;
		return false;
	}
}

bool C11_Node::push_occupancy_grid_proccess(C10_Common::push_occupancy_grid::Request  &req,
                  		  C10_Common::push_occupancy_grid::Response &res )
{
	int grid[48][48];
	for(int i=0; i<48; i++)
	{
		for(int j=0; j<48;j++)
		{
			grid[i][j] = req.OGD.row[47-i].column[j].status;
		}
	}
	pIC11_Node_Subscriber->OnOccupancyGridReceived(grid);
	res.ACK.mes = 1;
	return true;
}

void C11_Node::LoadMission(int index)
{
	C10_Common::mission_selection ms;
	ms.request.MSN.MSN = index;
	if (LoadMissionClient.call(ms))
	{
		if(ms.response.MES.mes != 1)
		{

		}
	}
	else
	{
		ROS_ERROR("Failed to call service C11_Agent::mission_selection");
	}
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

