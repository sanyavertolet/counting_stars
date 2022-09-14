//
// Created by sanyavertolet on 06.09.2022.
//
#include "gtest/gtest.h"
#include "../StringInt.h"

class StringInt_operators_test : public testing::Test { };

TEST(StringInt_operators_test, comparator_check)
{
    StringInt lhs(123);
    StringInt rhs(321);
    ASSERT_TRUE(lhs < rhs);
    ASSERT_TRUE(rhs > lhs);
    ASSERT_TRUE(lhs <= rhs);
    ASSERT_TRUE(rhs >= lhs);
    ASSERT_FALSE(lhs == rhs);

    rhs = -321;
    lhs = -321;
    ASSERT_FALSE(lhs < rhs);
    ASSERT_FALSE(rhs > lhs);
    ASSERT_TRUE(lhs <= rhs);
    ASSERT_TRUE(rhs >= lhs);
    ASSERT_TRUE(lhs == rhs);
}

TEST(StringInt_operators_test, plus_check)
{
    StringInt lhs(123);
    StringInt rhs(321);
    ASSERT_EQ(lhs + rhs, 444);

    lhs = 999;
    rhs = 1;
    ASSERT_EQ(lhs + rhs, 1000);

    lhs = 90;
    rhs = 9;
    ASSERT_TRUE(lhs + rhs == 99);

    lhs = 999;
    rhs = 999;
    ASSERT_TRUE(lhs + rhs == 1998);

    lhs = 84;
    rhs = 21;
    ASSERT_TRUE(lhs + rhs == 105);
}

TEST(StringInt_operators_test, minus_check)
{
    StringInt lhs(999);
    StringInt rhs(1);
    ASSERT_EQ(lhs - rhs, 998);

    lhs = 999;
    rhs = 999;
    ASSERT_EQ(lhs - rhs, 0);

    lhs = 123;
    rhs = 321;
    ASSERT_EQ(lhs - rhs, -198);

    lhs = 0;
    rhs = 9999;
    ASSERT_EQ(lhs - rhs, -9999);
}

TEST(StringInt_operators_test, multiply_check)
{
    {
        StringInt lhs(999);
        StringInt rhs(1);
        ASSERT_EQ(lhs * rhs, 999);
    }

    {
        StringInt lhs(2);
        StringInt rhs(2);
        ASSERT_EQ(lhs * rhs, 4);
    }

    {
        StringInt lhs(99);
        StringInt rhs(99);
        ASSERT_EQ(lhs * rhs, 9801);
    }

    {
        StringInt lhs(0);
        StringInt rhs(9999);
        ASSERT_EQ(lhs * rhs, 0);
    }

    {
        StringInt lhs(99999);
        StringInt rhs(-99999);
        ASSERT_EQ(lhs * rhs, StringInt("-9999800001"));
    }

    {
        StringInt lhs("999990000000000");
        StringInt rhs("999990000000000");
        ASSERT_EQ(lhs * rhs, StringInt("999980000100000000000000000000"));
    }
}

TEST(StringInt_operators_test, division_check)
{
    {
        StringInt lhs("21");
        StringInt rhs("-21");
        ASSERT_EQ(lhs / rhs, StringInt("-1"));
    }

    {
        StringInt lhs("2121");
        StringInt rhs("21");
        ASSERT_EQ(lhs / rhs, StringInt("101"));
    }

    {
        StringInt lhs("-64825753086690");
        StringInt rhs("14946");
        ASSERT_EQ(lhs / rhs, StringInt("-4337331265"));
    }

    {
        StringInt lhs("993");
        StringInt rhs("3");
        ASSERT_EQ(lhs / rhs, StringInt("331"));
    }
}

TEST(StringInt_operators_test, gcd_check)
{
    StringInt result;

    result = gcd(64, 24);
    ASSERT_EQ(result, 8);

    result = gcd(96, 128);
    ASSERT_EQ(result, 32);

    result = gcd(22, 26);
    ASSERT_EQ(result, 2);

    result = gcd(StringInt("188748146801"), StringInt("98976967896"));
    ASSERT_EQ(result, 1);

    result = gcd(993, 432);
    ASSERT_EQ(result, 3);
}
