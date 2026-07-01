# Option Pricing Engine (C++)

A lightweight C++ application built to price financial derivatives using Monte Carlo simulations.

## What it does
* **Option Pricing**: Computes the fair value of vanilla European options and path-dependent Double Knock-Out barrier options.
* **Stochastic Simulation**: Simulates asset price trajectories under standard Black-Scholes market dynamics.
* **High-Precision Math**: Utilizes Moro's High-Precision Inverse CDF algorithm to generate accurate standard normal random variables via a Mersenne Twister engine.

## Project Architecture
* **Model**: Generates asset paths (`Model`, `BlackandScholes`).
* **Option**: Defines contract payoffs (`IOption`, `EuropeaOption`, `BarrierOption`).
* **Pricing Engine**: Runs the Monte Carlo loop and computes expected discounted payoffs (`MonteCarloGenerator`, `MonteCarloPricer`).
