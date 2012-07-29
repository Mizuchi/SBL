#include"../../sbl/math/modular.hpp"

TEST(math, modular) {
    EXPECT_EQ(sbl::pow_mod(2, 3, 3), 2);

    EXPECT_EQ(sbl::add_mod(9876, 7889, 12345), 5420);
    EXPECT_EQ(sbl::mul_mod(9876, 5432, 12345), 7407);
    EXPECT_EQ(sbl::pow_mod(1234, 5678, 12345), 10066);
}
