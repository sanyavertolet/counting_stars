/**
 * Tests for Complex_number operators.
 *
 * @author sanyavertolet
 */

#include "../../src/Complex_number/Complex_number.h"
#include "../../src/StringInt/StringInt.h"
#include "../../src/Rational_number/Rational_number.h"
#include "gtest/gtest.h"

class Complex_number_operators_test : public testing::Test { };

TEST(Complex_number_operators_test, plus_check)
{
    Complex_number<StringInt, Rational_number> lhs(StringInt(1), Rational_number("-5/7"));
    Complex_number<StringInt, Rational_number> rhs(StringInt("-33333333333333333"), Rational_number("8/14"));
    auto result = lhs + rhs;

    ASSERT_EQ(result.get_re(), StringInt("-33333333333333332"));
    ASSERT_EQ(result.get_im(), Rational_number("-1/7"));
}

TEST(Complex_number_operators_test, minus_check)
{
    Complex_number<StringInt, Rational_number> lhs(StringInt(1), Rational_number("-5/7"));
    Complex_number<StringInt, Rational_number> rhs(StringInt("-33333333333333333"), Rational_number("8/14"));
    auto result = lhs - rhs;

    ASSERT_EQ(result.get_re(), StringInt("33333333333333334"));
    ASSERT_EQ(result.get_im(), Rational_number("-9/7"));
}

TEST(Complex_number_operators_test, multiply_check)
{
    Complex_number<StringInt, Rational_number> lhs(StringInt(1), Rational_number("-5/7"));
    Complex_number<StringInt, Rational_number> rhs(StringInt("-3"), Rational_number("8/14"));
    auto result = lhs * rhs;

    ASSERT_EQ(typeid(result.get_re()), typeid(Rational_number));
    ASSERT_EQ(result.get_re().get_numerator(), StringInt("-127"));
    ASSERT_EQ(result.get_re().get_denominator(), StringInt("49"));
    ASSERT_EQ(typeid(result.get_im()), typeid(Rational_number));
    ASSERT_EQ(result.get_im().get_numerator(), StringInt("19"));
    ASSERT_EQ(result.get_im().get_denominator(), StringInt("7"));
}

TEST(Complex_number_operators_test, division_check)
{
    Complex_number<StringInt, Rational_number> lhs(StringInt(1), Rational_number("-5/7"));
    Complex_number<StringInt, Rational_number> rhs(StringInt("-2"), Rational_number("8/14"));
    auto result = lhs / rhs;

    ASSERT_EQ(result.get_re(), Rational_number("-59/106"));
    ASSERT_EQ(result.get_im(), Rational_number("21/106"));
}

TEST(Complex_number_operators_test, compare_check)
{
    Complex_number<StringInt, Rational_number> lhs(StringInt(1), Rational_number("-5/7"));
    Complex_number<StringInt, Rational_number> rhs(StringInt("-2"), Rational_number("8/14"));

    ASSERT_FALSE(lhs == rhs);
    ASSERT_TRUE(lhs != rhs);
    ASSERT_TRUE(lhs <= rhs);
    ASSERT_FALSE(lhs >= rhs);
    ASSERT_TRUE(lhs < rhs);
    ASSERT_FALSE(lhs > rhs);
}

