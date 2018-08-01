#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <sstream>

using namespace std;
using namespace cv;

char window_name[] = "Image Window";
bool B_display = false;
Mat image, tmpImg;

void help();
void imgDisplay(Mat image);
void onMouse(int event,int x,int y,int flag, void *param);


int main()
{
	help();
	image = imread("../../images/puppy.bmp");
	
	if (!image.data)
	{
		cout << "Read image data failure!" << endl;
		getchar();
		return -1;
	}
	image.copyTo(tmpImg);
	
	namedWindow(window_name,CV_WINDOW_AUTOSIZE);
	setMouseCallback(window_name, onMouse, (void*)&tmpImg);
	imgDisplay(tmpImg);
	
	waitKey(0);
	return 0;
}

void help()
{
	cout << endl;
	cout << endl;
	cout << "=========================================================================" << endl;
	cout << "This program introduces the basic operations of images with opencv GUI..." << endl;
	cout << "Press s to show the image:" << endl;
	cout << "Press c to convert the RGB image into gray image:" << endl;
	cout << "Press h to horizontally flip the image:"<<endl;
	cout << "Press v to vertically flip the image:" << endl;
	cout << "=========================================================================" << endl;
}

void imgDisplay(Mat image)
{
	imshow(window_name,image);
}
void onMouse(int event, int x, int y, int flag, void *params)
{
	stringstream ss;
	Mat &img = *(Mat*)params;
	switch (event)
	{
	case EVENT_LBUTTONDOWN:
	{
		ss<<"("<<static_cast<int>(img.at<Vec3b>(x, y)[0])<<","<< static_cast<int>(img.at<Vec3b>(x, y)[1])<<","<< static_cast<int>(img.at<Vec3b>(x, y)[2])<<")";
		putText(img,ss.str(),Point(x,y),FONT_HERSHEY_PLAIN,2.0,Scalar(103,23,43),2,8);
		imgDisplay(img);
	}
	break;
	case EVENT_RBUTTONDOWN:
	{
		image.copyTo(tmpImg);
		circle(img, Point(x, y), 65, Scalar(100, 200, 120), 2, 8);
		imgDisplay(img);
	}
	break;
	default:
		break;
	}
}