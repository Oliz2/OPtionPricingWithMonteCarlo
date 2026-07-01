#pragma once 
#include <functional>
#include <vector>
#include "IOption.h"

using namespace std;

// Contract specification for a Double Knock-Out Barrier option
class BarrierOption : public IOption
{

private:

	// Contract parameters, boundaries, and the underlying payoff logic
	double maturity;
	double riskFreeRate;
	double lowerBarrier;
	double upperBarrier;
	function<double(double)> payoffFunction;

public:

	// Constructor to initialize the option maturity, risk-free rate, payoff lambda, and barrier levels
	BarrierOption(double maturity, double riskFreeRate, function<double(double)> payoffFunction, double lowerBarrier, double upperBarrier)
		: maturity(maturity), riskFreeRate(riskFreeRate), payoffFunction(payoffFunction), lowerBarrier(lowerBarrier), upperBarrier(upperBarrier) {
	}

	// Overrides the base method to evaluate the path-dependent Double Knock-Out payoff
	double getPayoff(const vector<double>& path) const override;

	// Getter to retrieve the option's time to maturity
	double getMaturity() const override { return maturity; }

};
