#include <iostream>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
	string img_path = "C:/Users/64414/OneDrive - Texas Tech University/computerVision/opencv3Cookbook/Chpt03/images/boldt.jpg";
	cv::Mat image = cv::imread(img_path);
	cv::namedWindow("Original Image");
	cv::imshow("Original Image",image);

	cv::floodFill(image,
		cv::Point(100, 50),
		cv::Scalar(255,255,255),
		(cv::Rect*)0,
		cv::Scalar(35,35,35),
		cv::Scalar(35,35,35),
		cv::FLOODFILL_FIXED_RANGE);

	cv::namedWindow("Processed Image");
	cv::imshow("Processed Image",image);

	cv::waitKey(0);
	return 0;
}