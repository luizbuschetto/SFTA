#include "sfta.h"
#include "otsurec.h"

void sfta(Mat I, int nt)
{
	I.convertTo(I, CV_8UC1);
	// Colocar uma verifica��o aqui: se est� em grayscale
	cvtColor(I, I, CV_BGR2GRAY, 1);

	double T[nt][COLS];
	// Initializing matrix
	for(int i = 0; i < nt; i++)
			T[i][0] = 0;

	 otsurec(I, nt, T);

	 for(int i = 0; i < nt; i++)
			 cout << T[i][0] << endl;
}
