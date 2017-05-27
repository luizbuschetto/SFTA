#include "hausDim.h"

void hausDim(Mat I)
{
    int maxDim = 0;

    if (I.rows >= I.cols)
        maxDim = I.rows;
    else
        maxDim = I.cols;

    int newDimSize = pow(2, ceil(log2(maxDim)));
    int rowPad = newDimSize - I.rows;
    int colPad = newDimSize - I.cols;

    copyMakeBorder(I, I, rowPad, rowPad, colPad, colPad, BORDER_CONSTANT, 255);

    namedWindow("thresh_test", WINDOW_NORMAL);
    imshow("thresh_test", I);
    waitKey(0);
}
