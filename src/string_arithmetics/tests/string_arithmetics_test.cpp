//
// Created by sanyavertolet on 06.09.2022.
//
#include "gtest/gtest.h"
#include "../string_arithmetics.h"

class string_arithmetics_test : public testing::Test { };

TEST(string_arithmetics_test, comparator_check)
{
    ASSERT_TRUE(string_arithmetics::compare_as_numbers("123", "321") == string_arithmetics::Comparator_result::LESS);
    ASSERT_TRUE(string_arithmetics::compare_as_numbers("9876543210123456789", "9876543210123456789") == string_arithmetics::Comparator_result::EQUAL);
    ASSERT_TRUE(string_arithmetics::compare_as_numbers("1249", "1239") == string_arithmetics::Comparator_result::GREATER);
    ASSERT_TRUE(string_arithmetics::compare_as_numbers("9", "11") == string_arithmetics::Comparator_result::LESS);
    ASSERT_ANY_THROW(string_arithmetics::compare_as_numbers("", "1239"));
    ASSERT_ANY_THROW(string_arithmetics::compare_as_numbers("1", ""));
}

TEST(string_arithmetics_test, char_plus_check)
{
    auto overflow = 0;
    auto result = string_arithmetics::plus('1', '2', overflow);
    ASSERT_TRUE(result == '3' && overflow == 0);

    overflow = 0;
    result = string_arithmetics::plus('9', '9', overflow);
    ASSERT_TRUE(result == '8' && overflow == 1);

    overflow = 1;
    result = string_arithmetics::plus('9', '9', overflow);
    ASSERT_TRUE(result == '9' && overflow == 1);

    overflow = 1;
    result = string_arithmetics::plus('2', '2', overflow);
    ASSERT_TRUE(result == '5' && overflow == 0);
}

TEST(string_arithmetics_test, char_minus_check)
{
    int underflow;
    char result;

    underflow = 0;
    result = string_arithmetics::minus('1', '2', underflow);
    ASSERT_TRUE(result == '9' && underflow == 1);

    underflow = 0;
    result = string_arithmetics::minus('8', '7', underflow);
    ASSERT_TRUE(result == '1' && underflow == 0);

    underflow = 1;
    result = string_arithmetics::minus('3', '2', underflow);
    ASSERT_TRUE(result == '0' && underflow == 0);

    underflow = 1;
    result = string_arithmetics::minus('9', '9', underflow);
    ASSERT_TRUE(result == '9' && underflow == 1);

    underflow = 0;
    result = string_arithmetics::minus('1', '3', underflow);
    ASSERT_TRUE(result == '8' && underflow == 1);

    underflow = 1;
    result = string_arithmetics::minus('2', '2', underflow);
    ASSERT_TRUE(result == '9' && underflow == 1);

    underflow = 1;
    result = string_arithmetics::minus('3', '1', underflow);
    ASSERT_TRUE(result == '1' && underflow == 0);
}

TEST(string_arithmetics_test, char_multiply_check)
{
    int overflow;
    char result;

    overflow = 0;
    result = string_arithmetics::multiply('2', '2', overflow);
    ASSERT_TRUE(result == '4' && overflow == 0);

    overflow = 4;
    result = string_arithmetics::multiply('2', '2', overflow);
    ASSERT_TRUE(result == '8' && overflow == 0);

    overflow = 4;
    result = string_arithmetics::multiply('4', '4', overflow);
    ASSERT_TRUE(result == '0' && overflow == 2);

    overflow = 9;
    result = string_arithmetics::multiply('9', '9', overflow);
    ASSERT_TRUE(result == '0' && overflow == 9);

    overflow = 8;
    result = string_arithmetics::multiply('9', '0', overflow);
    ASSERT_TRUE(result == '8' && overflow == 0);
}

TEST(string_arithmetics_test, semi_multiply_check)
{
    std::string result;

    result = string_arithmetics::multiply("48", '2');
    ASSERT_TRUE(result == "96");

    result = string_arithmetics::multiply("1000", '5');
    ASSERT_TRUE(result == "5000");

    result = string_arithmetics::multiply("999", '9');
    ASSERT_TRUE(result == "8991");

    result = string_arithmetics::multiply("999", '0');
    ASSERT_TRUE(result == "0");

    result = string_arithmetics::multiply("0", '9');
    ASSERT_TRUE(result == "0");
}

