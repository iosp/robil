#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>


#include <image_transport/image_transport.h>
#include <message_filters/synchronizer.h>
#include <message_filters/subscriber.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <sensor_msgs/PointCloud2.h>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>
#include <pcl/correspondence.h>
#include <pcl/point_cloud.h>
#include <pcl/common/common_headers.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <image_transport/subscriber_filter.h>
#include <pcl_ros/point_cloud.h>
#include <pcl/filters/passthrough.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl_ros/transforms.h>
#include <tf/tf.h>
#include <tf/transform_listener.h>
#include <math.h>

#include <C23_ObjectRecognition/C23C0_OD.h>
#include <C23_ObjectRecognition/C23C0_ODIM.h>
#include "C23_Detector.hpp"
#include <C21_VisionAndLidar/C21_obj.h>
#include <math.h>


#define MIN(x,y) (x < y ? x : y)
#define MAX(x,y) (x > y ? x : y)
bool C23_Detector::pictureCoordinatesToGlobalPosition(int x1, int y1, int x2, int y2, int* x, int* y, int *z) {
    C21_VisionAndLidar::C21_obj c21srv;
    c21srv.request.sample.x1 = x1;
    c21srv.request.sample.y1 = y1;
    c21srv.request.sample.x2 = x2;
    c21srv.request.sample.y2 = y2;
    
    if(c21client.call(c21srv))
    {
        if(x != NULL) *x = round(c21srv.response.point.x);
        if(y != NULL) *y = round(c21srv.response.point.y);
        if(z != NULL) *z = round(c21srv.response.point.z);
        cout << "Received data: " << c21srv.response.point.x << "," << c21srv.response.point.y << "," << c21srv.response.point.z << endl;
        return true;
    }
    return false;
    
}

Mat fromSensorMsg(const sensor_msgs::ImageConstPtr& msg)
{
    cv_bridge::CvImagePtr cv_ptr;
    try
    {
        cv_ptr = cv_bridge::toCvCopy(msg, enc::BGR16);
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        exit(1);
    }
    return cv_ptr->image;
}


C23_Detector::C23_Detector(const char* left_cam, const char* right_cam, const char* pointc):
it_(nh),
left_image_sub_( it_, left_cam, 1 ),
pointcloud(nh,pointc,1),
sync( MySyncPolicy( 10 ), left_image_sub_,pointcloud)
{

    sync.registerCallback( boost::bind( &C23_Detector::callback, this, _1, _2 ) ); //Specifying what to do with the data
    objectDetectedPublisher = nh.advertise<C23_ObjectRecognition::C23C0_OD>("C23/object_detected", 1);
    objectDeminsionsPublisher = nh.advertise<C23_ObjectRecognition::C23C0_ODIM>("C23/object_deminsions", 1);
    c21client = nh.serviceClient<C21_VisionAndLidar::C21_obj>("C21/C23"); //Subscribe to the service node to get the absolute coordinates of a point
    ROS_INFO("Started...");
    //	gates = new vector<Gate*>();

}


bool C23_Detector::detect(const string target) {

    //   ROS_INFO(target.c_str());
    
    if(!target.compare("Gate")) {
        _target = GATE;
        //  ROS_INFO("We are looking for a gate...");
    } else if (!target.compare("Car")) {
        _generalDetector.initialize("carEntry");
        _target = CAR;
        ROS_INFO("We are looking for a Car...");
    } else if (!target.compare("Path")) {
        _target = PATH;
        ROS_INFO("We are looking for a path...");
    } else if (!target.compare("Valve")) {
        _target = VALVE;
        ROS_INFO("We are looking for a valve...");
    } else if (!target.compare("Firehose")) {
        _target = FIREHOSE;
        ROS_INFO("We are looking for a firehose...");
    } else if (!target.compare("Picture")) {
        _target = PICTURE;
        ROS_INFO("We are taking a picture ... say cheese ...");
    }
    return true;
    
}
void C23_Detector::publishMessage(bool isFound) {
    //   ROS_INFO("Publishing message..");
    C23_ObjectRecognition::C23C0_OD msg;
    C23_ObjectRecognition::C23C0_ODIM msg2;
    string target;
    switch (_target) {
        
        case CAR:
            target = "Car";
            break;
        case GATE:
            target = "Gate";
            break;
    }
    if(!isFound) {
        x= - 1;
    }
    msg.ObjectDetected = isFound ? 1 : 0;
    msg2.x = x;
    msg2.y = y;
    msg2.width = width;
    msg2.height = height;
    msg2.Object = target;
    msg.Object = target;
    //  ROS_INFO("Publishing message..");
    objectDeminsionsPublisher.publish(msg2);
    objectDetectedPublisher.publish(msg);
    
    
}
void C23_Detector::callback(const sensor_msgs::ImageConstPtr& msg,const sensor_msgs::PointCloud2::ConstPtr &cloud)
{
    //    ROS_INFO("Receiving image..");
    Mat srcImg = fromSensorMsg(msg);
    bool res;
    switch (_target) {
        case PATH:
            res = detectPath(srcImg);
            publishMessage(res);
            break;
        case CAR:
            ROS_INFO("CAR");
            res = detectCar(srcImg,cloud);
            publishMessage(res);
            break;
        case GATE:
            ROS_INFO("GATE");         
            res = detectGate(srcImg,cloud);
            publishMessage(res);
            break;
        case VALVE:
            ROS_INFO("VALVE");
            res = detectValve(srcImg,cloud);
            publishMessage(res);
            break;
        case FIREHOSE:
            ROS_INFO("FIREHOSE");
            res = detectFirehose(srcImg,cloud);
            publishMessage(res);
            break;
        case PICTURE:
            imwrite("picture.jpg",srcImg);
            _target=NONE;
            break;
    }
    srcImg.release();
    
}


