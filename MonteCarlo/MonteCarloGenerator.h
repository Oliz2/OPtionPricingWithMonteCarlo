#pragma once
#include <vector>
#include <iostream>
#include <random>

using namespace std;

// Class responsible for generating uniform and standard normal random numbers
class MonteCarloGenerator
{

private:

	// Total number of random samples to be generated
	int numberOfSimulation;
	// Container for uniformly distributed pseudo-random numbers in (0, 1)
	vector<double> uniformNumber;
	// Container for standard normally distributed random numbers
	vector<double> valuesNormalNumber;

public:

	// Constructor to set the total number of simulations/samples
	MonteCarloGenerator(int numberOfSimulation) : numberOfSimulation(numberOfSimulation) {}

	// Generates uniformly distributed random numbers using the Mersenne Twister engine
	vector<double> generteNumberWithMersenneTwister();

	// Transforms uniform numbers into standard normal numbers using Moro's algorithm
	vector<double> generatenormalNumber();

	// Getter to retrieve the vector of generated uniform numbers
	vector<double> getUniformValue() {
		return uniformNumber;
	}

	// Getter to retrieve the vector of generated standard normal numbers
	vector<double> getValuesNormalNumber() {
		return valuesNormalNumber;
	}

	// Getter to retrieve the configured number of simulations
	double getNumberOfSimulation() {
		return numberOfSimulation;
	}

};
