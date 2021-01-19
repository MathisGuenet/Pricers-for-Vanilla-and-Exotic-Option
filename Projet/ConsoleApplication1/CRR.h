#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include "Option.h"

//this class is for a binomial pricer
class CRR
{
public:
	CRR(int steps, double r, double s0, double up, double down);//CRR classic
	CRR(int steps, double maturity, double r, double s0, double sigma, bool bs ); //Blacksholes as limit of the binomial Tree

	double factorial(int n);
	void setNode(double value, int step, int node);
	double getNode(int step, int node);
	double Up(double up, int j);
	double Down(double down, int j);
	double getStockPrice(int j, double S0, int N);
	void Display();

	//pricers CRRmodel
	double pricer(EuropeanOption& option);
	double pricer(AmericanCall& option);
	double pricer(AmericanPut& option);
	
	//pricers closed formula CRR
	double pricerClosedFormula(EuropeanOption& option);

private:
	int _steps; //nbr of steps in the binary tree
	double _s0;
	double _r;
	double _up;
	double _down;
	std::vector<std::vector<double>> crrModel_;
};