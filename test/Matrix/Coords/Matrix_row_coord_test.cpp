/**
 * Tests for [Matrix_row_coords].
 *
 * @author sanyavertolet
 */

#include "../../../src/Matrix/Coords/Matrix_row_coord.h"
#include "gtest/gtest.h"

class Matrix_row_coord_test : public testing::Test { };

TEST(Matrix_row_coord_test, general_test)
{
    ASSERT_EQ(Matrix_row_coord().get_row_index(), 0);
    ASSERT_EQ(Matrix_row_coord(5).get_row_index(), 5);
    ASSERT_THROW(Matrix_row_coord(-5), IllegalStateException);
    ASSERT_TRUE(Matrix_row_coord(0).has({0, 1}));
    ASSERT_FALSE(Matrix_row_coord(0).has({1, 0}));
}
