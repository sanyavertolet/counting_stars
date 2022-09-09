//
// Created by sanyavertolet on 06.09.2022.
//
#include "../Rational_number.h"
#include "gtest/gtest.h"

class Rational_number_operators_test : public testing::Test { };

TEST(Rational_number_operators_test, unary_minus_operator_check)
{
    auto rational = -Rational_number('+', "10", "12");
    ASSERT_TRUE(rational.sign == '-' && rational.numerator == "10" && rational.denominator == "12");

    rational = -Rational_number('-', "10", "12");
    ASSERT_TRUE(rational.sign == '+' && rational.numerator == "10" && rational.denominator == "12");

    rational = -(-Rational_number('+', "10", "12"));
    ASSERT_TRUE(rational.sign == '+' && rational.numerator == "10" && rational.denominator == "12");
}

TEST(Rational_number_operators_test, prefix_increment_check)
{
    auto rational = ++Rational_number('+', "10", "12");
    ASSERT_TRUE(rational.sign == '+' && rational.numerator == "22" && rational.denominator == "12");

    rational = ++Rational_number('-', "10", "12");
    ASSERT_TRUE(rational.sign == '+' && rational.numerator == "2" && rational.denominator == "12");

    rational = ++Rational_number('-', "13", "12");
    ASSERT_TRUE(rational.sign == '-' && rational.numerator == "1" && rational.denominator == "12");

    rational = ++Rational_number('-', "12", "12");
    ASSERT_TRUE(rational.sign == '+' && rational.numerator == "0" && rational.denominator == "12");
}

TEST(Rational_number_operators_test, postfix_increment_check)
{
    auto rational = Rational_number('+', "10", "12");
    ASSERT_TRUE(rational++.numerator == "10");
    ASSERT_TRUE(rational.sign == '+' && rational.numerator == "22" && rational.denominator == "12");

    rational = Rational_number('-', "10", "12");
    ASSERT_TRUE(rational++.numerator == "10");
    ASSERT_TRUE(rational.sign == '+' && rational.numerator == "2" && rational.denominator == "12");

    rational = Rational_number('-', "13", "12");
    ASSERT_TRUE(rational++.numerator == "13");
    ASSERT_TRUE(rational.sign == '-' && rational.numerator == "1" && rational.denominator == "12");

    rational = Rational_number('-', "12", "12");
    ASSERT_TRUE(rational++.numerator == "12");
    ASSERT_TRUE(rational.sign == '+' && rational.numerator == "0" && rational.denominator == "12");
}

TEST(Rational_number_operators_test, prefix_decrement_check)
{
    auto rational = --Rational_number('+', "10", "12");
    ASSERT_TRUE(rational.sign == '-' && rational.numerator == "2" && rational.denominator == "12");

    rational = --Rational_number('-', "10", "12");
    ASSERT_TRUE(rational.sign == '-' && rational.numerator == "22" && rational.denominator == "12");

    rational = --Rational_number('+', "15", "12");
    ASSERT_TRUE(rational.sign == '+' && rational.numerator == "3" && rational.denominator == "12");

    rational = --Rational_number('+', "12", "12");
    ASSERT_TRUE(rational.sign == '+' && rational.numerator == "0" && rational.denominator == "12");
}

TEST(Rational_number_operators_test, postfix_decrement_check)
{
    auto rational = Rational_number('+', "10", "12");
    ASSERT_TRUE(rational--.numerator == "10");
    ASSERT_TRUE(rational.sign == '-' && rational.numerator == "2" && rational.denominator == "12");

    rational = Rational_number('-', "10", "12");
    ASSERT_TRUE(rational--.numerator == "10");
    ASSERT_TRUE(rational.sign == '-' && rational.numerator == "22" && rational.denominator == "12");

    rational = Rational_number('+', "15", "12");
    ASSERT_TRUE(rational--.numerator == "15");
    ASSERT_TRUE(rational.sign == '+' && rational.numerator == "3" && rational.denominator == "12");

    rational = Rational_number('+', "12", "12");
    ASSERT_TRUE(rational--.numerator == "12");
    ASSERT_TRUE(rational.sign == '+' && rational.numerator == "0" && rational.denominator == "12");
}

TEST(Rational_number_operators_test, plus_check)
{
    auto one = Rational_number('+', "10", "12");
    auto another = Rational_number('+', "10", "12");
    auto result = one + another;
    ASSERT_TRUE(result.sign == '+' && result.numerator == "20" && result.denominator == "12");

    one = Rational_number('+', "10", "12");
    another = Rational_number('-', "10", "12");
    result = one + another;
    ASSERT_TRUE(result.sign == '+' && result.numerator == "0" && result.denominator == "12");

    one = Rational_number('+', "10", "12");
    another = Rational_number('+', "10", "24");
    result = one + another;
    ASSERT_TRUE(result.sign == '+' && result.numerator == "30" && result.denominator == "24");

    one = Rational_number('+', "5", "12");
    another = Rational_number('-', "10", "12");
    result = one + another;
    ASSERT_TRUE(result.sign == '-' && result.numerator == "5" && result.denominator == "12");

    one = Rational_number('-', "5", "12");
    another = Rational_number('-', "10", "12");
    result = one + another;
    ASSERT_TRUE(result.sign == '-' && result.numerator == "15" && result.denominator == "12");

    one = Rational_number('-', "5", "12");
    another = Rational_number('+', "10", "12");
    result = one + another;
    ASSERT_TRUE(result.sign == '+' && result.numerator == "5" && result.denominator == "12");

    one = Rational_number('-', "345", "993");
    another = Rational_number('+', "228", "432");
    result = one + another;
    ASSERT_TRUE(result.sign == '+' && result.numerator == "25788" && result.denominator == "142992");
}

