#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

#include "sfta.h"

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{

			double start = cv::getTickCount();

			Mat src = imread("test.jpg");
			sfta(src, 8);

			cout << endl;
			cout << "Time: " << ((double)cv::getTickCount() - start) / cv::getTickFrequency() << std::endl;
}
