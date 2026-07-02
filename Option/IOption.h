#pragma once
#include <vector>

using namespace std;

// Abstract interface defining the mandatory contract for all option products
class IOption
{

public:

	// Virtual destructor ensuring proper cleanup of derived option classes
	virtual ~IOption() {}

	// Pure virtual function to calculate the contract payoff given an asset price path
	virtual double getPayoff(const vector<double>& path) const = 0;

	// Pure virtual function to retrieve the option's expiration time
	virtual double getMaturity() const = 0;

};
