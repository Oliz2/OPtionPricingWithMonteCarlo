#include "MonteCarloGenerator.h"

// Coefficients for Moro's approximation (central region: 0.08 < u < 0.92)
static double a_0 = 2.50662823884;
static double a_1 = -18.61500062529;
static double a_2 = 41.39119773534;
static double a_3 = -25.44106049637;
static double b_0 = -8.47351093090;
static double b_1 = 23.08336743743;
static double b_2 = -21.06224101826;
static double b_3 = 3.13082909833;

// Coefficients for Moro's approximation (tail regions: u <= 0.08 or u >= 0.92)
static double c_0 = 0.3374754822726147;
static double c_1 = 0.9761690190917186;
static double c_2 = 0.1607979714918209;
static double c_3 = 0.0276438810333863;
static double c_4 = 0.0038405729373609;
static double c_5 = 0.0003951896511919;
static double c_6 = 0.0000321767881768;
static double c_7 = 0.0000002888167364;
static double c_8 = 0.00000003960315187;

// Generates pseudo-random uniform numbers in the open interval (0, 1) using Mersenne Twister
vector<double> MonteCarloGenerator::generteNumberWithMersenneTwister() {

	// Clear previous data and pre-allocate memory for performance
	uniformNumber.clear();
	uniformNumber.reserve(numberOfSimulation);

	// Initialize the random device and seed the Mersenne Twister engine
	random_device rd;
	mt19937 casualNumber(rd());

	// Loop to generate uniformly distributed random numbers
	for (int simulation = 0; simulation < numberOfSimulation; simulation++) {
		// Map the 32-bit integer output to a double in (0, 1) to avoid 0 and 1 boundaries
		double values = (static_cast<double>(casualNumber()) + 0.5) / (static_cast<double>(casualNumber.max()) + 1);
		uniformNumber.push_back(values);

	}

	return uniformNumber;

}


// Moro's Algorithm for Inverse Transform Method to generate standard normal random variables
vector<double> MonteCarloGenerator::generatenormalNumber() {

	// Ensure uniform random numbers are available before transforming them
	if (uniformNumber.empty()) {
		generteNumberWithMersenneTwister();
	}

	// Clear previous data and pre-allocate memory
	valuesNormalNumber.clear();
	valuesNormalNumber.reserve(numberOfSimulation);

	double normalNumber = 0;
	// Loop through each uniform random number to transform it into a normal distribution
	for (int simulation = 0; simulation < numberOfSimulation; simulation++) {

		double u = uniformNumber[simulation];

		// Central region approximation
		if (u < 0.92 && u > 0.08) {

			double y = u - 0.5;
			double  x = y * y;
			// Polynomial evaluation for the numerator and denominator
			double numerator = a_0 + a_1 * x + a_2 * pow(x, 2) + a_3 * pow(x, 3);
			double denominator = 1 + b_0 * x + b_1 * pow(x, 2) + b_2 * pow(x, 3) + b_3 * pow(x, 4);

			// Compute the standard normal variable for the central region
			normalNumber = y * (numerator / denominator);

		}
		// Tail regions approximation
		else if (u < 0.08 || u > 0.92) {

			// Left tail transformation
			if (u <= 0.5) {


				double p = log(-log(u));

				// Chebyshev polynomial expansion for the left tail (negative values)
				normalNumber = -(c_0 + c_1 * p + c_2 * pow(p, 2) + c_3 * pow(p, 3)
					+ c_4 * pow(p, 4) + c_5 * pow(p, 5) + c_6 * pow(p, 6) + c_7 * pow(p, 7) + c_8 * pow(p, 8));
			}
			// Right tail transformation
			else {

				double p = log(-log(1 - u));
				// Chebyshev polynomial expansion for the right tail (positive values)
				normalNumber = c_0 + c_1 * p + c_2 * pow(p, 2) + c_3 * pow(p, 3)
					+ c_4 * pow(p, 4) + c_5 * pow(p, 5) + c_6 * pow(p, 6) + c_7 * pow(p, 7) + c_8 * pow(p, 8);
			}

		}

		// Store the final calculated standard normal number
		valuesNormalNumber.push_back(normalNumber);

	}

	return valuesNormalNumber;
}
