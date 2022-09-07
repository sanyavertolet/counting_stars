//
// Created by sanyavertolet on 06.09.2022.
//

#include "Rational_number.h"

#include <utility>

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

char plus(char one, char another, int &overflow) {
    auto tmp = (one - '0') + (another - '0') + overflow;
    overflow = tmp / 10;
    return char(tmp % 10 + '0');
}

char minus(char one, char another, int &underflow) {
    auto tmp = one - another - underflow;
    if (tmp < 0) {
        underflow = 1;
    } else {
        underflow = 0;
    }
    return char((10 + tmp) % 10 + '0');
}

char multiply(char one, char another, int &overflow) {
    auto tmp = (one - '0') * (another - '0') + overflow;
    overflow = tmp / 10;
    return char(tmp % 10 + '0');
}

std::string multiply(std::string number, char multiplier) {
    if (multiplier == '0' || number == "0") {
        return "0";
    }
    std::string result;
    int overflow = 0;
    for (int i = 0; i < number.length(); ++i) {
        char new_digit = multiply(number[number.length() - i - 1], multiplier, overflow);
        result = std::string(1, new_digit).append(result);
    }
    if (overflow != 0) {
        result = std::string(1, char(overflow + '0')).append(result);
    }
    return result;
}

int compare_as_numbers(const std::string &one, const std::string &another) {
    if (one.empty() || another.empty()) {
        throw std::runtime_error("Wrong strings: [" + one + "] and [" + another + "]");
    }
    if (one.length() > another.length()) {
        return 1;
    } else if (another.length() > one.length()) {
        return -1;
    } else {
        for (int i = 0; i < one.length(); ++i) {
            if (one[i] > another[i]) {
                return 1;
            } else if (another[i] > one[i]) {
                return -1;
            }
        }
        return 0;
    }
}

std::string plus(std::string one, std::string another) {
    std::string result;
    auto max_length = std::max(one.length(), another.length());
    int overflow = 0;
    for (auto i = 0; i < max_length; ++i) {
        char one_digit;
        if (one.length() > i) {
            one_digit = one[one.length() - i - 1];
        } else {
            one_digit = '0';
        }
        char another_digit;
        if (another.length() > i) {
            another_digit = another[another.length() - i - 1];
        } else {
            another_digit = '0';
        }

        auto new_digit = plus(one_digit, another_digit, overflow);
        result = std::string(1, new_digit).append(result);
    }
    if (overflow != 0) {
        result = std::string(1, char(overflow + '0')).append(result);
    }
    return result;
}

std::string minus(std::string one, std::string another) {
    if (one == another) {
        return "0";
    }
    std::string result;
    if (compare_as_numbers(one, another) == -1) {
        std::swap(one, another);
    }
    int underflow = 0;
    for (int i = 0; i < one.length(); ++i) {
        char one_digit = one[one.length() - i - 1];
        char another_digit;
        if (another.length() > i) {
            another_digit = another[another.length() - i - 1];
        } else {
            another_digit = '0';
        }
        auto new_digit = minus(one_digit, another_digit, underflow);
        result = std::string(1, new_digit).append(result);
    }
    return result;
}

std::string multiply(std::string one, const std::string& another) {
    if (one == "0" || another == "0") {
        return "0";
    }
    std::string result = "0";
    std::string postfix_nulls;
    for (int i = 0; i < one.length(); ++i) {
        char multiplier = one[one.length() - i - 1];
        std::string temp_result = multiply(another, multiplier).append(postfix_nulls);
        result = plus(result, temp_result);
        postfix_nulls = postfix_nulls.append("0");
    }
    return result;
}

Rational_number& Rational_number::operator++() {
    auto comparator_result = compare_as_numbers(numerator, denominator);
    if (sign == '+') {
        numerator = plus(numerator, denominator);
    } else if (comparator_result == 0) {
        numerator = "0";
        sign = '+';
    } else if (comparator_result == 1) {
        numerator = minus(numerator, denominator);
    } else {
        numerator = minus(numerator, denominator);
        sign = '+';
    }
    remove_leading_zeros();
    return *this;
}

//NOLINTNEXTLINE
Rational_number Rational_number::operator++(int) {
    auto result = *this;
    auto comparator_result = compare_as_numbers(numerator, denominator);
    if (sign == '+') {
        numerator = plus(numerator, denominator);
    } else if (comparator_result == 0) {
        numerator = "0";
        sign = '+';
    } else if (comparator_result == 1) {
        numerator = minus(numerator, denominator);
    } else {
        numerator = minus(numerator, denominator);
        sign = '+';
    }
    remove_leading_zeros();
    return result;
}

Rational_number& Rational_number::operator--() {
    auto comparator_result = compare_as_numbers(numerator, denominator);
    if (sign == '-') {
        numerator = plus(numerator, denominator);
    } else if (comparator_result == 0) {
        numerator = "0";
    } else if (comparator_result == 1) {
        numerator = minus(numerator, denominator);
    } else {
        sign = '-';
        numerator = minus(numerator, denominator);
    }
    remove_leading_zeros();
    return *this;
}

//NOLINTNEXTLINE
Rational_number Rational_number::operator--(int) {
    auto result = *this;
    auto comparator_result = compare_as_numbers(numerator, denominator);
    if (sign == '-') {
        numerator = plus(numerator, denominator);
    } else if (comparator_result == 0) {
        numerator = "0";
    } else if (comparator_result == 1) {
        numerator = minus(numerator, denominator);
    } else {
        sign = '-';
        numerator = minus(numerator, denominator);
    }
    remove_leading_zeros();
    return result;
}

std::string operator*(std::string one, std::string another) {
    std::string result;
    for (auto i = another.length() - 1; i >= 0; --i) {
        int overflow = 0;
        for (auto j = one.length() - 1; j >= 0; --j) {
            auto tmp = (one[j] - '0') * (another[i] - '0');
            auto current_value = tmp % 10 + overflow;
            overflow = tmp / 10;
        }
    }
    return one;
}

#ifdef ___DEV___
Rational_number Rational_number::operator*=(const Rational_number& other) {
    if (sign == '-' && other.sign == '-' || sign == '+' && other.sign == '+') {
        sign = '+';
    } else {
        sign = '-';
    }
    numerator = numerator * other.numerator;
    denominator = denominator * other.denominator;
    return *this;
}
#endif
