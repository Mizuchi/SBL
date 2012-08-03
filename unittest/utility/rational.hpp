#include<gtest/gtest.h>
#include"../../sbl/utility/rational.hpp"
#include"../../sbl/utility/bigint.hpp"

TEST(rational, normal) {
   using namespace sbl;
   Rational<int> a(7, 30), b(13, 30), c;
   c = a;
   c += b;
   EXPECT_EQ(c.numerator(), 2);
   EXPECT_EQ(c.denominator(), 3);
   EXPECT_EQ(c, a + b);
   c = a;
   c -= b;
   EXPECT_EQ(c.numerator(), -1);
   EXPECT_EQ(c.denominator(), 5);
   EXPECT_EQ(c, a - b);
   c = a;
   c *= b;
   EXPECT_EQ(c.numerator(), 91);
   EXPECT_EQ(c.denominator(), 900);
   EXPECT_EQ(c, a * b);
   c = a;
   c /= b;
   EXPECT_EQ(c.numerator(), 7);
   EXPECT_EQ(c.denominator(), 13);
   EXPECT_EQ(c, a / b);
}

TEST(rational, catalan) {
    typedef sbl::Rational<sbl::Bigint> Fraction;

    Fraction c(1);
    const int n = 30;
    for (int k = 2; k <= n; k++)
        c *= Fraction(n + k, k);
    sbl::Bigint ans("3814986502092304");
    EXPECT_EQ(c, ans);
}
