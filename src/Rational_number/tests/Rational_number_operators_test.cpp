/**
 * Tests for Rational_number operators.
 *
 * @author sanyavertolet
 */

#include "../Rational_number.h"
#include "gtest/gtest.h"

class Rational_number_operators_test : public testing::Test { };

TEST(Rational_number_operators_test, unary_minus_operator_check)
{
    auto rational = -Rational_number("10/12");
    ASSERT_EQ(rational.get_numerator().get_sign(), '-');
    ASSERT_EQ(rational.get_numerator().get_val(), "10");
    ASSERT_EQ(rational.get_denominator().get_sign(), '+');
    ASSERT_EQ(rational.get_denominator().get_val(), "12");

    rational = -Rational_number("-10/12");
    ASSERT_EQ(rational.get_numerator().get_sign(), '+');
    ASSERT_EQ(rational.get_numerator().get_val(), "10");
    ASSERT_EQ(rational.get_denominator().get_sign(), '+');
    ASSERT_EQ(rational.get_denominator().get_val(), "12");

    rational = -(-Rational_number("+10/12"));
    ASSERT_EQ(rational.get_numerator().get_sign(), '+');
    ASSERT_EQ(rational.get_numerator().get_val(), "10");
    ASSERT_EQ(rational.get_denominator().get_sign(), '+');
    ASSERT_EQ(rational.get_denominator().get_val(), "12");
}

TEST(Rational_number_operators_test, increment_check)
{
    auto rational = ++Rational_number("10/12");
    ASSERT_EQ(rational.get_numerator().get_sign(), '+');
    ASSERT_EQ(rational.get_numerator().get_val(), "11");
    ASSERT_EQ(rational.get_denominator().get_sign(), '+');
    ASSERT_EQ(rational.get_denominator().get_val(), "6");

    rational = ++Rational_number("-10/12");
    ASSERT_EQ(rational.get_numerator().get_sign(), '+');
    ASSERT_EQ(rational.get_numerator().get_val(), "1");
    ASSERT_EQ(rational.get_denominator().get_sign(), '+');
    ASSERT_EQ(rational.get_denominator().get_val(), "6");

    rational = ++Rational_number("-13/12");
    ASSERT_EQ(rational.get_numerator().get_sign(), '-');
    ASSERT_EQ(rational.get_numerator().get_val(), "1");
    ASSERT_EQ(rational.get_denominator().get_sign(), '+');
    ASSERT_EQ(rational.get_denominator().get_val(), "12");

    rational = ++Rational_number("-12/12");
    ASSERT_EQ(rational.get_numerator().get_sign(), '+');
    ASSERT_EQ(rational.get_numerator().get_val(), "0");
    ASSERT_EQ(rational.get_denominator().get_sign(), '+');
    ASSERT_EQ(rational.get_denominator().get_val(), "1");
}

TEST(Rational_number_operators_test, decrement_check)
{
    Rational_number rational;

    rational = --Rational_number("10/12");
    ASSERT_EQ(rational.get_numerator().get_sign(), '-');
    ASSERT_EQ(rational.get_numerator().get_val(), "1");
    ASSERT_EQ(rational.get_denominator().get_sign(), '+');
    ASSERT_EQ(rational.get_denominator().get_val(), "6");

    rational = --Rational_number("-10/12");
    ASSERT_EQ(rational.get_numerator().get_sign(), '-');
    ASSERT_EQ(rational.get_numerator().get_val(), "11");
    ASSERT_EQ(rational.get_denominator().get_sign(), '+');
    ASSERT_EQ(rational.get_denominator().get_val(), "6");

    rational = --Rational_number("15/12");
    ASSERT_EQ(rational.get_numerator().get_sign(), '+');
    ASSERT_EQ(rational.get_numerator().get_val(), "1");
    ASSERT_EQ(rational.get_denominator().get_sign(), '+');
    ASSERT_EQ(rational.get_denominator().get_val(), "4");

    rational = --Rational_number("12/12");
    ASSERT_EQ(rational.get_numerator().get_sign(), '+');
    ASSERT_EQ(rational.get_numerator().get_val(), "0");
    ASSERT_EQ(rational.get_denominator().get_sign(), '+');
    ASSERT_EQ(rational.get_denominator().get_val(), "1");
}

