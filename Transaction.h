#pragma once
#include <ctime>
#include "Money.h"

class Transaction
{
public:
    // Enum for transaction types used to identify if a transaction is withdrawal/deposit.
    // Once application grows more types can be added
    enum class transactionType { null, deposit, withdraw };

private:
    std::string desc;
    time_t timestamp;
    Money value;
    transactionType type;

public:
    // Default constructor when working with templates etc.
    Transaction();
    Transaction(Money amount, transactionType type, std::string reason = "None.");

    // Comparison operator overloading
    bool operator>(const Transaction& tRhs) const;
    bool operator<(const Transaction& tRhs) const;
    bool operator==(const Transaction& tRhs) const;
    bool operator!=(const Transaction& tRhs) const;

    // toString that display key transaction details, description, timestamp, amount
    std::string toString() const;

    // Allow transaction call to be printed to console by calling toString function
    friend std::ostream& operator<<(std::ostream& os, const Transaction& transaction);

    // Getters
    Money getValue() const;
    std::string getDesc() const;
    time_t getTimestamp() const;
    bool isWithdrawal() const;
};