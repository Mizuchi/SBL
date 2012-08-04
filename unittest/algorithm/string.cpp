#include"../../sbl/algorithm/string.hpp"
#include<gtest/gtest.h>
#include<string.h>
#include<string>

TEST(algorithm, min_rotate) {
    const char s[] = "dontcallmebfu";
    const char *ans = sbl::min_rotate(s, s+strlen(s));
    EXPECT_EQ(std::string(ans), "allmebfu");
}

TEST(algorithm, split) {
    using sbl::split;
    {
        AUTO(ans, split("1<>2<>3", "<>"));
        EXPECT_EQ(ans.size(), 3);
        EXPECT_EQ(ans[0], "1");
        EXPECT_EQ(ans[1], "2");
        EXPECT_EQ(ans[2], "3");
    }
    {
        // FIXME: this behavior is difference compare with python str.split
        AUTO(ans, split("1,,2", ","));
        EXPECT_EQ(ans.size(), 2);
        EXPECT_EQ(ans[0], "1");
        //EXPECT_EQ(ans[1], "");
        EXPECT_EQ(ans[1], "2");
    }
    {
        AUTO(ans, split(" 1  2\n3  "));
        EXPECT_EQ(ans[0], "1");
        EXPECT_EQ(ans[1], "2");
        EXPECT_EQ(ans[2], "3");
    }
}
