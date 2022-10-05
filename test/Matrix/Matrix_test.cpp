/**
 * Tests for [Matrix].
 *
 * @author sanyavertolet
 */

#include "gtest/gtest.h"

#include "../../src/Matrix/Matrix.h"

class Matrix_test : public testing::Test { };

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
}