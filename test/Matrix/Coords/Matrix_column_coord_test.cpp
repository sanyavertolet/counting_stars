/**
 * Tests for [Matrix_column_coords].
 *
 * @author sanyavertolet
 */

#include "../../../src/Matrix/Coords/Matrix_column_coord.h"
#include "gtest/gtest.h"

class Matrix_column_coord_test : public testing::Test { };

TEST(Matrix_column_coord_test, general_test)
{
    ASSERT_EQ(Matrix_column_coord().get_column_index(), 0);
    ASSERT_EQ(Matrix_column_coord(5).get_column_index(), 5);
    ASSERT_THROW(Matrix_column_coord(-5), IllegalStateException);
    ASSERT_TRUE(Matrix_column_coord(0).has({1, 0}));
    ASSERT_FALSE(Matrix_column_coord(0).has({0, 1}));
}
