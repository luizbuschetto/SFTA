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

    // for (int i = 0; i < I.rows; i++){
    //   for (int j = 0; j < I.cols; j++){
    //       cout << I.at<float> << endl; } cout << endl; }

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
    // int minBox[4096] = (int*)malloc(newDimSize * sizeof(int));
    // int maxBox[4096] = (int*)malloc(newDimSize * sizeof(int));

    //cout << I.rows << endl;
    //cout << I.cols << endl;

    while(boxSize >= 1)
    {
        boxCount = 0;

        // Equivalent to: ------------------------------------------------------
        // minBox = (1: boxSize: (iSize - boxSize) + 1);
        // minBox = insertInArray(minBox, boxSize, iSize, boxesPerDim);

        // Acredito que dê para otimizar

        int valueMinBox = 1;
        int valueMaxBox = boxSize;

        //cout << "boxesPerDim: " << boxesPerDim << endl;
        for (int i = 0; i < boxesPerDim; i++)
        {
            minBox[i] = valueMinBox;
            maxBox[i] = valueMaxBox;
            valueMinBox += boxSize;
            valueMaxBox += boxSize;

            //cout << "minBox[" << i << "]: " << minBox[i] << endl;
            //cout << "maxBox[" << i << "]: " << maxBox[i] << endl;
        }

        //cout << "boxSize: " << boxSize << endl;

        // ---------------------------------------------------------------------

        for (int boxRow = 0; boxRow < boxesPerDim; boxRow++)
        {
            for (int boxCol = 0; boxCol < boxesPerDim; boxCol++)
            {
                  objFound = false;
                  //cout << "boxRow: " << boxRow << endl;
                  //cout << "boxCol: " << boxCol << endl;
                  for(int row = minBox[boxRow]; row <= maxBox[boxRow]; row++)
                  {
                      for(int col = minBox[boxCol]; col <= maxBox[boxCol]; col++)
                      {
                            //cout << "row: " << row << endl;
                            //cout << "col: " << col << endl;
                            // Os "-1" são questões de detalhes diferentes entre o OpenCV e o MATLAB
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
        idx += 1; // O indice é incrementado depois porque no C++ o range vai de 0 ~ ceil_result

        boxesPerDim = boxesPerDim * 2;
        boxSize = boxSize / 2;
    }

    for (int i = 0; i <= ceil_result; i++)
    {
        resolutions[i] = log(resolutions[i]);
        boxCounts[i] = log(boxCounts[i]);
        //cout << "log: resolutions[" << i+1 << "]: " << resolutions[i] << endl;
        //cout << "log: boxCounts[" << i+1 << "]: " << boxCounts[i] << endl;
    }

    Mat resolutionsMat(ceil_result + 1, 1, CV_64FC1, resolutions);
    Mat boxCountsMat(ceil_result + 1, 1, CV_64FC1, boxCounts);
    // cout << resolutionsMat << endl;
    // cout << endl;
    // cout << boxCountsMat << endl;
    Mat DMat = Mat::zeros(2, 1, CV_64FC1);
    cvPolyfit(resolutionsMat, boxCountsMat, DMat, 1);

    double D = DMat.at<double>(0,1);
    //cout << "D: " << finalD << endl;

    return D;

    // namedWindow("thresh_test", WINDOW_NORMAL);
    // imshow("thresh_test", I);
    // waitKey(0);
}
