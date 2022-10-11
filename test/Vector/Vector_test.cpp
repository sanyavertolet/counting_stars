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

std::filesystem::path vector_test_path = project_path() / "test" / "Vector" / "vector-files";

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
    int_vector = Vector<int>(11);
    int_vector(5) = 10;
    int_vector(10) = 20;
    ASSERT_EQ(to_string(int_vector), "vector <i> 11\n\n6 10\n11 20\n");
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
    rational_number_vector = Vector<Rational_number>(1000000);
    std::stringstream ss;
    rational_number_vector(5) = Rational_number("5/11");
    rational_number_vector(10000) = Rational_number("-177/98");
    ss << rational_number_vector;
    ASSERT_EQ(ss.str(), "vector rational 1000000\n\n6 5/11\n10001 -177/98\n");
    Vector<Rational_number> new_rational_vector(1000000);
    ss >> new_rational_vector;
    ASSERT_EQ(to_string(new_rational_vector), to_string(rational_number_vector));
}

TEST(Vector_test, Complex_number_test)
{
    Vector<Complex_number<double, double>> complex_vector(StringInt("99999999999999999999"));
    complex_vector(StringInt("9999999999999999999")) = Complex_number<double, double>(123123.123, 2.0);
    complex_vector(2) = Complex_number<double, double>(1.5, 6.3);

    ASSERT_EQ(complex_vector(0), Complex_number(0));
    ASSERT_EQ(complex_vector(1), Complex_number(0));
    ASSERT_EQ(complex_vector(2), Complex_number(1.5, 6.3));
    ASSERT_EQ(complex_vector(3), Complex_number(0));
    ASSERT_EQ(complex_vector(StringInt("9999999999999999999")), Complex_number(123123.123, 2.0));
    ASSERT_EQ(complex_vector.get_size(), 2);
    ASSERT_EQ(complex_vector.get_capacity(), StringInt("99999999999999999999"));
    complex_vector.set_precision(1000);
    ASSERT_EQ(complex_vector.get_size(), 1);
    complex_vector = Vector<Complex_number<double, double>>(1000000);
    std::stringstream ss;
    complex_vector(5) = Complex_number(1.1, 2.2);
    complex_vector(10000) = Complex_number(3.3, 4.4);
    ss << complex_vector;
    ASSERT_EQ(ss.str(), "vector complex 1000000\n\n6 (1,2)\n10001 (3,4)\n");
    Vector<Complex_number<double, double>> new_complex_vector(1000000);
    ss >> new_complex_vector;
    ASSERT_EQ(to_string(new_complex_vector), to_string(complex_vector));
    Vector<Complex_number<double, double>> vector_from_input;
    vector_from_input = Vector<Complex_number<double, double>>(std::string(vector_test_path / "vector2.txt").c_str());
    ASSERT_EQ(vector_from_input(1 - 1), Complex_number<double>(1.1, 5.5));
    ASSERT_EQ(vector_from_input(6000 - 1), Complex_number<double>(1.0, 1.0));
    ASSERT_EQ(vector_from_input(7 - 1), Complex_number<double>(1.2, 5.5));
    ASSERT_EQ(vector_from_input(22 - 1), Complex_number<double>(1.5, 0.0));
    ASSERT_THROW(Vector<Complex_number<double>>(std::string(vector_test_path / "vector.txt").c_str()), FileNotFoundException);
    ASSERT_THROW(Vector<Complex_number<double>>(std::string(vector_test_path / "vector-parse-exception.txt").c_str()), ParseException);
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
    vector_from_input = Vector<bool>(std::string(vector_test_path / "vector1.txt").c_str());
    ASSERT_EQ(vector_from_input(1 - 1), true);
    ASSERT_EQ(vector_from_input(6000 - 1), true);
    ASSERT_EQ(vector_from_input(7 - 1), true);
    ASSERT_EQ(vector_from_input(22 - 1), true);
    ASSERT_NO_THROW(Vector<bool>(std::string(vector_test_path / "vector-empty.txt").c_str()));
    ASSERT_THROW(Vector<bool>(std::string(vector_test_path / "vector-broken.txt").c_str()), ParseException);
}

TEST(Vector_test, just_a_test) {
    ASSERT_THROW(Vector<bool>(std::string(vector_test_path / "vector-broken.txt").c_str()), ParseException);
}
