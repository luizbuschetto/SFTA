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

			Mat src = imread(argv[1]);

			int nt = atoi(argv[2]);

			double* D;
			D = sfta(src, nt);

			int featureQuantity = nt * 6; // nt * 2 Binary Images * 3 Features

			for(int i = 0; i < featureQuantity; i++)
					cout << "D[" << i + 1 << "]: " << D[i] << endl;

			cout << endl;
			cout << "Time: " << ((double)getTickCount() - start) / getTickFrequency() << endl;

			free(D);
}
