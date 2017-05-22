#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

#include "sfta.h"

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	Mat src = imread("test.jpg");
	sfta(src, 8);
}