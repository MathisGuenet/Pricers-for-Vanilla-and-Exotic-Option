#include "CRR.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include "Option.h"

CRR::CRR(int steps, double r, double s0, double up, double down)
{
	_r = r;
	_s0 = s0;
	_steps = steps;
	_up = up;
	_down = down;
	crrModel_.resize(_steps + 1);
	for (int n = _steps; n >= 0; n--) //n is the step
	{
		crrModel_[n].resize(n + 1);
	}
}

CRR::CRR(int steps, double maturity,double r, double s0, double sigma, bool bs)
{
	_s0 = s0;
	_steps = steps;
	double h = maturity / _steps;
	_r = exp(r * h) - 1;
	_up = exp((_r + (sigma * sigma) / 2) * h + sigma * sqrt(h));
	_down = exp((_r + (sigma * sigma) / 2) * h - sigma * sqrt(h));

	crrModel_.resize(_steps + 1);
	for (int n = _steps; n >= 0; n--) //n is the step
	{
		crrModel_[n].resize(n + 1);
	}
}

void CRR::setNode(double value, int step, int node)
{
	crrModel_[step][node] = value;
}

double CRR::getNode(int step, int node)
{
	return crrModel_[step][node];
}

double CRR::pricer(EuropeanOption& option)
{
	//get all the payoffs at maturity of the entire binomial tree
	for (int j = _steps; j >= 0 ;j--) //j is number of time stock goes up
	{
		crrModel_[_steps][j] = option.payOff(getStockPrice(j, _s0, _steps));
	}
	//now that we have the full payoff at maturity, we have to discount it until the present with the neutral probability
	double p = ((1 + _r) - _down) / (_up - _down);					//((1 + r) - d) / (u - d) = probabilité neutral risk
	
	//let's get the discounted payoffs for each node
	// node = (p*payoff + (1-p)*payoff)/(1+r)
	for (int n = _steps - 1; n >= 0; n--) //n is the step
	{
		for(int j = n; j>= 0; j--)
		{
			crrModel_[n][j] = (p * crrModel_[n + 1][j + 1] + (1 - p) * crrModel_[n + 1][j]) / (1 + _r);
		}
	}
	return crrModel_[0][0];
}

double CRR::pricer(AmericanCall& option)
{
	EuropeanCall call(option._k, option._t);
	//get all the payoffs at maturity of the entire binomial tree
	//For the AmericanCall, the payoff at maturity is the same than a European Call
	for (int j = _steps; j >= 0;j--) //j is number of time stock goes up
	{
		crrModel_[_steps][j] = call.payOff(getStockPrice(j, _s0, _steps));
	}
	double p = ((1 + _r) - _down) / (_up - _down);
	//get the price of the american option at steps n and node j
	for (int n = _steps - 1; n >= 0; n--) //n is the step
	{
		for (int j = n; j >= 0; j--)
		{
			double a = (p * crrModel_[n + 1][j + 1] +  (1-p)* crrModel_[n + 1][j])/(1+_r);
			double b = call.payOff(getStockPrice(j, _s0, n));
			crrModel_[n][j] = std::max(a,b);
		}
	}
	return crrModel_[0][0];
}

double CRR::pricer(AmericanPut& option)
{
	EuropeanPut put(option._k, option._t);
	//get all the payoffs at maturity of the entire binomial tree
	//For the AmericanCall, the payoff at maturity is the same than a European Call
	for (int j = _steps; j >= 0;j--) //j is number of time stock goes up
	{
		crrModel_[_steps][j] = put.payOff(getStockPrice(j, _s0, _steps));
	}
	double p = ((1 + _r) - _down) / (_up - _down);
	//get the price of the american option at steps n and node j
	for (int n = _steps - 1; n >= 0; n--) //n is the step
	{
		for (int j = n; j >= 0; j--)
		{
			double a = (p * crrModel_[n + 1][j + 1] + (1 - p) * crrModel_[n + 1][j]) / (1 + _r);
			double b = put.payOff(getStockPrice(j, _s0, n));
			crrModel_[n][j] = std::max(a, b);
		}
	}
	return crrModel_[0][0];
}

double CRR::pricerClosedFormula(EuropeanOption& option)
{
	float sum = 0;
	double p = ((1 + _r) - _down) / (_up - _down);
	for (int i = 0; i <= _steps; i++)
	{
		sum += (factorial(_steps) / (factorial(i) * factorial(_steps - i))) * pow(p, i) * pow((1 - p), (_steps - i)) * option.payOff(getStockPrice(i, _s0, _steps));
	}
	return exp(-_r * _steps) * sum;
}


double CRR::factorial(int n)
{
	if (n > 1)
		return n * factorial(n - 1);
	else
		return 1;
}

double CRR::getStockPrice(int j, double S0, int N)
{
	double S = S0 * Up(_up,j) * Down(_down,N - j);
	return S;
}

double CRR::Up(double up, int j)
{
	double Pow = pow(up, j);
	return Pow;
}

double CRR::Down(double down, int j)
{
	double Pow = pow(down, j);
	return Pow;
}

void CRR::Display()
{
	std::string phrase;
	phrase = "";
	int compteur = 1;
	//let's get the discounted payoffs for each node
	// node = (ppayoff + (1-p)payoff)/(1+r)
	for (int n = _steps - 1; n >= 0; n--) //n is the step
	{
		for (int j = n; j >= 0; j--)
		{
			phrase = phrase + std::to_string(crrModel_[n][j]) + "    ";
		}
		phrase = phrase + "\n";
		for (int k = compteur; k > 0; k--)
		{
			phrase = phrase + "      ";
		}
		for (int k = compteur; _steps - k > 0; k++)
		{
			phrase = phrase + "  \\   /     ";
		}

		phrase = phrase + "\n";
		for (int k = compteur; k > 0; k--)
		{
			phrase = phrase + "      ";
		}
		compteur++;
	}
	std::cout << phrase;
}
