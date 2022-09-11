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
    ASSERT_TRUE(rational.sign == '+' && rational.numerator == "11" && rational.denominator == "6");

    rational = ++Rational_number('-', "10", "12");
    ASSERT_TRUE(rational.sign == '+' && rational.numerator == "1" && rational.denominator == "6");

    rational = ++Rational_number('-', "13", "12");
    ASSERT_TRUE(rational.sign == '-' && rational.numerator == "1" && rational.denominator == "12");

    rational = ++Rational_number('-', "12", "12");
    ASSERT_TRUE(rational.sign == '+' && rational.numerator == "0" && rational.denominator == "1");
}

TEST(Rational_number_operators_test, postfix_increment_check)
{
    auto rational = Rational_number('+', "10", "12");
    ASSERT_TRUE(rational++.numerator == "10");
    ASSERT_TRUE(rational.sign == '+' && rational.numerator == "11" && rational.denominator == "6");

    rational = Rational_number('-', "10", "12");
    ASSERT_TRUE(rational++.numerator == "10");
    ASSERT_TRUE(rational.sign == '+' && rational.numerator == "1" && rational.denominator == "6");

    rational = Rational_number('-', "13", "12");
    ASSERT_TRUE(rational++.numerator == "13");
    ASSERT_TRUE(rational.sign == '-' && rational.numerator == "1" && rational.denominator == "12");

    rational = Rational_number('-', "12", "12");
    ASSERT_TRUE(rational++.numerator == "12");
    ASSERT_TRUE(rational.sign == '+' && rational.numerator == "0" && rational.denominator == "1");
}

TEST(Rational_number_operators_test, prefix_decrement_check)
{
    auto rational = --Rational_number('+', "10", "12");
    ASSERT_TRUE(rational.sign == '-' && rational.numerator == "1" && rational.denominator == "6");

    rational = --Rational_number('-', "10", "12");
    ASSERT_TRUE(rational.sign == '-' && rational.numerator == "11" && rational.denominator == "6");

    rational = --Rational_number('+', "15", "12");
    ASSERT_TRUE(rational.sign == '+' && rational.numerator == "1" && rational.denominator == "4");

    rational = --Rational_number('+', "12", "12");
    ASSERT_TRUE(rational.sign == '+' && rational.numerator == "0" && rational.denominator == "1");
}

TEST(Rational_number_operators_test, postfix_decrement_check)
{
    auto rational = Rational_number('+', "10", "12");
    ASSERT_TRUE(rational--.numerator == "10");
    ASSERT_TRUE(rational.sign == '-' && rational.numerator == "1" && rational.denominator == "6");

    rational = Rational_number('-', "10", "12");
    ASSERT_TRUE(rational--.numerator == "10");
    ASSERT_TRUE(rational.sign == '-' && rational.numerator == "11" && rational.denominator == "6");

    rational = Rational_number('+', "15", "12");
    ASSERT_TRUE(rational--.numerator == "15");
    ASSERT_TRUE(rational.sign == '+' && rational.numerator == "1" && rational.denominator == "4");

    rational = Rational_number('+', "12", "12");
    ASSERT_TRUE(rational--.numerator == "12");
    ASSERT_TRUE(rational.sign == '+' && rational.numerator == "0" && rational.denominator == "1");
}

TEST(Rational_number_operators_test, plus_check)
{
    auto one = Rational_number('+', "10", "12");
    auto another = Rational_number('+', "10", "12");
    auto result = one + another;
    ASSERT_TRUE(result.sign == '+' && result.numerator == "5" && result.denominator == "3");

    one = Rational_number('+', "10", "12");
    another = Rational_number('-', "10", "12");
    result = one + another;
    ASSERT_TRUE(result.sign == '+' && result.numerator == "0" && result.denominator == "1");

    one = Rational_number('+', "10", "12");
    another = Rational_number('+', "10", "24");
    result = one + another;
    ASSERT_TRUE(result.sign == '+' && result.numerator == "5" && result.denominator == "4");

    one = Rational_number('+', "5", "12");
    another = Rational_number('-', "10", "12");
    result = one + another;
    ASSERT_TRUE(result.sign == '-' && result.numerator == "5" && result.denominator == "12");

    one = Rational_number('-', "5", "12");
    another = Rational_number('-', "10", "12");
    result = one + another;
    ASSERT_TRUE(result.sign == '-' && result.numerator == "5" && result.denominator == "4");

    one = Rational_number('-', "5", "12");
    another = Rational_number('+', "10", "12");
    result = one + another;
    ASSERT_TRUE(result.sign == '+' && result.numerator == "5" && result.denominator == "12");

    one = Rational_number('-', "345", "993");
    another = Rational_number('+', "228", "432");
    result = one + another;
    ASSERT_TRUE(result.sign == '+' && result.numerator == "2149" && result.denominator == "11916");
}

