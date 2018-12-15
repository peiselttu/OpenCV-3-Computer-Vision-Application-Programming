#include <iostream>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>

using namespace std;
using namespace cv;

void wave(Mat& image,Mat &result)
{
	Mat srcX(image.size(),CV_32F);
	Mat srcY(image.size(),CV_32F);

	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			srcX.at<float>(i, j) = j;
			srcY.at<float>(i, j) = i + 5 * sin(j/10.0);
		}
	}
	//srcX.copyTo(result);
	remap(image, result, srcX, srcY, cv::INTER_LINEAR);
}

int main()
{
	Mat image = imread("../../../images/boldt.jpg");
	imshow("original Image",image);
	Mat result;
	wave(image,result);
	
	imshow("remapped Image",result);
	waitKey(0);
	return 0;
}