#include"../../sbl/utility/foreach.hpp"
#include<string>
#include<vector>
#include<map>

TEST(foreach, vector_no_ref) {
    std::vector<int> a(10, 20);
    int j = 0, s2 = 0;
    foreach(i, a) {
        static_cast<void>(i);
        i = j++;
    }
    foreach(i, a) s2 += i;
    EXPECT_EQ(s2, 200);
}

TEST(foreach, vector_ref) {
    std::vector<int> a(10, 20);
    int j = 0, s2 = 0;
    foreach(&i, a) i = j++;
    foreach(i, a) s2 += i;
    EXPECT_EQ(s2, 45);
}

TEST(foreach, map) {
    std::map<int, int> sqr;
    for (int i = 1; i <= 100; i++)
        sqr[i] = i * i;
    foreach(i, sqr) {
        EXPECT_EQ(i.second, i.first * i.first);
    }
}
