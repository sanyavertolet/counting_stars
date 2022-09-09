//
// Created by Александр Фролов on 09.09.2022.
//

#include "string_arithmetics.h"

string_arithmetics::Comparator_result string_arithmetics::compare_as_numbers(const std::string &one, const std::string &another) {
    if (one.empty() || another.empty()) {
        throw std::runtime_error("Wrong strings: [" + one + "] and [" + another + "]");
    }
    if (one.length() > another.length()) {
        return Comparator_result::GREATER;
    } else if (another.length() > one.length()) {
        return Comparator_result::LESS;
    } else {
        for (int i = 0; i < one.length(); ++i) {
            if (one[i] > another[i]) {
                return Comparator_result::GREATER;
            } else if (another[i] > one[i]) {
                return Comparator_result::LESS;
            }
        }
        return Comparator_result::EQUAL;
    }
}

std::string string_arithmetics::remove_leading_zeros(std::string number) {
    while(number.length() > 1 && number[0] == '0') {
        number.erase(number.begin());
    }
    return number;
}

char string_arithmetics::plus(char one, char another, int &overflow) {
    auto tmp = (one - '0') + (another - '0') + overflow;
    overflow = tmp / 10;
    return char(tmp % 10 + '0');
}

char string_arithmetics::minus(char one, char another, int &underflow) {
    auto tmp = one - another - underflow;
    if (tmp < 0) {
        underflow = 1;
    } else {
        underflow = 0;
    }
    return char((10 + tmp) % 10 + '0');
}

char string_arithmetics::multiply(char one, char another, int &overflow) {
    auto tmp = (one - '0') * (another - '0') + overflow;
    overflow = tmp / 10;
    return char(tmp % 10 + '0');
}

std::string string_arithmetics::multiply(std::string number, char multiplier) {
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

std::string string_arithmetics::plus(std::string one, std::string another) {
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
    return remove_leading_zeros(result);
}

std::string string_arithmetics::minus(std::string one, std::string another) {
    if (one == another) {
        return "0";
    }
    std::string result;
    if (compare_as_numbers(one, another) == Comparator_result::LESS) {
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
    return remove_leading_zeros(result);
}

std::string string_arithmetics::multiply(std::string one, const std::string& another) {
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

std::string string_arithmetics::gcd(std::string one, std::string another) {
    while (one != "0" && another != "0") {
        if (compare_as_numbers(one, another) == Comparator_result::LESS) {
            std::swap(one, another);
        }
        one = minus(one, another);
    }
    if (one == "0") {
        return another;
    } else {
        return one;
    }
}

std::pair<std::string, std::string> string_arithmetics::division_step(std::string current_number, std::string divisor) {
    std::string current_divisor = divisor;
    if (string_arithmetics::compare_as_numbers(current_number, divisor) == Comparator_result::LESS) {
        return { "0", "0" };
    }
    int i;
    for (i = 1; i < 10; ++i) {
        auto new_current_divisor = plus(current_divisor, divisor);
        if (compare_as_numbers(current_number, new_current_divisor) == Comparator_result::LESS) {
            break;
        } else {
            current_divisor = new_current_divisor;
        }
    }
    return { { char(i + '0') }, current_divisor };
}

std::string string_arithmetics::divide_as_integers(std::string one, std::string another) {
    if (another == "0") {
        throw std::runtime_error("Null division: [" + one + "/" + another + "]");
    }
    if (compare_as_numbers(one, another) == Comparator_result::LESS) {
        return "0";
    }

    std::string result;
    std::string current_number;
    while(!one.empty()) {
        if (current_number == "0") {
            current_number = std::string(1, one[0]);
        } else {
            current_number += std::string(1, one[0]);
        }
        one.erase(one.begin());
        auto [new_digit, calculated_number] = division_step(current_number, another);
        result += new_digit;
        current_number = minus(current_number, calculated_number);
    }

    return remove_leading_zeros(result);
}