bool C23_Detector::detectValve(Mat srcImg, const sensor_msgs::PointCloud2::ConstPtr &cloud) {
    ROS_INFO("Detecting a valve..");
    RNG rng(12345);
    
    Mat imgHSV, imgThreshed;
    cvtColor(srcImg,imgHSV,CV_BGR2HSV);
    inRange(imgHSV,Scalar(60,30,30),Scalar(80,255,255),imgThreshed);
    //namedWindow("TESTING");
    // imshow("TESTING",imgThreshed);
    // waitKey(0);
    // imwrite("test12.jpg",imgThreshed);
    Mat bw;
    vector<vector<cv::Point> > contours;
    threshold(imgThreshed,bw,10,255,CV_THRESH_BINARY);
    // imshow("TESTING",bw);
    // waitKey(0);
    cv::Scalar colors[3];
    colors[0] = cv::Scalar(120, 120, 0);
    colors[1] = cv::Scalar(120, 255, 0);
    colors[2] = cv::Scalar(0, 100, 255);
    findContours(bw,contours,CV_RETR_LIST,CV_CHAIN_APPROX_SIMPLE);
    size_t idx;
    for (idx = 0; idx < contours.size(); idx++) {
        cv::drawContours(srcImg, contours, idx, colors[idx % 3]);
    }
    
    //  drawContours(srcImg,contours,-1,CV_RGB(255,0,0),2);
    // imshow("TESSTING",srcImg);
    waitKey(0);
    vector<RotatedRect> minEllipse( contours.size() );
    int biggest_size = 0;
    int biggest = 0;
    for( int i = 0; i < contours.size(); i++ )
    {
        cout << "Contour: " << i << ", Size: " << contours[i].size() << endl;
        if( contours[i].size() > biggest_size )
        { 
            biggest_size = contours[i].size();
            biggest = i;
            
        }
    }
    if(biggest_size > 30 && biggest_size < 80) {
        
        
        
        
        /* for( int i = 0; i < contours.size(); i++ )
         *            {
         *                cout << "Contour: " << i << ", Size: " << contours[i].size() << endl;
         *                if( contours[i].size() > 5 )
         *                    { 
         *                        minEllipse[i] = fitEllipse( Mat(contours[i]) ); 
         *                        
         }
         }*/
        RotatedRect minRect =  minAreaRect( Mat(contours[biggest]));
        Point2f rect_points[4]; minRect.points( rect_points );
        for( int j = 0; j < 4; j++ )
            line( srcImg, rect_points[j], rect_points[(j+1)%4], CV_RGB(255,0,0), 1, 8 );
        // ellipse( srcImg, fitEllipse( Mat(contours[biggest]) ), CV_RGB(255,0,0), 2, 8 );
            /// Draw contours + rotated rects + ellipses
            // Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
            /* for( int i = 0; i< contours.size(); i++ )
             *            {
             *                Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
             *                // contour
             *            //  drawContours( bw, contours, i, color, 1, 8, vector<Vec4i>(), 0, Pointf() );
             *                // ellipse
             *                ellipse( imgThreshed, minEllipse[i], color, 2, 8 );
             }*/
            imshow("TESTING",srcImg);
            waitKey(0);
            pictureCoordinatesToGlobalPosition(minRect.center.x-10,minRect.center.y+10,minRect.center.x+10,minRect.center.y+10,&x,&y,NULL);
            return true;
    }
    return false;
    
}

