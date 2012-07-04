#include<gtest/gtest.h>
#include"../../sbl/math/isprime.hpp"

TEST(isprime, example1) {
    EXPECT_TRUE(sbl::isprime(65537));
    EXPECT_FALSE(sbl::isprime(1001));
    EXPECT_TRUE(sbl::isprime(1000003));
}

bool is_prime_slow(int i) {
    if (i == 1)return false;
    for (int j = 2; j <= i / j; j++)
        if (i % j == 0)
            return false;
    return true;
}

TEST(isprime, example2) {
    for (int n = 1; n < 9999; n++) {
        EXPECT_EQ(sbl::isprime(n), is_prime_slow(n)) << "Test Number: " << n;
    }
}