TEST(Rational_number_operators_test, minus_check)
{
    auto one = Rational_number('+', "10", "12");
    auto another = Rational_number('+', "10", "12");
    auto result = one - another;
    ASSERT_TRUE(result.sign == '+' && result.numerator == "0" && result.denominator == "12");

    one = Rational_number('+', "10", "12");
    another = Rational_number('-', "10", "12");
    result = one - another;
    ASSERT_TRUE(result.sign == '+' && result.numerator == "20" && result.denominator == "12");

    one = Rational_number('+', "10", "12");
    another = Rational_number('+', "10", "24");
    result = one - another;
    ASSERT_TRUE(result.sign == '+' && result.numerator == "10" && result.denominator == "24");

    one = Rational_number('+', "5", "12");
    another = Rational_number('-', "10", "12");
    result = one - another;
    ASSERT_TRUE(result.sign == '+' && result.numerator == "15" && result.denominator == "12");

    one = Rational_number('-', "5", "12");
    another = Rational_number('-', "10", "12");
    result = one - another;
    ASSERT_TRUE(result.sign == '+' && result.numerator == "5" && result.denominator == "12");

    one = Rational_number('-', "5", "12");
    another = Rational_number('+', "10", "12");
    result = one - another;
    ASSERT_TRUE(result.sign == '-' && result.numerator == "15" && result.denominator == "12");

    one = Rational_number('-', "345", "993");
    another = Rational_number('+', "228", "432");
    result = one - another;
    ASSERT_TRUE(result.sign == '-' && result.numerator == "125148" && result.denominator == "142992");

    one = Rational_number('-', "345", "993");
    another = Rational_number('-', "228", "432");
    result = one - another;
    ASSERT_TRUE(result.sign == '+' && result.numerator == "25788" && result.denominator == "142992");
}

TEST(Rational_number_operators_test, multiply_check)
{
    auto one = Rational_number('+', "10", "12");
    auto another = Rational_number('+', "10", "12");
    auto result = one * another;
    ASSERT_TRUE(result.sign == '+' && result.numerator == "100" && result.denominator == "144");

    one = Rational_number('+', "10", "12");
    another = Rational_number('-', "10", "12");
    result = one * another;
    ASSERT_TRUE(result.sign == '-' && result.numerator == "100" && result.denominator == "144");

    one = Rational_number('+', "10", "12");
    another = Rational_number('+', "10", "24");
    result = one * another;
    ASSERT_TRUE(result.sign == '+' && result.numerator == "100" && result.denominator == "288");

    one = Rational_number('+', "5", "12");
    another = Rational_number('-', "10", "12");
    result = one * another;
    ASSERT_TRUE(result.sign == '-' && result.numerator == "50" && result.denominator == "144");

    one = Rational_number('-', "5", "12");
    another = Rational_number('-', "10", "12");
    result = one * another;
    ASSERT_TRUE(result.sign == '+' && result.numerator == "50" && result.denominator == "144");

    one = Rational_number('-', "5", "12");
    another = Rational_number('+', "10", "12");
    result = one * another;
    ASSERT_TRUE(result.sign == '-' && result.numerator == "50" && result.denominator == "144");

    one = Rational_number('-', "345", "993");
    another = Rational_number('+', "228", "432");
    result = one * another;
    ASSERT_TRUE(result.sign == '-' && result.numerator == "78660" && result.denominator == "428976");

    one = Rational_number('-', "345", "993");
    another = Rational_number('-', "228", "432");
    result = one * another;
    ASSERT_TRUE(result.sign == '+' && result.numerator == "78660" && result.denominator == "428976");
}

TEST(Rational_number_operators_test, division_check)
{
    auto one = Rational_number('+', "10", "12");
    auto another = Rational_number('+', "10", "12");
    auto result = one / another;
    ASSERT_TRUE(result.sign == '+' && result.numerator == "120" && result.denominator == "120");

    one = Rational_number('+', "10", "12");
    another = Rational_number('-', "0", "12");
    ASSERT_ANY_THROW(one / another);

    one = Rational_number('+', "10", "12");
    another = Rational_number('+', "10", "24");
    result = one / another;
    ASSERT_TRUE(result.sign == '+' && result.numerator == "240" && result.denominator == "120");

    one = Rational_number('+', "5", "12");
    another = Rational_number('-', "10", "12");
    result = one / another;
    ASSERT_TRUE(result.sign == '-' && result.numerator == "60" && result.denominator == "120");

    one = Rational_number('-', "5", "12");
    another = Rational_number('-', "10", "12");
    result = one / another;
    ASSERT_TRUE(result.sign == '+' && result.numerator == "60" && result.denominator == "120");

    one = Rational_number('-', "345", "993");
    another = Rational_number('+', "228", "432");
    result = one / another;
    ASSERT_TRUE(result.sign == '-' && result.numerator == "149040" && result.denominator == "226404");

    one = Rational_number('-', "345", "993");
    another = Rational_number('-', "228", "432");
    result = one / another;
    ASSERT_TRUE(result.sign == '+' && result.numerator == "149040" && result.denominator == "226404");
}