TEST(Rational_number_operators_test, plus_check)
{
    Rational_number lhs;
    Rational_number rhs;
    Rational_number result;

    lhs = Rational_number("10/12");
    rhs = Rational_number("10/12");
    result = lhs + rhs;
    ASSERT_EQ(result.get_numerator().get_sign(), '+');
    ASSERT_EQ(result.get_numerator().get_val(), "5");
    ASSERT_EQ(result.get_denominator().get_sign(), '+');
    ASSERT_EQ(result.get_denominator().get_val(), "3");

    lhs = Rational_number("10/12");
    rhs = Rational_number("-10/12");
    result = lhs + rhs;
    ASSERT_EQ(result.get_numerator().get_sign(), '+');
    ASSERT_EQ(result.get_numerator().get_val(), "0");
    ASSERT_EQ(result.get_denominator().get_sign(), '+');
    ASSERT_EQ(result.get_denominator().get_val(), "1");

    lhs = Rational_number("10/12");
    rhs = Rational_number("10/24");
    result = lhs + rhs;
    ASSERT_EQ(result.get_numerator().get_sign(), '+');
    ASSERT_EQ(result.get_numerator().get_val(), "5");
    ASSERT_EQ(result.get_denominator().get_sign(), '+');
    ASSERT_EQ(result.get_denominator().get_val(), "4");

    lhs = Rational_number("5/12");
    rhs = Rational_number("-10/12");
    result = lhs + rhs;
    ASSERT_EQ(result.get_numerator().get_sign(), '-');
    ASSERT_EQ(result.get_numerator().get_val(), "5");
    ASSERT_EQ(result.get_denominator().get_sign(), '+');
    ASSERT_EQ(result.get_denominator().get_val(), "12");

    lhs = Rational_number("-5/12");
    rhs = Rational_number("-10/12");
    result = lhs + rhs;
    ASSERT_EQ(result.get_numerator().get_sign(), '-');
    ASSERT_EQ(result.get_numerator().get_val(), "5");
    ASSERT_EQ(result.get_denominator().get_sign(), '+');
    ASSERT_EQ(result.get_denominator().get_val(), "4");

    lhs = Rational_number("-5/12");
    rhs = Rational_number("10/12");
    result = lhs + rhs;
    ASSERT_EQ(result.get_numerator().get_sign(), '+');
    ASSERT_EQ(result.get_numerator().get_val(), "5");
    ASSERT_EQ(result.get_denominator().get_sign(), '+');
    ASSERT_EQ(result.get_denominator().get_val(), "12");

    lhs = Rational_number("-345/993");
    rhs = Rational_number("228/432");
    result = lhs + rhs;
    ASSERT_EQ(result.get_numerator().get_sign(), '+');
    ASSERT_EQ(result.get_numerator().get_val(), "2149");
    ASSERT_EQ(result.get_denominator().get_sign(), '+');
    ASSERT_EQ(result.get_denominator().get_val(), "11916");
}

TEST(Rational_number_operators_test, minus_check)
{
    Rational_number lhs;
    Rational_number rhs;
    Rational_number result;

    lhs = Rational_number("10/12");
    rhs = Rational_number("10/12");
    result = lhs - rhs;
    ASSERT_EQ(result.get_numerator().get_sign(), '+');
    ASSERT_EQ(result.get_numerator().get_val(), "0");
    ASSERT_EQ(result.get_denominator().get_sign(), '+');
    ASSERT_EQ(result.get_denominator().get_val(), "1");

    lhs = Rational_number("10/12");
    rhs = Rational_number("-10/12");
    result = lhs - rhs;
    ASSERT_EQ(result.get_numerator().get_sign(), '+');
    ASSERT_EQ(result.get_numerator().get_val(), "5");
    ASSERT_EQ(result.get_denominator().get_sign(), '+');
    ASSERT_EQ(result.get_denominator().get_val(), "3");

    lhs = Rational_number("10/12");
    rhs = Rational_number("10/24");
    result = lhs - rhs;
    ASSERT_EQ(result.get_numerator().get_sign(), '+');
    ASSERT_EQ(result.get_numerator().get_val(), "5");
    ASSERT_EQ(result.get_denominator().get_sign(), '+');
    ASSERT_EQ(result.get_denominator().get_val(), "12");

    lhs = Rational_number("5/12");
    rhs = Rational_number("-10/12");
    result = lhs - rhs;
    ASSERT_EQ(result.get_numerator().get_sign(), '+');
    ASSERT_EQ(result.get_numerator().get_val(), "5");
    ASSERT_EQ(result.get_denominator().get_sign(), '+');
    ASSERT_EQ(result.get_denominator().get_val(), "4");

    lhs = Rational_number("-5/12");
    rhs = Rational_number("-10/12");
    result = lhs - rhs;
    ASSERT_EQ(result.get_numerator().get_sign(), '+');
    ASSERT_EQ(result.get_numerator().get_val(), "5");
    ASSERT_EQ(result.get_denominator().get_sign(), '+');
    ASSERT_EQ(result.get_denominator().get_val(), "12");

    lhs = Rational_number("-5/12");
    rhs = Rational_number("10/12");
    result = lhs - rhs;
    ASSERT_EQ(result.get_numerator().get_sign(), '-');
    ASSERT_EQ(result.get_numerator().get_val(), "5");
    ASSERT_EQ(result.get_denominator().get_sign(), '+');
    ASSERT_EQ(result.get_denominator().get_val(), "4");

    lhs = Rational_number("-345/993");
    rhs = Rational_number("228/432");
    result = lhs - rhs;
    ASSERT_EQ(result.get_numerator().get_sign(), '-');
    ASSERT_EQ(result.get_numerator().get_val(), "10429");
    ASSERT_EQ(result.get_denominator().get_sign(), '+');
    ASSERT_EQ(result.get_denominator().get_val(), "11916");

    lhs = Rational_number("-345/993");
    rhs = Rational_number("-228/432");
    result = lhs - rhs;
    ASSERT_EQ(result.get_numerator().get_sign(), '+');
    ASSERT_EQ(result.get_numerator().get_val(), "2149");
    ASSERT_EQ(result.get_denominator().get_sign(), '+');
    ASSERT_EQ(result.get_denominator().get_val(), "11916");
}

