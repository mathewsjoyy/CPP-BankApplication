#include "Money.h"
#include <iomanip>

Money::Money(): pounds(0), pence(0) {}

Money::Money(const long pounds): pounds(pounds), pence(0) {}

Money::Money(const long pounds, const int pence): pounds(pounds), pence(pence) {}

Money Money::operator+(const Money& moneyRhs) const {
	// Convert all money to pence then do addition
	const long poundsInPence = (pounds + moneyRhs.pounds) * 100;
	const int totalPence = pence + moneyRhs.pence;
	const long allPence = poundsInPence + totalPence;

	const Money m3 = Money(allPence / 100, allPence % 100);
	return m3;
}

Money Money::operator-(const Money& moneyRhs) const {
	// Convert all money to pence then do subtraction
	const long poundsInPence = (pounds - moneyRhs.pounds) * 100;
	const int totalPence = pence - moneyRhs.pence;
	const long allPence = poundsInPence + totalPence;

	const Money m3 = Money(allPence / 100, allPence % 100);
	return m3;
}

std::string Money::toString() const {
	// Check so see if the pence value is 1 digit, if so we need to add a trailing 0 for output
	// e.g £150.5 becomes £150.05
	return std::to_string(getPounds())
		+ (getPence() < 10 ? ".0" : ".")
		+ std::to_string(getPence());
}

std::ostream& operator<<(std::ostream& os, const Money& money) {
	os << money.toString();
	return os;
}

long Money::getPounds() const {
	return pounds;
}

int Money::getPence() const {
	return pence;
}

bool Money::operator==(const Money& rhs) const {
	return getPounds() == rhs.getPounds() && getPence() == rhs.getPence();
}

bool Money::operator!=(const Money& rhs) const {
	return !(*this == rhs);
}

bool Money::operator>(const Money& rhs) const {
	if (getPounds() > rhs.getPounds()) {
		return true;
	}
	if (getPounds() == rhs.getPounds()) {
		return getPence() > rhs.getPence();
	}
	return false;
}

bool Money::operator<(const Money& rhs) const {
	return !(*this == rhs || *this > rhs);
}


