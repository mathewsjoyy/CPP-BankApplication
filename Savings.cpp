#include "Savings.h"
#include <cmath>

Savings::Savings(const long openingPounds, const int openingPence, const bool isISA)
    : Account(isISA ? "ISA" : "Savings", openingPounds, openingPence), interestRate(0.85), isa(isISA) {
    if (isa) { // if account to be created is an ISA then set interestRate to 1.15 %
        interestRate = 1.15;
    }
}

double Savings::computeInterest(const int timeProjectedYears) const {
    constexpr double compoundRate = 12.00;

    // Equation to compute compound interest
    return std::stod(getBalance().toString()) * pow(1 + getInterestRate() / 100 / compoundRate,
        timeProjectedYears * compoundRate);
}

// Decrease account balance / overdraft if possible and update transaction history
bool Savings::withdraw(const long pounds, const int pence, std::string reason) {
    const Money withdrawAmount(pounds, pence);
    const Money remainingAmount = *this->balance - withdrawAmount;

    // Check if we have enough money to withdraw
    if (remainingAmount.getPounds() >= 0 && remainingAmount.getPence() >= 0) {
        balance = std::make_unique<Money>(*this->balance - withdrawAmount);
        history.insert(std::make_unique<Transaction>(withdrawAmount, Transaction::transactionType::withdraw, reason));

        std::cout << ">- Withdrawal to " << getName() << " successful." << std::endl;
        return true;
    }

    std::cout << ">- Withdrawal to " << getName() << " unsuccessful. Not enough funds in your account." << std::endl;
    return false;
}

// Increase account balance and update transaction history
bool Savings::deposit(const long pounds, const int pence, std::string reason) {
    const Money depositAmount(pounds, pence);

    // Check if too much money has been deposited into savings for the bank to hold
    if (fabs(std::stod((*balance + depositAmount).toString())) > MAX_MONEY_HOLDING) {
        std::cout << ">- Deposit to " << getName() << " failed. The bank cannot store such a large amount." << std::endl;
        return false;
    }

    // Update the balance and insert new deposit transaction
    balance = std::make_unique<Money>(*this->balance + depositAmount);
    history.insert(std::make_unique<Transaction>(depositAmount, Transaction::transactionType::deposit, reason));

    std::cout << ">- Deposit to " << getName() << " successful." << std::endl;
    return true;
}

std::string Savings::toString() const {

    std::string accountInfo = getName() + " account | Balance \x9C" + getBalance().toString() + "\n";
    return accountInfo;
}

double Savings::getInterestRate() const {
    return interestRate;
}

bool Savings::getIsa() const {
    return isa;
}