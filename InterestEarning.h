#pragma once

// Interface to be implemented by Savings Account
class InterestEarning
{
public:
	// Virtual function to be implemented by derived classes
	virtual double computeInterest(int timeProjectedYears) const = 0;
};