#include<gtest/gtest.h>
#include"../../sbl/utility/bigint.hpp"

TEST(bigint, base) {
    using sbl::Bigint;
    Bigint a = "1928357189237489127834";
    Bigint b = "2348976123896478912342";
    Bigint c = "4277333313133968040176";
    EXPECT_EQ(a + b, c);
    c = "-420618934658989784508";
    EXPECT_EQ(a - b, c);
    c = "4529664995862986093368661229233674518327228";
    EXPECT_EQ(a * b, c);
    b = 1633555129;
    c = "1180466551146";
    EXPECT_EQ(a / b, c);
    b = "7490598434714082";
    EXPECT_EQ(a / b, 257437);
    EXPECT_GE(a / b, 0);
}

TEST(bigint, base2) {
    using sbl::Bigint;
    EXPECT_EQ(Bigint(32) / 2, 16);
    EXPECT_EQ(Bigint(16) * 2, 32);
    EXPECT_EQ(Bigint(32) - Bigint(32) / Bigint(2) * Bigint(2), 0);
    EXPECT_EQ(Bigint(32) % Bigint(2), 0);
    EXPECT_EQ(Bigint(2) % Bigint(32), 2);
}
