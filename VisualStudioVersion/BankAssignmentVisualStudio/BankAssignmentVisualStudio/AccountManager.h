#pragma once

#include "Account.h"
#include "IncorrectAmountOfArguments.h"

class AccountManager
{
private:
	// Index of the most recently viewed account set when opening an account and viewing an account
	size_t recent_account_index_{};

	// Vector collection of pointers to all opened accounts
	std::vector<std::unique_ptr<Account>> opened_accounts_;

public:
	AccountManager();

	// Opens a new bank account depending on type
	void openAccount(const std::string& accountType, std::string accountBalance);

	// Display all opened accounts information
	void viewAllAccounts() const;

	// Display an accounts info by their index
	void viewAccountsIndex(const std::string& index);

	// Withdraw to most recent account index
	void withdraw(std::string amount) const;

	// Deposit to most recent account index
	void deposit(std::string amount) const;

	// Transfer money between 2 accounts, by calling withdraw and deposit functions
	void transfer(const std::string& takeMoneyAcc, const std::string& giveMoneyAcc, std::string amount) const;

	// Project an account X years into the future
	void project(const std::string& years) const;

	// Search an account
	void search(std::string value) const;

	// Function that takes 2 reference variable and a input amount, and checks if the input can be a
	// valid money amount, and assigns the valid pound and pence amount by reference to the first 2 params
	bool canComputeMoneyInput(long& poundsOut, int& penceOut, std::string input) const;

	// Find if user has opened current or ISA account already
	static std::pair<bool, bool> doesCurrentISAExist(const std::vector<std::unique_ptr<Account>>& openedAccounts);

};

