#include <iostream>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
	string img_path= "C:/Users/64414/OneDrive - Texas Tech University/computerVision/opencv3Cookbook/Chpt03/images/boldt.jpg";
	cv::Mat image = cv::imread(img_path);


	//define a rectangle to distinguish the background and foreground
	cv::Rect rectgl(50,25,210,180);

	
	cv::Mat result;
	cv::Mat bgModel, fgModel;

	cv::grabCut(image,
		result,
		rectgl,
		bgModel,
		fgModel,
		5,
		cv::GC_INIT_WITH_RECT);

	//get the pixels masked as likely to be the fore ground pixel
	cv::compare(result, cv::GC_PR_FGD, result, cv::CMP_EQ);

	cv::Mat foreGround(image.size(),CV_8UC3,cv::Scalar(255,255,255));

	image.copyTo(foreGround, result);

	cv::rectangle(image, rectgl, cv::Scalar(255, 255, 255), 1);
	cv::namedWindow("original Image");
	cv::imshow("original Image", image);

	cv::namedWindow("result");
	cv::imshow("result", result);

	cv::namedWindow("foreGround");
	cv::imshow("foreGround",foreGround);

	cv::waitKey(0);
	return 0;
}