bool C23_Detector::detectFirehose(Mat srcImg, const sensor_msgs::PointCloud2::ConstPtr &cloud) {
    ROS_INFO("Detecting a Firehose..");
    RNG rng(12345);
    
    Mat imgHSV, imgThreshed;
    cvtColor(srcImg,imgHSV,CV_BGR2HSV);
    inRange(imgHSV,Scalar(90, 130, 40), Scalar(150, 255, 250),imgThreshed);
    //namedWindow("TESTING");
    imshow("TESTING",imgThreshed);
    waitKey(0);
   // imwrite("test12.jpg",imgThreshed);
    Mat imgDilated;
    Mat element = getStructuringElement( MORPH_ELLIPSE,
                                         Size( 2*18 + 1, 2*18+1 ),
                                         cv::Point( 18, 18 ) );
    /// Apply the dilation operation
    dilate( imgThreshed, imgDilated, element );
    Mat bw;
    vector<vector<cv::Point> > contours;
    threshold(imgDilated,bw,10,255,CV_THRESH_BINARY);
     imshow("TESTING",bw);
     waitKey(0);
    cv::Scalar colors[3];
    colors[0] = cv::Scalar(120, 120, 0);
    colors[1] = cv::Scalar(120, 255, 0);
    colors[2] = cv::Scalar(0, 100, 255);
    findContours(bw,contours,CV_RETR_LIST,CV_CHAIN_APPROX_SIMPLE);
    size_t idx;
    for (idx = 0; idx < contours.size(); idx++) {
        cv::drawContours(srcImg, contours, idx, colors[idx % 3]);
    }
    
    //  drawContours(srcImg,contours,-1,CV_RGB(255,0,0),2);
    // imshow("TESSTING",srcImg);
    waitKey(0);
    vector<RotatedRect> minEllipse( contours.size() );
    int biggest_size = 0;
    int biggest = 0;
    for( int i = 0; i < contours.size(); i++ )
    {
        cout << "Contour: " << i << ", Size: " << contours[i].size() << endl;
        if( contours[i].size() > biggest_size )
        { 
            biggest_size = contours[i].size();
            biggest = i;
            
        }
    }
    if(biggest_size > 50 && biggest_size < 180) {
        
        
        
        
        /* for( int i = 0; i < contours.size(); i++ )
         *            {
         *                cout << "Contour: " << i << ", Size: " << contours[i].size() << endl;
         *                if( contours[i].size() > 5 )
         *                    { 
         *                        minEllipse[i] = fitEllipse( Mat(contours[i]) ); 
         *                        
    }
    }*/
        RotatedRect minRect =  minAreaRect( Mat(contours[biggest]));
        Point2f rect_points[4]; minRect.points( rect_points );
        for( int j = 0; j < 4; j++ )
            line( srcImg, rect_points[j], rect_points[(j+1)%4], CV_RGB(255,0,0), 1, 8 );
        // ellipse( srcImg, fitEllipse( Mat(contours[biggest]) ), CV_RGB(255,0,0), 2, 8 );
            /// Draw contours + rotated rects + ellipses
            // Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
            /* for( int i = 0; i< contours.size(); i++ )
             *            {
             *                Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
             *                // contour
             *            //  drawContours( bw, contours, i, color, 1, 8, vector<Vec4i>(), 0, Pointf() );
             *                // ellipse
             *                ellipse( imgThreshed, minEllipse[i], color, 2, 8 );
    }*/
            imshow("TESTING",srcImg);
            waitKey(0);
            pictureCoordinatesToGlobalPosition(minRect.center.x-100,minRect.center.y+100,minRect.center.x+100,minRect.center.y+100,&x,&y,NULL);
            return true;
    }
    return false;
    
}

