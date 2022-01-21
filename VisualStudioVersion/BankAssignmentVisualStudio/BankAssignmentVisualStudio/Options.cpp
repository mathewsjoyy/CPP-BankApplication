#include "Options.h"

Options::Options(std::string title) : title(std::move(title)) {
    // Insert commands we want to give to the user along with the descriptions
    options.emplace_back("open type initial_deposit : open a current (1), savings (2) or ISA (3) account");
    options.emplace_back("view [index] : view balance and recent transactions" );
    options.emplace_back("withdraw sum : withdraw funds from most recently viewed account" );
    options.emplace_back("deposit sum : deposit funds into most recently viewed account" );
    options.emplace_back("transfer src dest sum : transfer funds between accounts" );
    options.emplace_back("project years : project balance forward in time" );
    options.emplace_back("options : view these options again" );
    options.emplace_back("search amount : search your account history for a transaction "
        "by amount (most recently viewed account)" );
    options.emplace_back("exit : close this application" );
    options.emplace_back("clear : clear the screen" );

    std::cout << "> Type 'options' to see a list of commands." << std::endl;
}

std::string Options::toString() const {
    std::string stringFormat{};

    stringFormat += "---- " + getTitle() + " options! ----\n";

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
