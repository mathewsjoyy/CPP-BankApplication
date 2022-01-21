#pragma once

#include <memory>
#include "Money.h"
#include "Transaction.h"
#include "RedBlackSearchTree.h"

// Abstract class (not to be implemented)
class Account {
protected: // Protected members so derived classes can have direct access
    std::unique_ptr<Money> balance;
    RedBlackSearchTree<Transaction> history; // Red Black tree to store all account transactions
    std::string name;

public:
    // Overloaded constructors
    explicit Account(const std::string& name, long openingPounds, int openingPence);
    explicit Account(const std::string& name, long openingPounds);
    explicit Account(const std::string& name);

    // Virtual destructor, allowing derived classes destructor to be called if defined
    virtual ~Account();

    // Pure virtual function that must be overriden in derived classes
    virtual void deposit(long pounds, int pence = 0, std::string reason = "Deposit") = 0;

    // Withdraw is bool so we can see if the action was successful (true) or a fail (false)
    virtual bool withdraw(long pounds, int pence = 0, std::string reason = "Withdrawal") = 0;

    // toString method to print out the key account details
    virtual std::string toString() const = 0;

    // Friend function for overloading << operator
    const friend std::ostream& operator<<(std::ostream& os, const Account& account);

    // Search function allowing searching history for transactions of a specific value
    void searchTransactionsByAmount(Money searchVal) const;

    // Getters
    void getHistory() const;
    std::string getName() const;
    Money getBalance() const;
};
