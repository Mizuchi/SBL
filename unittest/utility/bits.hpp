#include"../../sbl/utility/bits.hpp"
#include<gtest/gtest.h>
#include<math.h>
#include<climits>

TEST(bits, base) {
    using namespace sbl;
    EXPECT_EQ(power_of_two(10), 1 << 10);
    EXPECT_EQ(power_of_two(34LL), 17179869184LL);
    EXPECT_EQ(power_of_two(0), 1);


    EXPECT_FALSE(contain(10, 0));
    EXPECT_TRUE(contain(10, 1));
    EXPECT_FALSE(contain(10, 2));
    EXPECT_TRUE(contain(10, 3));
    EXPECT_FALSE(contain(10, 4));
    EXPECT_FALSE(contain(10, 5));

    // 0
    // 1
    // 1010
    // 1100100
    // 1111101000

    EXPECT_EQ(count_set_bits(0), 0);
    EXPECT_EQ(count_set_bits(1), 1);
    EXPECT_EQ(count_set_bits(10), 2);
    EXPECT_EQ(count_set_bits(100), 3);
    EXPECT_EQ(count_set_bits(1000), 6);

    EXPECT_EQ(highest_set_bit_index(0), 0);
    EXPECT_EQ(highest_set_bit_index(1), 1);
    EXPECT_EQ(highest_set_bit_index(10), 4);
    EXPECT_EQ(highest_set_bit_index(100), 7);
    EXPECT_EQ(highest_set_bit_index(1000), 10);

    EXPECT_EQ(highest_set_bit(0), 0);
    EXPECT_EQ(highest_set_bit(1), 1);
    EXPECT_EQ(highest_set_bit(10), 8);
    EXPECT_EQ(highest_set_bit(100), 64);
    EXPECT_EQ(highest_set_bit(1000), 512);

    EXPECT_EQ(lowest_set_bit_index(0), 0);
    EXPECT_EQ(lowest_set_bit_index(1), 1);
    EXPECT_EQ(lowest_set_bit_index(10), 2);
    EXPECT_EQ(lowest_set_bit_index(100), 3);
    EXPECT_EQ(lowest_set_bit_index(1000), 4);

    EXPECT_EQ(lowest_set_bit(0), 0);
    EXPECT_EQ(lowest_set_bit(1), 1);
    EXPECT_EQ(lowest_set_bit(10), 2);
    EXPECT_EQ(lowest_set_bit(100), 4);
    EXPECT_EQ(lowest_set_bit(1000), 8);

    EXPECT_EQ(next_combination(1), 2);
    EXPECT_EQ(next_combination(10), 12);
    EXPECT_EQ(next_combination(100), 104);
    EXPECT_EQ(next_combination(992), 1039);

    EXPECT_TRUE(addition_is_safe(INT_MAX / 4, INT_MAX / 4));
    EXPECT_FALSE(addition_is_safe(INT_MAX - 2, INT_MAX - 2));

    EXPECT_TRUE(multiplication_is_safe(int(sqrt(INT_MAX) / 2), 
                                       int(sqrt(INT_MAX) / 2)));
    EXPECT_FALSE(multiplication_is_safe(INT_MAX - 2, INT_MAX - 2));

    EXPECT_TRUE(exponentiation_is_safe(3, 14));
    EXPECT_TRUE(exponentiation_is_safe(2LL, 30));
    EXPECT_FALSE(exponentiation_is_safe(2, 31));
    EXPECT_FALSE(exponentiation_is_safe(2, 32));
}
