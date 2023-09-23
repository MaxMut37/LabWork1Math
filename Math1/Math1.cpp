#include <iostream>
#include <omp.h>
#include <math.h>

double func(double* y, double t, int i)
{
	double w = 0;
	switch (i)
	{
	case 0: w = y[1]; break;
	case 1: w = -0.07 * t * y[1] - t * t * y[0]; break;
	}
	return w;
}

int main()
{
	const int n = 2;
	double t0 = 0.0, timeMax = 5.0, tau = 0.01, t = t0, tn, tk, deltat;
	double y[n] = { 0.0, 0.125 };
	double yy[n] = { 0.0 };

	tn = omp_get_wtime();
	for (double t = t0; t <= timeMax; t += tau)
	{
		for (int i = 0; i < n; i++)
		{
			yy[i] = y[i] + tau * func(y, t, i);
		}
		for (int i = 0; i < n; i++)
			y[i] = yy[i];
	}

	tk = omp_get_wtime();
	deltat = tk - tn;
	std::cout << "Delta t = " << deltat << std::endl;
	for (int i = 0; i < n; i++)
	{
		std::cout << "Array[" << i << "]: " << y[i] << std::endl;
	}
	return 0;
}