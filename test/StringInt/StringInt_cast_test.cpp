/**
 * Tests for StringInt casts.
 *
 * @author sanyavertolet
 */

#include "gtest/gtest.h"
#include "../../src/StringInt/StringInt.h"

class StringInt_cast_test : public testing::Test { };

TEST(StringInt_cast_test, StringInt_to_integets_test)
{
    StringInt rational;

    rational = StringInt("9999999999999999999999999999999999999");
    ASSERT_THROW((long long) (rational), OverflowException);
    ASSERT_THROW((int) (rational), OverflowException);
    ASSERT_THROW((short)(rational), OverflowException);
    ASSERT_THROW((char)(rational), OverflowException);

    rational = StringInt(100000000000LL);
    ASSERT_EQ((long long) (rational), 100000000000LL);
    ASSERT_THROW((int)(rational), OverflowException);
    ASSERT_THROW((short)(rational), OverflowException);
    ASSERT_THROW((char)(rational), OverflowException);

    rational = StringInt(100000LL);
    ASSERT_EQ((long long) (rational), 100000LL);
    ASSERT_EQ(int (rational), 100000LL);
    ASSERT_THROW((short)(rational), OverflowException);
    ASSERT_THROW((char)(rational), OverflowException);

    rational = StringInt(1000);
    ASSERT_EQ((long long) (rational), 1000);
    ASSERT_EQ(int (rational), 1000);
    ASSERT_EQ((short)(rational), 1000);
    ASSERT_THROW((char)(rational), OverflowException);
}

TEST(StringInt_cast_test, signed_constructor_test)
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

TEST(StringInt_cast_test, to_StringInt_cast_check)
{
    StringInt string_int;

    string_int = 5;
    ASSERT_EQ(string_int, StringInt('+', "5"));
    string_int = -5;
    ASSERT_EQ(string_int, StringInt('-', "5"));
    string_int = -123123123ll;
    ASSERT_EQ(string_int, StringInt('-', "123123123"));
    string_int = 123123123ull;
    ASSERT_EQ(string_int, StringInt('+', "123123123"));
}
