#include"../../sbl/utility/float.hpp"
#include<gtest/gtest.h>

TEST(Float, base) {
    {
        double x = 0.1, y = 0.1, z = 0.01;
        EXPECT_NE(x * y, z);
    }
    {
        sbl::Float x = 0.1, y = 0.1, z = 0.01;
        EXPECT_EQ(x * y, z);
        EXPECT_EQ(x + y, 0.2);
        EXPECT_EQ(0.2, x + y);
        EXPECT_EQ(x - y, 0);
        EXPECT_EQ(0, x - y);
        EXPECT_EQ(x / y, 1);
        EXPECT_EQ(1, x / y);
        EXPECT_EQ(x / z, 10);
        EXPECT_EQ(z / x, 0.1);
        x = -25;
        y = 25;
        EXPECT_EQ(x / y, -1);
    }
}

void float_implicit_convert(Float a) {}

struct FloatImplicitConvert {
    FloatImplicitConvert(Float a) {}
    void operator=(Float a) {}
}; // struct FloatImplicitConvert 

TEST(Float, convert) {
    float_implicit_convert(1.0); // ok
    FloatImplicitConvert x(1.0); // ok
    x = 1.0; // ok

    // FIXME: can not convert from a float
    // FloatImplicitConvert y = 1.0; 
}
