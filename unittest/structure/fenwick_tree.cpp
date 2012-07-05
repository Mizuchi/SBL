#include<gtest/gtest.h>
#include"../../sbl/structure/fenwick_tree.hpp"

TEST(structure, fenwick_small) {
    sbl::FenwickTree<int> a(10);
    EXPECT_EQ(a.prefix_sum(0), 0);
    EXPECT_EQ(a.prefix_sum(9), 0);
    a.increase_nth_element(3, 7);
    a.increase_nth_element(5, 8);
    a.increase_nth_element(8, 9);
    a.increase_nth_element(9, 10);

    EXPECT_EQ(a.prefix_sum(0), 0);
    EXPECT_EQ(a.prefix_sum(1), 0);
    EXPECT_EQ(a.prefix_sum(2), 0);
    EXPECT_EQ(a.prefix_sum(3), 7);
    EXPECT_EQ(a.prefix_sum(4), 7);
    EXPECT_EQ(a.prefix_sum(5), 15);
    EXPECT_EQ(a.prefix_sum(6), 15);
    EXPECT_EQ(a.prefix_sum(7), 15);
    EXPECT_EQ(a.prefix_sum(8), 24);
    EXPECT_EQ(a.prefix_sum(9), 34);

    EXPECT_EQ(a.min_index_that_prefix_sum_greater_than(7), 5);
    EXPECT_EQ(a.min_index_that_prefix_sum_greater_than(8), 5);
    EXPECT_EQ(a.min_index_that_prefix_sum_greater_than(14), 5);
    EXPECT_EQ(a.min_index_that_prefix_sum_greater_than(15), 8);
    EXPECT_EQ(a.min_index_that_prefix_sum_greater_than(100), 10);


    a.increase_nth_element(4, -6);

    EXPECT_EQ(a.prefix_sum(0), 0);
    EXPECT_EQ(a.prefix_sum(1), 0);
    EXPECT_EQ(a.prefix_sum(2), 0);
    EXPECT_EQ(a.prefix_sum(3), 7);
    EXPECT_EQ(a.prefix_sum(4), 1);
    EXPECT_EQ(a.prefix_sum(5), 9);
    EXPECT_EQ(a.prefix_sum(6), 9);
    EXPECT_EQ(a.prefix_sum(7), 9);
    EXPECT_EQ(a.prefix_sum(8), 18);
    EXPECT_EQ(a.prefix_sum(9), 28);
};
