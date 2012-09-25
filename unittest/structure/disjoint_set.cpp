#include"../../sbl/structure/disjoint_set.hpp"
#include<gtest/gtest.h>

TEST(structure, disjoint_set) {
    sbl::DisjointSet a;
    a.merge(1, 4);
    a.merge(8, 4);
    a.merge(2, 5);
    a.merge(7, 10);
    EXPECT_TRUE(a.same(1, 4));
    EXPECT_TRUE(a.same(1, 8));
    EXPECT_FALSE(a.same(2, 10));
    a.merge(5, 7);
    EXPECT_FALSE(a.same(0, 1));
    EXPECT_TRUE(a.same(2, 10));
    EXPECT_FALSE(a.same(1, 2));
    EXPECT_FALSE(a.same(2, 3));
    EXPECT_FALSE(a.same(3, 4));
    EXPECT_TRUE(a.same(5, 10));
    EXPECT_FALSE(a.same(4, 5));
    EXPECT_FALSE(a.same(5, 6));
    EXPECT_FALSE(a.same(6, 7));
    EXPECT_TRUE(a.same(2, 7));
    EXPECT_FALSE(a.same(7, 8));
    EXPECT_FALSE(a.same(8, 9));
    EXPECT_TRUE(a.same(8, 1));
};
TEST(structure, disjoint_dict) {
    sbl::DisjointMap<int> a;
    a.merge(1, 4);
    a.merge(8, 4);
    a.merge(2, 5);
    a.merge(7, 10);
    EXPECT_TRUE(a.same(1, 4));
    EXPECT_TRUE(a.same(1, 8));
    EXPECT_FALSE(a.same(2, 10));
    a.merge(5, 7);
    EXPECT_FALSE(a.same(0, 1));
    EXPECT_TRUE(a.same(2, 10));
    EXPECT_FALSE(a.same(1, 2));
    EXPECT_FALSE(a.same(2, 3));
    EXPECT_FALSE(a.same(3, 4));
    EXPECT_TRUE(a.same(5, 10));
    EXPECT_FALSE(a.same(4, 5));
    EXPECT_FALSE(a.same(5, 6));
    EXPECT_FALSE(a.same(6, 7));
    EXPECT_TRUE(a.same(2, 7));
    EXPECT_FALSE(a.same(7, 8));
    EXPECT_FALSE(a.same(8, 9));
    EXPECT_TRUE(a.same(8, 1));
};
