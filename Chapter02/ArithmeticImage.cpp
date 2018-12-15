#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

int main()
{
	Mat image1, image2;
	image1 = imread("../../images/boldt.jpg");
	image2 = imread("../../images/rain.jpg");

	imshow("original Image1",image1);
	imshow("original Image2",image2);

	Mat image3;
	add(image1,image2,image3);
	imshow("the result of adding two images",image3);

	Mat image4;
	addWeighted(image1,0.7,image2,0.9,0.,image4);
	imshow("addweigted Image",image4);
	// add rain image on to the blue channnel of the image
	Mat image5;
	vector<Mat> planes;
	split(image1,planes);
	cvtColor(image2, image2, COLOR_RGB2GRAY);
	planes[0] += image2;

	imshow("planes[0]",planes[0]);
	imshow("planes[1]",planes[1]);
	imshow("planes[2]",planes[2]);

	// merge the image together
	merge(planes, image5);
	imshow("the merged Images",image5);

	waitKey(0);

	return 0;
}