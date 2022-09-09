//
// Created by sanyavertolet on 09.09.2022.
//

#ifndef COUNTING_STARS_STRING_ARITHMETICS_H
#define COUNTING_STARS_STRING_ARITHMETICS_H

#include <string>
#include <map>

namespace string_arithmetics {
    enum class Comparator_result {
        LESS = -1,
        EQUAL = 0,
        GREATER = 1,
    };

    Comparator_result compare_as_numbers(const std::string &one, const std::string &another);

    std::string remove_leading_zeros(std::string number);

    char plus(char one, char another, int &overflow);

    char minus(char one, char another, int &underflow);

    char multiply(char one, char another, int &overflow);

    std::string multiply(std::string number, char multiplier);

    std::string plus(std::string one, std::string another);

    std::string minus(std::string one, std::string another);

    std::string multiply(std::string one, const std::string &another);

    std::string gcd(std::string one, std::string another);

    std::pair<std::string, std::string> division_step(std::string current_number, std::string divisor);

    std::string divide_as_integers(std::string one, std::string another);
}

#endif //COUNTING_STARS_STRING_ARITHMETICS_H
