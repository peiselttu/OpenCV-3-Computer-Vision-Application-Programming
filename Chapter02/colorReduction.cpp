#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

// Common Method
void colorReduce(Mat image, int div = 64)
{
	int nc = image.cols*image.channels(); //numbers of pixels in a row
	int nr = image.rows; //numbers of rows

	for (int i = 0; i < nr; i++)
	{
		uchar *data = image.ptr<uchar>(i);
		for (int j= 0;  j<nc; j++)
		{
			data[j] = (data[j] / div)*div+div/2;
		}
	}
}

// Version with input/output images
void colorReduce_1(const Mat &input,
	Mat &output,
	int div = 64) {

	int nl = input.rows;
	int nc = input.cols;
	int nchannels = input.channels();

	output.create(input.rows, input.cols, input.type());

	for (int i = 0; i < nl; i++)
	{
		const uchar* data_in = input.ptr<uchar>(i);
		uchar* data_out = output.ptr<uchar>(i);
		for (int j = 0; j < nc*nchannels; j++)
		{
			data_out[j] = data_in[j] / div * div + div / 2;
		}

	}
}

//Test 1
//this version uses dereference operator *
void colorReduce1(Mat image, int div = 64)
{
	int nl = image.rows;
	int nc = image.cols*image.channels();

	int div2 = div >> 1;

	for (int i = 0; i < nl; i++)
	{
		uchar *data = image.ptr<uchar>(i);
		for (int j = 0; j < nc; j++)
		{
			*data++ += *data / div * div + div2;
		}
	}
}

//test 5
//this method recomputes the row size each loop
void colorReduce5(Mat image, int div = 64)
{
	int nl = image.rows;
	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0) + 0.5);
	uchar mask = 0xff << n;
	for (int i = 0; i < nl; i++)
	{
		uchar *data = image.ptr<uchar>(i);
		for (int j = 0; j < image.cols*image.channels(); j++)
		{
			*data &= mask;
			*data++ += div / 2;
		}
	}
}

//Test2
//Method2 Equivalent Method using modulo operator
void colorReduce2(Mat image, int div = 64)
{
	int nc = image.cols*image.channels();
	int nr = image.rows;
	uchar div2 = div >> 1;

	for (int i = 0; i < nr; i++)
	{
		uchar* data = image.ptr<uchar>(i);
		for (int j = 0; j < nc; j++)
		{
			int v = *data;
			*data++ = v - v % div + div2;
		}
	}
}

//test3
//this version uses a binary mask

void colorReduce3(Mat image, int div=64)
{
	int nl = image.rows;
	int nc = image.cols*image.channels();

	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0) + 0.5);
	uchar mask = 0xff << n;
	uchar div2 = 1 >> (n - 1);

	for (int i = 0; i < nl; i++)
	{
		uchar *data = image.ptr<uchar>(i);
		for (int j = 0; j < nc; j++)
		{
			*data &= mask;
			*data++ |= div2;
		}

	}
}

//test4
//this version uses direct pointer arithmetic with a binary mask
void colorReduce4(Mat image,int div=64)
{
	int nl = image.rows;
	int nc = image.cols*image.channels();

	int step = image.step;

	int n = static_cast<int>(log(static_cast<double>(div))/log(2.0)+0.5);

	uchar mask = 0xff << n;
	uchar div2 = div >> 1;

	uchar *data = image.data;
	for (int i = 0; i < nl; i++)
	{
		for (int j = 0; j < nc; j++)
		{
			*(data+j) &= mask;
			*(data+j) |= div2;
		}
		data += step;
	}

}

//test 6
//this version optimizes the case of continuous
void colorReduce6(Mat image, int div = 64)
{
	int nl = image.rows;
	int nc = image.cols*image.channels();
	int n = static_cast<int>(log(static_cast<double>(div))/log(2.0)+0.5);
	uchar mask = 0xff << n;
	int div2 = 1 << (n - 1);
	if (image.isContinuous())
	{
		nc = nc * nl;
		nl = 1;
	}
	for (int i = 0; i <nl; i++)
	{
		uchar *data = image.ptr<uchar>(i);
		for (int j = 0; j < nc; j++)
		{
			*data &= mask;
			*data++ += div2;
		}
	}
}

//test7
//this version uses reshape on continuous image
void colorReduce7(Mat image, int div = 64)
{
	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0) + 0.5);
	uchar mask = 0xff << n;
	int div2 = div / 2;
	
	if (image.isContinuous())
	{
		image.reshape(1,
			1);
	}
	int nl = image.rows;
	int nc = image.cols*image.channels();

	for (size_t i = 0; i < nl; i++)
	{
		uchar *data = image.ptr<uchar>(i);
		for (size_t j = 0;  j < nc;  j++)
		{
			*data &= mask;
			*data++ += div2;
		}
	}
}

//test 8
//this version uses the 3 channels inside the loop with MatIterator_
void colorReduce8(Mat image, int div = 64)
{
	int div2 = div / 2;
	MatIterator_<Vec3b> it = image.begin<Vec3b>();
	MatIterator_<Vec3b> end = image.end<Vec3b>();
	
	for (;it!=end;it++)
	{
		(*it)[0] = (*it)[0]/div*div;
		(*it)[0] = (*it)[0] + div2;

		(*it)[1] = (*it)[1] / div * div;
		(*it)[1] = (*it)[1] + div2;

		(*it)[2] = (*it)[2] / div * div;
		(*it)[2] = (*it)[2] + div2;

	}
}

