#define _CRT_SECURE_NO_WARNINGS
#include "Transaction.h"
#include <algorithm>
#include <string>
#include <iostream>

// Default constructor when working with templates and such types
Transaction::Transaction() : desc_("None."), timestamp_(time(nullptr)), value_(Money(0,0)), type_(transactionType::null) {}

// timestamp is current date/time based on current system
Transaction::Transaction(const Money amount, const transactionType type, std::string reason)
    : desc_(std::move(reason)), timestamp_(time(nullptr)), value_(amount), type_(type){}

std::string Transaction::toString() const {
    // convert timestamp to string form
    const std::string stringTimestamp = ctime(&timestamp_);

    return isWithdrawal() ?
        "-- " + getDesc() + ": -\x9C" + getValue().toString() + " on " + stringTimestamp :
		"-- " + getDesc() + ": \x9C" + getValue().toString() + " on " + stringTimestamp;
}

std::ostream& operator<<(std::ostream& os, const Transaction& transaction){
    os << transaction.toString();
    return os;
}

Money Transaction::getValue() const {
    return value_;
}

std::string Transaction::getDesc() const {
    return desc_;
}

time_t Transaction::getTimestamp() const {
    return timestamp_;
}

bool Transaction::isWithdrawal() const {
    return type_ == transactionType::withdraw;
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
