#pragma once
#include "Account.h"
#include "Money.h"

class Current final : public Account
{
private:
    // Money object to store available overdraft for current account
    Money overdraft_;

public:
    explicit Current(long openingPounds = 0, int openingPence = 0);

    // Override functions of base class 
    bool withdraw(long pounds, int pence = 0, std::string reason = "Withdrawal") override;
    bool deposit(long pounds, int pence = 0, std::string reason = "Deposit") override;
    std::string toString() const override;

    // Getters
    Money getOverdraft() const;
};