TEST(string_arithmetics_test, string_plus_check)
{
    std::string result;

    result = string_arithmetics::plus("123", "321");
    ASSERT_TRUE(result == "444");

    result = string_arithmetics::plus("999", "1");
    ASSERT_TRUE(result == "1000");

    result = string_arithmetics::plus("90", "9");
    ASSERT_TRUE(result == "99");

    result = string_arithmetics::plus("999", "999");
    ASSERT_TRUE(result == "1998");

    result = string_arithmetics::plus("84", "21");
    ASSERT_TRUE(result == "105");
}

TEST(string_arithmetics_test, string_minus_check)
{
    std::string result;

    result = string_arithmetics::minus("999", "1");
    ASSERT_TRUE(result == "998");

    result = string_arithmetics::minus("999", "999");
    ASSERT_TRUE(result == "0");

    result = string_arithmetics::minus("123", "321");
    ASSERT_TRUE(result == "198");

    result = string_arithmetics::minus("0", "9999");
    ASSERT_TRUE(result == "9999");
}

TEST(string_arithmetics_test, string_multiply_check)
{
    std::string result;

    result = string_arithmetics::multiply("999", "1");
    ASSERT_TRUE(result == "999");

    result = string_arithmetics::multiply("2", "2");
    ASSERT_TRUE(result == "4");

    result = string_arithmetics::multiply("99", "99");
    ASSERT_TRUE(result == "9801");

    result = string_arithmetics::multiply("0", "9999");
    ASSERT_TRUE(result == "0");

    result = string_arithmetics::multiply("99999", "99999");
    ASSERT_TRUE(result == "9999800001");

    result = string_arithmetics::multiply("9999900000", "9999900000");
    ASSERT_TRUE(result == "99998000010000000000");

    result = string_arithmetics::multiply("999990000000000", "999990000000000");
    ASSERT_TRUE(result == "999980000100000000000000000000");
}

TEST(string_arithmetics_test, gcd_check)
{
    std::string result;

    result = string_arithmetics::gcd("64", "24");
    ASSERT_TRUE(result == "8");

    result = string_arithmetics::gcd("96", "128");
    ASSERT_TRUE(result == "32");

    result = string_arithmetics::gcd("22", "26");
    ASSERT_TRUE(result == "2");

    result = string_arithmetics::gcd("188748146801", "98976967896");
    ASSERT_TRUE(result == "1");

    result = string_arithmetics::gcd("993", "432");
    ASSERT_TRUE(result == "3");
}

TEST(string_arithmetics_test, division_step_check)
{
    {
        auto [result, to_subtract] = string_arithmetics::division_step("21", "21");
        ASSERT_TRUE(result == "1" && to_subtract == "21");
    }

    {
        auto [result, to_subtract] = string_arithmetics::division_step("22", "21");
        ASSERT_TRUE(result == "1" && to_subtract == "21");
    }

    {
        auto [result, to_subtract] = string_arithmetics::division_step("187", "21");
        ASSERT_TRUE(result == "8" && to_subtract == "168");
    }

    {
        auto [result, to_subtract] = string_arithmetics::division_step("99", "10");
        ASSERT_TRUE(result == "9" && to_subtract == "90");
    }

    {
        auto [result, to_subtract] = string_arithmetics::division_step("3", "3");
        ASSERT_TRUE(result == "1" && to_subtract == "3");
    }
}

TEST(string_arithmetics_test, divide_as_integers_check)
{
    std::string result;

    result = string_arithmetics::divide_as_integers("21", "21");
    ASSERT_TRUE(result == "1");

    result = string_arithmetics::divide_as_integers("2121", "21");
    ASSERT_TRUE(result == "101");

    result = string_arithmetics::divide_as_integers("64825753086690", "14946");
    ASSERT_TRUE(result == "4337331265");

    result = string_arithmetics::divide_as_integers("993", "3");
    ASSERT_TRUE(result == "331");
}
