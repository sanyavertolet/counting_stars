//
// Created by sanyavertolet on 06.09.2022.
//
#include "../Rational_number.h"
#include "gtest/gtest.h"

class Rational_number_utils_test : public testing::Test { };

TEST(Rational_number_utils_test, remove_leading_zeros_check)
{
    auto rational = Rational_number('+', "00001", "12");
    rational.remove_leading_zeros();
    ASSERT_TRUE(rational.sign == '+' && rational.numerator == "1" && rational.denominator == "12");

    rational = Rational_number('+', "00000000000000000000000000", "12");
    rational.remove_leading_zeros();
    ASSERT_TRUE(rational.sign == '+' && rational.numerator == "0" && rational.denominator == "12");
}
