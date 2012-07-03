#include"../../sbl/algebra/element.hpp"

TEST(element, int) {
    EXPECT_EQ(sbl::identity(std::plus<int>()), 0);
    EXPECT_EQ(sbl::identity(std::multiplies<int>()), 1);
    EXPECT_EQ(sbl::inverse(std::plus<int>(), 7), -7);
}
