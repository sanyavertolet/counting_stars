//
// Created by sanyavertolet on 06.09.2022.
//
#include "../Rational_number.h"
#include "gtest/gtest.h"

class Rational_number_constructor_test : public testing::Test { };

TEST(Rational_number_constructor_test, null_is_null)
{
    Rational_number null_rational = 0;
    StringInt null_numerator = null_rational.get_numerator();
    StringInt null_denominator = null_rational.get_denominator();
    ASSERT_EQ(null_numerator.get_sign(), '+') << "Sign of null should be +, got " << null_numerator.get_sign();
    ASSERT_EQ(null_numerator.get_val(), "0") << "Numerator of null should be 0, got " << null_numerator.get_val();
    ASSERT_EQ(null_denominator.get_sign(), '+') << "Sign of denominator should always be +, got " << null_denominator.get_sign();
    ASSERT_EQ(null_denominator.get_val(), "1") << "Denominator of null should be 1, got " << null_denominator.get_val();
}

TEST(Rational_number_constructor_test, simple_constructor_check)
{
    auto number = Rational_number(StringInt("123"), StringInt("321"));
    ASSERT_EQ(number.get_numerator().get_sign(), '+') << "Got " << number.get_numerator().get_sign() << ", should be +";
    ASSERT_EQ(number.get_numerator().get_val(), "123") << "Got " << number.get_numerator().get_val() << ", should be 123";
    ASSERT_EQ(number.get_denominator().get_sign(), '+') << "Got " << number.get_denominator().get_sign() << ", should be +";
    ASSERT_EQ(number.get_denominator().get_val(), "321") << "Got " << number.get_denominator().get_val() << ", should be 321";

    number = Rational_number(StringInt("-123"), StringInt("-321"));
    ASSERT_EQ(number.get_numerator().get_sign(), '+') << "Got " << number.get_numerator().get_sign() << ", should be +";
    ASSERT_EQ(number.get_numerator().get_val(), "123") << "Got " << number.get_numerator().get_val() << ", should be 123";
    ASSERT_EQ(number.get_denominator().get_sign(), '+') << "Got " << number.get_denominator().get_sign() << ", should be +";
    ASSERT_EQ(number.get_denominator().get_val(), "321") << "Got " << number.get_denominator().get_val() << ", should be 321";

    number = Rational_number(StringInt("-123"), StringInt("321"));
    ASSERT_EQ(number.get_numerator().get_sign(), '-') << "Got " << number.get_numerator().get_sign() << ", should be -";
    ASSERT_EQ(number.get_numerator().get_val(), "123") << "Got " << number.get_numerator().get_val() << ", should be 123";
    ASSERT_EQ(number.get_denominator().get_sign(), '+') << "Got " << number.get_denominator().get_sign() << ", should be +";
    ASSERT_EQ(number.get_denominator().get_val(), "321") << "Got " << number.get_denominator().get_val() << ", should be 321";

    number = Rational_number(StringInt("123"), StringInt("-321"));
    ASSERT_EQ(number.get_numerator().get_sign(), '-') << "Got " << number.get_numerator().get_sign() << ", should be -";
    ASSERT_EQ(number.get_numerator().get_val(), "123") << "Got " << number.get_numerator().get_val() << ", should be 123";
    ASSERT_EQ(number.get_denominator().get_sign(), '+') << "Got " << number.get_denominator().get_sign() << ", should be +";
    ASSERT_EQ(number.get_denominator().get_val(), "321") << "Got " << number.get_denominator().get_val() << ", should be 321";
}

TEST(Rational_number_constructor_test, from_string)
{
    auto number = Rational_number("-111/123");
    ASSERT_EQ(number.get_numerator().get_sign(), '-') << "Got " << number.get_numerator().get_sign() << ", should be -";
    ASSERT_EQ(number.get_numerator().get_val(), "111") << "Got " << number.get_numerator().get_val() << ", should be 111";
    ASSERT_EQ(number.get_denominator().get_sign(), '+') << "Got " << number.get_denominator().get_sign() << ", should be +";
    ASSERT_EQ(number.get_denominator().get_val(), "123") << "Got " << number.get_denominator().get_val() << ", should be 123";

    number = Rational_number("123.321");
    ASSERT_EQ(number.get_numerator().get_sign(), '+') << "Got " << number.get_numerator().get_sign() << ", should be +";
    ASSERT_EQ(number.get_numerator().get_val(), "123321") << "Got " << number.get_numerator().get_val() << ", should be 123321";
    ASSERT_EQ(number.get_denominator().get_sign(), '+') << "Got " << number.get_denominator().get_sign() << ", should be +";
    ASSERT_EQ(number.get_denominator().get_val(), "1000") << "Got " << number.get_denominator().get_val() << ", should be 1000";

    number = Rational_number("228");
    ASSERT_EQ(number.get_numerator().get_sign(), '+') << "Got " << number.get_numerator().get_sign() << ", should be +";
    ASSERT_EQ(number.get_numerator().get_val(), "228") << "Got " << number.get_numerator().get_val() << ", should be 228";
    ASSERT_EQ(number.get_denominator().get_sign(), '+') << "Got " << number.get_denominator().get_sign() << ", should be +";
    ASSERT_EQ(number.get_denominator().get_val(), "1") << "Got " << number.get_denominator().get_val() << ", should be 1";


    ASSERT_ANY_THROW(Rational_number("-1/-1"));
    ASSERT_ANY_THROW(Rational_number("0/0"));
    ASSERT_ANY_THROW(Rational_number("/0"));
    ASSERT_ANY_THROW(Rational_number("-1/"));
    ASSERT_ANY_THROW(Rational_number("/"));
}

