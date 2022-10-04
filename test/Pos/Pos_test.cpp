/**
 * Tests for [Pos].
 *
 * @author sanyavertolet
 */

#include <unordered_set>

#include "gtest/gtest.h"
#include "../../src/Pos/Pos.h"

class Pos_test : public testing::Test { };

TEST(Pos_test, general_test)
{
    Pos pos1;
    ASSERT_EQ(pos1.get_i(), 0);
    ASSERT_EQ(pos1.get_j(), 0);

    Pos pos2(1, 2);
    ASSERT_EQ(pos2.get_i(), 1);
    ASSERT_EQ(pos2.get_j(), 2);

    pos1 = ~pos2;
    ASSERT_EQ(pos2.get_i(), 1);
    ASSERT_EQ(pos2.get_j(), 2);

    ASSERT_EQ((~pos1).get_i(), pos1.get_j());
    ASSERT_EQ((~pos1).get_j(), pos1.get_i());

    ASSERT_TRUE(pos1 == ~pos2);
    ASSERT_TRUE(pos1 != pos2);
    ASSERT_TRUE(pos1 < Pos(50, 50));
    ASSERT_TRUE(Pos(50, 50) > pos1);
    ASSERT_TRUE(pos1 <= Pos(50, 50));
    ASSERT_TRUE(Pos(50, 50) >= pos1);
    ASSERT_TRUE(pos1 <= pos1);
    ASSERT_TRUE(pos1 >= pos1);

    ASSERT_EQ(Pos(1, 1) - Pos(2, 2), 2);
    ASSERT_EQ(Pos(5, 1) - Pos(1, 5), 8);
    ASSERT_EQ(Pos(25, 25) - Pos(25, 25), 0);

    ASSERT_THROW(Pos(-2, -2), IllegalStateException);
}

TEST(Pos_test, has_std_hash)
{
    std::unordered_set<Pos> set;
    set.insert({1, 1});
    set.insert({2, 2});
    set.insert({3, 3});
    ASSERT_EQ(set.count({3, 3}), 1);
    ASSERT_EQ(set.size(), 3);
}
