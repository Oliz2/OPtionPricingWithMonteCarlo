#include <iostream>
#include "MonteCarloGenerator.h"
#include "BlackandScholes.h"
#include "Model.h"
#include "EuropeaOption.h"
#include "MonteCarloPricer.h"
#include "BarrierOption.h"


using namespace std;


int main()
{

	//1/n sommatoria ( x - media ) ^ 2

	// Financial and simulation input parameters
	double InitialValue = 100;
	double strike = 100;
	double numberOfTimeStep = 0.01;
	double maturity = 3;
	double volatility = 0.2;
	double riskFreerate = 0.05;
	int numberOfSimulation = 100000;
	double numberOftimesStep = 0.01;
	// Compute the total number of discrete time steps for the simulation
	int numberOfTimes = static_cast<int>(maturity / numberOfTimeStep);
	double upperBarrier = 150;
	double lowerBarrier = 80;

	// Initialize the Black-Scholes asset price model
	BlackandScholes blackandScholes(InitialValue, strike, numberOfTimeStep, maturity, volatility,
		riskFreerate, numberOfSimulation);

	// Generate the matrix containing all simulated price trajectories
	vector<vector<double>> values = blackandScholes.generateValue();

	// Define the vanilla payoff functions using lambda expressions
	function<double(double)> payoffFunctionPut = [strike](double InitialValue) {
		return (strike > InitialValue) ? strike - InitialValue : 0;
		};

	function<double(double)> payoffFunctionCall = [strike](double InitialValue) {
		return (InitialValue > strike) ? InitialValue - strike : 0;
		};

	// Instantiate the European and Double Knock-Out Barrier option products
	EuropeaOption OptionPut(maturity, riskFreerate, payoffFunctionPut);
	BarrierOption barrierOptionPut(maturity, riskFreerate, payoffFunctionPut, lowerBarrier, upperBarrier);

	EuropeaOption OptionCall(maturity, riskFreerate, payoffFunctionCall);
	BarrierOption barrierOptionCall(maturity, riskFreerate, payoffFunctionCall, lowerBarrier, upperBarrier);


	// Initialize the Monte Carlo pricing engine
	MonteCarloPricer monteCarloPricer;

	// Compute the discounted expected value for each option contract
	double pricerEuropeanPut = monteCarloPricer.getValue(&OptionPut, &blackandScholes);
	double pricerBarrierPut = monteCarloPricer.getValue(&barrierOptionPut, &blackandScholes);

	double pricerEuropeanCall = monteCarloPricer.getValue(&OptionCall, &blackandScholes);
	double pricerBarrierCall = monteCarloPricer.getValue(&barrierOptionCall, &blackandScholes);

	// Display the final option prices in the console
	cout << "The value of an European Put is: " << pricerEuropeanPut << endl;
	cout << "The value of an barrier Put is: " << pricerBarrierPut << endl;

	cout << "--------------------------------" << endl;

	cout << "The value of an European Call is: " << pricerEuropeanCall << endl;
	cout << "The value of an barrier Call is: " << pricerBarrierCall << endl;

}
