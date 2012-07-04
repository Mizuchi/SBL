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

    ASSERT_EQ(integer_sqrt(0), 0);
    ASSERT_EQ(integer_sqrt(1), 1);


    for (int i = 1; i < 100; i ++) {
        int sqrt = integer_sqrt(i);
        EXPECT_TRUE(sqrt <= i / sqrt) << "integer_sqrt: " << i;
        EXPECT_TRUE(sqrt + 1 > i / (sqrt + 1)) << "integer_sqrt: " << i;
    }
}

TEST(bits, overflow) {
    using namespace sbl;
    ASSERT_EQ(power_integer(3, 0), 1);
    ASSERT_EQ(power_integer(3, 1), 3);
    ASSERT_EQ(power_integer(3, 2), 9);
    ASSERT_EQ(power_integer(3, 10), 59049);
    ASSERT_EQ(power_integer(3, 19), 1162261467);

    int a, b;

    a = INT_MAX / 2, b = INT_MAX - a;
    EXPECT_TRUE(addition_is_safe(a, b));
    EXPECT_FALSE(addition_is_safe(a, b + 1));
    EXPECT_FALSE(addition_is_safe(a + 1, b));

    a = int(sqrt(INT_MAX)), b = INT_MAX / a;
    EXPECT_TRUE(multiplication_is_safe(a, b));
    EXPECT_FALSE(multiplication_is_safe(a, b + 1));
    EXPECT_FALSE(multiplication_is_safe(a + 1, b));

    a = 2, b = std::numeric_limits<int>::digits;
    EXPECT_TRUE(exponentiation_is_safe(a, b - 1));
    EXPECT_FALSE(exponentiation_is_safe(a, b));

    for (a = 2; a < 100; a++) {
        b = log(std::numeric_limits<int>::max()) / log(a);
        EXPECT_TRUE(exponentiation_is_safe(a, b));
        EXPECT_FALSE(exponentiation_is_safe(a, b + 1));
    }

}
