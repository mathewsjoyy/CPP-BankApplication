#include "AccountManager.h"
#include "IncorrectArgumentValue.h"
#include "Current.h"
#include "Savings.h"
#include <string>
#include <algorithm>
#include <utility>

AccountManager::AccountManager() = default;

void AccountManager::openAccount(const std::string& accountType, std::string accountBalance) {

	// To store temporary money values for commands
	long pounds{};
	int pence{};

	const std::pair<bool, bool> canMakeCurrentIsa = doesCurrentISAExist(opened_accounts_);  // Check if user already has current/ISA

	// Check opening balance doesn't exceeds the total the bank can store and money values can be found
	if (canComputeMoneyInput(pounds, pence, std::move(accountBalance)) == false || pounds >= MAX_MONEY_HOLDING) {
		std::cout << ">- Unrecognizable opening balance value.\n>- Ensure a valid money value is entered";
		std::cout << ", and amount entered doesn't exceed banks total acceptable holding amount" << std::endl;
	}
	else {
		if (pounds < 0 || pence < 0) {
			std::cout << ">- Unable to open an account with negative opening balance." << std::endl;
		}
		else if (accountType.compare("2") == 0) { // create a standard savings
			opened_accounts_.push_back(std::make_unique<Savings>(pounds, pence));
			recent_account_index_ = opened_accounts_.size() - 1; // set the most recently opened account
		}
		else if (accountType.compare("1") == 0) { // Create a current account
			if (canMakeCurrentIsa.first == false) {
				opened_accounts_.push_back(std::make_unique<Current>(pounds, pence));
				recent_account_index_ = opened_accounts_.size() - 1;
			}
			else {
				std::cout << ">- Sorry you already have an existing Current account. Use 'view' command to see accounts" << std::endl;
			}
		}
		else if (accountType.compare("3") == 0) { // Create a ISA
			if (canMakeCurrentIsa.second == false) {
				if (pounds < 1000) {
					std::cout << ">- ISA initial balance must be >= \x9C 1000." << std::endl;
				}
				else {
					opened_accounts_.push_back(std::make_unique<Savings>(pounds, pence, true));
					recent_account_index_ = opened_accounts_.size() - 1;
				}
			}
			else {
				std::cout << ">- Sorry you already have an existing ISA account. Use 'view' command to view accounts." << std::endl;
			}
		}
		else {
			std::cout << ">- Error: Invalid account type" << std::endl;
		}
	}
}

void AccountManager::viewAllAccounts() const {
	if (opened_accounts_.empty()) { // Check if any account have been opened
		std::cout << ">- You need to open some accounts before you can view them.";
	}
	else { // No index is given, then display all accounts.
		for (const auto& account : opened_accounts_) {
			std::cout << *account;
			account->getHistory();
		}
	}
}

void AccountManager::viewAccountsIndex(const std::string& index) {
	if (opened_accounts_.empty()) { // Check if any account have been opened
		std::cout << ">- You need to open some accounts before you can view them.";
	}
	else { // Index is given
		try {
			const int intIndex = std::stoi(index) - 1;

			std::cout << *opened_accounts_.at(intIndex);
			opened_accounts_.at(intIndex)->getHistory();

			recent_account_index_ = intIndex; // Update recent account index
		}
		catch (std::exception&) {
			std::cout << ">- Cannot view account: Invalid Index.";
		}
	}
}

void AccountManager::withdraw(std::string amount) const {

	// To store temporary money values for commands
	long pounds{};
	int pence{};

	if (opened_accounts_.empty()) {
		std::cout << ">- You need to open some accounts before you can withdraw money.";
	}

	if (canComputeMoneyInput(pounds, pence, std::move(amount)) == false) {
		std::cout << ">- Unrecognizable withdrawal amount value." << std::endl;
	}
	else if (pounds < 0 || pence < 0) {
		std::cout << ">- Unable to withdraw a negative amount, consider the 'deposit' command." << std::endl;
	}
	else {
		opened_accounts_.at(recent_account_index_)->withdraw(pounds, pence); // Withdraw from account
	}
}

void AccountManager::deposit(std::string amount) const {

	// To store temporary money values for commands
	long pounds{};
	int pence{};

	if (opened_accounts_.empty()) {
		std::cout << ">- You need to open some accounts before you can deposit money.";
	}

	if (canComputeMoneyInput(pounds, pence, std::move(amount)) == false) {
		std::cout << ">- Unrecognizable deposit amount value." << std::endl;
	}
	else if (pounds < 0 || pence < 0) {
		std::cout << ">- Unable to deposit a negative amount, consider the 'withdraw' command." << std::endl;
	}
	else {
		opened_accounts_.at(recent_account_index_)->deposit(pounds, pence); // Deposit into the account
	}
}

