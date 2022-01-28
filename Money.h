#pragma once
#include <stdexcept>
#include <string>

class Money {
private:
	long pounds;
	int pence;

public:
	Money();
	// Overloaded constructors
	explicit Money(long pounds);
	Money(long pounds, int pence);

	// Overload operators to allow easier arithmetic of money objects
	Money operator+(const Money& moneyRhs) const;
	Money operator-(const Money& moneyRhs) const;

	// Doesn't make sense to multiply (or divide) 2 money values, instead you can times by a number
	// e.g How much would it cost if i want 3 sandwiches each being ?3.50 (3.50 * 3)
	template <class T>
	Money operator*(T number) const {
		const int penceMult = pence * number;
		const int newPence = penceMult % 100;

		const long newPounds = pounds * number + (penceMult / 100);
		const Money tmp(newPounds, newPence);
		return tmp;
	}

	template <class T>
	Money operator/(T number) const {
		if (number == 0) {
			throw std::invalid_argument("Division by zero");
		}

		long total = (100 * pounds) + pence;
		const long result = total / number;

		const int newPence = result % 100;
		const long newPounds = result / 100;
		const Money tmp(newPounds, newPence);
		return tmp;
	}

	// Allows Money class object to be print our money to string
	friend std::ostream& operator<<(std::ostream& os, const Money& money);

	// toString method to print out money object
	std::string toString() const;

	// Getters
	long getPounds() const;
	int getPence() const;

	// Overloading comparison operators
	bool operator<(const Money& rhs) const;
	bool operator>(const Money& rhs) const;
	bool operator!=(const Money& rhs) const;
	bool operator==(const Money& rhs) const;
};