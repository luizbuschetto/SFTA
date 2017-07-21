#include "sfta.h"
#include "otsurec.h"
#include "findBorders.h"
#include "hausDim.h"

double* sfta(Mat I, int nt)
{
	double range = 255; // Considering the image type = uint8 -> CV_8UC1

	I.convertTo(I, CV_8UC1);
	cvtColor(I, I, CV_BGR2GRAY, 1);

	double T[nt+1];
	for(int i = 0; i < nt; i++)
			T[i] = 0;

	 otsurec(I, nt, T);

	 int dSize = nt * 6;
	 double* D = (double*)malloc(dSize * sizeof(double));
	 int pos = 0; 				// Begins at 0 because the value range in OpenCV is different of MATLAB
	 Mat Ib = Mat::zeros(I.rows, I.cols, I.type());

	 for(int t = 0; t < nt; t++)
	 {
		 		double thresh = T[t];

				// MATLAB Range: 0 ~ 1;
				// OpenCV Range: 0 ~ 255.
				// So, to apply the threshold, we need to normalize the pixel values between 0 and 1
				I.convertTo(Ib, CV_32FC3, 1.0/255.5);

				threshold(Ib, Ib, thresh, 255, THRESH_BINARY); // Using 255 because it's equivalent to 1 in MATLAB

				Mat Ib_borders = Mat::zeros(Ib.rows, Ib.cols, Ib.type());
				Ib_borders = findBorders(Ib);

				// OTIMIZAR URGENTEMENTE ESSA SEÇÃO DE CÓDIGO!!!!!! --------------------
				double sumVals = 0;
				int countVals = 0;

				// Equivalent to: vals = double(I(Ib));
			  for(int i = 0; i < Ib_borders.rows; i++)
			  {
			 	  		for(int j = 0; j < Ib_borders.cols; j++)
				  		{
					  			if (Ib_borders.at<float>(i,j) == 255)
						  		{
											 sumVals = sumVals + I.at<uchar>(i,j);
											 countVals++;
								  }
				 		  }
			  }

				// ---------------------------------------------------------------------

				D[pos] = hausDim(Ib_borders);
				pos += 1;

				D[pos] = sumVals / countVals;
				pos += 1;

				D[pos] = countVals;
				pos += 1;

	 	}

		 T[nt] = 1;

		for(int t = 0; t < nt; t++)
		{
				double lowerThresh = T[t];
				double upperThresh = T[t + 1];

				Mat lowThresh = Mat::zeros(I.rows, I.cols, I.type());
				Mat upThresh = Mat::zeros(I.rows, I.cols, I.type());
				threshold(I, lowThresh, lowerThresh*range, 255, THRESH_BINARY);
				threshold(I, upThresh, upperThresh*range, 255, THRESH_BINARY_INV);

				Mat Ib_thresh = Mat::zeros(Ib.rows, Ib.cols, Ib.type());
				bitwise_and(lowThresh, upThresh, Ib_thresh);

				Ib_thresh.convertTo(Ib_thresh, Ib.type());

				Mat Ib_borders = Mat::zeros(Ib.rows, Ib.cols, Ib.type());
				Ib_borders = findBorders(Ib_thresh);

				// OTIMIZAR URGENTEMENTE ESSA SEÇÃO DE CÓDIGO!!!!!! --------------------
				double sumVals = 0;
				int countVals = 0;

				// Equivalent to: vals = double(I(Ib));
			  for(int i = 0; i < Ib_borders.rows; i++)
			  {
			 	  		for(int j = 0; j < Ib_borders.cols; j++)
				  		{
					  			if (Ib_borders.at<float>(i,j) == 255)
						  		{
											 sumVals = sumVals + I.at<uchar>(i,j);
											 countVals++;
								  }
				 		  }
			  }

				// ---------------------------------------------------------------------

				D[pos] = hausDim(Ib_borders);
				pos += 1;

				D[pos] = sumVals / countVals;
				pos += 1;

				D[pos] = countVals;
				pos += 1;
		}

		return D;
}
