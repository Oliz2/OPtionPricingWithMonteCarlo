#include "MonteCarloPricer.h"

// Computes the option price using the Monte Carlo method by averaging simulated payoffs
double MonteCarloPricer::getValue(IOption* option, Model* model) {

	// Generate all simulated asset price paths from the model
	vector<vector<double>> path = model->generateValue();
	double sommaPayoff = 0;

	// Loop through each path to calculate and aggregate the option's payoff
	for (int i = 0; i < path.size(); i++) {
		sommaPayoff += option->getPayoff(path[i]);
	}

	// Calculate the expected value (sample mean) of the payoffs
	sommaPayoff /= path.size();

	return sommaPayoff;
}
