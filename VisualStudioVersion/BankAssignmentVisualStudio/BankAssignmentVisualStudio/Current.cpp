#include "Current.h"

// Constructor calls base class constructor to assign values to inherited members
Current::Current(const long openingPounds, const int openingPence)
    : Account("Current", openingPounds, openingPence), overdraft(500) {
    std::cout << ">- Current account comes with a \x9C" << getOverdraft() << " overdraft." << std::endl;
}

// Increase account balance and update transaction history
void Current::deposit(const long pounds, const int pence, const std::string reason) {

	const Money depositAmount(pounds, pence);
    balance = std::make_unique<Money>(*balance + depositAmount);

    history.insert(std::make_unique<Transaction>(depositAmount,Transaction::transactionType::deposit ,reason));

    std::cout << ">- Deposit to " << getName() << " account successful." << std::endl;
}

bool Current::withdraw(const long pounds, const int pence, std::string reason) {

	const Money withdrawAmount(pounds, pence);
	const Money remainingBalanceAmount = *balance - withdrawAmount;
    const Money remainingAfterOverdraft = *balance + overdraft - withdrawAmount;

    // Check we have enough money in main balance (not including overdraft)
    if (remainingBalanceAmount.getPounds() >= 0 && remainingBalanceAmount.getPence() >= 0) {
        balance = std::make_unique<Money>(*balance - withdrawAmount);

        history.insert(std::make_unique<Transaction>(withdrawAmount,Transaction::transactionType::withdraw, reason));
        std::cout << ">- Withdrawal to " << getName() << " successful." << std::endl;
        return true;
    }

    // Check we have enough overdraft
    if (remainingAfterOverdraft.getPounds() >= 0 && remainingAfterOverdraft.getPence() >= 0) {
        // Update new overdraft amount and balance
        overdraft = overdraft + (remainingAfterOverdraft - overdraft); 
        balance = std::make_unique<Money>(overdraft - remainingAfterOverdraft);

        history.insert(std::make_unique<Transaction>(withdrawAmount,Transaction::transactionType::withdraw, reason));

        std::cout << ">- Withdrawal to " << getName() << " successful. (Gone into overdraft)" << "\n";
        std::cout << ">- Remaining Overdraft: \x9C" << getOverdraft() << ", Account Balance: \x9C" << getBalance() << "\n";
        return true;
    }

	// Not enough money
	std::cout << ">- Withdrawal to " << getName() << " unsuccessful. No available funds in your current account." << std::endl;
	return false;
}

std::string Current::toString() const {

	std::string accountInfo = "|[ " + getName() + " account | Overdraft \x9C"
							+ getOverdraft().toString() +" | Balance \x9C" + getBalance().toString() + " ]|" + "\n";
	return accountInfo;
}

Money Current::getOverdraft() const{

    return overdraft;
}