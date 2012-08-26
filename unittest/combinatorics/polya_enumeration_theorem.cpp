#include<gtest/gtest.h>
#include"../../sbl/combinatorics/polya_enumeration_theorem.hpp"

TEST(combinatorics, polya_enumeration_theorem) {
    int s[4] = {1, 2, 3, 0};
    sbl::Permutation x(s, s + 4);
    {
        // Part A
        sbl::Permutation::Composition op;
        AUTO(a, generate_closure(&x, &x + 1, op));
        std::set< sbl::Permutation > b;
        b.insert(sbl::identity(op, x));
        b.insert(x);
        b.insert(op(x, x));
        b.insert(op(op(x, x), x));
        ASSERT_EQ(a, b);
        foreach(p, a) {
            ASSERT_LE(p.cycle_notation_count(), 4);
            ASSERT_GE(p.cycle_notation_count(), 1);
        }
    }
    {
        // Part B
        EXPECT_EQ(sbl::polya_enumeration_theorem<int>(&x, &x + 1, 2), 6);
    }
}
