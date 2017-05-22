#include "otsurec.h"

// References
// https://stackoverflow.com/questions/15771512/compare-histograms-of-grayscale-images-in-opencv
void otsurec(Mat I, int ttotal)
{
	
	if (!I.empty())
	{
		I = I.reshape(1, I.rows*I.cols);

		// Histogram data

		// Set histogram bins count
		int num_bins = 256;
		int histSize[] = { num_bins };

		// Set ranges for histogram bins
		float lranges[] = { 0, 256 };
		const float* ranges[] = { lranges };

		// Create matrix for histogram
		Mat counts = Mat::zeros(num_bins, 1, CV_64F);
		int channels[] = { 0 };

		// Calculate histogram
		calcHist(&I, 1, channels, cv::Mat(), counts, 1, histSize, ranges, true, false);

		otsu(counts);

		//Mat T = Mat::zeros(ttotal, 1, CV_32F); // verificar se este tipo está certo
	}
	else
		return;
}

int otsu(Mat counts)
{
	double sum_counts = 0;

	for (int i = 0; i < counts.rows; i++)
	{
		sum_counts += counts.at<float>(i, 0);
	}

	Mat p = Mat::zeros(counts.rows, counts.cols, counts.type());
	Mat omega = Mat::zeros(counts.rows, counts.cols, counts.type());

	for (int i = 0; i < counts.rows; i++)
	{
		p.at<float>(i, 0) = counts.at<float>(i, 0) / sum_counts;
		
		for (int j = 0; j < i; j++) // Equivalent to "omega = cumsum(p)" on MATLAB
		{
			omega.at<float>(i, 0) += p.at<float>(j, 0);
		}
	}

	Mat mu = Mat::zeros(counts.rows, counts.cols, counts.type());

	for (int i = 0; i < counts.rows; i++) //Equivalent to "mu = cumsum(p .* (1:numel(counts))')"
	{
		//mu.at<double>(i-1, 0) = p.at<double>(i-1, 0) * i;
		for (int j = i; j >= 0; j--) 
		{
			mu.at<float>(i, 0) += p.at<float>(j, 0) * (j+1);
		}
	}
	
	double mu_t = mu.at<float>(counts.rows-1, 0);

	// cout << mu << endl; // Até aqui tá tudo certo

	Mat sigma_b_squared = Mat::zeros(counts.rows, counts.cols, counts.type());
	double maxval = 0;

	for (int i = 0; i < counts.rows; i++)
	{
		sigma_b_squared.at<float>(i, 0) = pow((mu_t * omega.at<float>(i, 0) - mu.at<float>(i, 0)), 2) / (omega.at<float>(i, 0) * (1 - omega.at<float>(i, 0)));
		/*if (sigma_b_squared.at<float>(i, 0) > maxval)
			maxval = sigma_b_squared.at<float>(i, 0);*/
	}

	cout << sigma_b_squared << endl;
	//cout << "maxval: " << maxval << endl;

	return 0;
}