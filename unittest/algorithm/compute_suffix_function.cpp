#include"../../sbl/base.hpp"
#include"../../sbl/algorithm/compute_suffix_function.hpp"
#include<string>

TEST(algorithm, lcp1) {
    using namespace std;
    string t = "abcabcabc";
    string s = "abcabcd";
    AUTO(ans, sbl::compute_suffix_function(
             s.begin(),
             s.end(),
             t.begin(),
             t.end())
        );

    EXPECT_EQ(ans[0], 6);
    EXPECT_EQ(ans[1], 0);
    EXPECT_EQ(ans[2], 0);
    EXPECT_EQ(ans[3], 3);
    EXPECT_EQ(ans[4], 0);
    EXPECT_EQ(ans[5], 0);
    EXPECT_EQ(ans[6], 0);
    t = "abaabaab";
    s = t;
    ans = sbl::compute_suffix_function(
              s.begin(),
              s.end(),
              t.begin(),
              t.end());

    size_t tmp[8] = {8, 0, 1, 5, 0, 1, 2, 0};
    TYPEOF(ans) result(tmp, tmp + 8);
    EXPECT_EQ(ans, result);
}
