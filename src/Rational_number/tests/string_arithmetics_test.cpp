//
// Created by sanyavertolet on 06.09.2022.
//
#include "gtest/gtest.h"

int compare_as_numbers(const std::string &one, const std::string &another);

char plus(char one, char another, int &overflow);
char minus(char one, char another, int &underflow);
char multiply(char one, char another, int &overflow);

std::string multiply(std::string number, char multiplier);

std::string plus(std::string one, std::string another);
std::string minus(std::string one, std::string another);
std::string multiply(std::string one, const std::string& another);

class string_arithmetics_test : public testing::Test { };

TEST(string_arithmetics_test, comparator_check)
{
    ASSERT_TRUE(compare_as_numbers("123", "321") == -1);
    ASSERT_TRUE(compare_as_numbers("9876543210123456789", "9876543210123456789") == 0);
    ASSERT_TRUE(compare_as_numbers("1249", "1239") == 1);
    ASSERT_TRUE(compare_as_numbers("9", "11") == -1);
    ASSERT_ANY_THROW(compare_as_numbers("", "1239"));
    ASSERT_ANY_THROW(compare_as_numbers("1", ""));
}

TEST(string_arithmetics_test, char_plus_check)
{
    auto overflow = 0;
    auto result = plus('1', '2', overflow);
    ASSERT_TRUE(result == '3' && overflow == 0);

    overflow = 0;
    result = plus('9', '9', overflow);
    ASSERT_TRUE(result == '8' && overflow == 1);

    overflow = 1;
    result = plus('9', '9', overflow);
    ASSERT_TRUE(result == '9' && overflow == 1);

    overflow = 1;
    result = plus('2', '2', overflow);
    ASSERT_TRUE(result == '5' && overflow == 0);
}

TEST(string_arithmetics_test, char_minus_check)
{
    int underflow;
    char result;

    underflow = 0;
    result = minus('1', '2', underflow);
    ASSERT_TRUE(result == '9' && underflow == 1);

    underflow = 0;
    result = minus('8', '7', underflow);
    ASSERT_TRUE(result == '1' && underflow == 0);

    underflow = 1;
    result = minus('3', '2', underflow);
    ASSERT_TRUE(result == '0' && underflow == 0);

    underflow = 1;
    result = minus('9', '9', underflow);
    ASSERT_TRUE(result == '9' && underflow == 1);

    underflow = 0;
    result = minus('1', '3', underflow);
    ASSERT_TRUE(result == '8' && underflow == 1);

    underflow = 1;
    result = minus('2', '2', underflow);
    ASSERT_TRUE(result == '9' && underflow == 1);

    underflow = 1;
    result = minus('3', '1', underflow);
    ASSERT_TRUE(result == '1' && underflow == 0);
}

TEST(string_arithmetics_test, char_multiply_check)
{
    int overflow;
    char result;

    overflow = 0;
    result = multiply('2', '2', overflow);
    ASSERT_TRUE(result == '4' && overflow == 0);

    overflow = 4;
    result = multiply('2', '2', overflow);
    ASSERT_TRUE(result == '8' && overflow == 0);

    overflow = 4;
    result = multiply('4', '4', overflow);
    ASSERT_TRUE(result == '0' && overflow == 2);

    overflow = 9;
    result = multiply('9', '9', overflow);
    ASSERT_TRUE(result == '0' && overflow == 9);

    overflow = 8;
    result = multiply('9', '0', overflow);
    ASSERT_TRUE(result == '8' && overflow == 0);
}

TEST(string_arithmetics_test, semi_multiply_check)
{
    std::string result;

    result = multiply("48", '2');
    ASSERT_TRUE(result == "96");

    result = multiply("1000", '5');
    ASSERT_TRUE(result == "5000");

    result = multiply("999", '9');
    ASSERT_TRUE(result == "8991");

    result = multiply("999", '0');
    ASSERT_TRUE(result == "0");

    result = multiply("0", '9');
    ASSERT_TRUE(result == "0");
}

TEST(string_arithmetics_test, string_plus_check)
{
    std::string result;

    result = plus("123", "321");
    ASSERT_TRUE(result == "444");

    result = plus("999", "1");
    ASSERT_TRUE(result == "1000");

    result = plus("90", "9");
    ASSERT_TRUE(result == "99");

    result = plus("999", "999");
    ASSERT_TRUE(result == "1998");
}

TEST(string_arithmetics_test, string_minus_check)
{
    std::string result;

    result = minus("999", "1");
    ASSERT_TRUE(result == "998");

    result = minus("999", "999");
    ASSERT_TRUE(result == "0");

    result = minus("123", "321");
    ASSERT_TRUE(result == "198");

    result = minus("0", "9999");
    ASSERT_TRUE(result == "9999");
}

TEST(string_arithmetics_test, string_multiply_check)
{
    std::string result;

    result = multiply("999", "1");
    ASSERT_TRUE(result == "999");

    result = multiply("2", "2");
    ASSERT_TRUE(result == "4");

    result = multiply("99", "99");
    ASSERT_TRUE(result == "9801");

    result = multiply("0", "9999");
    ASSERT_TRUE(result == "0");

    result = multiply("99999", "99999");
    ASSERT_TRUE(result == "9999800001");

    result = multiply("9999900000", "9999900000");
    ASSERT_TRUE(result == "99998000010000000000");

    result = multiply("999990000000000", "999990000000000");
    ASSERT_TRUE(result == "999980000100000000000000000000");
}
