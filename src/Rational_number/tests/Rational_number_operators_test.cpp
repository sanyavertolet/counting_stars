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