TEST(Rational_number_operators_test, multiply_check)
{
    Rational_number lhs;
    Rational_number rhs;
    Rational_number result;

    lhs = Rational_number("10/12");
    rhs = Rational_number("10/12");
    result = lhs * rhs;
    ASSERT_EQ(result.get_numerator().get_sign(), '+');
    ASSERT_EQ(result.get_numerator().get_val(), "25");
    ASSERT_EQ(result.get_denominator().get_sign(), '+');
    ASSERT_EQ(result.get_denominator().get_val(), "36");

    lhs = Rational_number("10/12");
    rhs = Rational_number("-10/12");
    result = lhs * rhs;
    ASSERT_EQ(result.get_numerator().get_sign(), '-');
    ASSERT_EQ(result.get_numerator().get_val(), "25");
    ASSERT_EQ(result.get_denominator().get_sign(), '+');
    ASSERT_EQ(result.get_denominator().get_val(), "36");

    lhs = Rational_number("10/12");
    rhs = Rational_number("10/24");
    result = lhs * rhs;
    ASSERT_EQ(result.get_numerator().get_sign(), '+');
    ASSERT_EQ(result.get_numerator().get_val(), "25");
    ASSERT_EQ(result.get_denominator().get_sign(), '+');
    ASSERT_EQ(result.get_denominator().get_val(), "72");

    lhs = Rational_number("5/12");
    rhs = Rational_number("-10/12");
    result = lhs * rhs;
    ASSERT_EQ(result.get_numerator().get_sign(), '-');
    ASSERT_EQ(result.get_numerator().get_val(), "25");
    ASSERT_EQ(result.get_denominator().get_sign(), '+');
    ASSERT_EQ(result.get_denominator().get_val(), "72");

    lhs = Rational_number("-5/12");
    rhs = Rational_number("-10/12");
    result = lhs * rhs;
    ASSERT_EQ(result.get_numerator().get_sign(), '+');
    ASSERT_EQ(result.get_numerator().get_val(), "25");
    ASSERT_EQ(result.get_denominator().get_sign(), '+');
    ASSERT_EQ(result.get_denominator().get_val(), "72");

    lhs = Rational_number("-5/12");
    rhs = Rational_number("10/12");
    result = lhs * rhs;
    ASSERT_EQ(result.get_numerator().get_sign(), '-');
    ASSERT_EQ(result.get_numerator().get_val(), "25");
    ASSERT_EQ(result.get_denominator().get_sign(), '+');
    ASSERT_EQ(result.get_denominator().get_val(), "72");

    lhs = Rational_number("345/993");
    rhs = Rational_number("-228/432");
    result = lhs * rhs;
    ASSERT_EQ(result.get_numerator().get_sign(), '-');
    ASSERT_EQ(result.get_numerator().get_val(), "2185");
    ASSERT_EQ(result.get_denominator().get_sign(), '+');
    ASSERT_EQ(result.get_denominator().get_val(), "11916");

    lhs = Rational_number("-345/993");
    rhs = Rational_number("-228/432");
    result = lhs * rhs;
    ASSERT_EQ(result.get_numerator().get_sign(), '+');
    ASSERT_EQ(result.get_numerator().get_val(), "2185");
    ASSERT_EQ(result.get_denominator().get_sign(), '+');
    ASSERT_EQ(result.get_denominator().get_val(), "11916");
}

