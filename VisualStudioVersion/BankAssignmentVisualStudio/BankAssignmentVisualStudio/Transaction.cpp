#define _CRT_SECURE_NO_WARNINGS
#include "Transaction.h"
#include <algorithm>
#include <string>
#include <iostream>

// Default constructor when working with templates and such types
Transaction::Transaction() : desc("None."), timestamp(time(nullptr)), value(Money(0,0)), type(transactionType::null) {}

// timestamp is current date/time based on current system
Transaction::Transaction(const Money amount, const transactionType type, std::string reason)
    : desc(std::move(reason)), timestamp(time(nullptr)), value(amount), type(type){}

std::string Transaction::toString() const {
    // convert timestamp to string form
    const std::string stringTimestamp = ctime(&timestamp);

    return isWithdrawal() ?
        "-- " + getDesc() + ": -\x9C" + getValue().toString() + " on " + stringTimestamp :
		"-- " + getDesc() + ": \x9C" + getValue().toString() + " on " + stringTimestamp;
}

std::ostream& operator<<(std::ostream& os, const Transaction& transaction){
    os << transaction.toString();
    return os;
}

Money Transaction::getValue() const {
    return value;
}

std::string Transaction::getDesc() const {
    return desc;
}

time_t Transaction::getTimestamp() const {
    return timestamp;
}

bool Transaction::isWithdrawal() const {
    return type == transactionType::withdraw;
}

bool Transaction::operator>(const Transaction& tRhs) const {
	return getValue() > tRhs.getValue();
}

bool Transaction::operator<(const Transaction& tRhs) const {
	return getValue() < tRhs.getValue();
}

bool Transaction::operator==(const Transaction& tRhs) const {
	return getValue() == tRhs.getValue();
}

bool Transaction::operator!=(const Transaction& tRhs) const {
	return getValue() != tRhs.getValue();
}
