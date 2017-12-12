#include "hausDim.h"
#include "polyfit.h"

double hausDim(Mat I)
{
    int maxDim = 0;

    if (I.rows >= I.cols)
        maxDim = I.rows;
    else
        maxDim = I.cols;

    int ceil_result = ceil(log2(maxDim)); // Saving on a variable because it will be used after
    int newDimSize = pow(2, ceil_result);
    int rowPad = newDimSize - I.rows;
    int colPad = newDimSize - I.cols;

    // Equivalent to: I = padarray(I, [rowPad, colPad], 'post');
    copyMakeBorder(I, I, 0, rowPad, 0, colPad, BORDER_CONSTANT, 0); // Adding in the bottom and right

    double boxCounts[ceil_result];
    double resolutions[ceil_result];

    int iSize = I.rows;
    double boxSize = iSize;
    int boxesPerDim = 1;
    int idx = 0;

    int boxCount = 0;
    bool objFound = false;

    int* minBox = new int [newDimSize];
    int* maxBox = new int [newDimSize];

    while(boxSize >= 1)
    {
        boxCount = 0;

        // Equivalent to: ------------------------------------------------------
        // minBox = (1: boxSize: (iSize - boxSize) + 1);
        // minBox = insertInArray(minBox, boxSize, iSize, boxesPerDim);

        int valueMinBox = 1;
        int valueMaxBox = boxSize;

        for (int i = 0; i < boxesPerDim; i++)
        {
            minBox[i] = valueMinBox;
            maxBox[i] = valueMaxBox;
            valueMinBox += boxSize;
            valueMaxBox += boxSize;
        }

        for (int boxRow = 0; boxRow < boxesPerDim; boxRow++)
        {
            for (int boxCol = 0; boxCol < boxesPerDim; boxCol++)
            {
                  objFound = false;

                  for(int row = minBox[boxRow]; row <= maxBox[boxRow]; row++)
                  {
                      for(int col = minBox[boxCol]; col <= maxBox[boxCol]; col++)
                      {
                            // Have the "-1" because of the difference on the pixel ranges of OpenCV and MATLAB
                            if (I.at<float>(row - 1, col - 1) == 255)
                            {
                                boxCount += 1;
                                objFound = true;
                                break;
                            }
                      }

                      if(objFound)
                          break;
                  }
            }
        }

        boxCounts[idx] = boxCount;
        resolutions[idx] = 1 / boxSize;
        idx += 1; // The index is increased here because in C++ the range is: 0 ~ ceil_result

        boxesPerDim = boxesPerDim * 2;
        boxSize = boxSize / 2;
    }

    for (int i = 0; i <= ceil_result; i++)
    {
        resolutions[i] = log(resolutions[i]);
        boxCounts[i] = log(boxCounts[i]);
    }

    Mat resolutionsMat(ceil_result + 1, 1, CV_64FC1, resolutions);
    Mat boxCountsMat(ceil_result + 1, 1, CV_64FC1, boxCounts);

    Mat DMat = Mat::zeros(2, 1, CV_64FC1);
    cvPolyfit(resolutionsMat, boxCountsMat, DMat, 1);

    double D = DMat.at<double>(0,1);

    return D;
}
