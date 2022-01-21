#pragma once
#include <iostream>
#include <vector>

class Options {
private:
    std::string title{};
    std::vector<std::string> options{}; // Vector off all options

public:
    // Constructor that sets the, and inserts all options to options vector
    explicit Options(std::string title = "Lincoln Bank");

    // You are overloading << operator as a member function, therefore, 
    // the first parameter is implicitly the calling object.
    // so we need to make it a friend function.
    friend std::ostream& operator<<(std::ostream& os, const Options& options);

    // Getters
    std::string getTitle() const;

    // return string format
    std::string toString() const;
};