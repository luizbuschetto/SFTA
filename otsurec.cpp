#include "otsurec.h"

// References
// https://stackoverflow.com/questions/15771512/compare-histograms-of-grayscale-images-in-opencv
// http://www.geeksforgeeks.org/pass-2d-array-parameter-c/

void otsurec(Mat I, int ttotal, double T[])
{
	if (!I.empty())
	{
		I = I.reshape(1, I.rows*I.cols);

		// Histogram data

		// Set histogram bins count
		int histSize[] = { NUM_BINS };

		// Set ranges for histogram bins
		float lranges[] = { 0, 256 };
		const float* ranges[] = { lranges };

		// Create matrix for histogram
		Mat hist = Mat::zeros(NUM_BINS, 1, CV_16UC1);
		int channels[] = { 0 };

		// Calculate histogram
		calcHist(&I, 1, channels, cv::Mat(), hist, 1, histSize, ranges, true, false);

		double counts[NUM_BINS];

		for (int i = 0; i < hist.rows; i++)
				counts[i] = hist.at<float>(i,0);

		double pos = otsu(counts, 256);

		otsurec_helper(T, counts, 1, NUM_BINS, 1, ttotal);
	}
	else
		return;
}

double otsu(double counts[], int countsSize)
{
	double sum_counts = 0;

	for (int i = 0; i < countsSize; i++)
		sum_counts += counts[i];

	cout << fixed << setprecision(15);

	double p[countsSize];
	double omega[countsSize];

	// Initializing omega
	for (int i = 0; i < countsSize; i++)
			omega[i] = 0;

	for (int i = 0; i < countsSize; i++)
	{
		p[i] = counts[i] / sum_counts;

		for (int j = i; j >= 0; j--) // Equivalent to "omega = cumsum(p)" on MATLAB
			omega[i] += p[j];
	}

	double mu[countsSize];

	// Initializing mu
	for (int i = 0; i < countsSize; i++)
			mu[i] = 0;

	for (int i = 0; i < countsSize; i++) //Equivalent to "mu = cumsum(p .* (1:numel(counts))')"
		for (int j = i; j >= 0; j--)
			mu[i] += p[j] * (j+1);

	double mu_t = mu[countsSize-1];

	double sigma_b_squared[countsSize];
	double maxval = 0;

	for (int i = 0; i < countsSize; i++)
	{
		sigma_b_squared[i] = pow((mu_t * omega[i] - mu[i]), 2) / (omega[i] * (1 - omega[i]));
		if (sigma_b_squared[i] > maxval)
			maxval = sigma_b_squared[i];
	}

	double pos = 0;

	if(isfinite(maxval))
	{
		int num_pos = 0;
		for (int i = 0; i < countsSize; i++)
		{
				if(sigma_b_squared[i] == maxval)
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

void otsurec_helper(double T[], double counts[], int lowerBin, int upperBin, int tLower, int tUpper)
{
		if ((tUpper < tLower) || (lowerBin >= upperBin))
			return;
		else
		{
				int size = ceil(upperBin) - ceil(lowerBin) + 1;
				double counts_aux[size];

				int j = 0;
				// The "- 1" on limits: Array in C++: 0..255. In MATLAB 1..256
				for (int i = ceil(lowerBin) - 1; i <= ceil(upperBin); i++)
				{
						counts_aux[j] = counts[i];
						j++;
				}

				double level = otsu(counts_aux, size) + lowerBin + 1;

				// For some reason, I was getting a problem for calculating the insertPos
				// in one line. So, the only way I make it work is that
				float aux = (tLower + tUpper);
				float aux1 = aux / 2;
				float aux2 = ceil(aux1);
				int insertPos = aux2;

				T[insertPos-1] = level / NUM_BINS;
				otsurec_helper(T, counts, lowerBin, level, tLower, insertPos - 1);
        otsurec_helper(T, counts, level + 1, upperBin, insertPos + 1, tUpper);
		}
}
