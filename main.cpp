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

			Mat src = imread("test.jpg");

			double* D;
			D = sfta(src, 8);

			for(int i = 0; i < 48; i++)
					cout << "D[" << i + 1 << "]: " << D[i] << endl;

			cout << endl;
			cout << "Time: " << ((double)getTickCount() - start) / getTickFrequency() << endl;

			free(D);
}
