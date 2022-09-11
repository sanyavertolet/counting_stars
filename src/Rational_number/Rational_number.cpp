//
// Created by sanyavertolet on 06.09.2022.
//

#include "Rational_number.h"

#include <utility>
#include "../string_arithmetics/string_arithmetics.h"

enum class Comparator_result {
    LESS = -1,
    EQUAL = 0,
    GREATER = 1,
};

Rational_number::Rational_number(char sgn, std::string num, std::string denom) {
    sign = sgn;
    numerator = std::move(num);
    denominator = std::move(denom);
    validate();
}

Rational_number::Rational_number(signed num, unsigned denom) {
    if (num < 0) {
        sign = '-';
    } else {
        sign = '+';
    }
    numerator = std::to_string(abs(num));
    denominator = std::to_string(denom);
    validate();
}

Rational_number::Rational_number(int number) {
    if (number < 0) {
        sign = '-';
    } else {
        sign = '+';
    }
    numerator = std::to_string(abs(number));
    denominator = "1";
    validate();
}

Rational_number::Rational_number(std::string number) {
    if (number.empty()) {
        throw std::runtime_error("Invalid input number: [" + number + "]");
    }
    if (number[0] == '-') {
        sign = '-';
        number.erase(0, 1);
    } else if (number[0] == '+') {
        sign = '+';
        number.erase(0, 1);
    } else {
        sign = '+';
    }
    auto slash_pos = number.find('/');
    if (slash_pos == std::string::npos) {
        auto dot_pos = number.find('.');
        if (dot_pos == std::string::npos) {
            numerator = number;
            denominator = "1";
        } else {
            auto power = number.substr(dot_pos).size() - 1;
            number.erase(dot_pos, 1);
            numerator = number;
            denominator = "1";
            for (int i = 0; i < power; ++i) {
                denominator += "0";
            }
        }
    } else {
        if (slash_pos + 1 < number.length()) {
            denominator = number.substr(slash_pos + 1);
        }
        numerator = number.substr(0, slash_pos);
    }
    validate();
}

void Rational_number::validate() {
    if (sign != '+' && sign != '-') {
        throw std::runtime_error("Invalid sign: [" + std::string(1, sign) + "]");
    }
    if (numerator.empty()) {
        throw std::runtime_error("Empty numerator");
    }
    if (denominator.empty()) {
        throw std::runtime_error("Empty denominator");
    }
    if (denominator == "0") {
        throw std::runtime_error("Denominator of rational number should not be null");
    }
    remove_leading_zeros();
    for (char digit : numerator) {
        if (!isnumber(digit)) {
            throw std::runtime_error("Invalid numerator: [" + numerator + "]");
        }
    }
    for (char digit : denominator) {
        if (!isnumber(digit)) {
            throw std::runtime_error("Invalid denominator: [" + denominator + "]");
        }
    }
}

void Rational_number::remove_leading_zeros() {
    auto size = numerator.length();
    int i;
    for (i = 0; i < size - 1; ++i) {
        if (numerator[i] != '0') {
            break;
        }
    }
    numerator = numerator.substr(i);
}

Rational_number::operator std::string() const {
    if (sign == '-') {
        return sign + numerator + '/' + denominator;
    } else {
        return numerator + '/' + denominator;
    }
}

std::string to_string(Rational_number &number) {
    return std::string(number);
}

Rational_number Rational_number::operator-() const {
    if (sign == '-') {
        return Rational_number('+', numerator, denominator);
    } else {
        return Rational_number('-', numerator, denominator);
    }
}

Rational_number& Rational_number::operator++() {
    auto comparator_result = string_arithmetics::compare_as_numbers(numerator, denominator);
    if (sign == '+') {
        numerator = string_arithmetics::plus(numerator, denominator);
    } else if (comparator_result == string_arithmetics::Comparator_result::EQUAL) {
        numerator = "0";
        sign = '+';
    } else if (comparator_result == string_arithmetics::Comparator_result::GREATER) {
        numerator = string_arithmetics::minus(numerator, denominator);
    } else {
        numerator = string_arithmetics::minus(numerator, denominator);
        sign = '+';
    }
    remove_leading_zeros();
    this->simplify();
    return *this;
}

//NOLINTNEXTLINE
Rational_number Rational_number::operator++(int) {
    auto result = *this;
    auto comparator_result = string_arithmetics::compare_as_numbers(numerator, denominator);
    if (sign == '+') {
        numerator = string_arithmetics::plus(numerator, denominator);
    } else if (comparator_result == string_arithmetics::Comparator_result::EQUAL) {
        numerator = "0";
        sign = '+';
    } else if (comparator_result == string_arithmetics::Comparator_result::GREATER) {
        numerator = string_arithmetics::minus(numerator, denominator);
    } else {
        numerator = string_arithmetics::minus(numerator, denominator);
        sign = '+';
    }
    remove_leading_zeros();
    this->simplify();
    return result;
}

Rational_number& Rational_number::operator--() {
    auto comparator_result = string_arithmetics::compare_as_numbers(numerator, denominator);
    if (sign == '-') {
        numerator = string_arithmetics::plus(numerator, denominator);
    } else if (comparator_result == string_arithmetics::Comparator_result::EQUAL) {
        numerator = "0";
    } else if (comparator_result == string_arithmetics::Comparator_result::GREATER) {
        numerator = string_arithmetics::minus(numerator, denominator);
    } else {
        sign = '-';
        numerator = string_arithmetics::minus(numerator, denominator);
    }
    remove_leading_zeros();
    this->simplify();
    return *this;
}

