#include "otsurec.h"

// References
// https://stackoverflow.com/questions/15771512/compare-histograms-of-grayscale-images-in-opencv
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

		double pos = otsu(counts);
		cout << pos << endl;

		//Mat T = Mat::zeros(ttotal, 1, CV_32F); // verificar se este tipo est� certo
	}
	else
		return;
}

double otsu(double counts[NUM_BINS][COLS])
{
	double sum_counts = 0;

	for (int i = 0; i < NUM_BINS; i++)
		sum_counts += counts[i][0];


	cout << fixed << setprecision(15);

	double p[NUM_BINS][COLS];
	double omega[NUM_BINS][COLS];

	// Initializing omega
	for (int i = 0; i < NUM_BINS; i++)
			omega[i][0] = 0;

	for (int i = 0; i < NUM_BINS; i++)
	{
		p[i][0] = counts[i][0] / sum_counts;

		for (int j = i; j >= 0; j--) // Equivalent to "omega = cumsum(p)" on MATLAB
			omega[i][0] += p[j][0];
	}

	double mu[NUM_BINS][COLS];

	// Initializing mu
	for (int i = 0; i < NUM_BINS; i++)
			mu[i][0] = 0;

	for (int i = 0; i < NUM_BINS; i++) //Equivalent to "mu = cumsum(p .* (1:numel(counts))')"
		for (int j = i; j >= 0; j--)
			mu[i][0] += p[j][0] * (j+1);

	double mu_t = mu[NUM_BINS-1][0];

	double sigma_b_squared[NUM_BINS][COLS];
	double maxval = 0;

	for (int i = 0; i < NUM_BINS; i++)
	{
		sigma_b_squared[i][0] = pow((mu_t * omega[i][0] - mu[i][0]), 2) / (omega[i][0] * (1 - omega[i][0]));
		if (sigma_b_squared[i][0] > maxval)
			maxval = sigma_b_squared[i][0];
	}

	double pos = 0;

	if(isfinite(maxval))
	{
		int num_pos = 0;
		for (int i = 0; i < NUM_BINS; i++)
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
