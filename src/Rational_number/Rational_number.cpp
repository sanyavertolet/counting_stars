//
// Created by sanyavertolet on 06.09.2022.
//

#include "Rational_number.h"

// ================================== CONSTRUCTORS ===================================

Rational_number::Rational_number(): numerator(1), denominator(1) { }

Rational_number::Rational_number(const StringInt& num): numerator(num), denominator(1) { }

Rational_number::Rational_number(StringInt num, StringInt denom) {
    numerator = std::move(num);
    denominator = std::move(denom);
    if (numerator.get_sign() == denominator.get_sign()) {
        numerator.set_sign('+');
    } else {
        numerator.set_sign('-');
    }
    denominator.set_sign('+');
    validate();
}

Rational_number::Rational_number(const signed& num, const unsigned& denom): numerator(num), denominator(denom) {
    validate();
}

Rational_number::Rational_number(const int& number): numerator(number), denominator(1) { }

Rational_number::Rational_number(std::string number) {
    if (number.empty()) {
        throw std::runtime_error("Invalid input number: [" + number + "]");
    }
    if (number[0] == '-' || number[0] == '+') {
        numerator.set_sign(number[0]);
        number.erase(0, 1);
    } else {
        numerator.set_sign('+');
    }
    auto slash_pos = number.find('/');
    if (slash_pos == std::string::npos) {
        auto dot_pos = number.find('.');
        if (dot_pos == std::string::npos) {
            numerator.set_val(number);
            denominator = 1;
        } else {
            auto power = number.substr(dot_pos).size() - 1;
            number.erase(dot_pos, 1);
            numerator.set_val(number);
            denominator = 1;
            for (int i = 0; i < power; ++i) {
                denominator.set_val(denominator.get_val() += "0");
            }
        }
    } else {
        if (slash_pos + 1 < number.length()) {
            denominator.set_val(number.substr(slash_pos + 1));
        }
        numerator.set_val(number.substr(0, slash_pos));
    }
    validate();
}

Rational_number::Rational_number(const signed long long& num): numerator(num), denominator(1) { }

Rational_number::Rational_number(const signed long long& num, const unsigned long long& denom): numerator(num), denominator(denom) {
    validate();
}

Rational_number Rational_number::operator-() const {
    return { -numerator, denominator };
}

// ================================== SETTERS ===================================

void Rational_number::set_numerator(const StringInt& new_numerator) {
    numerator = new_numerator;
}

void Rational_number::set_denominator(const StringInt& new_denominator) {
    if (new_denominator == 0) {
        throw DivisionByZeroException("Denominator cannot be null.");
    } else if (new_denominator.get_sign() != '+') {
        throw IllegalSignException("Denominator must be unsigned.");
    } else {
        denominator = new_denominator;
    }
}

// ================================== GETTERS ===================================

StringInt Rational_number::get_numerator() {
    return numerator;
}
StringInt Rational_number::get_denominator() {
    return denominator;
}

// ================================== INC/DEC ===================================

Rational_number& Rational_number::operator++() {
    *this += 1;
    return this->make_canonical();
}

//NOLINTNEXTLINE
Rational_number Rational_number::operator++(int) {
    Rational_number tmp(*this);
    operator++();
    make_canonical();
    return tmp;
}

Rational_number& Rational_number::operator--() {
    *this -= 1;
    return this->make_canonical();
}

//NOLINTNEXTLINE
Rational_number Rational_number::operator--(int) {
    Rational_number tmp(*this);
    operator--();
    make_canonical();
    return tmp;
}

// ================================== STREAMS ===================================

std::ostream& operator<< (std::ostream& os, Rational_number const& x) {
    os << std::string(x);
    return os;
}

std::istream& operator>> (std::istream& is, Rational_number& x) {
    std::string rational_number_string;
    is >> rational_number_string;
    x = Rational_number(rational_number_string);
    return is;
}

// ================================== COMPARATORS ===================================

