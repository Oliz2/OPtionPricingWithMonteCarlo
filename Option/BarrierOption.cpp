#include "BarrierOption.h"

// Computes the payoff for a Double Knock-Out barrier option
double BarrierOption::getPayoff(const vector<double>& path) const {

	// Check if the asset price breached either barrier at any time step
	for (int time = 0; time < path.size(); time++) {
		if (path[time] >= upperBarrier || path[time] <= lowerBarrier) {
			return  0.0;
		}
	}

	// Calculate the discounted payoff at maturity if no barriers were breached
	double finalValue = path[path.size() - 1];
	return payoffFunction(finalValue) * exp(-riskFreeRate * maturity);

}
