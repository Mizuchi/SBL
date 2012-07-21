#include"../../sbl/utility/random.hpp"
#include<gtest/gtest.h>
#include<set>

TEST(random, ten) {
    std::set<unsigned long> a;
    for (int i = 0; i < 23; i++) {
        unsigned long x = sbl::random();
        EXPECT_EQ(a.count(x), 0);
        a.insert(x);
        EXPECT_EQ(a.count(x), 1);
    }
}