bool operator<(const Rational_number& lhs, const Rational_number& rhs) {
    return lhs.numerator * rhs.denominator < rhs.numerator * lhs.denominator;
}

bool operator>(const Rational_number& lhs, const Rational_number& rhs) {
    return rhs < lhs;
}

bool operator==(const Rational_number& lhs, const Rational_number& rhs) {
    return lhs.numerator == rhs.numerator && lhs.denominator == rhs.denominator;
}

bool operator!=(const Rational_number& lhs, const Rational_number& rhs) {
    return !(lhs == rhs);
}

bool operator<=(const Rational_number& lhs, const Rational_number& rhs) {
    return lhs == rhs || lhs < rhs;
}

bool operator>=(const Rational_number& lhs, const Rational_number& rhs) {
    return rhs <= lhs;
}

// ================================== ASSIGNING BINARY OPERATORS ===================================

Rational_number& Rational_number::operator+=(const Rational_number &rhs) {
    auto greatest_common_divider = gcd(denominator, rhs.denominator);
    auto left_multiplier = rhs.denominator / greatest_common_divider;
    auto right_multiplier = denominator / greatest_common_divider;
    auto left_extended_numerator = numerator * left_multiplier;
    auto right_extended_numerator = rhs.numerator * right_multiplier;
    numerator = left_extended_numerator + right_extended_numerator;
    denominator *= left_multiplier;
    return this->make_canonical();
}

Rational_number& Rational_number::operator-=(const Rational_number &rhs) {
    auto greatest_common_divider = gcd(denominator, rhs.denominator);
    auto left_multiplier = rhs.denominator / greatest_common_divider;
    auto right_multiplier = denominator / greatest_common_divider;
    auto left_extended_numerator = numerator * left_multiplier;
    auto right_extended_numerator = rhs.numerator * right_multiplier;
    numerator = left_extended_numerator - right_extended_numerator;
    denominator *= left_multiplier;
    return this->make_canonical();
}

Rational_number& Rational_number::operator*=(const Rational_number &rhs) {
    numerator *= rhs.numerator;
    denominator *= rhs.denominator;
    return this->make_canonical();
}

Rational_number& Rational_number::operator/=(const Rational_number &rhs) {
    if (rhs.numerator.get_val() == "0") {
        throw DivisionByZeroException();
    }
    numerator.set_sign(numerator.get_sign() == rhs.numerator.get_sign() ? '+' : '-');
    numerator *= rhs.denominator;
    denominator = abs(denominator * rhs.numerator);
    return this->make_canonical();
}

// ================================== BINARY OPERATORS ===================================

Rational_number operator+(Rational_number lhs, const Rational_number& rhs) {
    return lhs += rhs;
}

Rational_number operator-(Rational_number lhs, const Rational_number& rhs) {
    return lhs -= rhs;
}

Rational_number operator*(Rational_number lhs, const Rational_number& rhs) {
    return lhs *= rhs;
}

Rational_number operator/(Rational_number lhs, const Rational_number& rhs) {
    return lhs /= rhs;
}

// ================================== BOOLEAN OPERATORS ===================================

bool Rational_number::operator!() const {
    return !(operator bool());
}

Rational_number::operator bool() const {
    return numerator != 0;
}

Rational_number::operator std::string() const {
    return std::string(numerator) + "/" + denominator.get_val();
}

// ================================== UTILITY METHODS ===================================

Rational_number& Rational_number::make_canonical() {
    if (numerator.get_val() == "0") {
        numerator.set_sign('+');
        denominator = 1;
    } else {
        StringInt greatest_common_divider = gcd(numerator, denominator);
        numerator /= greatest_common_divider;
        denominator /= greatest_common_divider;
    }
    return *this;
}

// ================================== PRIVATE METHODS ===================================

void Rational_number::validate() const {
    if (denominator == StringInt(0)) {
        throw DivisionByZeroException("Denominator of rational number should not be null");
    }
}
