#ifndef __GENERAL_DETECTION_HPP__
#define __GENERAL_DETECTION_HPP__



#include <opencv2/opencv.hpp>
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"

using namespace cv;
using namespace std;
class GeneralDetector {
public:

	  GeneralDetector();
	  void initialize(const string& object);
	  void detect(Mat img);
	//  void detect(Mat img, int* x, int* y, int* width, int* height);
//	  void learn(const string featuresFile, const string descriptorVectorFile, const string posSamplesDir, const string negSamplesDir,  const string svmModelFile);
	
private:
 // HOGDescriptor hog;
  
  // Directory containing positive sample images
 

 // vector<float> descriptorVector;
 
  
public:
    int _x,_y,_width,_height;
    float confident;
    map<string,CvSVM> classes_classifiers;
    Mat vocabulary;
    SiftFeatureDetector detector;
    vector<KeyPoint> keypoints;	

  // computing descriptors
     Ptr<DescriptorExtractor > extractor;
     Mat descriptors;
     FlannBasedMatcher *matcher;
     BOWImgDescriptorExtractor *bowide;
};

#endif