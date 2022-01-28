#include "Options.h"

Options::Options(std::string title) : title(std::move(title)) {
    // Insert commands we want to give to the user along with the descriptions
    options.push_back("open [type] [initial_deposit] : open a current (1), savings (2) or ISA (3) account");
    options.push_back("view [index] : view balance and recent transactions");
    options.push_back("withdraw [sum] : withdraw funds from most recently viewed account");
    options.push_back("deposit [sum] : deposit funds into most recently viewed account");
    options.push_back("transfer [src] [dest] [sum] : transfer funds between accounts");
    options.push_back("project [years] : project balance forward in time");
    options.push_back("options : view these options again");
    options.push_back("search [amount] : search your account history for a transaction "
        "by amount (most recently viewed account)");
    options.push_back("exit : close this application");
    options.push_back("clear : clear the screen");

    // Great and display all available commands
    std::cout << "~~~ Welcome to Linc Bank! ~~~ \n\n";
    std::cout << toString();
}

std::string Options::toString() const {
    std::string stringFormat{};

    stringFormat += "--- " + getTitle() + " options ---\n";

    // Loop through and format each command and add to stringFormat variable
    for (const auto& option : options) {
        stringFormat += ">- " + option + "\n";
    }

    return stringFormat;
}

std::ostream& operator<<(std::ostream& os, const Options& options) {
    os << options.toString();
    return os;
}

std::string Options::getTitle() const {
    return title;
}
