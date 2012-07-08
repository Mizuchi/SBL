#include<gtest/gtest.h>
#include"../../sbl/math/function.hpp"

TEST(math, euler) {
    int a[] = {0, 1, 1, 2, 2, 4, 2, 6, 4, 6, 4, 10, 4, 12, 6,
               8, 8, 16, 6, 18, 8, 12, 10, 22, 8, 20, 12, -1
              };
    for (int i = 1; a[i] != -1; i++)
        EXPECT_EQ(a[i], sbl::euler(i));
}

TEST(math, mobius) {
    int a[] = {0, 1, -1, -1, 0, -1, 1, -1, 0, 0, 1, -1, 0,
               -1, 1, 1, 0, -1, 0, -1, 0, 1, 1, -1, 0, 0, -1
              };
    for (int i = 1; a[i] != -1; i++)
        EXPECT_EQ(a[i], sbl::mobius(i));
}

TEST(math, carmichael) {
    int a[] = {0, 1, 1, 2, 2, 4, 2, 6, 2, 6, 4, 10, 2, 12,
               6, 4, 4, 16, 6, 18, 4, 6, 10, 22, 2, 20, 12, -1
              };
    for (int i = 1; a[i] != -1; i++)
        EXPECT_EQ(a[i], sbl::carmichael(i));
}
