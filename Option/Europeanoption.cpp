#include "EuropeaOption.h"

// Computes the standard discounted payoff for a European option at maturity
double EuropeaOption::getPayoff(const vector<double>& path) const {

	// Get the terminal asset price at maturity (the last element of the path)
	double finalValue = path[path.size() - 1];

	// Evaluate the payoff function and apply the risk-free discount factor
	return payoffFunction(finalValue) * exp(-riskFreeRate * maturity);

}