//NOLINTNEXTLINE
Rational_number Rational_number::operator--(int) {
    auto result = *this;
    auto comparator_result = string_arithmetics::compare_as_numbers(numerator, denominator);
    if (sign == '-') {
        numerator = string_arithmetics::plus(numerator, denominator);
    } else if (comparator_result == string_arithmetics::Comparator_result::EQUAL) {
        numerator = "0";
    } else if (comparator_result == string_arithmetics::Comparator_result::GREATER) {
        numerator = string_arithmetics::minus(numerator, denominator);
    } else {
        sign = '-';
        numerator = string_arithmetics::minus(numerator, denominator);
    }
    remove_leading_zeros();
    this->simplify();
    return result;
}

Rational_number Rational_number::operator+(const Rational_number &another) const {
    std::string gcd = string_arithmetics::gcd(denominator, another.denominator);
    std::string left_multiplier = string_arithmetics::divide_as_integers(another.denominator, gcd);
    std::string right_multiplier = string_arithmetics::divide_as_integers(denominator, gcd);
    std::string left_extended_numerator = string_arithmetics::multiply(numerator, left_multiplier);
    std::string right_extended_numerator = string_arithmetics::multiply(another.numerator, right_multiplier);
    std::string new_denominator = string_arithmetics::multiply(denominator, left_multiplier);

    auto comparator_result = string_arithmetics::compare_as_numbers(left_extended_numerator, right_extended_numerator);
    char new_sign;
    if ((sign == '+' && another.sign == '+') ||
        (sign == '-' && another.sign == '+' && comparator_result != string_arithmetics::Comparator_result::GREATER) ||
        (sign == '+' && another.sign == '-' && comparator_result != string_arithmetics::Comparator_result::LESS)
    ) {
        new_sign = '+';
    } else {
        new_sign = '-';
    }

    std::string new_numerator;
    if (sign == another.sign) {
        new_numerator = string_arithmetics::plus(left_extended_numerator, right_extended_numerator);
    } else {
        new_numerator = string_arithmetics::minus(left_extended_numerator, right_extended_numerator);
    }

    return Rational_number(new_sign, new_numerator, new_denominator).simplify();
}

Rational_number Rational_number::operator-(const Rational_number &another) const {
    std::string gcd = string_arithmetics::gcd(denominator, another.denominator);
    std::string left_multiplier = string_arithmetics::divide_as_integers(another.denominator, gcd);
    std::string right_multiplier = string_arithmetics::divide_as_integers(denominator, gcd);
    std::string left_extended_numerator = string_arithmetics::multiply(numerator, left_multiplier);
    std::string right_extended_numerator = string_arithmetics::multiply(another.numerator, right_multiplier);
    std::string new_denominator = string_arithmetics::multiply(denominator, left_multiplier);

    auto comparator_result = string_arithmetics::compare_as_numbers(left_extended_numerator, right_extended_numerator);
    char new_sign;
    if ((sign == '+' && another.sign == '-') ||
        (sign == '+' && another.sign == '+' && comparator_result != string_arithmetics::Comparator_result::LESS) ||
        (sign == '-' && another.sign == '-' && comparator_result != string_arithmetics::Comparator_result::GREATER)
            ) {
        new_sign = '+';
    } else {
        new_sign = '-';
    }

    std::string new_numerator;
    if (sign != another.sign) {
        new_numerator = string_arithmetics::plus(left_extended_numerator, right_extended_numerator);
    } else {
        new_numerator = string_arithmetics::minus(left_extended_numerator, right_extended_numerator);
    }
    return Rational_number(new_sign, new_numerator, new_denominator).simplify();
}

Rational_number Rational_number::operator*(const Rational_number &another) const {
    char new_sign;
    if (sign == another.sign) {
        new_sign = '+';
    } else {
        new_sign = '-';
    }
    std::string new_numerator = string_arithmetics::multiply(numerator, another.numerator);
    std::string new_denominator = string_arithmetics::multiply(denominator, another.denominator);
    return Rational_number(new_sign, new_numerator, new_denominator).simplify();
}

Rational_number Rational_number::operator/(const Rational_number &another) const {
    char new_sign;
    if (sign == another.sign) {
        new_sign = '+';
    } else {
        new_sign = '-';
    }
    std::string new_numerator = string_arithmetics::multiply(numerator, another.denominator);
    std::string new_denominator = string_arithmetics::multiply(denominator, another.numerator);
    return Rational_number(new_sign, new_numerator, new_denominator).simplify();
}

Rational_number Rational_number::simplify() const {
    std::string gcd = string_arithmetics::gcd(numerator, denominator);
    std::string new_numerator = string_arithmetics::divide_as_integers(numerator, gcd);
    std::string new_denominator = string_arithmetics::divide_as_integers(denominator, gcd);
    return Rational_number(sign, new_numerator, new_denominator);
}

Rational_number& Rational_number::simplify() {
    if (numerator == "0") {
        denominator = "1";
    } else {
        std::string gcd = string_arithmetics::gcd(numerator, denominator);
        numerator = string_arithmetics::divide_as_integers(numerator, gcd);
        denominator = string_arithmetics::divide_as_integers(denominator, gcd);
    }
    return *this;
}
