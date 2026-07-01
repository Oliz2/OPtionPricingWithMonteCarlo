#include "BlackandScholes.h"
#include "MonteCarloGenerator.h"

// Generates the asset price paths matrix using the Black-Scholes model
const vector<vector<double>>& BlackandScholes::generateValue() {

    // Initialize the generator with the total number of random numbers needed (Simulations * Time Steps)
    MonteCarloGenerator monteCarloGenerator(numberOfSimulation * numberOfTimes);

    // Clear previous data and pre-allocate memory for performance optimization
    valuesBlackandScholes.clear();
    valuesBlackandScholes.reserve(numberOfTimes * numberOfSimulation);

    // Generate the flat vector containing all the standard normal random numbers
    vector<double> browninanmotion = monteCarloGenerator.generatenormalNumber();

    // Main loop: iterate through each independent path simulation
    for (int simulation = 0; simulation < numberOfSimulation; simulation++) {

        // Initialize the price at the start of the path with the initial spot price (S_0)
        double currentPrice = Initialvalue;
        // Vector to store the temporal evolution of the price for the current path
        vector<double> currentPath;

        // Secondary loop: evolve the asset price through each discrete time step
        for (int time = 0; time < numberOfTimes; time++) {

            // Extract the random shock Z corresponding to the current simulation and time index
            double z = browninanmotion[simulation * numberOfTimes + time];

            // Discretized Black-Scholes formula using Geometric Brownian Motion (SDE solution)
            double BlackAndScholesValue = currentPrice * exp((riskFreeRate - 0.5 * volatility * volatility) * numberOfTimeStep
                + volatility * sqrt(numberOfTimeStep) * z);

            // Update the current asset price to the newly calculated value
            currentPrice = BlackAndScholesValue;

            // Store the updated price into the current path vector
            currentPath.push_back(currentPrice);
        }

        // Save the complete path trajectory into the global matrix structure
        valuesBlackandScholes.push_back(currentPath);

    }

    // Return the reference to the generated price paths matrix
    return valuesBlackandScholes;
}