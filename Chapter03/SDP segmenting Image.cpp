#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include "colorDetector.h"


using namespace std;
using namespace cv;

int main()
{
	//1. Read an Image from a file
	string image_path = "C:/Users/64414/OneDrive - Texas Tech University/computerVision/opencv3Cookbook/Chpt03/images/boldt.jpg";
	cv::Mat image = cv::imread(image_path);

	//2. Create an image processor instance
	colorDetector cdetector;

	//3. set parameters of the cdetector instance
	cdetector.setTargetColor(230,190,130);
	cdetector.setColorDistanceThreshold(100);

	cout << "the target color needs to be detected is: " << cdetector.getTargetColor() << endl;
	cout << "the color distance threshold now is: " << cdetector.getColorDistanceThreshold() << endl;

	
	
	//Testing Area
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//cdetector.setTargetColor(1,1,1);
	//cv::Vec3b color = cv::Vec3b(2,2,2);
	//int dist = cdetector.getDistanceToTargetColor(color);

	//cout << "The distance from current color to target color is: " << dist << endl;
	//
	//float f = 1.731;
	//int i = static_cast<int>(f);
	//cout << i << endl;

	//cdetector.setTargetColor(30,20,90);
	cv::Mat result2 = cdetector.processorOpenCV(image);

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	cv::Mat result=cdetector.processor(image);

	cv::namedWindow("result Image");
	cv::imshow("result Image",result);

	cv::namedWindow("result Image2");
	cv::imshow("result Image2",result2);

	cv::namedWindow("Original Image");
	cv::imshow("Original Image", image);
	cv::waitKey();
	return 0;
}