#include "ros/ros.h"
#include "C21_VisionAndLidar/C21_obj.h"
#include <image_transport/image_transport.h>
#include <message_filters/synchronizer.h>
#include <message_filters/subscriber.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <sensor_msgs/image_encodings.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/Image.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>
#include <pcl/correspondence.h>
#include <pcl/point_cloud.h>
#include <pcl/common/common_headers.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <image_transport/subscriber_filter.h>
#include "geometry_msgs/Polygon.h"
#include <pcl_ros/point_cloud.h>
#include <pcl/filters/passthrough.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl_ros/transforms.h>
#include <tf/tf.h>
#include <tf/transform_listener.h>
#include <math.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/features/normal_3d.h>
namespace enc=sensor_msgs::image_encodings;
using namespace tf;
using namespace cv;

Mat *myImage;
void my_mouse_callback( int event, int x, int y, int flags, void* param );

Rect box;
bool drawing_box = false;
bool box_chosen = false;
int x1,y2;
static double posx,posy,posz;
double minx,maxx,miny,maxy;

bool first=true;

void draw_box( Mat* img, Rect rect ){
	cv::rectangle( *img, rect,
				Scalar(255,100,100) );
}

// Implement mouse callback
void my_mouse_callback( int event, int x, int y, int flags, void* param ){
	switch( event ){
		case CV_EVENT_MOUSEMOVE:
			if( drawing_box ){
				box.width = x-box.x;
				box.height = y-box.y;
			}
			break;

		case CV_EVENT_LBUTTONDOWN:
			box_chosen = false;
			drawing_box = true;
			box = cvRect( x, y, 0, 0 );
			x1=x;
			y2=y;
			break;

		case CV_EVENT_LBUTTONUP:
			drawing_box = false;
			if( box.width < 0 ){
				box.x += box.width;
				box.width *= -1;
			}
			if( box.height < 0 ){
				box.y += box.height;
				box.height *= -1;
			}
			minx=std::min(x1,x);
			maxx=std::max(x1,x);
			miny=std::min(y2,y);
			maxy=std::max(y2,y);
			box_chosen = true;
			break;
	}
}


class CloudFetch{

public:

	CloudFetch() :
		it_(nh_),
		left_image_sub_( it_, "/multisense_sl/camera/left/image_color", 1 ),
		pointcloud(nh_,"/multisense_sl/camera/points2",1),
		sync( MySyncPolicy( 10 ), left_image_sub_,pointcloud)
		{
			cloudpub= nh_.advertise<geometry_msgs::Polygon>("fetchedCloud", 1000);
			service= nh_.serviceClient<C21_VisionAndLidar::C21_obj>("C21/C23");
			sync.registerCallback( boost::bind( &CloudFetch::callback, this, _1, _2 ) ); //Specifying what to do with the data

		}



	void callback(const sensor_msgs::ImageConstPtr& left_msg,const sensor_msgs::PointCloud2::ConstPtr &cloud){
		cv_bridge::CvImagePtr left;
		try
		{
			left = cv_bridge::toCvCopy(left_msg,enc::BGR8);
		}
		catch (cv_bridge::Exception& e)
		{
			ROS_ERROR("cv_bridge exception: %s", e.what());
			return;
		}
		myImage=&left->image;


		if(box_chosen){
			draw_box( myImage, box );
			C21_VisionAndLidar::C21_obj msg;
			msg.request.sample.x1=minx;
			msg.request.sample.y1=miny;
			msg.request.sample.x2=maxx;
			msg.request.sample.y1=maxy;
			if(service.call(msg)){
				std::stringstream s;
				s<<"global position\n:"<<" x:"<<msg.response.point.x<<" y:"<<msg.response.point.y<<" z:"<<msg.response.point.z;
				posx=msg.response.point.x;
				posy=msg.response.point.y;
				posz=msg.response.point.z;
				cv::Point org;
				org.x=10;
				org.y=10;
std::cout<<"global position\n:"<<" x:"<<msg.response.point.x<<" y:"<<msg.response.point.y<<" z:"<<msg.response.point.z<<std::endl;
				cv::putText(*myImage, s.str(), cvPoint(30,30),
				FONT_HERSHEY_COMPLEX_SMALL, 1.2, cvScalar(0,200,250), 1, CV_AA);
			}
			box_chosen=false;
		}
				std::stringstream s;
				s<<"global position:"<<" x:"<<posx<<" y:"<<posy<<" z:"<<posz;
				cv::Point org;
				org.x=10;
				org.y=10;
				cv::putText(*myImage, s.str(), cvPoint(30,30),
				FONT_HERSHEY_COMPLEX_SMALL, 1.2, cvScalar(0,200,250), 1, CV_AA);


			imshow("Window",*myImage);



	}

private:
  ros::NodeHandle nh_;
  image_transport::ImageTransport it_;
  typedef image_transport::SubscriberFilter ImageSubscriber;
  ImageSubscriber left_image_sub_;
  message_filters::Subscriber<sensor_msgs::PointCloud2> pointcloud;
  tf::TransformListener listener;
  typedef message_filters::sync_policies::ApproximateTime<
    sensor_msgs::Image,sensor_msgs::PointCloud2
    > MySyncPolicy;
  message_filters::Synchronizer< MySyncPolicy > sync;
  ros::Publisher cloudpub;
  boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
  ros::ServiceClient service;
};


int main(int argc, char* argv[])
{
	ros::init(argc, argv,"cloud_fetch");
	const char* name = "Window";
	box = cvRect(-1,-1,0,0);
	CloudFetch *cf=new CloudFetch();

	cvNamedWindow( "Window" );
	cvStartWindowThread();
	// Set up the callback
	cvSetMouseCallback( name, my_mouse_callback, (void*) myImage);
	while(ros::ok()){
		ros::spin();
	}
	// Main loop
	cvDestroyWindow( name );

	return 0;
}
