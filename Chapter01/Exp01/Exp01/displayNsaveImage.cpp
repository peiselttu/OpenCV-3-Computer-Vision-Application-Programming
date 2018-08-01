#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>

using namespace std;
using namespace cv;

void onMouse(int event, int x, int y, int flags, void * params)
{
	Mat *img = reinterpret_cast<Mat *>(params);
	switch (event)
	{
	case EVENT_LBUTTONDOWN:
		cout << "at (" << x << "," << y << ") the pixel value is " 
			<< static_cast<int>(img->at<uchar>(Point(x, y))) << endl;
		break;
	default:
		break;
	}
}

int main()
{
	Mat image;
	cout << "This image is " << image.rows << " X " << image.cols << endl;

	// read the image from the file
	image = imread("../../images/puppy.bmp",IMREAD_GRAYSCALE);
	if (image.empty())
	{
		cout << "Error Reading the Image..." << endl;
		return 0;
	}

	cout << "This image is " << image.rows << " X " << image.cols << endl;
	cout << "The channel of the image is " << image.channels() << endl;
	namedWindow("Original Window",CV_WINDOW_AUTOSIZE);
	imshow("Original Window",image);

	setMouseCallback("Original Window", onMouse, reinterpret_cast<void *>(&image));

	Mat result;
	flip(image,result,0);
	namedWindow("flipped image",CV_WINDOW_AUTOSIZE);
	imshow("flipped image",result);
	waitKey(0);

	imwrite("output.jpg",result);

	namedWindow("Draw on the image");
	circle(image,
		   Point(155, 110),
		   65,
		   0,
		   3);
	putText(image,
			"This is a dog",
			Point(40,200),
			FONT_HERSHEY_PLAIN,
			2.0,
			255,
			2);
	imshow("Draw on the image",image);
	waitKey(0);

	getchar();
	return 0;
}