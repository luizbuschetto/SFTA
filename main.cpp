#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

#include "sfta.h"

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
			double start = getTickCount();

			Mat src = imread("pisos/bom.jpg");
			sfta(src, 8);

			cout << endl;
			cout << "Time: " << ((double)getTickCount() - start) / getTickFrequency() << endl;
}
