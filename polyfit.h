#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

void cvPolyfit(cv::Mat &src_x, cv::Mat &src_y, cv::Mat &dst, int order);
