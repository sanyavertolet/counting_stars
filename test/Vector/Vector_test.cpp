/**
 * Tests for [Vector].
 *
 * @author sanyavertolet
 */

#include "../../src/StringInt/StringInt.h"
#include "../../src/Rational_number/Rational_number.h"
#include "../../src/Complex_number/Complex_number.h"
#include "../../src/Vector/Vector.h"

#include "../../src/utils.h"

#include "gtest/gtest.h"

class Vector_test : public testing::Test { };

std::filesystem::path test_path = project_path / "test" / "Vector";

TEST(Vector_test, int_test)
{
    Vector<int> int_vector;
    int_vector(1) = 5;
    int_vector(2) = 6;

    ASSERT_EQ(int_vector(0), 0);
    ASSERT_EQ(int_vector(1), 5);
    ASSERT_EQ(int_vector(2), 6);
    ASSERT_EQ(int_vector(3), 0);
    ASSERT_EQ(int_vector.get_size(), 2);
    ASSERT_EQ(int_vector.get_capacity(), -1);
    int_vector.set_precision(10.0);
    ASSERT_EQ(int_vector.get_size(), 0);
}

TEST(Vector_test, long_double_test)
{
    Vector<long double> long_double_vector;
    long_double_vector(StringInt("9999999999999999999")) = 99.5;
    long_double_vector(2) = 0.00004;

    ASSERT_EQ(long_double_vector(0), 0);
    ASSERT_EQ(long_double_vector(1), 0);
    ASSERT_EQ(long_double_vector(2), 0.00004);
    ASSERT_EQ(long_double_vector(3), 0);
    ASSERT_EQ(long_double_vector(StringInt("9999999999999999999")), 99.5);
    ASSERT_EQ(long_double_vector.get_size(), 2);
    ASSERT_EQ(long_double_vector.get_capacity(), -1);
    long_double_vector.set_precision(10.0);
    ASSERT_EQ(long_double_vector.get_size(), 1);
}

TEST(Vector_test, StringInt_test)
{
    Vector<StringInt> stringint_vector;
    stringint_vector(StringInt("9999999999999999999")) = StringInt(123123123);
    stringint_vector(2) = StringInt("9999999999");

    ASSERT_EQ(stringint_vector(0), 0);
    ASSERT_EQ(stringint_vector(1), 0);
    ASSERT_EQ(stringint_vector(2), StringInt("9999999999"));
    ASSERT_EQ(stringint_vector(3), 0);
    ASSERT_EQ(stringint_vector(StringInt("9999999999999999999")), 123123123);
    ASSERT_EQ(stringint_vector.get_size(), 2);
    ASSERT_EQ(stringint_vector.get_capacity(), -1);
    stringint_vector.set_precision(123123999);
    ASSERT_EQ(stringint_vector.get_size(), 1);
}

TEST(Vector_test, Rational_number_test)
{
    Vector<Rational_number> rational_number_vector;
    rational_number_vector(StringInt("9999999999999999999")) = Rational_number(123123123, 2);
    rational_number_vector(2) = StringInt("9999999999");

    ASSERT_EQ(rational_number_vector(0).get_numerator(), 0);
    ASSERT_EQ(rational_number_vector(0).get_denominator(), 1);
    ASSERT_EQ(rational_number_vector(1).get_numerator(), 0);
    ASSERT_EQ(rational_number_vector(1).get_denominator(), 1);
    ASSERT_EQ(rational_number_vector(2).get_numerator(), StringInt("9999999999"));
    ASSERT_EQ(rational_number_vector(2).get_denominator(), 1);
    ASSERT_EQ(rational_number_vector(3).get_numerator(), 0);
    ASSERT_EQ(rational_number_vector(3).get_denominator(), 1);
    ASSERT_EQ(rational_number_vector(StringInt("9999999999999999999")).get_numerator(), 123123123);
    ASSERT_EQ(rational_number_vector(StringInt("9999999999999999999")).get_denominator(), 2);
    ASSERT_EQ(rational_number_vector.get_size(), 2);
    ASSERT_EQ(rational_number_vector.get_capacity(), -1);
    rational_number_vector.set_precision(123123999);
    ASSERT_EQ(rational_number_vector.get_size(), 1);
}

TEST(Vector_test, bool_test)
{
    Vector<bool> bool_vector(100);
    bool_vector(1, true);
    bool_vector(2, true);
    ASSERT_EQ(bool_vector(0), false);
    ASSERT_EQ(bool_vector(1), true);
    ASSERT_EQ(bool_vector(2), true);
    ASSERT_EQ(bool_vector(3), false);
    ASSERT_EQ(bool_vector.get_size(), 2);
    bool_vector(1, false);
    ASSERT_EQ(bool_vector.get_size(), 1);
    ASSERT_EQ((~bool_vector).get_size(), 99);
    Vector<bool> another_bool_vector(100);
    another_bool_vector(0, true);
    ASSERT_EQ((bool_vector += another_bool_vector).get_size(), 2);
    ASSERT_EQ((bool_vector *= another_bool_vector).get_size(), 1);
    ASSERT_EQ(to_string(bool_vector), "vector bit 100\n\n1 1\n");
    bool_vector(0, false);
    bool_vector(1, true);
    ASSERT_EQ((bool_vector + another_bool_vector).get_size(), 2);
    ASSERT_EQ((bool_vector * another_bool_vector).get_size(), 0);
    std::stringstream ss;
    ss << bool_vector;
    ASSERT_EQ(ss.str(), "vector bit 100\n\n2 1\n");
//    ASSERT_THROW(ss >> another_bool_vector, std::runtime_error);
    ASSERT_TRUE(bool_vector != another_bool_vector);
    ASSERT_TRUE(bool_vector == ~~bool_vector);
    std::stringstream is("vector bit 100\n\n2 1\n");
    Vector<bool>vector_from_input(100);
    is >> vector_from_input;
    ASSERT_FALSE(is.bad());
    ASSERT_TRUE(bool_vector == vector_from_input);
    ASSERT_EQ(bool_vector, vector_from_input);
    is = std::stringstream ("vector bit 100\n\n\n");
    is >> vector_from_input;
    ASSERT_EQ(to_string(vector_from_input), "vector bit 100\n\n");
    vector_from_input = Vector<bool>(std::string(test_path / "vector1.txt").c_str());
    ASSERT_EQ(vector_from_input(1 - 1), true);
    ASSERT_EQ(vector_from_input(6000 - 1), true);
    ASSERT_EQ(vector_from_input(7 - 1), true);
    ASSERT_EQ(vector_from_input(22 - 1), true);
}
