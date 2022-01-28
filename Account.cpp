#include "Account.h"

Account::Account(const std::string& name, long openingPounds, int openingPence)
    : balance(std::make_unique<Money>(openingPounds, openingPence)), name(name) {

    // Add initial deposit to transaction history
    history.insert(std::make_unique<Transaction>(getBalance(),
        Transaction::transactionType::deposit, "Initial Deposit"));

    std::cout << ">- " << name << " Account has been opened with \x9C" << getBalance() << "\n";
}

Account::Account(const std::string& name, const long openingPounds) : Account(name, openingPounds, 0) {}

Account::Account(const std::string& name) : Account(name, 0, 0) {}

Account::~Account() {
    std::cout << getName() << " Account has been closed." << std::endl;
}

void Account::searchTransactionsByAmount(const Money searchVal) const {

    std::cout << ">- Search value (" << searchVal.toString() << ") Results:\n";
    try {
        // Call search function of red-black tree
        history.searchTree(Transaction(searchVal, Transaction::transactionType::null))->printData();
    }
    catch (const std::exception&) {
        std::cout << ">- Invalid search term, try again later.\n";
    }
}

void Account::printHistory() const {
    // Call getAllNodesInOrder function from RBTransactionTree, that prints out all tree node data.
    history.printAllNodesInOrder();
}

const std::ostream& operator<<(std::ostream& os, const Account& account) {
    os << account.toString();
    return os;
}

std::string Account::getName() const {
    return name;
}

Money Account::getBalance() const {
    return *balance;
}
