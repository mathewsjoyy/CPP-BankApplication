#pragma once

// Interface to be implemented by Savings Account
class InterestEarning
{
public:
	virtual ~InterestEarning() = default;
	
	virtual double computeInterest(int timeProjectedYears) const = 0;
};