#if !define COLORDETECTOR
#define COLORDETECTOR
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

class colorDetector {
private:
	int maxDist;
	Vec3b target;
	Mat result;

public:
	//default constructor
	colorDetector():maxDist(100), target(0, 0, 0) {}

	//full constructor
	colorDetector(uchar blue, uchar green, uchar red, int mxDist = 100) :maxDist(mxDist) {
		setTargetColor(blue,green,red);
	}

	// processor
	Mat processor(Mat image)
	{
		result.create(image.size(),CV_8U);
		Mat_<Vec3b>::const_iterator it = image.begin<Vec3b>();
		Mat_<Vec3b>::const_iterator itend = image.end<Vec3b>();
		Mat_<uchar>::iterator itout = result.begin<uchar>();

		for (;it!=itend;it++,itout++)
		{
			if (getDistanceToTargetColor(*it)<=maxDist)
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

	//Computes the distance between the target Color
	int getDistanceToTargetColor(const Vec3b& color)
	{
		return getColorDistance(color,target);
	}

	//Computes the city-block distance between two colors
	int getColorDistance(const Vec3b& color1,const Vec3b& color2) {
		return abs(color1[0] - color2[0]) +
			abs(color1[1] - color2[1]) +
			abs(color1[2]-color2[2]);
	}

	//set the distance threshold
	void setColorDistanceThreshold(int distance)
	{
		if (distance < 0)
			distance = 0;
		maxDist = distance;
	}

	//set the colors
	void setTargetColor(uchar blue, uchar green, uchar red)
	{
		target = Vec3b(blue,green,red);
	}
	
	void setTargetColor(Vec3b color)
	{
		target = color;
	}

	//get the colors
	Vec3b getTargetColor()
	{
		return target;
	}
};
#endif