bool C23_Detector::detectCar(Mat srcImg, const sensor_msgs::PointCloud2::ConstPtr &cloud) {
    
    //Define the service client to be accessed
    C21_VisionAndLidar::C21_obj c21srv;
    
    pcl::PointCloud<pcl::PointXYZ>pclcloud;
    pcl::fromROSMsg<pcl::PointXYZ>(*cloud,pclcloud);
    
    // _generalDetector.detect(srcImg);
    cout << "Done detection" << endl;
    // 215,365,182,114
    _generalDetector._x = 215;
    _generalDetector._y = 365;
    _generalDetector._width = 182;
    _generalDetector._height = 114;
    
    Point2f minImagePoint;
    minImagePoint.x = -1;
    minImagePoint.y = -1;
    if(_generalDetector._x != -1) {
        x = _generalDetector._x;
        y = _generalDetector._y;
        width = _generalDetector._width;
        height = _generalDetector._height;
        cout << "Calculating point cloud" << endl;
        int min = 100000;
        pcl::PointXYZ minPoint, absolutePoint;
        
        
        //Get the closest point from the robot to the car
        cout << x << "," << y << "," << width << "," << height << endl;
        for(int i = x; i < x + width; i++) {
            for(int j = y; j < y + height; j++) {
                //     cout << "(" << i << "," << j << "," << pclcloud.at(i,j).z << ")" << endl;
                if(sqrt(pclcloud.at(i,j).x*pclcloud.at(i,j).x+pclcloud.at(i,j).y*pclcloud.at(i,j).y+pclcloud.at(i,j).z*pclcloud.at(i,j).z*10000) < min) {
                    min = sqrt(pclcloud.at(i,j).x*pclcloud.at(i,j).x+pclcloud.at(i,j).y*pclcloud.at(i,j).y+pclcloud.at(i,j).z*pclcloud.at(i,j).z*10000);
                    minPoint = pcl::PointXYZ(pclcloud.at(i,j).x,pclcloud.at(i,j).y,pclcloud.at(i,j).z);//Check
                    minImagePoint.x = i;
                    minImagePoint.y = j;
                }
            }
        }
        
        
        //Expand a bounding box to fit the car
	int x1,y1;
	int x0,y0;
	int flag = 0;
	float depth = 0;
	double THRESHOLD = 2;
	int nanColumnCounter = 0;
	bool nanColumnFlag = true;
	cout<<"Max depth: "<<minPoint.x<<endl;
	for(int i = 1; i < 500 && i + minImagePoint.x < srcImg.cols; i +=10) {
		      flag = 0;
		      cout << "Checking column: " << i << endl;
		      nanColumnFlag = true;
		      for(int j= 150; j >= -150; j--) {
			depth = pclcloud.at(minImagePoint.x+i,minImagePoint.y-j).x;
			
			cout<<"Depth: "<<depth<<endl;
			
			
			if (depth!=depth)//If all values are nan then it will stop
			{
			  //ROS_INFO("Nan values obtained. Cannot determine the distance to the car");
			  continue;
			}
			
			nanColumnFlag = false;
			
			if(depth < minPoint.x+THRESHOLD && depth > minPoint.x-THRESHOLD) {
			  
			    x1 = minImagePoint.x+i;
			    cout<<"X1: "<<x1<<endl;
			    flag = 1;
			  }
		    }
		    if(nanColumnFlag) nanColumnCounter++;
		    
		    
		    if(!flag && nanColumnCounter>50) {
		      break;
		    }
	
	}
	cout<<"X1: "<<x1<<", Xmin: "<<minImagePoint.x<<endl;
	//Draw the right boundary column of the car
	circle( srcImg, Point2f(x1,minImagePoint.y),10, 200, -1, 8, 0 );
	
	nanColumnCounter = 0;
	nanColumnFlag = true;
	depth = 0;
	for(int i = 0; i < 500; i +=10) {
	    flag = 0;
	    cout << "Checking column: " << i << endl;
	    nanColumnFlag = true;
	    for(int j= 150; j >= -150; j--) {
		depth = pclcloud.at(minImagePoint.x-i,minImagePoint.y-j).x;
	      
		if (depth!=depth)
		{
		  //ROS_INFO("Nan values obtained. Cannot determine the distance to the car");
		  continue;
		}
		
		nanColumnFlag = false;
		
		
		if(depth < minPoint.x+THRESHOLD && depth > minPoint.x-THRESHOLD) {
		    x0 = minImagePoint.x-i;
		    flag = 1;
		}
	    }
	    if(nanColumnFlag) nanColumnCounter++;
		    
	    
	    if(!flag && nanColumnCounter>50) {
	      break;
	    }
	   
	}
         cout << "X0: " << x0 << " X1: " << x1 << endl;
	//The left boundary column of the car
        circle( srcImg, Point2f(x0,minImagePoint.y),10, 300, -1, 8, 0 );
	
         //Display the sub-region of the car found
         int carHeight = x1  - x0; //Asssume height and width are approximately the same
         
         std::vector<cv::Point> bounds;
	 line( srcImg, cv::Point(x0, minImagePoint.y - carHeight/2), cv::Point(x0, minImagePoint.y + carHeight/2), Scalar(0,0,255), 3, CV_AA);
	 line( srcImg, cv::Point(x0, minImagePoint.y + carHeight/2), cv::Point(x1, minImagePoint.y + carHeight/2), Scalar(0,0,255), 3, CV_AA);
	 line( srcImg, cv::Point(x0, minImagePoint.y - carHeight/2), cv::Point(x1, minImagePoint.y - carHeight/2), Scalar(0,0,255), 3, CV_AA);
	 line( srcImg, cv::Point(x1, minImagePoint.y - carHeight/2), cv::Point(x1, minImagePoint.y + carHeight/2), Scalar(0,0,255), 3, CV_AA);
	 
	 //Get the absolute coordinates of the closest point on the car
        //--------------------------------------------------------------
        //Use the service to get the new coordinates
        c21srv.request.sample.x1 = x0;
        c21srv.request.sample.y1 = minImagePoint.y - carHeight/2;
        c21srv.request.sample.x2 = x1;
        c21srv.request.sample.y2 = minImagePoint.y + carHeight/3;
        
        if(c21client.call(c21srv)){
            ROS_INFO("Service initiated");
            ROS_INFO("Before...\n");
            absolutePoint.x = (float)c21srv.response.point.x;
            absolutePoint.y = (float)c21srv.response.point.y;
            absolutePoint.z = (float)c21srv.response.point.z;
            ROS_INFO("The points after are %f, %f, %f\n",absolutePoint.x , absolutePoint.y , absolutePoint.z);
        }
        else{
            return false;
        }
        
        //The absolute coordinates of the center of the car
        cout << "Real World Points: "<<absolutePoint.x << "," << absolutePoint.y << "," << absolutePoint.z << endl;   
        
	//Check if the points are valid
	if (absolutePoint.x!=absolutePoint.x && absolutePoint.y!=absolutePoint.y&&absolutePoint.z!=absolutePoint.z)
	{
	  ROS_INFO("Nan values obtained. Cannot determine the distance to the car");
	  return false;
	}
	//Draw the closest point to the car
        cout << "Best point: " << sqrt(absolutePoint.x*absolutePoint.x+absolutePoint.y*absolutePoint.y+absolutePoint.z*absolutePoint.z) << endl;
        circle( srcImg, Point2f(minImagePoint.x,minImagePoint.y), 5, 60, -1, 8, 0 ); 
	//The average
	//circle( srcImg, Point2f(), 5, 80, -1, 8, 0 ); 
        x = absolutePoint.x;
	y = absolutePoint.y;
	//imshow("Testing",srcImg);
       // waitKey(0);
        
        
	
	
	
        return true;
    }
    x = -1;
    return false;
    
    
}

