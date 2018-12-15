#pragma once
#if !defined COLORDETECTOR
#define COLORDETECTOR

#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>

class colorDetector {
private:
	// minimum acceptable distance
	int maxDist;
	
	// target color
	cv::Vec3b target;

	// image containing result--binary image
	cv::Mat result;

public:

	// Define Constructor
	 
	//empty constructor
	//default parameter initialization here
	colorDetector():maxDist(100), target(0, 0, 0) {}

	//define a full constructor that enables user to input the parameters
	colorDetector(uchar blue, uchar green, uchar red, int distance = 100) :maxDist(distance), target(blue, green, red) {
		setTargetColor(blue,green,red);
	}

	//Get distance to the target color
	int getDistanceToTargetColor(const cv::Vec3b &color)
	{
		return getColorDistance(color, target);
	}

	//Get the color distance
	int getColorDistance(const cv::Vec3b &color1, const cv::Vec3b &color2)
	{
	/*	return abs(color1[0] - color2[0]) +
			abs(color1[1] - color2[1]) +
			abs(color1[2] - color2[2]);*/


		// Another method to get the distance between the two vectors in opencv
		/*return static_cast<int>(cv::norm<int, 3>(cv::Vec3i(color1[0] - color2[0], color1[1] - color2[1], color1[2] - color2[2])));*/

		//Another method to get the distance between the two colors using absdiff()
		cv::Vec3b dist;
		cv::absdiff(color1,color2,dist);
		int d = cv::sum(dist)[3];
		return cv::sum(dist)[0];
	}
	
	//Set the color to be detected
	void setTargetColor(uchar blue, uchar green, uchar red)
	{
		target = cv::Vec3b(blue,green,red);
	}
	//Get the target color
	cv::Vec3b getTargetColor()
	{
		return target;
	}

	//Set the color distance threshold
	//threshold must be positive if negative set to 0
	void setColorDistanceThreshold(int distance)
	{
		if (distance < 0)
		{
			maxDist = 0;
		}
		else
		{
			maxDist = distance;
		}
	}

	//Get color distance threshold
	int getColorDistanceThreshold()
	{
		return maxDist;
	}


	// Processor -- the operation to calculate the color difference of each pixel in the image between the target
	cv::Mat processor(const cv::Mat& image)
	{
		// create an image with the same size as the input image but the single channel
		result.create(image.size(), CV_8U);

		//initialize the iterators
		cv::Mat_<cv::Vec3b>::const_iterator it = image.begin<cv::Vec3b>();
		cv::Mat_<cv::Vec3b>::const_iterator itend = image.end<cv::Vec3b>();

		cv::Mat_<uchar>::iterator itout = result.begin<uchar>();

		//iterator every pixel in the image
		for (; it != itend; ++it, ++itout)
		{
			int distance = getDistanceToTargetColor(*it);
			if (distance <= maxDist)
			{
				*itout = 255;
			}
			else
			{
				*itout = 0;
			}

		}
		return result;		
	}

	cv::Mat processorOpenCV(const cv::Mat& image)
	{
		result.create(image.size(),CV_8U);

		cv::absdiff(image, cv::Scalar(target), result);

		//cv::imshow("result1", result);

		std::vector<cv::Mat> imgPlanes;
		cv::split(result, imgPlanes);

		result = imgPlanes[0] + imgPlanes[1] + imgPlanes[2];
		//cv::imshow("result2",result);
		
		cv::threshold(result,
			result,
			maxDist,
			255,
			cv::THRESH_BINARY);
		

		return result;

	}

};
#endif
