/**
 * Tests for [Matrix_coords].
 *
 * @author sanyavertolet
 */

#include "../Matrix_coords.h"
#include "gtest/gtest.h"

#include <string>

class Matrix_coords_test : public testing::Test { };

TEST(Matrix_coords_test, constructor_test)
{
    Matrix_coords coords;
    ASSERT_EQ(coords.get_tlhs(), Pos(-1, -1));
    ASSERT_EQ(coords.get_brhs(), Pos(-1, -1));

    Matrix_coords single_dot_coords(Pos(1, 1));
    ASSERT_EQ(single_dot_coords.get_tlhs(), Pos(1, 1));
    ASSERT_EQ(single_dot_coords.get_brhs(), Pos(1, 1));

    Matrix_coords double_dot_coords({0, 0}, {5, 5});
    ASSERT_EQ(double_dot_coords.get_tlhs(), Pos(0, 0));
    ASSERT_EQ(double_dot_coords.get_brhs(), Pos(5, 5));

    Matrix_coords two_index_coords(0, 5);
    ASSERT_EQ(two_index_coords.get_tlhs(), Pos(0, 5));
    ASSERT_EQ(two_index_coords.get_brhs(), Pos(0, 5));

    Matrix_coords four_index_coords(0, 0, 5, 5);
    ASSERT_EQ(four_index_coords.get_tlhs(), Pos(0, 0));
    ASSERT_EQ(four_index_coords.get_brhs(), Pos(5, 5));
}

TEST(Matrix_coords_test, has_test)
{
    Matrix_coords coords(1, 1, 100, 100);

    ASSERT_TRUE(coords.has({5, 5}));
    ASSERT_FALSE(coords.has({0, 0}));

    coords = Matrix_coords(-1, -1, -1, -1);
    ASSERT_TRUE(coords.has({5, 5}));
    ASSERT_TRUE(coords.has({12321, 10000}));

    coords = Matrix_coords(-1, 5, 5, 5);
    ASSERT_FALSE(coords.has({1, 7}));
    ASSERT_FALSE(coords.has({7, 1}));
    ASSERT_FALSE(coords.has({7, 7}));
    ASSERT_FALSE(coords.has({5, 1}));
    ASSERT_TRUE(coords.has({5, 5}));
    ASSERT_TRUE(coords.has({1, 5}));
}
