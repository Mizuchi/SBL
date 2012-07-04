#include<gtest/gtest.h>
#include"../../sbl/math/gcd.hpp"

TEST(math, gcd) {
    ASSERT_EQ(sbl::lcm(2520, 3600), 25200);

    for (int i = 0; i < 100; i ++)
        for (int j = 0; j < 100; j++) {
            int x = 0, y = 0;
            int ans = sbl::gcd(i, j, &x, &y);
            ASSERT_EQ(ans, sbl::gcd(i, j)) << i << ", " << j;
            ASSERT_EQ(i * x + j * y, ans)
                << "i: " << i << ", j: " << j <<", gcd(i, j): " << ans;
        }

    for (int i = 1; i < 100; i ++)
        for (int j = 1; j < 100; j++) 
            if(i % j != 0 and sbl::gcd(i, j) == 1) {
            int k = sbl::modular_inverse(i, j);
            ASSERT_EQ(i * k % j, 1) << "modular_inverse wrong."
                << "i: " << i << ", j: " << j <<", k: " << k;
        }
}
