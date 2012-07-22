#include<gtest/gtest.h>
#include"../../sbl/geometry/point.hpp"

TEST(geometry, base) {
    using namespace sbl;
    Point a(-7, 2), b(3, -6);
    EXPECT_EQ(cross(a, b), 36);
    EXPECT_EQ(dot(a, b), -33);
}

TEST(geometry, point_position) {
    using namespace sbl;
    {
        Point a(2, 4), b(3, 3), c(4, 2);
        EXPECT_TRUE(on_same_line(a, b, c));

        EXPECT_EQ(position(b, a), state::left);
        EXPECT_NE(position(b, a), state::right);

        EXPECT_EQ(position(b, c), state::right);
        EXPECT_NE(position(b, c), state::left);

        EXPECT_EQ(position(c, b, a), state::front);
        EXPECT_NE(position(c, b, a), state::back);

        EXPECT_EQ(position(a, b, c), state::front);
        EXPECT_NE(position(a, b, c), state::back);

        EXPECT_EQ(position(c, a, b), state::back);
        EXPECT_EQ(position(a, c, b), state::back);
        EXPECT_EQ(position(b, a, c), state::reverse);
        EXPECT_EQ(position(a, a), state::same);
    }
}