TEST(Rational_number_constructor_test, from_pair)
{
    auto number = Rational_number(1, 2);
    ASSERT_EQ(number.get_numerator().get_sign(), '+') << "Got " << number.get_numerator().get_sign() << ", should be +";
    ASSERT_EQ(number.get_numerator().get_val(), "1") << "Got " << number.get_numerator().get_val() << ", should be 1";
    ASSERT_EQ(number.get_denominator().get_sign(), '+') << "Got " << number.get_denominator().get_sign() << ", should be +";
    ASSERT_EQ(number.get_denominator().get_val(), "2") << "Got " << number.get_denominator().get_val() << ", should be 2";

    number = Rational_number(-4, 8);
    ASSERT_EQ(number.get_numerator().get_sign(), '-') << "Got " << number.get_numerator().get_sign() << ", should be -";
    ASSERT_EQ(number.get_numerator().get_val(), "4") << "Got " << number.get_numerator().get_val() << ", should be 4";
    ASSERT_EQ(number.get_denominator().get_sign(), '+') << "Got " << number.get_denominator().get_sign() << ", should be +";
    ASSERT_EQ(number.get_denominator().get_val(), "8") << "Got " << number.get_denominator().get_val() << ", should be 8";

    number = Rational_number(-0, 1);
    ASSERT_EQ(number.get_numerator().get_sign(), '+') << "Got " << number.get_numerator().get_sign() << ", should be +";
    ASSERT_EQ(number.get_numerator().get_val(), "0") << "Got " << number.get_numerator().get_val() << ", should be 1";
    ASSERT_EQ(number.get_denominator().get_sign(), '+') << "Got " << number.get_denominator().get_sign() << ", should be +";
    ASSERT_EQ(number.get_denominator().get_val(), "1") << "Got " << number.get_denominator().get_val() << ", should be 1";

    ASSERT_ANY_THROW(Rational_number(0, 0));
}

TEST(Rational_number_constructor_test, from_int)
{
    auto number = Rational_number(1);
    ASSERT_EQ(number.get_numerator().get_sign(), '+') << "Got " << number.get_numerator().get_sign() << ", should be +";
    ASSERT_EQ(number.get_numerator().get_val(), "1") << "Got " << number.get_numerator().get_val() << ", should be 1";
    ASSERT_EQ(number.get_denominator().get_sign(), '+') << "Got " << number.get_denominator().get_sign() << ", should be +";
    ASSERT_EQ(number.get_denominator().get_val(), "1") << "Got " << number.get_denominator().get_val() << ", should be 1";

    number = Rational_number(2);
    ASSERT_EQ(number.get_numerator().get_sign(), '+') << "Got " << number.get_numerator().get_sign() << ", should be +";
    ASSERT_EQ(number.get_numerator().get_val(), "2") << "Got " << number.get_numerator().get_val() << ", should be 2";
    ASSERT_EQ(number.get_denominator().get_sign(), '+') << "Got " << number.get_denominator().get_sign() << ", should be +";
    ASSERT_EQ(number.get_denominator().get_val(), "1") << "Got " << number.get_denominator().get_val() << ", should be 1";

    number = Rational_number(-1);
    ASSERT_EQ(number.get_numerator().get_sign(), '-') << "Got " << number.get_numerator().get_sign() << ", should be -";
    ASSERT_EQ(number.get_numerator().get_val(), "1") << "Got " << number.get_numerator().get_val() << ", should be 1";
    ASSERT_EQ(number.get_denominator().get_sign(), '+') << "Got " << number.get_denominator().get_sign() << ", should be +";
    ASSERT_EQ(number.get_denominator().get_val(), "1") << "Got " << number.get_denominator().get_val() << ", should be 1";
}
