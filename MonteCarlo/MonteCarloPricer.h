#pragma once
#include "Model.h"
#include "IOption.h"

// Pricing engine that implements the Monte Carlo evaluation method
class MonteCarloPricer
{

private:

	// Internal state variables for the calculated price, contract, and underlying model
	double priceValue;
	IOption* option;
	Model* model;


public:

	// Default constructor
	MonteCarloPricer() {}

	// Computes the option price by connecting the target contract and the market simulation model
	double getValue(IOption* option, Model* model);

};
