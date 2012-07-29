#include<gtest/gtest.h>
#include"../../sbl/math/solve.hpp"

TEST(math, solve) {
    AUTO(ans, sbl::solve_modular_linear_equations(14, 30, 100));
    std::sort(ans.begin(), ans.end());
    EXPECT_EQ(ans.size(), 2);
    EXPECT_EQ(ans[0], 45);
    EXPECT_EQ(ans[1], 95);
}
