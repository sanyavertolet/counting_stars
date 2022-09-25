/**
 * Tests for Complex_number constructors.
 *
 * @author sanyavertolet
 */

#include "../Complex_number.h"
#include "gtest/gtest.h"

class Complex_number_constructor_test : public testing::Test { };

TEST(Complex_number_constructor_test, constructor_check)
{
    auto number1 = Complex_number<int>(321);
    ASSERT_EQ(number1.get_re(), 321);
    ASSERT_EQ(number1.get_im(), 0.0);
    ASSERT_EQ(typeid(number1.get_re()), typeid(int));
    ASSERT_EQ(typeid(number1.get_im()), typeid(double));

    auto number2 = Complex_number<long double, bool>(321.123, false);
    ASSERT_EQ(number2.get_re(), 321.123);
    ASSERT_EQ(number2.get_im(), false);
    ASSERT_EQ(typeid(number2.get_re()), typeid(long double));
    ASSERT_EQ(typeid(number2.get_im()), typeid(false));

    auto number3 = Complex_number();
    ASSERT_EQ(number3.get_re(), 0.0);
    ASSERT_EQ(number3.get_im(), 0.0);
    ASSERT_EQ(typeid(number3.get_re()), typeid(double));
    ASSERT_EQ(typeid(number3.get_im()), typeid(double));
}

TEST(Complex_number_constructor_test, copy_constructor_check)
{
#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedValue"
#pragma clang diagnostic pop
    Complex_number number = Complex_number<long double, bool>(321.123, false);
    auto result(number);
    ASSERT_EQ(result.get_re(), 321.123);
    ASSERT_EQ(result.get_im(), false);
}


TEST(Complex_number_constructor_test, copy_operator_check)
{
#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedValue"
    auto number1 = Complex_number<int>(321);
#pragma clang diagnostic pop
    auto number2 = Complex_number<long double, bool>(321.123, false);
    number1 = number2;
    ASSERT_EQ(number1.get_re(), 321);
    ASSERT_EQ(number1.get_im(), 0.0);
}
