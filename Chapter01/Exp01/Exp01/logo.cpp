#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat image = imread("../../images/puppy.bmp");
	Mat logo = imread("../../images/smalllogo.png");

	imshow("Original Image",image);
	imshow("The logo",logo);
	waitKey(0);

	// define image ROI at the right-bottom on the image
	Mat imageROI(image,Rect(image.cols-logo.cols,
				 image.rows-logo.rows,
				 logo.cols,
				 logo.rows));
	//insert the logo to imageROI
	logo.copyTo(imageROI);
	imshow("Image with Logo",image);
	waitKey(0);

	//re-read the original image
	image = imread("../../images/puppy.bmp");

	//create the ROI at the right bottom at the image
	Mat imageROI1(image, Rect(image.cols-logo.cols,
							 image.rows-logo.rows,
							 logo.cols,
							 logo.rows));
	//use logo as a mask and the mask must be a gray image
	Mat mask(logo);
	imshow("mask",logo);
	// copy the corresponding value in logo at the position where the pixel value on the mask is not 0
	logo.copyTo(imageROI1,mask);
	imshow("Image",image);
	waitKey(0);


	return 0;
}