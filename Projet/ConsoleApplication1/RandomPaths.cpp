#include "RandomPaths.h"
#include <vector>
#include <time.h>
#include <random>
#include <math.h>
#include "Option.h"

RandomPaths::RandomPaths(int nSimul, double r, double sigma, double s0, double steps, Option& option)
{
	_r = r;
	_sigma = sigma;
	_s0 = s0;
	_steps = steps;
	nSimul_ = nSimul;
	//t = maturity
	//let's resize our paths vector of vector
	paths_.resize(nSimul_);
	for (int n = 0; n < nSimul_; n++)
	{
		paths_[n].resize(_steps + 1);
	}
	srand(time(NULL));
	for(int n = 0; n < nSimul_; n++) //create n paths
	{
		
		paths_[n][0] = _s0;
		for(int t = 1; t < _steps + 1; t++) //create a path of n steps
		{
			//tk = k/m * T avec m : nbr of steps and T maturity
			//tk - tk-1 = k/m * T - k-1/m * T = T/m
			//double increment = option._t / steps;
			paths_[n][t] = paths_[n][t - 1] * exp((_r - (_sigma * _sigma) / 2) + _sigma * boxMuller());
		}
	}
}

double RandomPaths::pricerPathDependent(EuropeanOption& option)
{
	double sum = 0;
	//let's determine the average payOff of all our paths
	for (int i = 0; i < nSimul_; i++)
	{
		sum += option.payOff(paths_[i][option._t]);
	}
	double meanPayoffs = sum / nSimul_;
	double price = exp(-_r * option._t) * meanPayoffs;
	return price;
}

double RandomPaths::pricerPathDependent(AsianOption& option)
{
	double sum = 0;
	for (int i = 0; i < nSimul_; i++)
	{
		sum += option.payOff(paths_[i]);
	}
	double meanPayoffs = sum / nSimul_;
	double price = exp(-_r * option._t) * meanPayoffs;
	return price;
}

double RandomPaths::boxMuller()
{
	double unif_01 = (double(rand()) / double(RAND_MAX));
	double unif_02 = (double(rand()) / double(RAND_MAX));
	double R = sqrt(-2 * log(unif_01));
	double Teta = 2 * 3.14159265358979323846 * unif_02;
	return R * sin(Teta);
}




