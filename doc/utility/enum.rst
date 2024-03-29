Enum
####

A type safe enumerate type.

Example
==========

.. code-block:: cpp
 
    #include <sbl/utility/enum.hpp>

    struct ColorDef {
        enum type { red, green, blue };
    };
    typedef sbl::Enum<ColorDef> Color;

    struct ShapeDef {
        enum type { circle, square, triangle };
    };
    typedef sbl::Enum<ShapeDef, unsigned char> Shape;

    int main() {
        Color c = Color::red;
        // bool flag = (c == Shape::triangle); // Compiler error.
        EXPECT_EQ(c, Color::red);
        EXPECT_NE(c, Color::green);
        EXPECT_NE(c, Color::blue);
    }
