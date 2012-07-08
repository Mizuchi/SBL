#include"../../sbl/math/integer_factorization.hpp"

TEST(math, integer_factorization) {
    using namespace sbl;
    using namespace std;

    map<int, int> x = factorize_integer(1001);
    EXPECT_EQ(x.size(), 3);
    EXPECT_EQ(x[7], 1);
    EXPECT_EQ(x[11], 1);
    EXPECT_EQ(x[13], 1);

    vector<int> y;
    factorize_integer(1001, &y);
    EXPECT_EQ(y.size(), 3);
    EXPECT_EQ(y[0]*y[0] + y[1]*y[1] + y[2]*y[2], 7 * 7 + 11 * 11 + 13 * 13);

    y = get_all_divisor(1001);
    sort(y.begin(), y.end());
    EXPECT_EQ(y.size(), 8);
    EXPECT_EQ(y[0], 1);
    EXPECT_EQ(y[1], 7);
    EXPECT_EQ(y[2], 11);
    EXPECT_EQ(y[3], 13);
    EXPECT_EQ(y[4], 7 * 11);
    EXPECT_EQ(y[5], 7 * 13);
    EXPECT_EQ(y[6], 11 * 13);
    EXPECT_EQ(y[7], 1001);
}

TEST(math, integer_factorization2) {
    using namespace sbl;
    using namespace std;

    map<int, int> x = factorize_integer(100);
    EXPECT_EQ(x.size(), 2);
    EXPECT_EQ(x[2], 2);
    EXPECT_EQ(x[5], 2);

    vector<int> y;
    factorize_integer(100, &y);
    sort(y.begin(), y.end());
    EXPECT_EQ(y.size(), 4);
    EXPECT_EQ(y[0], 2);
    EXPECT_EQ(y[1], 2);
    EXPECT_EQ(y[2], 5);
    EXPECT_EQ(y[3], 5);

    y = get_all_divisor(100);
    sort(y.begin(), y.end());
    EXPECT_EQ(y.size(), 9);
    EXPECT_EQ(y[0], 1);
    EXPECT_EQ(y[1], 2);
    EXPECT_EQ(y[2], 4);
    EXPECT_EQ(y[3], 5);
    EXPECT_EQ(y[4], 10);
    EXPECT_EQ(y[5], 20);
    EXPECT_EQ(y[6], 25);
    EXPECT_EQ(y[7], 50);
    EXPECT_EQ(y[8], 100);
}
