#include<gtest/gtest.h>
#include"../../sbl/combinatorics/formula.hpp"

TEST(combinatorics, formula) {
    EXPECT_EQ(sbl::count_permutation<int>(7, 3), 7 * 6 * 5);
    EXPECT_EQ(sbl::count_combination<int>(7, 3), 7 * 6 * 5 / (3 * 2));
    EXPECT_EQ(sbl::factorial<int>(0), 1);
    EXPECT_EQ(sbl::factorial<int>(7), 1 * 2 * 3 * 4 * 5 * 6 * 7);
}
