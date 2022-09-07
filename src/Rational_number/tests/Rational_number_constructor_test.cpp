//
// Created by sanyavertolet on 06.09.2022.
//
#include "../Rational_number.h"
#include "gtest/gtest.h"

class Rational_number_constructor_test : public testing::Test { };

TEST(Rational_number_constructor_test, null_is_null)
{
    auto null_rational = Rational_number::null();
    ASSERT_TRUE(null_rational.sign == '+' && null_rational.numerator == "0" && null_rational.denominator == "1");
}

TEST(Rational_number_constructor_test, simple_constructor_check)
{
    auto number = Rational_number('-', "123", "321");
    ASSERT_TRUE(number.sign == '-' && number.numerator == "123" && number.denominator == "321");
    ASSERT_ANY_THROW(Rational_number('1', "123", "321"));
    ASSERT_ANY_THROW(Rational_number('-', "", "321"));
    ASSERT_ANY_THROW(Rational_number('+', "1", "0"));
}

TEST(Rational_number_constructor_test, from_string)
{
    auto rational = Rational_number("-111/123");
    ASSERT_TRUE(rational.sign == '-' && rational.numerator == "111" && rational.denominator == "123");

    rational = Rational_number("123.321");
    ASSERT_TRUE(rational.sign == '+' && rational.numerator == "123321" && rational.denominator == "1000");

    rational = Rational_number("228");
    ASSERT_TRUE(rational.sign == '+' && rational.numerator == "228" && rational.denominator == "1");

    ASSERT_ANY_THROW(Rational_number("-1/-1"));
    ASSERT_ANY_THROW(Rational_number("0/0"));
    ASSERT_ANY_THROW(Rational_number("/0"));
    ASSERT_ANY_THROW(Rational_number("-1/"));
    ASSERT_ANY_THROW(Rational_number("/"));
}

TEST(Rational_number_constructor_test, from_pair)
{
    auto rational = Rational_number(1, 2);
    ASSERT_TRUE(rational.sign == '+' && rational.numerator == "1" && rational.denominator == "2");

    rational = Rational_number(-4, 8);
    ASSERT_TRUE(rational.sign == '-' && rational.numerator == "4" && rational.denominator == "8");

    rational = Rational_number(-0, 1);
    ASSERT_TRUE(rational.sign == '+' && rational.numerator == "0" && rational.denominator == "1");

    ASSERT_ANY_THROW(Rational_number(0, 0));
}

TEST(Rational_number_constructor_test, from_int)
{
    auto rational = Rational_number(1);
    ASSERT_TRUE(rational.sign == '+' && rational.numerator == "1" && rational.denominator == "1");

    rational = Rational_number(2);
    ASSERT_TRUE(rational.sign == '+' && rational.numerator == "2" && rational.denominator == "1");

    rational = Rational_number(-1);
    ASSERT_TRUE(rational.sign == '-' && rational.numerator == "1" && rational.denominator == "1");

    rational = Rational_number(0);
    ASSERT_TRUE(rational.sign == '+' && rational.numerator == "0" && rational.denominator == "1");
}
