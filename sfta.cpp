#include "sfta.h"
#include "otsurec.h"
#include "findBorders.h"
#include "hausDim.h"

void sfta(Mat I, int nt)
{
	I.convertTo(I, CV_8UC1);
	// Colocar uma verificação aqui: se está em grayscale
	cvtColor(I, I, CV_BGR2GRAY, 1);

	double T[nt+1][COLS];
	// Initializing matrix
	for(int i = 0; i < nt; i++)
			T[i][0] = 0;

	 otsurec(I, nt, T);

	//  for (int i = 0; i < nt; i++)
	//  		cout << T[i][0] << endl;

	 int dSize = nt * 6; 	// dSize = numel(T) * 6: nt = numel(T) sempre? Verificar isso
	 double D[dSize];
	 int pos = 0; // Começa em zero porque o range do OpenCV é diferente do MATLAB
	 Mat Ib = Mat::zeros(I.rows, I.cols, I.type());

	 for( int t = 0; t < nt; t++ )
	 {
		 		double thresh = T[t][0];


				// MATLAB Range: 0 ~ 1;
				// OpenCV Range: 0 ~ 255.
				// So, to apply the threshold, we need to normalize the pixel values between 0 and 1
				I.convertTo(Ib, CV_32FC3, 1.0/255.5);

				threshold(Ib, Ib, thresh, 255, THRESH_BINARY); // Using 255 because it's equivalent to 1 in MATLAB

				pair <Mat, int> findBordersVars (Mat::zeros(Ib.rows, Ib.cols, CV_64FC1), 0);
				findBordersVars = findBorders(Ib); // Essa função pode retornar só a imagem agora

				// Return of findBorders:
				// Ib 			 = findBordersVars.first
				// vals_size = findBordersVars.second

				// OTIMIZAR URGENTEMENTE ESSA SEÇÃO DE CÓDIGO!!!!!! --------------------
				//int vals[findBordersVars.second][1];
				double sumVals = 0;
				int countVals = 0;

				// cout << findBordersVars.first.rows << endl;
				// cout << findBordersVars.first.cols << endl;

				// Equivalent to: vals = double(I(Ib));
			  for(int i = 0; i < findBordersVars.first.rows; i++)
			  {
			 	  		for(int j = 0; j < findBordersVars.first.cols; j++)
				  		{
					  			if (findBordersVars.first.at<float>(i,j) == 255)
						  		{
							  			 //vals[countVals][0] = I.at<uchar>(j,i); // Ainda precisa dessa variável?
								  		 //cout << vals_count+1 << ": " << vals[vals_count][0] << endl;
											 sumVals = sumVals + I.at<uchar>(i,j);
											 countVals++;
								  }
				 		  }
			  }

				// ---------------------------------------------------------------------

				D[pos] = hausDim(findBordersVars.first);
				pos += 1;

				D[pos] = sumVals / countVals;
				pos += 1;

				D[pos] = countVals;
				pos += 1;

	 	} // Termina o primeiro for

		T[nt][0] = 1;
		 double range = 255;
		// minMaxLoc(I, NULL, &range);
		//
		// cout << "range: " << range << endl;

		for( int t = 0; t < nt; t++ )
		{
				double lowerThresh = T[t][0];
				double upperThresh = T[t + 1][0];

				Mat lowThresh = Mat::zeros(I.rows, I.cols, I.type());
				Mat upThresh = Mat::zeros(I.rows, I.cols, I.type());
				threshold(I, lowThresh, lowerThresh*range, 255, THRESH_BINARY);
				threshold(I, upThresh, upperThresh*range, 255, THRESH_BINARY_INV);

				Mat result = Mat::zeros(upThresh.rows, upThresh.cols, upThresh.type());
				bitwise_and(lowThresh, upThresh, result);

				result.convertTo(result, Ib.type());
				//cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAND" << endl;

				// namedWindow("lowThresh", WINDOW_NORMAL);
				// imshow("lowThresh", lowThresh);
				// namedWindow("upThresh", WINDOW_NORMAL);
				// imshow("upThresh", upThresh);
				// namedWindow("result2", WINDOW_NORMAL);
				// imshow("result2", result);
				// waitKey(0);

				// a partir daqui=============================================================

				pair <Mat, int> findBordersVars1 (Mat::zeros(result.rows, result.cols, CV_64FC1), 0);
				findBordersVars1 = findBorders(result); // Essa função pode retornar só a imagem agora

				// Return of findBorders:
				// Ib 			 = findBordersVars.first
				// vals_size = findBordersVars.second

				// OTIMIZAR URGENTEMENTE ESSA SEÇÃO DE CÓDIGO!!!!!! --------------------
				//int vals[findBordersVars.second][1];
				double sumVals = 0;
				int countVals = 0;

				// cout << findBordersVars.first.rows << endl;
				// cout << findBordersVars.first.cols << endl;

				// Equivalent to: vals = double(I(Ib));
			  for(int i = 0; i < findBordersVars1.first.rows; i++)
			  {
			 	  		for(int j = 0; j < findBordersVars1.first.cols; j++)
				  		{
					  			if (findBordersVars1.first.at<float>(i,j) == 255)
						  		{
							  			 //vals[countVals][0] = I.at<uchar>(j,i); // Ainda precisa dessa variável?
								  		 //cout << vals_count+1 << ": " << vals[vals_count][0] << endl;
											 sumVals = sumVals + I.at<uchar>(i,j);
											 countVals++;
								  }
				 		  }
			  }

				// ---------------------------------------------------------------------

				D[pos] = hausDim(findBordersVars1.first);
				pos += 1;

				D[pos] = sumVals / countVals;
				pos += 1;

				D[pos] = countVals;
				pos += 1;
		}



		for(int i = 0; i < pos; i++)
				cout << "D[" << i + 1 << "]: " << D[i] << endl;

}