TEST(Rational_number_operators_test, minus_check)
{
    auto one = Rational_number('+', "10", "12");
    auto another = Rational_number('+', "10", "12");
    auto result = one - another;
    ASSERT_TRUE(result.sign == '+' && result.numerator == "0" && result.denominator == "1");

    one = Rational_number('+', "10", "12");
    another = Rational_number('-', "10", "12");
    result = one - another;
    ASSERT_TRUE(result.sign == '+' && result.numerator == "5" && result.denominator == "3");

    one = Rational_number('+', "10", "12");
    another = Rational_number('+', "10", "24");
    result = one - another;
    ASSERT_TRUE(result.sign == '+' && result.numerator == "5" && result.denominator == "12");

    one = Rational_number('+', "5", "12");
    another = Rational_number('-', "10", "12");
    result = one - another;
    ASSERT_TRUE(result.sign == '+' && result.numerator == "5" && result.denominator == "4");

    one = Rational_number('-', "5", "12");
    another = Rational_number('-', "10", "12");
    result = one - another;
    ASSERT_TRUE(result.sign == '+' && result.numerator == "5" && result.denominator == "12");

    one = Rational_number('-', "5", "12");
    another = Rational_number('+', "10", "12");
    result = one - another;
    ASSERT_TRUE(result.sign == '-' && result.numerator == "5" && result.denominator == "4");

    one = Rational_number('-', "345", "993");
    another = Rational_number('+', "228", "432");
    result = one - another;
    ASSERT_TRUE(result.sign == '-' && result.numerator == "10429" && result.denominator == "11916");

    one = Rational_number('-', "345", "993");
    another = Rational_number('-', "228", "432");
    result = one - another;
    ASSERT_TRUE(result.sign == '+' && result.numerator == "2149" && result.denominator == "11916");
}

TEST(Rational_number_operators_test, multiply_check)
{
    auto one = Rational_number('+', "10", "12");
    auto another = Rational_number('+', "10", "12");
    auto result = one * another;
    ASSERT_TRUE(result.sign == '+' && result.numerator == "25" && result.denominator == "36");

    one = Rational_number('+', "10", "12");
    another = Rational_number('-', "10", "12");
    result = one * another;
    ASSERT_TRUE(result.sign == '-' && result.numerator == "25" && result.denominator == "36");

    one = Rational_number('+', "10", "12");
    another = Rational_number('+', "10", "24");
    result = one * another;
    ASSERT_TRUE(result.sign == '+' && result.numerator == "25" && result.denominator == "72");

    one = Rational_number('+', "5", "12");
    another = Rational_number('-', "10", "12");
    result = one * another;
    ASSERT_TRUE(result.sign == '-' && result.numerator == "25" && result.denominator == "72");

    one = Rational_number('-', "5", "12");
    another = Rational_number('-', "10", "12");
    result = one * another;
    ASSERT_TRUE(result.sign == '+' && result.numerator == "25" && result.denominator == "72");

    one = Rational_number('-', "5", "12");
    another = Rational_number('+', "10", "12");
    result = one * another;
    ASSERT_TRUE(result.sign == '-' && result.numerator == "25" && result.denominator == "72");

    one = Rational_number('-', "345", "993");
    another = Rational_number('+', "228", "432");
    result = one * another;
    ASSERT_TRUE(result.sign == '-' && result.numerator == "2185" && result.denominator == "11916");

    one = Rational_number('-', "345", "993");
    another = Rational_number('-', "228", "432");
    result = one * another;
    ASSERT_TRUE(result.sign == '+' && result.numerator == "2185" && result.denominator == "11916");
}

TEST(Rational_number_operators_test, division_check)
{
    auto one = Rational_number('+', "10", "12");
    auto another = Rational_number('+', "10", "12");
    auto result = one / another;
    ASSERT_TRUE(result.sign == '+' && result.numerator == "1" && result.denominator == "1");

    one = Rational_number('+', "10", "12");
    another = Rational_number('-', "0", "12");
    ASSERT_ANY_THROW(one / another);

    one = Rational_number('+', "10", "12");
    another = Rational_number('+', "10", "24");
    result = one / another;
    ASSERT_TRUE(result.sign == '+' && result.numerator == "2" && result.denominator == "1");

    one = Rational_number('+', "5", "12");
    another = Rational_number('-', "10", "12");
    result = one / another;
    ASSERT_TRUE(result.sign == '-' && result.numerator == "1" && result.denominator == "2");

    one = Rational_number('-', "5", "12");
    another = Rational_number('-', "10", "12");
    result = one / another;
    ASSERT_TRUE(result.sign == '+' && result.numerator == "1" && result.denominator == "2");

    one = Rational_number('-', "345", "993");
    another = Rational_number('+', "228", "432");
    result = one / another;
    ASSERT_TRUE(result.sign == '-' && result.numerator == "4140" && result.denominator == "6289");

    one = Rational_number('-', "345", "993");
    another = Rational_number('-', "228", "432");
    result = one / another;
    ASSERT_TRUE(result.sign == '+' && result.numerator == "4140" && result.denominator == "6289");
}

TEST(Rational_number_operators_test, simplify_check)
{
    auto result = Rational_number('+', "10", "12").simplify();
    ASSERT_TRUE(result.sign == '+' && result.numerator == "5" && result.denominator == "6");

    result = Rational_number('+', "10", "24").simplify();
    ASSERT_TRUE(result.sign == '+' && result.numerator == "5" && result.denominator == "12");

    result = Rational_number('-', "345", "993").simplify();
    ASSERT_TRUE(result.sign == '-' && result.numerator == "115" && result.denominator == "331");
}
