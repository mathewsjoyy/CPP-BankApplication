#pragma once

#include "Account.h"
#include "InterestEarning.h"

class Savings final : public Account, public InterestEarning
{
private:
    double interestRate;
    bool isa;

public:
    // Savings constructor, isISA is set to false as we want to create standard savings
    // class by default
    explicit Savings(long openingPounds = 0, int openingPence = 0, bool isISA = false);

    // Override function from interface (InterestEarning)
    double computeInterest(int timeProjectedYears) const override;

    // Override functions from base class for Savings specific functionality 
    bool withdraw(long pounds, int pence = 0,std::string reason = "Withdrawal") override;
    void deposit(long pounds, int pence = 0, std::string reason = "Deposit") override;
    std::string toString() const override;

    // Getters
    double getInterestRate() const;
    bool getIsa() const;
};