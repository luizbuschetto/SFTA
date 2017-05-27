#include "sfta.h"
#include "otsurec.h"
#include "findBorders.h"
#include "hausDim.h"

void sfta(Mat I, int nt)
{
	I.convertTo(I, CV_8UC1);
	// Colocar uma verificação aqui: se está em grayscale
	cvtColor(I, I, CV_BGR2GRAY, 1);

	double T[nt][COLS];
	// Initializing matrix
	for(int i = 0; i < nt; i++)
			T[i][0] = 0;

	 otsurec(I, nt, T);

	//  for (int i = 0; i < nt; i++)
	//  		cout << T[i][0] << endl;

	 int dSize = nt * 6; 	// dSize = numel(T) * 6: nt = numel(T) sempre? Verificar isso
	 //Mat D = Mat::zeros(1, dSize, CV_64F);
	 int pos = 1;

	// for( int t = 0; t < nt; t++ )
	 //{
		 		double thresh = T[0][0];
				Mat Ib = Mat::zeros(I.rows, I.cols, I.type());

				// MATLAB Range: 0 ~ 1;
				// OpenCV Range: 0 ~ 255.
				// So, to apply the threshold, we need to normalize the pixel values between 0 and 1
				I.convertTo(Ib, CV_32FC3, 1.0/255.5);

				threshold(Ib, Ib, thresh, 255, THRESH_BINARY); // Using 255 because it's equivalent to 1 in MATLAB

				pair <Mat, int> findBordersVars (Mat::zeros(Ib.rows, Ib.cols, I.type()), 0);
				findBordersVars = findBorders(Ib);

				// Return of findBorders:
				// Ib 			 = findBordersVars.first
				// vals_size = findBordersVars.second

				// OTIMIZAR URGENTEMENTE ESSA SEÇÃO DE CÓDIGO!!!!!! --------------------
				int vals[findBordersVars.second][1];
				int vals_count = 0;

				// Equivalent to: vals = double(I(Ib));
			  for(int i = 0; i < findBordersVars.first.rows; i++)
			  {
			 	  		for(int j = 0; j < findBordersVars.first.cols; j++)
				  		{
					  			if (findBordersVars.first.at<float>(j,i) == 255)
						  		{
							  			 vals[vals_count][0] = I.at<uchar>(j,i);
								  		 //cout << vals_count+1 << ": " << vals[vals_count][0] << endl;
									  	 vals_count++;
								  }
				 		  }
			  }

				// ---------------------------------------------------------------------

				double D = hausDim(findBordersVars.first);
				cout << "D no final: " << D << endl;
				// namedWindow("thresh_test", WINDOW_NORMAL);
				// imshow("thresh_test", Ib);
				// waitKey(0);

	 	//} // termina o for

}
