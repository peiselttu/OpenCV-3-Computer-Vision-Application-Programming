#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "colorDetector.h"

using namespace std;
using namespace cv;

Mat image;

void callBackFunc(int event, int x, int y,int flags, void* userdata)
{
	if (event==EVENT_LBUTTONDOWN)
	{
		Vec3b color;
		Mat img;
		image.copyTo(img);
		color[0] = img.at<Vec3b>(y, x)[0];
		color[1] = img.at<Vec3b>(y,x)[1];
		color[2] = img.at<Vec3b>(y,x)[2];
		cout << "color=(" << (int)color[0] <<","<<(int)color[1]<<","<<(int)color[2]<<")"<< endl;
	}
}

int main()
{
	colorDetector cdetector;

	//Mat image = imread("../../images/boldt.jpg");

	image = imread("46.jpg");
	namedWindow("Original Image");
	
	setMouseCallback("Original Image", callBackFunc,NULL);
	imshow("Original Image", image);
	cdetector.setColorDistanceThreshold(60);
	cdetector.setTargetColor(89,29,73);
	Mat result = cdetector.processor(image);

	imshow("detected Image",result);

	waitKey(0);
	return 0;
}