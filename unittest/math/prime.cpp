#include<gtest/gtest.h>
#include"../../sbl/math/prime.hpp"

TEST(math, isprime) {
    EXPECT_TRUE(sbl::isprime(65537));
    EXPECT_FALSE(sbl::isprime(1001));
    EXPECT_TRUE(sbl::isprime(1000003));
}


TEST(math, isprine2) {
    struct {
        bool operator()(int i) const {
            if (i == 1)return false;
            for (int j = 2; j <= i / j; j++)
                if (i % j == 0)
                    return false;
            return true;

        }
    } is_prime_slow;
    for (int n = 1; n < 9999; n++) {
        EXPECT_EQ(sbl::isprime(n), is_prime_slow(n)) << "Test Number: " << n;
    }
}

TEST(math, gen_prime) {
    AUTO(ans, sbl::generate_prime(20));
    int a[8] = {2, 3, 5, 7, 11, 13, 17, 19};
    TYPEOF(ans) out(a, a+8);
    EXPECT_EQ(ans, out);
}

TEST(math, gen_prime_fast) {
    AUTO(ans, sbl::generate_prime_fast(10));
    const std::string s = "00110101000";
    EXPECT_EQ(ans.size(), s.size());
    for (size_t i = 0; i < ans.size(); i++)
        EXPECT_EQ(ans[i], s[i] == '1');
}
