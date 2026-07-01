#pragma once
#include <vector>
#include <iostream>
#include "Model.h"

using namespace std;

// Model implementation for asset price path generation using Black-Scholes dynamics
class BlackandScholes : public Model
{

private:

	// Parameters for the asset, contract specification, and grid discretisation
	double Initialvalue;
	double strike;
	int numberOfTimes;
	double numberOfTimeStep;
	double maturity;
	double volatility;
	double riskFreeRate;
	int numberOfSimulation;

	// Matrix to store the simulated asset price paths (Simulations x Time Steps)
	vector<vector<double>> valuesBlackandScholes;


public:

	// Constructor to initialize the Black-Scholes model parameters and calculate total time steps
	BlackandScholes(double Initialvalue, double strike, double numberOfTimeStep, double maturity,
		double volatility, double riskFreeRate, int numberOfSimulation) : Initialvalue(Initialvalue), numberOfTimeStep(numberOfTimeStep), strike(strike),
		numberOfTimes(static_cast<int>(maturity / numberOfTimeStep)), maturity(maturity), volatility(volatility), riskFreeRate(riskFreeRate),
		numberOfSimulation(numberOfSimulation) {
	}

	// Overrides the base method to generate and return the matrix of simulated price paths
	const vector<vector<double>>& generateValue() override;

};
