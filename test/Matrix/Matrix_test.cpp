/**
 * Tests for [Matrix].
 *
 * @author sanyavertolet
 */

#include "gtest/gtest.h"

#include "../../src/utils.h"
#include "../../src/Vector/Vector.h"
#include "../../src/Matrix/Matrix.h"

class Matrix_test : public testing::Test { };

std::filesystem::path matrix_test_path = project_path() / "test" / "Matrix" / "matrix-files";

TEST(Matrix_test, int_matrix_test) {
    Matrix<int> m;
    ASSERT_EQ(m.get_size(), 0);
    m(5, 4) = 5;
    ASSERT_EQ(m(5, 4), 5);
    ASSERT_EQ(m.get_size(), 1);
    auto proxy = m[Matrix_row_coord(5)];
    ASSERT_EQ(proxy(4), 5);
    ASSERT_EQ(proxy(5), 0);
    ASSERT_EQ(m[Matrix_row_coord(5)](4), m[Matrix_column_coord(4)](5));
    ASSERT_EQ(proxy(4), m[Matrix_coords({4, 4}, {5, 5})](1, 0));
    ASSERT_NO_THROW(Vector<int>v(proxy));
    auto v = Vector(proxy);
    ASSERT_EQ(v(4), 5);
    auto rectangle_proxy = m[Matrix_coords(4, 4, 5, 5)];
    Matrix<int> new_m = Matrix(rectangle_proxy);
    rectangle_proxy(0,0) += 50;
    ASSERT_EQ(m(4, 4), 50);
    ASSERT_EQ(to_string(m), "matrix FivE 1000 1000\n\n6 5 5\n5 5 50\n");
}

TEST(Matrix_test, Rational_number_matrix_test) {
    Matrix<Rational_number> m = Matrix<Rational_number>();
    ASSERT_EQ(m.get_size(), 0);
    m(5, 4) = Rational_number("5/12");
    ASSERT_EQ(m(5, 4), Rational_number(5, 12));
    ASSERT_EQ(m.get_size(), 1);
    auto proxy = m[Matrix_row_coord(5)];
    ASSERT_EQ(proxy(4), Rational_number(5, 12));
    ASSERT_EQ(proxy(5), Rational_number(0));
    ASSERT_EQ(m[Matrix_row_coord(5)](4), m[Matrix_column_coord(4)](5));
    ASSERT_EQ(proxy(4), m[Matrix_coords({4, 4}, {5, 5})](1, 0));
    ASSERT_NO_THROW(Vector<Rational_number>v(proxy));
    auto v = Vector(proxy);
    ASSERT_EQ(v(4), Rational_number(5, 12));
    auto rectangle_proxy = m[Matrix_coords(4, 4, 5, 5)];
    Matrix<Rational_number> new_m = Matrix(rectangle_proxy);
    rectangle_proxy(0,0) += Rational_number(50, 3);
    ASSERT_EQ(m(4, 4), Rational_number(50, 3));
}

TEST(Matrix_test, Complex_number_matrix_test) {
    Matrix<Complex_number<StringInt, StringInt>> m = Matrix<Complex_number<StringInt, StringInt>>();
    ASSERT_EQ(m.get_size(), 0);
    m(5, 4) = Complex_number(StringInt(5), StringInt(4));
    ASSERT_EQ(m(5, 4), Complex_number(StringInt(5), StringInt(4)));
    ASSERT_EQ(m.get_size(), 1);
    auto proxy = m[Matrix_row_coord(5)];
    ASSERT_EQ(proxy(4), Complex_number(StringInt(5), StringInt(4)));
    ASSERT_EQ(proxy(5), Complex_number(StringInt(0), StringInt(0)));
    ASSERT_EQ(m[Matrix_row_coord(5)](4), m[Matrix_column_coord(4)](5));
    ASSERT_EQ(proxy(4), m[Matrix_coords({4, 4}, {5, 5})](1, 0));
    auto v = Vector(proxy);
    ASSERT_EQ(v(4), Complex_number(StringInt(5), StringInt(4)));
    auto rectangle_proxy = m[Matrix_coords(4, 4, 5, 5)];
    Matrix new_m = Matrix(rectangle_proxy);
    rectangle_proxy(0,0) += Complex_number(StringInt(50), StringInt(3));
    ASSERT_EQ(m(4, 4), Complex_number(StringInt(50), StringInt(3)));
}

TEST(Matrix_test, parser_test) {
    ASSERT_NO_THROW(Matrix<Rational_number>(std::string(matrix_test_path / "matrix1.txt").c_str()));
    Matrix<Rational_number> rational(std::string(matrix_test_path / "matrix1.txt").c_str());
    ASSERT_EQ(rational(1 - 1, 1 - 1), Rational_number(1));
    ASSERT_EQ(rational(6000 - 1, 6000 - 1), Rational_number(1, 5));
    ASSERT_EQ(rational(7 - 1, 7 - 1), Rational_number(7, 3));
    ASSERT_EQ(rational(22 - 1, 22 - 1), Rational_number(1));

    ASSERT_NO_THROW(Matrix<Complex_number<double>>(std::string(matrix_test_path / "matrix2.txt").c_str()));
    Matrix<Complex_number<double, double>> complex(std::string(matrix_test_path / "matrix2.txt").c_str());
    ASSERT_EQ(complex(1 - 1, 1 - 1), Complex_number<double>(1.0, 1.0));
    ASSERT_EQ(complex(6000 - 1, 6000 - 1), Complex_number<double>(1.5, 1.5));
    ASSERT_EQ(complex(7 - 1, 7 - 1), Complex_number<double>(7.7, 3.3));
    ASSERT_EQ(complex(22 - 1, 22 - 1), Complex_number<double>(1.1, 1.1));
}