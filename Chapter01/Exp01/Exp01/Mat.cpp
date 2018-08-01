#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

// define a Mat to create an image
cv::Mat function()
{
	cv::Mat image(500,500,CV_8U,50);
	return image;
}

int main()
{
	cv::Mat gray = function();
	cv::imshow("created image from function",gray);
	cv::waitKey(0);

#pragma region Two ways to create Mat
	//cv::Mat image1(240,320,CV_8U,100);
	cv::Mat image1(240,320,CV_8U,cv::Scalar(100));
	//cv::Mat image1(240,320,CV_8U);
	//image1 = 100;
	cv::imshow("image1",image1);
	cv::waitKey(0);
#pragma endregion

#pragma region Reallocate a Image
	image1.create(200,200,CV_8U);
	image1 = 200;
	cv::imshow("another image1",image1);
	cv::waitKey(0);
#pragma endregion

#pragma region Create a color Image
	cv::Mat image2(240,320,CV_8UC3,cv::Scalar(22,59,122));
	cv::imshow("color image2",image2);
	cv::waitKey(0);
#pragma endregion

#pragma region Read a Image
	cv::Mat image3 = cv::imread("../../images/puppy.bmp");
	cv::imshow("image image3",image3);
	cv::waitKey(0);
#pragma endregion

#pragma region All these images point to the same data block
	cv::Mat image4(image3);
	image1 = image3;

	image3.copyTo(image2);
	cv::Mat image5 = image3.clone();

	cv::imshow("image4",image4);
	cv::imshow("image3 to image1",image1);
	cv::imshow("image5",image5);
	cv::imshow("image2", image2);
	cv::waitKey(0);
#pragma endregion

#pragma region Flip the image
	cv::flip(image3, image3, 1);
	cv::imshow("image1_2",image1);
	cv::imshow("image4_2",image4);
	cv::imshow("image5_2",image5);
	cv::waitKey(0);
#pragma endregion

#pragma region Use the Convert method to convert image1 to image2
	image1.convertTo(image2,CV_32F,1/255.0,0.0);
	cv::imshow("converted image2",image2);
	cv::waitKey(0);
#pragma endregion

#pragma region Create a 3X3 matrix of double-precision
	cv::Matx33d matrix(3.0,2.0,1.0,
					   2.0,1.0,3.0,
					   1.0,2.0,3.0);

	// create a 3X1 vector
	cv::Matx31d vector(5.0,1.0,3.0);

	cv::Matx31d result = matrix * vector;

	std::cout << "result=" << result << std::endl;
	getchar();
#pragma endregion
	return 0;
}