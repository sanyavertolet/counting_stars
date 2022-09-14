//
// Created by sanyavertolet on 06.09.2022.
//
#include "gtest/gtest.h"
#include "../StringInt.h"

class StringInt_constructor_test : public testing::Test { };

TEST(StringInt_constructor_test, unsigned_constructor_test)
{
    unsigned unsigned_value = 12321;
    StringInt from_char_string = StringInt('+', std::to_string(unsigned_value));
    StringInt from_unsigned = StringInt(unsigned_value);
    StringInt from_unsigned_long_long = StringInt(static_cast<unsigned long long>(unsigned_value));

    ASSERT_EQ(from_unsigned, from_char_string) << "Should be equal as built from the same value " << unsigned_value;
    ASSERT_EQ(from_char_string, from_unsigned_long_long) << "Should be equal as built from the same value " << unsigned_value;
}

TEST(StringInt_constructor_test, signed_constructor_test)
{
    signed signed_value = -12321;
    StringInt from_char_string = StringInt('-', std::to_string(signed_value).erase(0, 1));
    StringInt from_signed = StringInt(signed_value);
    StringInt from_signed_long_long = StringInt(static_cast<long long>(signed_value));

    ASSERT_EQ(from_char_string.get_sign(), from_signed.get_sign()) << "Should be equal as built from the same value " << signed_value;
    ASSERT_EQ(from_char_string.get_val(), from_signed.get_val()) << "Should be equal as built from the same value " << signed_value;
    ASSERT_EQ(from_char_string.get_sign(), from_signed.get_sign()) << "Should be equal as built from the same value " << signed_value;
    ASSERT_EQ(from_char_string.get_val(), from_signed.get_val()) << "Should be equal as built from the same value " << signed_value;


    ASSERT_EQ(from_char_string, from_signed_long_long) << "Should be equal as built from the same value " << signed_value;
}

TEST(StringInt_constructor_test, cast_check)
{
    StringInt string_int = 5;
    ASSERT_EQ(string_int, StringInt('+', "5"));
    string_int = -5;
    ASSERT_EQ(string_int, StringInt('-', "5"));
    string_int = -123123123ll;
    ASSERT_EQ(string_int, StringInt('-', "123123123"));
    string_int = 123123123ull;
    ASSERT_EQ(string_int, StringInt('+', "123123123"));
}
