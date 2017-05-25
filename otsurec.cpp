#include "otsurec.h"

// References
// https://stackoverflow.com/questions/15771512/compare-histograms-of-grayscale-images-in-opencv
// http://www.geeksforgeeks.org/pass-2d-array-parameter-c/

void otsurec(Mat I, int ttotal)
{
	if (!I.empty())
	{
		// I = I.reshape(1, I.NUM_BINS*I.cols);
		//
		// // Histogram data
		//
		// // Set histogram bins count
		// int NUM_BINS = 256;
		// int histSize[] = { NUM_BINS };
		//
		// // Set ranges for histogram bins
		// float lranges[] = { 0, 256 };
		// const float* ranges[] = { lranges };
		//
		// // Create matrix for histogram
		// Mat hist = Mat::zeros(NUM_BINS, 1, CV_16UC1);
		// int channels[] = { 0 };
		//
		// // Calculate histogram
		// calcHist(&I, 1, channels, cv::Mat(), hist, 1, histSize, ranges, true, false);

		// Using the histogram genered by MATLAB to validate the algorithm
		float matrix[256][1];
		FILE* fid = fopen("hist_matlab.txt", "r");

		for ( int i = 0; i < 256; i++ )
				fscanf(fid, "%f", &matrix[i][0]);

		Mat hist = cv::Mat(256, 1, CV_32F, matrix);

		double counts[NUM_BINS][COLS];

		for ( int i = 0; i < hist.rows; i++ )
		{
				counts[i][0] = hist.at<float>(i,0);
		}

		// -------------------------------------------------------------------------

		double pos = otsu(counts, 256);
		//cout << "pos: " << pos << endl;

		double T[ttotal][COLS];

		// Initializing matrix
		for(int i = 0; i < ttotal; i++)
				T[i][0] = 0;

		otsurec_helper(T, counts, 1, NUM_BINS, 1, ttotal);

		for(int i = 0; i < ttotal; i++)
				cout << T[i][0] << endl;

		// Return the matrix "T" here

	}
	else
		return;
}

// void test_func(double test_array[][1], int i)
// {
// 		for (int i = 0; i < 18; i++)
// 			cout << i << ":"test_array[i][0] << endl;
// }

double otsu(double counts[][COLS], int countsSize)
{
	double sum_counts = 0;

	for (int i = 0; i < countsSize; i++)
		sum_counts += counts[i][0];

	cout << fixed << setprecision(15);

	double p[countsSize][COLS];
	double omega[countsSize][COLS];

	// Initializing omega
	for (int i = 0; i < countsSize; i++)
			omega[i][0] = 0;

	for (int i = 0; i < countsSize; i++)
	{
		p[i][0] = counts[i][0] / sum_counts;

		for (int j = i; j >= 0; j--) // Equivalent to "omega = cumsum(p)" on MATLAB
			omega[i][0] += p[j][0];
	}

	double mu[countsSize][COLS];

	// Initializing mu
	for (int i = 0; i < countsSize; i++)
			mu[i][0] = 0;

	for (int i = 0; i < countsSize; i++) //Equivalent to "mu = cumsum(p .* (1:numel(counts))')"
		for (int j = i; j >= 0; j--)
			mu[i][0] += p[j][0] * (j+1);

	double mu_t = mu[countsSize-1][0];

	double sigma_b_squared[countsSize][COLS];
	double maxval = 0;

	for (int i = 0; i < countsSize; i++)
	{
		sigma_b_squared[i][0] = pow((mu_t * omega[i][0] - mu[i][0]), 2) / (omega[i][0] * (1 - omega[i][0]));
		if (sigma_b_squared[i][0] > maxval)
			maxval = sigma_b_squared[i][0];
	}

	double pos = 0;

	if(isfinite(maxval))
	{
		int num_pos = 0;
		for (int i = 0; i < countsSize; i++)
		{
				if(sigma_b_squared[i][0] == maxval)
				{
						pos += i;
						num_pos++;
				}
		}
		pos = pos/num_pos;
	}
	else
		pos = 0;

	return pos;
}

void otsurec_helper(double T[][COLS], double counts[][COLS], int lowerBin, int upperBin, int tLower, int tUpper)
{
		if ((tUpper < tLower) || (lowerBin >= upperBin))
			return;
		else
		{
				int size = ceil(upperBin) - ceil(lowerBin) + 1;
				double counts_aux[size][1];

				int j = 0;
				// The "- 1" on limits: Array in C++: 0..255. In MATLAB 1..256
				for (int i = ceil(lowerBin) - 1; i <= ceil(upperBin); i++)
				{
						counts_aux[j][0] = counts[i][0];
						j++;
				}

				double level = otsu(counts_aux, size) + lowerBin + 1;

				// Por algum motivo, pra calcular a posição de inserção tava dando problema
				// só consegui arrumar assim
				float aux = (tLower + tUpper);
				float aux1 = aux / 2;
				float aux2 = ceil(aux1);
				int insertPos = aux2;

				T[insertPos-1][0] = level / NUM_BINS;
				otsurec_helper(T, counts, lowerBin, level, tLower, insertPos - 1);
        otsurec_helper(T, counts, level + 1, upperBin, insertPos + 1, tUpper);
		}
}
