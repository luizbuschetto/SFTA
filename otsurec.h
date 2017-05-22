#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <math.h>


using namespace std;
using namespace cv;

void otsurec(Mat I, int ttotal);
int otsu(Mat counts);