//test9 
//this version uses the Mat_ iterator
void colorReduce9(Mat image, int div = 64)
{
	Mat_<Vec3b>::iterator it = image.begin<Vec3b>();
	Mat_<Vec3b>::iterator end = image.end<Vec3b>();

	const Vec3b offset(div / 2, div / 2, div / 2);

	for (; it != end; it++)
	{
		*it = *it / div * div + offset;
	}
}

//test10
//this version uses Mat_ iterator and operate the div and and in the loop
void colorReduce10(Mat image, int div = 64)
{
	Mat_<Vec3b>::iterator it = image.begin<Vec3b>();
	Mat_<Vec3b>::iterator end = image.end<Vec3b>();

	for (; it != end; it++)
	{
		(*it)[0] = (*it)[0] / div * div + div/2;
		(*it)[1] = (*it)[1] / div * div + div / 2;
		(*it)[2] = (*it)[2] / div * div + div / 2;
	}
}

//test11 
// this version uses the Mat_ iterator with mask
void colorReduce11(Mat image, int div = 64)
{
	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0) + 0.5);
	uchar mask = 0xff << n;
	uchar div2 = 1 << (n-1);
	Mat_<Vec3b>::iterator it = image.begin<Vec3b>();
	Mat_<Vec3b>::iterator itend = image.end<Vec3b>();
	for (; it != itend; it++)
	{
		(*it)[0] &= mask;
		(*it)[0] |= div2;

		(*it)[1] &= mask;
		(*it)[1] |= div2;

		(*it)[2] &= mask;
		(*it)[2] |= div2;
	}

}
//test12
//this version uses at method
void colorReduce12(Mat image, int div = 64)
{
	int nl = image.rows;
	int nc = image.cols;
	uchar div2 = div >> 1;

	for (size_t i = 0; i < nl; i++)
	{
		for (size_t j = 0; j < nc; j++)
		{
			image.at<Vec3b>(i, j)[0] = image.at<Vec3b>(i, j)[0] / div * div;
			image.at<Vec3b>(i, j)[0] |= div2;

			image.at<Vec3b>(i, j)[1] = image.at<Vec3b>(i, j)[1] / div * div;
			image.at<Vec3b>(i, j)[1] |= div2;

			image.at<Vec3b>(i, j)[2] = image.at<Vec3b>(i, j)[2] / div * div;
			image.at<Vec3b>(i, j)[2] |= div2;
		}
	}
}

//test 13
//this version uses Mat overload operators
void colorReduce13(Mat image, int div = 64)
{
	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0) + 0.5);
	uchar mask = 0xff << n;
	image = (image&Scalar(mask, mask, mask)) + Scalar(div / 2, div / 2, div / 2);
}

//Method 14 this version uses a look up table
void colorReduce14(Mat img, int div = 64)
{
	Mat lookup(1,256,CV_8U);
	for (int i = 0; i < 256; i++)
	{
		lookup.at<uchar>(i) = i / div*div + div / 2;
	}
	LUT(img,lookup,img);
}


#define NTESTS 15
#define NITERATION 10

int main()
{
	Mat img = imread("../../images/boldt.jpg");
	imshow("Image",img);
	
	Mat images[NTESTS];

	int64 tinit,tend,t[NTESTS];

	for (size_t i = 0; i < NTESTS; i++)
	{
		t[i] = 0;
	}

	typedef void(*functionPointer)(Mat, int);
	functionPointer colorReducer[NTESTS] = 
	{colorReduce,colorReduce1,colorReduce2,
	colorReduce3,colorReduce4,colorReduce5,
	colorReduce6,colorReduce7,colorReduce8,
	colorReduce9,colorReduce10,colorReduce11,
	colorReduce12,colorReduce13,colorReduce14};

	//repeat the tests several times
	int n = NITERATION;
	for (size_t i = 0; i < n; i++)
	{
		cout << i << " of " << n << endl;

		//test each version
		for (int f = 0; f < NTESTS; f++)
		{
			images[f] = imread("../../images/boldt.jpg");
			tinit = getTickCount();
			colorReducer[f](images[f],64);
			tend = getTickCount();
			t[f] += (tend- tinit);
			cout << ".";

		}
		
		cout << tend<<"-"<<tinit<<": "<<tend-tinit<<endl;
	}

	//short description of each function
	string description[NTESTS] =
	{ "original version: ",
	"with dereference operator: ",
	"using modulo operator: ",
	"using binary mask: ",
	"direct ptr arithmetic: ",
	"row size recomputation: ",
	"continuous image: ",
	"reshape continuous image: ",
	"with iterators: ",
	"Vec3b iterators: ",
	"iterators and mask: ",
	"iterators from Mat_: ",
	"at method: ",
	"overload operators: ",
	"loop-up table: " };

	for (size_t t = 0; t < NTESTS; t++)
	{
		namedWindow(description[t]);
		imshow(description[t], images[t]);
	}

	//print the average excution time
	cout << endl<<"-----------------------------------------------" << endl;
	for (size_t i = 0; i < NTESTS; i++)
	{
		cout << i << ". " << description[i] << 1000.0 * t[i] / (n*getTickFrequency()) << " ms" << endl;
	}
	
	waitKey(0);
	return 0;
}