#include"../../sbl/math/log_mod.hpp"

TEST(math, log_mod) {
   EXPECT_EQ(sbl::log_mod(2, 1014, 1019), 519);
   EXPECT_EQ(sbl::log_mod(3, 13, 17), 4);
   EXPECT_EQ(sbl::log_mod(5, 44, 97), 58);
   EXPECT_EQ(sbl::log_mod(7, 15, 41), 3);
}
