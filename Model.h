#pragma once
#include <vector>
using namespace std;

// Base class defining the interface for all stochastic asset price models
class Model
{

public:

	// Virtual destructor ensuring proper cleanup of derived classes
	virtual ~Model() {}

	// Pure virtual function to generate and return simulated asset price paths
	virtual const vector<vector<double>>& generateValue() = 0;

};