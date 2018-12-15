#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\core.hpp>

using namespace std;
using namespace cv;

void sharpen(const cv::Mat &image, cv::Mat &result)
{
	result.create(image.size(),image.type());
	int channels = image.channels();

	for (int i = 1; i < image.rows - 1; i++)
	{
		const uchar* current = image.ptr<uchar>(i);
		const uchar* next = image.ptr<uchar>(i+1);
		const uchar* previous = image.ptr<uchar>(i-1);
		
		uchar* output = result.ptr<uchar>(i);

		for (int j = channels; j < channels*(image.cols-1); j++)
		{
			*output++ = cv::saturate_cast<uchar>(5 * current[j] - next[j] - previous[j] - current[j-channels]-current[j+channels]);
		}
	}
	result.col(0).setTo(cv::Scalar(0));
	result.col(result.cols - 1).setTo(cv::Scalar(0));
	result.row(0).setTo(cv::Scalar(0));
	result.row(result.rows - 1).setTo(cv::Scalar(0));
}

//using kernel
void sharpen2D(const Mat& image, Mat &result)
{
	Mat kernel(3,3,CV_32F,Scalar(0));
	kernel.at<float>(0, 1) = -1;
	kernel.at<float>(1, 0) = -1;
	kernel.at<float>(1, 1) = 5;
	kernel.at<float>(1, 2) = -1;
	kernel.at<float>(2, 1) = -1;

	filter2D(image, result,image.depth(),kernel);
}
void addImages(const Mat& image1,const Mat& image2, Mat &result,float k1=1.0,float k2=1.0,float k3=0.0)
{
	CV_Assert(image1.size() == image2.size());
	result.create(image1.size(),image1.type());
	addWeighted(image1, k1, image2, k2, k3, result);

}

int main()
{
	Mat image = imread("../../../images/boldt.jpg");
	if (!image.data)
	{
		return 0;
	}
	imshow("Original Image1",image);

	Mat result;
	double time = static_cast<double>(cv::getTickCount());
	sharpen(image,result);
	time = (static_cast<double>(cv::getTickCount()) - time) /(cv::getTickFrequency()) ;
	cout << "The runing time is :\n" << time;
	imshow("Sharpened Image",result);

	Mat result1;
	sharpen2D(image,result1);
	imshow("Sharpen2D Image",result1);

	Mat image2 = imread("../../../images/rain.jpg");
	imshow("Original Image2",image2);
	addImages(image,image2,result,0.7,0.9,0.0);
	imshow("The added Image",result);

	//subtract one image from another image
	subtract(image, image2, result);
	imshow("The subtracted Image",result);

	cvWaitKey(0);

	return 0;
}