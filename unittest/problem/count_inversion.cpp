#include<gtest/gtest.h>
#include<algorithm>
#include"../../sbl/problem/count_inversion.hpp"

TEST(problem, count_inversion) {
    int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    EXPECT_EQ(sbl::count_inversion(a, a + 10), 0);
    std::reverse(a, a + 10);
    EXPECT_EQ(sbl::count_inversion(a, a + 10), 45);
    {
        int b[9] = {4, 9, 2, 3, 5, 7, 8, 1, 6};
        int ans = 0;
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
                if (i < j and b[i] > b[j]) ans++;
        EXPECT_EQ(sbl::count_inversion(b, b + 9), ans);
    }
}

