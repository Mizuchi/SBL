#include<gtest/gtest.h>
#include"../../sbl/geometry/line.hpp"

TEST(geometry, line_intersect) {
    using namespace sbl;
    {
    AUTO(a1, intersect(segment(Point(0, 0), Point(1, 1)),
                       segment(Point(0, 1), Point(1, 0))));
    ASSERT_EQ(a1.size(), 1);
    EXPECT_DOUBLE_EQ(a1[0].real(), 0.5);
    EXPECT_DOUBLE_EQ(a1[0].imag(), 0.5);
    }
    {
    AUTO(a1, intersect(line(Point(0, 0), Point(-1, -1)),
                       segment(Point(0, 1), Point(1, 0))));
    ASSERT_EQ(a1.size(), 1);
    EXPECT_DOUBLE_EQ(a1[0].real(), 0.5);
    EXPECT_DOUBLE_EQ(a1[0].imag(), 0.5);
    }
    {
    AUTO(a1, intersect(segment(Point(0, 0), Point(-1, -1)),
                       segment(Point(0, 1), Point(1, 0))));
    EXPECT_TRUE(a1.empty());
    }
}
