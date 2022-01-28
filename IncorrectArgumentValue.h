#pragma once

#include <iostream>
#include <exception>

// Customer exception to use for when incorrect value of arguments is passed
class IncorrectArgumentValue final : public std::exception
{
private:
    std::string message;

public:
    explicit IncorrectArgumentValue(std::string message);

    // Override the what function
    const char* what() const throw () override {
        return message.c_str();
    }
};
