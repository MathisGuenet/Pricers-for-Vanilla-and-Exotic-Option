#include "BS.h"
#include "MonteCarloIntegralComputer.h"
#include <math.h>

BS::BS(double r, double sigma, double s0)
{
	_r = r;
	_sigma = sigma;
	_s0 = s0;
}

double BS::pricerBS(const EuropeanCall& call) 
{
	double d1 = (1 / (_sigma* sqrt(call._t))) * (log(_s0 / call._k) + (_r + _sigma * _sigma / 2) * call._t);
	double d2 = d1 - _sigma * sqrt(call._t);
	double price = _s0 * 0.5 * (1 + erf(d1 / sqrt(2))) - call._k * exp(-_r * call._t) * 0.5 * (1 + erf(d2 / sqrt(2)));
	return price;
}

double BS::pricerBS(const EuropeanPut& put)
{
	double d1 = (1 / (_sigma * sqrt(put._t))) * (log(_s0 / put._k) + (_r + _sigma * _sigma / 2) * put._t);
	double d2 = d1 - _sigma * sqrt(put._t);
	double price = put._k * exp(-_r * put._t) * 0.5*(1+erf(-d2/sqrt(2))) - _s0 * 0.5*(1+erf(-d1/sqrt(2)));
	return price;
}


double BS::pricerBSMonteCarlo(const EuropeanCall& call)
{
	
	double d1 = (1 / (_sigma * sqrt(call._t))) * (log(_s0 / call._k) + (_r + _sigma * _sigma / 2) * call._t);
	double d2 = d1 - _sigma * sqrt(call._t);
	NormalIntegrator CDF_d1(-4, d1);
	NormalIntegrator CDF_d2(-4, d2);
	CDF_d1.compute(1000000);
	CDF_d2.compute(1000000);
	return _s0 * CDF_d1() - call._k * exp(-_r * call._t) * CDF_d2();
}

double BS::pricerBSMonteCarlo(const EuropeanPut& put)
{
	double d1 = (1 / (_sigma * sqrt(put._t))) * (log(_s0 / put._k) + (_r + _sigma * _sigma / 2) * put._t);
	double d2 = d1 - _sigma * sqrt(put._t);
	NormalIntegrator CDF_d1(-4, -d1);
	NormalIntegrator CDF_d2(-4, -d2);
	CDF_d1.compute(1000000);
	CDF_d2.compute(1000000);
	return put._k * exp(-_r * put._t) * CDF_d2() - _s0 * CDF_d1();
}


double BS::deltaComputer(const Option& option) //delta = DC/DS = N(d1)
{
	double d1 = ((log(_s0 / option._k) + (_r + (_sigma * _sigma) * 0.5) * option._t)) / (_sigma / sqrt(option._t));
	return 1 + erf(d1 / sqrt(2));
}