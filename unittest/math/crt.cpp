#include<gtest/gtest.h>
#include"../../sbl/math/crt.hpp"

TEST(math, crt) {
    int a[3] = {2, 3, 2};
    int b[3] = {3, 5, 7};
    EXPECT_EQ(sbl::crt<int>(a, a + 3, b, b + 3), 23);
}
