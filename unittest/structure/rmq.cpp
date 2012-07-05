#include<gtest/gtest.h>
#include"../../sbl/structure/rmq.hpp"
#include<algorithm>
#include<vector>

TEST(structure, static_rmq) {
    int x[10] = {1, 4, 2, 3, 5, 9, 8, 4, 5, 6};
    std::vector<int> d(x, x + 10);
    sbl::StaticRangeMinimunQuery<int> a(x, x + 10);
    for (int i = 0; i < (int)d.size(); i++)
        for (int j = i+1; j < (int)d.size(); j++) {
            int s = 0;
            for (int k = i; k < j; k++)
                s = std::max(s, d[k]);
            EXPECT_EQ(s, a.top(i, j)) << "In Range [" << i << ", " << j << "]";
        }
};

TEST(structure, dynamic_rmq) {
    int x[10] = {1, 4, 2, 3, 5, 9, 8, 4, 5, 6};
    std::vector<int> d(x, x + 10);
    sbl::DynamicRangeMinimunQuery<int> a(10, 0);
    for (int i = 0; i < 10; i++)
        a.replace(i, x[i]);
    for (int i = 0; i < (int)d.size(); i++)
        for (int j = i+1; j < (int)d.size(); j++) {
            int s = 0;
            for (int k = i; k < j; k++)
                s = std::max(s, d[k]);
            EXPECT_EQ(s, a.top(i, j)) << "In Range [" << i << ", " << j << "]";
        }
};
