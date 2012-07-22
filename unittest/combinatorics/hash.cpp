#include"../../sbl/combinatorics/hash.hpp"
#include<gtest/gtest.h>

TEST(combinatorics, permutation2hash) {
    std::vector<size_t> p;
    p.push_back(0);
    p.push_back(3);
    p.push_back(1);
    p.push_back(2);
    p.push_back(4);
    EXPECT_EQ(sbl::permutation2hash<int>(p), 12);
    EXPECT_EQ(sbl::hash2permutation(12, 5), p);
}
