#pragma once

#include <iostream>
#include <exception>

// Customer exception to use for when incorrect amount of arguments is passed
class IncorrectAmountOfArguments final : public std::exception
{
private:
    std::string message{};

public:
	explicit IncorrectAmountOfArguments(std::string message = "");

    // Override the what function
    const char* what() const throw () override {
        std::cout << " (You have passed in an incorrect amount of arguments)\n";
        return message.c_str();
    }
};
