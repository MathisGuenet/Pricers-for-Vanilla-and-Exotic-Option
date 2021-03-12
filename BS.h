#pragma once
#include <iostream>
#include <ctime>
#include "Option.h"

//this class is for a closed pricer formula
class BS
{
public :
	BS(double r, double sigma, double s0);
	double pricerBS(const EuropeanCall& call);
	double pricerBS(const EuropeanPut& put);
	double pricerBSMonteCarlo(const EuropeanCall& call);
	double pricerBSMonteCarlo(const EuropeanPut& put);
	double deltaComputer(const Option& option);

	double _r;
	double _s0;
	double _sigma;
};

