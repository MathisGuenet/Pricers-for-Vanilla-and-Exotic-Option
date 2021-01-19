#include <vector>
#include <random>
#include <iostream>
#include <time.h>
#include "RandomWalkGenerator.h"

//Fill the random walk with random steps and initial value in function distribution
RandomWalkGenerator_singleton::RandomWalkGenerator_singleton(std::string distribution, int n,double initial_value)
{
	RandomWalk_singleton_gen.push_back(initial_value);
	if (distribution == "normal")
	{
		srand(time(NULL)); //set it here before entering in box_muller function, if i put it in box_muller it won't work
		for (int i = 1; i < n; i++)
		{
			RandomWalk_singleton_gen.push_back(box_Muller() + RandomWalk_singleton_gen[i - 1]);
		}
	}
	if (distribution == "bernouilli")
	{
		for (int i = 1; i < n; i++)
		{
			if (bernouilli(0.5) == 1) //go up
			{
				RandomWalk_singleton_gen.push_back(RandomWalk_singleton_gen[i - 1] * 1.1);
			}
			else // (bernouilli(0.5) == 0) go down
			{
				RandomWalk_singleton_gen.push_back(RandomWalk_singleton_gen[i - 1] * 0.9);
			}
		}
		
	}
}

RandomWalkGenerator_singleton& RandomWalkGenerator_singleton::getInstance(std::string distribution, int n, double initial_value)									// Returns a reference, a pointer on RandomWalk_singleton_gen
{
	static std::unique_ptr<RandomWalkGenerator_singleton> instance(new RandomWalkGenerator_singleton(distribution, n, initial_value));	// Create the unique instance of the class (unique pointer)
	return *instance;																// Returns the pointer on the instance, the reference of the instance
}

std::vector<double> RandomWalkGenerator_singleton::getRandomWalk_gen()
{
	return RandomWalk_singleton_gen;
}

//Normal law using box muller method
double RandomWalkGenerator_singleton::box_Muller()
{
	double unif_01 = (double(rand()) / double(RAND_MAX));
	double unif_02 = (double(rand()) / double(RAND_MAX));
	double R = sqrt(-2 * log(unif_01));
	double Teta = 2 * 3.14159265358979323846 * unif_02;
	return R * sin(Teta);
}

//return 1 with probability p and 0 with probability (1-p)
double RandomWalkGenerator_singleton::bernouilli(double p)
{
	std::random_device rd{}; // use to seed the rng 
	std::mt19937 rng{ rd() }; // rng
	std::bernoulli_distribution d(p);
	return d(rng); 
}