bool C23_Detector::detectPath(Mat srcImg) {
    // IplImage* img = new IplImage(srcImg);
    Mat imgHSV, imgThreshed;
    cvtColor(srcImg,imgHSV,CV_BGR2HSV);
    inRange(imgHSV,Scalar(20,30,30),Scalar(40,255,255),imgThreshed);
    //  namedWindow("TESTING");
    // imshow("TESTING",imgThreshed);
    //waitKey(0);
    // imwrite("test12.jpg",imgThreshed);
    Mat bw;
    vector<vector<cv::Point> > contours;
    threshold(imgThreshed,bw,10,255,CV_THRESH_BINARY);
    findContours(bw,contours,CV_RETR_LIST,CV_CHAIN_APPROX_SIMPLE);
    drawContours(srcImg,contours,-1,CV_RGB(255,0,0),2);
    imshow("TESSTING",srcImg);
    //waitKey(0);
    Mat dst,cdst;
    Canny(bw, dst, 50, 200, 3);
    cvtColor(dst, cdst, CV_GRAY2BGR);
    
    
    //Probabilistic Hough Line Transform
    vector<Vec4i> lines;
    HoughLinesP(dst, lines, 5, CV_PI/180, 50, 100, 10 );
    int max = 0;
    Vec4i maxVec;
    if(lines.size() == 0) {
        return false;
    }
    for( size_t i = 0; i < lines.size(); i++ )
    {
        Vec4i l = lines[i];
        cout << l[0] << "," << l[1] << "---" << l[2]  << "," << l[3] << endl;
        if(l[1] > max || l[3] > max) {
            max = l[1] > l[3] ? l[1] : l[3];
            maxVec = l;
        }
        // line( cdst, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
    }
    line( cdst, cv::Point(maxVec[0], maxVec[1]), cv::Point(maxVec[2], maxVec[3]), Scalar(0,0,255), 3, CV_AA);
    imshow("TESTING",cdst);
    waitKey(0);
    if(maxVec[1] < maxVec[3]) {
        x = maxVec[0];
        y = maxVec[1];
    } else {
        x = maxVec[2];
        y = maxVec[3];
    }
    return true;
    
    
}
bool C23_Detector::detectGate(Mat srcImg, const sensor_msgs::PointCloud2::ConstPtr &cloud) {
    
    pcl::PointCloud<pcl::PointXYZ>pclcloud;
    C21_VisionAndLidar::C21_obj c21srv;
    pcl::fromROSMsg<pcl::PointXYZ>(*cloud,pclcloud);
    static pcl::PointXYZ leftC;
    static pcl::PointXYZ rightC;
    static pcl::PointXYZ centerC;
    bool res = false;
    bool left=false, right=false;
    IplImage* img = new IplImage(srcImg);
    IplImage* imgHSV = cvCreateImage(cvGetSize(img), 8, 3);
    
    cvCvtColor(img, imgHSV, CV_BGR2HSV);
    IplImage* imgThreshed = cvCreateImage(cvGetSize(img), 8, 1);
    cvInRangeS(imgHSV, cvScalar(0, 30, 30), cvScalar(20, 255, 255), imgThreshed); //filter red
    
    Mat threshMat(imgThreshed);
    
    //imshow("Threshed",threshMat);
    //waitKey(0);
    //  ROS_INFO("Gate!");
    
    
    //contoursR
    Mat bw,gray;
    
    //  ROS_INFO("1");
    ////findng center mass of right column
    threshold(threshMat, bw, 10, 255, CV_THRESH_BINARY);
    
    vector<vector<cv::Point> > contoursR;
    findContours(bw, contoursR, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
    //cout<<"The Contour size: "<< contoursR.size()<<endl;
    vector<Moments> muR(contoursR.size() );
    vector<Point2f> mcR(contoursR.size() );
    int biggstR=0;
    if(contoursR.size() != 0) {
        drawContours(srcImg, contoursR, -1, CV_RGB(255,0,0), 2);
        
        /// Get the moments and mass centers:
        // imshow("Contours", srcImg);
        // waitKey(0);
        
        
        for(unsigned int i = 0; i < contoursR.size(); i++ )
        {
            muR[i] = moments( contoursR[i], false );
            mcR[i] = Point2f( muR[i].m10/muR[i].m00 , muR[i].m01/muR[i].m00 );
            if (muR[biggstR].m00<=muR[i].m00)
                biggstR=i;
            
        }
        //Draw a circle indicating the center of mass on the right pole
        circle( srcImg, mcR[biggstR], 16, 60, -1, 8, 0 );
        right = true;
        if (pclcloud.at(mcR[biggstR].x,mcR[biggstR].y).x<50 && pclcloud.at(mcR[biggstR].x,mcR[biggstR].y).y <50 && pclcloud.at(mcR[biggstR].x,mcR[biggstR].y).x !=0)
        {
            rightC=pclcloud.at(mcR[biggstR].x,mcR[biggstR].y);
            
        }
    }
    
    
    /////finding center mass of left column
    cvInRangeS(imgHSV, cvScalar(90, 130, 40), cvScalar(150, 255, 250), imgThreshed);//filter blue
    
    
    Mat threshMatL(imgThreshed),bwL;
    threshold(threshMatL, bwL, 10, 255, CV_THRESH_BINARY);
    vector<vector<cv::Point> > contoursL;
    //	  cout<<"next2"<<endl;
    findContours(bwL, contoursL, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
    vector<Moments> muL(contoursL.size() );
    vector<Point2f> mcL(contoursL.size() );
    int biggstL=0;
    if(contoursL.size() !=0) {
        drawContours(srcImg, contoursL, -1, CV_RGB(0,0,255), 2);
        
        
        
        for(unsigned int i = 0; i < contoursL.size(); i++ )
        {
            muL[i] = moments( contoursL[i], false );
            mcL[i] = Point2f( muL[i].m10/muL[i].m00 , muL[i].m01/muL[i].m00 );
            if (muL[biggstL].m00<=muL[i].m00)
                biggstL=i;
            
        }
        left = true;
        circle( srcImg, mcL[biggstL], 16, Scalar(0,0,255), -1, 8, 0 );
        if (pclcloud.at(mcL[biggstL].x,mcL[biggstL].y).x<50 && pclcloud.at(mcL[biggstL].x,mcL[biggstL].y).y <50 && pclcloud.at(mcL[biggstL].x,mcL[biggstL].y).x !=0)
        {
            leftC=pclcloud.at(mcL[biggstL].x,mcL[biggstL].y);
        }
        
    }
    
    if(left && right) {
        
        
        line( srcImg,mcL[biggstL],mcR[biggstR],Scalar(0,0,0),5,8);
        
        //	cout <<"\nleft :"<<leftC.x<<" ,"<<leftC.y<<endl;
        //	cout<<"\nright :"<<rightC.x<<" ,"<<rightC.y<<endl;
        
        double gate =sqrt(pow((leftC.x-rightC.x),2)+pow((leftC.y-rightC.y),2));
        //cout<<gate<<endl;
        res = false;
        if (gate > 4.5 && gate < 5.8)
        {
            res = true;
            
        }
        if(!res) {
            left = leftC.z < rightC.z;
            right = leftC.z > rightC.z;
            
        } else {
            //find lines
            Mat dst,cdst;
            // ROS_INFO("4.4");
            Canny(threshMat, dst, 50, 200, 3);
            // ROS_INFO("4.5");
            cvtColor(dst, cdst, CV_GRAY2BGR);
            //  ROS_INFO("5");
            //Probabilistic Hough Line Transform
            vector<Vec4i> lines;
            HoughLinesP(dst, lines, 5, CV_PI/180, 50, 100, 10 );
            for( size_t i = 0; i < lines.size(); i++ )
            {
                Vec4i l = lines[i];
                line( cdst, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
            }
            //   ROS_INFO("6");
            
            //cout<<"left"<<mcL[biggstL]<<"right"<<mcR[biggstR]<<endl;
            //These points are the central coordinates of the gate
            
            
            //   x = (mcL[biggstL].x + mcR[biggstR].x)/2;
            //    y = (mcL[biggstL].y + mcR[biggstR].y)/2;
            int x1,y1,x2,y2;
            cout << "Sending left: " << mcL[biggstL].x << "," << mcL[biggstL].y << endl;
            cout << "Sending right: " << mcR[biggstR].x << "," <<mcR[biggstR].y << endl;
            
            c21srv.request.sample.x1 = MIN(mcL[biggstL].x, mcR[biggstR].x);
            c21srv.request.sample.y1 = MIN(mcL[biggstL].y, mcR[biggstR].y);
            c21srv.request.sample.x2 = MAX(mcL[biggstL].x, mcR[biggstR].x);
            c21srv.request.sample.y2 = MAX(mcL[biggstL].y, mcR[biggstR].y);
            
            if(c21client.call(c21srv)){
                cout << "left..." << endl;
                x= (float)c21srv.response.point.x;
                y = (float)c21srv.response.point.y;
                cout << "Got data: " << x << "," << y << endl;
                
            }
            
            
            Point2f a((float) (mcL[biggstL].x + mcR[biggstR].x)/2,(float)(mcL[biggstL].y + mcR[biggstR].y)/2);
            circle( srcImg, a, 16, Scalar(0,0,255), -1, 8, 0 );
            //  imshow("TESTING",srcImg);
            // waitKey(0);
            return true;
        }
    }
    
    cvInRangeS(imgHSV, cvScalar(60,30,30),cvScalar(80,255,255), imgThreshed);//filter blue
    
    
    Mat threshMatM(imgThreshed),bwM;
    threshold(threshMatM, bwM, 10, 255, CV_THRESH_BINARY);
    vector<vector<cv::Point> > contoursM;
    //	  cout<<"next2"<<endl;
    findContours(bwM, contoursM, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
    vector<Moments> muM(contoursM.size() );
    vector<Point2f> mcM(contoursM.size() );
    int biggstM=0;
    
    if(contoursM.size() !=0) {
        drawContours(srcImg, contoursM, -1, CV_RGB(0,0,255), 2);
        //imshow("TESTING",srcImg);
        //waitKey(0);
        
        
        for(unsigned int i = 0; i < contoursM.size(); i++ )
        {
            muM[i] = moments( contoursM[i], false );
            mcM[i] = Point2f( muM[i].m10/muM[i].m00 , muM[i].m01/muM[i].m00 );
            if (muM[biggstM].m00<=muM[i].m00)
                biggstM=i;
            
        }
        
        circle( srcImg, mcM[biggstM], 16, Scalar(0,0,255), -1, 8, 0 );
        if (pclcloud.at(mcM[biggstM].x,mcM[biggstM].y).x<50 && pclcloud.at(mcM[biggstM].x,mcM[biggstM].y).y <50 && pclcloud.at(mcM[biggstM].x,mcM[biggstM].y).x !=0)
        {
            //set the center of mass of the green gate
            centerC=pclcloud.at(mcM[biggstM].x,mcM[biggstM].y);
        }
        
        
        //Add the check to make sure that the upper green part of the same gate is detected
        double gateUpperDistance =0;
        double contourOffset = 0;
        
        if(right) {
            //Find the distance between the center of mass of green and center of mass of red gate
            gateUpperDistance =sqrt(pow((centerC.x-rightC.x),2)+pow((centerC.y-rightC.y),2));
            
            //If the distance is half the length of the gate pole, then they are part of the same gate
            if(gateUpperDistance > 2.25 && gateUpperDistance < 2.9){      
                x = mcR[biggstR].x - (mcR[biggstR].y - mcM[biggstM].y);
                y =  mcR[biggstR].y;
            }
            else{
                //Find the smallest value in the corresponding contour to set the correct offset for the center of the gate
                double minContourOffsetR = mcR[biggstR].y;
                for(unsigned int i=0; i<contoursR[biggstR].size();i++){
                    
                    if(contoursR[biggstR][i].y < minContourOffsetR)
                    {
                        minContourOffsetR =  contoursR[biggstR][i].y;
                    }
                    
                }
                //Add the contour offset to get the correct coordinate in the image
                int x_pic = mcR[biggstR].x - (mcR[biggstR].y - minContourOffsetR);
                int y_pic =  mcR[biggstR].y;
                
                c21srv.request.sample.x1 = mcR[biggstR].x-20;
                c21srv.request.sample.y1 = mcR[biggstR].y-40;
                c21srv.request.sample.x2 = mcR[biggstR].x+20;
                c21srv.request.sample.y2 = mcR[biggstR].y+40;
                
                if(c21client.call(c21srv)){
                    ROS_INFO("Service initiated");
                    // minPoint.x = c21srv.response.x;
                    //minPoint.y = c21srv.response.y;
                    //minPoint.z = c21srv.response.z;
                    //absolutePoint = (pcl::PointXYZ)c21srv.response.point;
                    ROS_INFO("Before...\n");
                    x = (float)c21srv.response.point.x-3;
                    y = (float)c21srv.response.point.y;
                    
                    
                }
                cout<<"Point is: " <<x<<", " <<y <<endl;
                cout << "Detected right" << endl;
                circle( srcImg, Point2f(x_pic,y_pic), 16, Scalar(0,255,255), -1, 8, 0 );
            }
            
            //      imshow("Testing" , srcImg);
            //   waitKey(0);
            return mcM[biggstM].x < mcR[biggstR].x ? true : false;
            
        } else {
            //Find the distance between the cm of green and cm of blue gate
            gateUpperDistance =sqrt(pow((centerC.x-leftC.x),2)+pow((centerC.y-leftC.y),2));   
            
            if(gateUpperDistance > 2.25 && gateUpperDistance < 2.9){
                x = mcL[biggstL].x + (mcL[biggstL].y - mcM[biggstM].y);
                y =  mcL[biggstL].y;
            }else{
                //Find the smallest value in the corresponding contour
                double minContourOffsetL = mcL[biggstL].y;
                for(unsigned int i=0; i<contoursL[biggstL].size();i++){
                    
                    if(contoursL[biggstL][i].y < minContourOffsetL)
                    {
                        minContourOffsetL =  contoursL[biggstL][i].y;
                    }
                    
                }
                int x_pic = mcL[biggstL].x + (mcL[biggstL].y - minContourOffsetL);
                int y_pic =  mcL[biggstL].y;
                cout<<"Point is: " <<x<<", " <<y <<endl;
            }
            cout << "Detected left" << endl;
            circle( srcImg, Point2f(x,y), 16, Scalar(0,255,255), -1, 8, 0 );
            //   imshow("Testing" , srcImg);
            //   waitKey(0);
            c21srv.request.sample.x1 = mcL[biggstL].x-20;
            c21srv.request.sample.y1 = mcL[biggstL].y-40;
            c21srv.request.sample.x2 = mcL[biggstL].x+20;
            c21srv.request.sample.y2 = mcL[biggstL].y+40;
            
            if(c21client.call(c21srv)){
                ROS_INFO("Service initiated");
                // minPoint.x = c21srv.response.x;
                //minPoint.y = c21srv.response.y;
                //minPoint.z = c21srv.response.z;
                //absolutePoint = (pcl::PointXYZ)c21srv.response.point;
                ROS_INFO("Before...\n");
                x = (float)c21srv.response.point.x+3;
                y = (float)c21srv.response.point.y;
                
                
            }
            return mcM[biggstM].x > mcL[biggstL].x ? true : false;
            
        }
    }
    return false;
    
    
}



   
   
