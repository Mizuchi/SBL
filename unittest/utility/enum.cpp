#include"../../sbl/utility/enum.hpp"
#include<gtest/gtest.h>

struct ColorDef {
    enum type { red, green, blue };
};
typedef sbl::Enum<ColorDef> Color;

struct ShapeDef {
    enum type { circle, square, triangle };
};
typedef sbl::Enum<ShapeDef, unsigned char> Shape;

TEST(enum, base) {
    Color c = Color::red;
    // bool flag = (c == Shape::triangle); // Compiler error.
    EXPECT_EQ(c, Color::red);
    EXPECT_NE(c, Color::green);
    EXPECT_NE(c, Color::blue);
}
