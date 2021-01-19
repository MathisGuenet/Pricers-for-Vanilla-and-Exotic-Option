#pragma once

#pragma once
#include <random>

class MonteCarloIntegralComputer
{
public:
	MonteCarloIntegralComputer(double, double);
	~MonteCarloIntegralComputer();
	double intervalConfiance(int nb_points);
	void compute(int);
	virtual double f(double) = 0;
	double operator ()();

private:
	int m_n;                        //nb points already generated
	double m_a;                     //integral bounds
	double m_b;
	double m_upper_lim;             //rectangle bounds
	double m_lower_lim;
	double m_current_estimate;      //calculated by compute(int)
	std::mt19937 gen;           //random gen
};

class NormalIntegrator : public MonteCarloIntegralComputer
{
public:
	NormalIntegrator(double, double);
	~NormalIntegrator();
	double f(double) override;
};