TEST(Rational_number_operators_test, division_check)
{
    Rational_number lhs;
    Rational_number rhs;
    Rational_number result;

    lhs = Rational_number("10/12");
    rhs = Rational_number("10/12");
    result = lhs / rhs;
    ASSERT_EQ(result.get_numerator().get_sign(), '+');
    ASSERT_EQ(result.get_numerator().get_val(), "1");
    ASSERT_EQ(result.get_denominator().get_sign(), '+');
    ASSERT_EQ(result.get_denominator().get_val(), "1");

    lhs = Rational_number("10/12");
    rhs = Rational_number("-0/12");
    ASSERT_THROW(lhs / rhs, DivisionByZeroException);

    lhs = Rational_number("10/12");
    rhs = Rational_number("10/24");
    result = lhs / rhs;
    ASSERT_EQ(result.get_numerator().get_sign(), '+');
    ASSERT_EQ(result.get_numerator().get_val(), "2");
    ASSERT_EQ(result.get_denominator().get_sign(), '+');
    ASSERT_EQ(result.get_denominator().get_val(), "1");

    lhs = Rational_number("5/12");
    rhs = Rational_number("-10/12");
    result = lhs / rhs;
    ASSERT_EQ(result.get_numerator().get_sign(), '-');
    ASSERT_EQ(result.get_numerator().get_val(), "1");
    ASSERT_EQ(result.get_denominator().get_sign(), '+');
    ASSERT_EQ(result.get_denominator().get_val(), "2");

    lhs = Rational_number("-5/12");
    rhs = Rational_number("-10/12");
    result = lhs / rhs;
    ASSERT_EQ(result.get_numerator().get_sign(), '+');
    ASSERT_EQ(result.get_numerator().get_val(), "1");
    ASSERT_EQ(result.get_denominator().get_sign(), '+');
    ASSERT_EQ(result.get_denominator().get_val(), "2");

    lhs = Rational_number("-345/993");
    rhs = Rational_number("228/432");
    result = lhs / rhs;
    ASSERT_EQ(result.get_numerator().get_sign(), '-');
    ASSERT_EQ(result.get_numerator().get_val(), "4140");
    ASSERT_EQ(result.get_denominator().get_sign(), '+');
    ASSERT_EQ(result.get_denominator().get_val(), "6289");

    lhs = Rational_number("-345/993");
    rhs = Rational_number("-228/432");
    result = lhs / rhs;
    ASSERT_EQ(result.get_numerator().get_sign(), '+');
    ASSERT_EQ(result.get_numerator().get_val(), "4140");
    ASSERT_EQ(result.get_denominator().get_sign(), '+');
    ASSERT_EQ(result.get_denominator().get_val(), "6289");
}

TEST(Rational_number_operators_test, to_string_and_back_check)
{
    Rational_number result;

    result = std::string(Rational_number("10/12"));
    ASSERT_EQ(result.get_numerator().get_sign(), '+');
    ASSERT_EQ(result.get_numerator().get_val(), "10");
    ASSERT_EQ(result.get_denominator().get_sign(), '+');
    ASSERT_EQ(result.get_denominator().get_val(), "12");

    result = std::string(Rational_number("-10/12"));
    ASSERT_EQ(result.get_numerator().get_sign(), '-');
    ASSERT_EQ(result.get_numerator().get_val(), "10");
    ASSERT_EQ(result.get_denominator().get_sign(), '+');
    ASSERT_EQ(result.get_denominator().get_val(), "12");

    result = std::string(Rational_number("0/999999999"));
    ASSERT_EQ(result.get_numerator().get_sign(), '+');
    ASSERT_EQ(result.get_numerator().get_val(), "0");
    ASSERT_EQ(result.get_denominator().get_sign(), '+');
    ASSERT_EQ(result.get_denominator().get_val(), "1");

    result = std::string(Rational_number("-1/-2"));
    ASSERT_EQ(result.get_numerator().get_sign(), '+');
    ASSERT_EQ(result.get_numerator().get_val(), "1");
    ASSERT_EQ(result.get_denominator().get_sign(), '+');
    ASSERT_EQ(result.get_denominator().get_val(), "2");
}
