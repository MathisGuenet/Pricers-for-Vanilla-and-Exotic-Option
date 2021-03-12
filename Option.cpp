#include "Option.h"
#include <iostream>
#include <math.h>

//Main Option
Option::Option(double K, double t)
{
	//sigma is 0 if we have to use CRR model that doesnt care about volaitlity
	_k = K;
	_t = t;
}

//European Option
EuropeanOption::EuropeanOption(double k, double t) : Option(k, t){}

AsianOption::AsianOption(double k, double t):Option(k,t){}

AmericanOption::AmericanOption(double k, double t):Option(k,t){}

EuropeanCall::EuropeanCall(double k, double t) : EuropeanOption(k,t) {}

double EuropeanCall::payOff(double St)
{
	double payoff = std::max(St - _k, 0.0);
	return payoff;
}

EuropeanPut::EuropeanPut(double k, double t) :EuropeanOption(k, t) {}

double EuropeanPut::payOff(double St)
{
	double payoff = std::max(_k - St, 0.0);
	return payoff;
}

EuropeanDigitalCall::EuropeanDigitalCall(double k, double t) 
	: EuropeanOption (k, t){}

double EuropeanDigitalCall::payOff(double St)
{
	if (St > _k)
		return 1;
	else
		return 0;
}

EuropeanDigitalPut::EuropeanDigitalPut(double k, double t) 
	: EuropeanOption(k, t){}

double EuropeanDigitalPut::payOff(double St)
{
	if (St < _k)
		return 1;
	else
		return 0;
	//return St < K_ ? 1 : 0;
}

//Asian Option
AsianCall::AsianCall(double k, double t)
	:AsianOption(k,t){}


double AsianCall::payOff(std::vector<double> path)
{
	double sum = 0;
	for (int i = 1; i <_t + 1;i++)
	{
		sum = sum + path[i];
	}
	double payoff = std::max(sum / _t - _k, 0.0);
	return payoff;
}

AsianPut::AsianPut(double k, double t)
	:AsianOption(k, t) {}

double AsianPut::payOff(std::vector<double> path)
{
	double sum = 0;
	for (int i=1; i < _t + 1; i++)
	{
		sum = sum + path[i];
	}
	double payoff = std::max(_k - sum / _t, 0.0);
	return payoff;
}	
//American Option
AmericanCall::AmericanCall(double k, double t)
	:AmericanOption(k, t){}

AmericanPut::AmericanPut(double k, double t)
	: AmericanOption(k, t) {}


