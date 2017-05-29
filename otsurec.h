#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <math.h>
#include <iomanip>

#define NUM_BINS 256
#define COLS 1

using namespace std;
using namespace cv;

//void otsurec(Mat I, int ttotal);
void otsurec(Mat I, int ttotal, double T[]);
double otsu(double counts[], int countsSize);
void otsurec_helper(double T[], double counts[], int lowerBin, int upperBin, int tLower, int tUpper);
