#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>
#include <memory>
#include <string>
#include <Windows.h>

// Import headers needed in main
#include "IncorrectAmountOfArguments.h"
#include "AccountManager.h"
#include "Options.h"

int main(){

	std::vector <std::string> parameters;
	std::string userCommand;

	// Make a new account manager object for a new user
	AccountManager accounts = AccountManager();

	// Options object to display available options to user
	const Options options = Options();

	while (userCommand != "exit"){

		parameters.clear(); // Clear ready for next command
		std::cout << std::endl << ">>> ";

		std::getline(std::cin, userCommand);
		char* cstr = new char[userCommand.length() + 1];
		strcpy(cstr, userCommand.c_str());

		char* token;
		token = strtok(cstr, " ");

		while (token != nullptr){
			parameters.push_back(token);
			token = strtok(nullptr, " ");
		}

		try {
			if (parameters.empty()) {  // Check a user input isn't empty
				throw IncorrectAmountOfArguments(">- Make sure to enter a valid command!");
			}
			std::string command = parameters.at(0);

			if (command.compare("options") == 0) {   // Display the various commands to the user

				std::cout << "\n" << options;
			}
			else if (command.compare("open") == 0) {   // Allow a user to open an account

				if (parameters.size() < 3) {
					throw IncorrectAmountOfArguments(">- Make sure you have entered all valid parameters for this option.");
				}
				accounts.openAccount(parameters[1], parameters[2]);
			}
			else if (command.compare("view") == 0) {
				// Display an account according to an index (starting from 1)
				// alternatively, display all accounts if no index is provided
				if (parameters.size() < 2) { // No index is given, then display all accounts.
					accounts.viewAllAccounts();
				}
				else { // Index is given
					accounts.viewAccountsIndex(parameters[1]);
				}
			}
			else if (command.compare("withdraw") == 0) {   // allow user to withdraw funds from an account
				if (parameters.size() < 2 ) {
					throw IncorrectAmountOfArguments(">- Please make sure you enter a withdraw value");
				}

				accounts.withdraw(parameters[1]);
			}
			else if (command.compare("deposit") == 0) {   // allow user to deposit funds into an account
				if (parameters.size() < 2) {
					throw IncorrectAmountOfArguments(">- Please make sure you enter a deposit value");
				}

				accounts.deposit(parameters[1]);
			}
			else if (command.compare("transfer") == 0) {   // Allow user to transfer funds between accounts
				if (parameters.size() < 4) {
					throw IncorrectAmountOfArguments(">- Check you have the all input parameters.");
				}

				accounts.transfer(parameters[1], parameters[2], parameters[3]);
			}
			else if (command.compare("project") == 0) {  // Compute compound interest x years into the future
				if (parameters.size() < 2) {
					throw IncorrectAmountOfArguments(">- Check you have have the correct parameters.");
				}
				
				accounts.project(parameters[1]);
			}
			else if (command.compare("search") == 0) {   // Allow users to search their account history for a transaction

				if (parameters.size() < 2) {
					throw IncorrectAmountOfArguments(">- Check you have the correct parameters");
				}

				accounts.search(parameters[1]);
			}
			else if (command.compare("clear") == 0) {   // Clear the console
				system("cls");
			}
			else if (command.compare("exit") != 0) {
				std::cout << ">- Invalid command: " << command << std::endl;
			}
		}
		catch (const IncorrectAmountOfArguments& e) {   // Catch any incorrect amount of argument exceptions thrown
			std::cout << e.what() << "\n";
		}

		delete[] cstr; // free memory
	}

	std::cout << "Press any key to quit...";
	std::getchar();
}