void AccountManager::transfer(const std::string& takeMoneyAcc, const std::string& giveMoneyAcc, std::string amount) const {

	int accountReceiving, accountGiving;
	// To store temporary money values for commands
	long pounds{};
	int pence{};

	try {
		accountReceiving = std::stoi(giveMoneyAcc) - 1;
		accountGiving = std::stoi(takeMoneyAcc) - 1;

		const int openedAccountsSize = static_cast<int>(opened_accounts_.size()) - 1;

		if (accountGiving < 0 || accountGiving > openedAccountsSize || accountReceiving < 0 || accountReceiving > openedAccountsSize) {
			throw IncorrectArgumentValue(">- Account(s) with given index does not exist.");
		}
	}
	catch (const IncorrectArgumentValue& e) {
		std::cout << ">- " << e.what() << std::endl; return;
	}
	catch (const std::exception&) {
		std::cout << ">- " << ">- Invalid arguments, try again later." << std::endl; return;
	}

	if (canComputeMoneyInput(pounds, pence, std::move(amount)) == false) {
		std::cout << ">- Unrecognizable amount value." << std::endl;
	}
	else if (pounds < 0 || pence < 0) {
		std::cout << ">- Unable to deposit a negative amount, consider the 'withdraw' command." << std::endl;
	}
	else {
		const std::string withdrawMessage = "(Withdrawal) Transfer to account " + std::to_string(accountReceiving);
		const std::string depositMessage = "(Deposit) Transfer from account " + std::to_string(accountGiving);

		// Check withdrawal / deposit is successful
		if (opened_accounts_.at(accountGiving)->withdraw(pounds, pence, withdrawMessage) &&
			opened_accounts_.at(accountReceiving)->deposit(pounds, pence, depositMessage)) {
			std::cout << ">- All processes successful. Transfer complete." << std::endl;
		}
		else { // Unsuccessful withdrawal/deposit, then no transactions are made
			std::cout << ">- 1 (or more) processes failed. No transactions made. Try again later." << std::endl;
		}
	}
}

void AccountManager::project(const std::string& years) const {

	if (opened_accounts_.empty()) {
		std::cout << ">- You need to open some accounts before you can project.\n";
	}
	else
	{
		try {
			const int intYears = std::stoi(years);

			// Check the most recently viewed account is off type savings, else catch exception thrown
			const Savings& chosenSavingsAcc = dynamic_cast<Savings&>(*opened_accounts_.at(recent_account_index_));

			// Call compute interest function to find projected value on the account
			std::cout << "Projected Balance: \x9C" << chosenSavingsAcc.computeInterest(intYears) << std::endl;
		}
		catch (const std::exception&) {
			std::cout << ">- Make sure you have given a valid input for years and * are viewing a Savings/ISA account. *\n";
		}
	}
}

void AccountManager::search(std::string value) const {
	if (opened_accounts_.empty()) {
		std::cout << ">- You need to open some accounts before you can search for transactions.";
	}

	long pounds{};
	int pence{};

	if (canComputeMoneyInput(pounds, pence, std::move(value)) == false) {  // Check money values can be found
		std::cout << ">- Unrecognizable search value." << std::endl;
	}
	else {
		opened_accounts_.at(recent_account_index_)->searchTransactionsByAmount(Money(pounds, pence));
	}
}


bool AccountManager::canComputeMoneyInput(long& poundsOut, int& penceOut, std::string input) const {

	try {
		if (input.find('.') != std::string::npos) { // Found a decimal point (so there is pence as well)
			poundsOut = std::stol(input.substr(0, input.find('.')));
			input.erase(0, input.find('.') + 1);

			// Check for pence to see if user entered e.g 1.1 if so change to 1.10
			if ((input.substr(0, input.length()).length()) == 1) {
				penceOut = std::stoi(input.substr(0, input.length()) + "0");
			}
			else {
				penceOut = std::stoi(input.substr(0, input.length()));
			}
		}
		else {
			poundsOut = std::stoi(input);
			penceOut = 0;
		}

		// Use formula to find if pence is longer then 2 digits if so its invalid
		if ((penceOut > 0 ? static_cast<int>(log10(static_cast<double>(penceOut))) + 1 : 1) > 2) {
			return false;
		}
		return true;
	}
	catch (const std::exception&) {
		return false;
	}
}

std::pair<bool, bool> AccountManager::doesCurrentISAExist(const std::vector<std::unique_ptr<Account>>& openedAccounts) {

	// Lambda that gets count of all current accounts from openedAccounts vector
	const int64_t currentTotal = std::count_if(openedAccounts.begin(), openedAccounts.end(),
		[](const std::unique_ptr<Account>& ptr) { return ptr->getName() == "Current"; });

	// Lambda that gets count of all ISA accounts from openedAccounts vector
	const int64_t isaTotal = std::count_if(openedAccounts.begin(), openedAccounts.end(),
		[](const std::unique_ptr<Account>& ptr) { return ptr->getName() == "ISA"; });

	// return bool pair to see if ISA and current accounts exist
	return { currentTotal > 0, isaTotal > 0 };
}
