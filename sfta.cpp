#include "sfta.h"
#include "otsurec.h"

void sfta(Mat I, int nt)
{
	I.convertTo(I, CV_8UC1);
	// Colocar uma verificação aqui: se está em grayscale
	cvtColor(I, I, CV_BGR2GRAY, 1);

	otsurec(I, nt);
}