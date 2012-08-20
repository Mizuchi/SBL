#include<gtest/gtest.h>
#include"../../sbl/combinatorics/combination.hpp"
#include"../../sbl/utility/bits.hpp"

TEST(combinatorics, combination) {
    {
        int a[5] = {4, 5, 6, 7, 8};
        EXPECT_FALSE(sbl::next_combination(a, a + 5, 9));
    }
    {
        int a[5] = {0, 1, 2, 3, 4};
        EXPECT_FALSE(sbl::next_combination(a, a + 5, 5));
    }
    {
        int a[5] = {0, 1, 4, 5, 6};
        bool h = sbl::next_combination(a, a + 5, 7);
        EXPECT_TRUE(h);
        EXPECT_EQ(a[0], 0);
        EXPECT_EQ(a[1], 2);
        EXPECT_EQ(a[2], 3);
        EXPECT_EQ(a[3], 4);
        EXPECT_EQ(a[4], 5);
    }
}
