#pragma once
#include "IOption.h"
#include <functional>

using namespace std;

// Contract specification for a standard European option
class EuropeaOption : public IOption
{
private:

    // Contract parameters and the underlying payoff logic
    double maturity;
    double riskFreeRate;
    function<double(double)> payoffFunction;

public:

    // Constructor to initialize the option maturity, risk-free rate, and payoff lambda
    EuropeaOption(double maturity, double riskFreeRate, function<double(double)> payoffFunction)
        : maturity(maturity), riskFreeRate(riskFreeRate), payoffFunction(payoffFunction) {
    }

    // Overrides the base method to evaluate the vanilla payoff at maturity
    double getPayoff(const vector<double>& path) const override;

    // Getter to retrieve the option's time to maturity
    double getMaturity() const override { return maturity; }

};
