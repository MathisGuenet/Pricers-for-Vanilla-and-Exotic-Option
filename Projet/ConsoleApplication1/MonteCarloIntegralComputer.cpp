#include "MonteCarloIntegralComputer.h"
#include<time.h>

// Constructor
MonteCarloIntegralComputer::MonteCarloIntegralComputer(double a, double b)
{
	// Setting the variables here
	m_a = a;
	m_b = b;

	// Default value as we have just constructed the computer
	m_n = 0;
	m_lower_lim = 0;
	m_upper_lim = 0;
	m_current_estimate = 0;

	// Random generator here
	std::random_device rd;
	std::mt19937 gen(rd());
	gen = gen;
}

//Destructor
MonteCarloIntegralComputer::~MonteCarloIntegralComputer() { }

void MonteCarloIntegralComputer::compute(int nb_points)
{
	srand(time(NULL));
	double sum = 0;
	for (int i = 0; i < nb_points; i++)
	{
		double x = m_a + (double(rand()) / double(RAND_MAX)) * (m_b - m_a);       // x est généré dans [m_a ; m_b]
		sum += f(x);                                                     // on applique la fonction au point
	}
	m_current_estimate = ((m_b - m_a) * sum + m_current_estimate * m_n) / (double(m_n) + double(nb_points));
	m_n += nb_points;
}

double MonteCarloIntegralComputer::intervalConfiance(int nb_points)
{
	double sum = 0;
	double sum2 = 0;
	for (int i = 0; i < m_n; i++)
	{
		double x = (double(rand()) / double(RAND_MAX)) * (m_b - m_a);
		sum2 += x * x;                                                     // on applique la fonction au point
		sum += x;
	}
	double mean = sum / nb_points;
	double variance = (sum2 / nb_points) - (mean * mean);
	double ecart = 1.96 * sqrt(variance) / (sqrt(nb_points));
	double result = mean - ecart;
	return result;

}

double MonteCarloIntegralComputer::operator()()
{
	return m_current_estimate;
}


//X2 class methods

//Constructor
NormalIntegrator::NormalIntegrator(double a, double b) :MonteCarloIntegralComputer(a, b) { }

//Destructor
NormalIntegrator::~NormalIntegrator() { }

double NormalIntegrator::f(double x)
{
	double M_PI = 3.141592;
	return (1.0 / sqrt(2 * M_PI)) * exp(-x * x / 2);
}