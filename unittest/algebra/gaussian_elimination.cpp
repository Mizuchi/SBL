#include<gtest/gtest.h>
#include"../../sbl/algebra/gaussian_elimination.hpp"

TEST(algebra, rank) {
    // example from wikipedia
    sbl::Matrix<int> a(4, 4);
    a[0][0] =  2, a[0][1] =  4, a[0][2] = 1, a[0][3] = 3;
    a[1][0] = -1, a[1][1] = -2, a[1][2] = 1, a[1][3] = 0;
    a[2][0] =  0, a[2][1] =  0, a[2][2] = 2, a[2][3] = 2;
    a[3][0] =  3, a[3][1] =  6, a[3][2] = 2, a[3][3] = 5;
    EXPECT_EQ(rank(a), 2);

    sbl::Matrix<int> b(3, 3);
    b[0][0] =  1, b[0][1] =  2, b[0][2] = 1;
    b[1][0] = -2, b[1][1] = -3, b[1][2] = 1;
    b[2][0] =  3, b[2][1] =  5, b[2][2] = 0;

    EXPECT_EQ(rank(b), 2);
}

TEST(algebra, determinant) {
    // example from wikipedia
    sbl::Matrix<int> a(2, 2);
    a[0][0] = 2, a[0][1] = 3;
    a[1][0] = 1, a[1][1] = 4;
    EXPECT_EQ(determinant(a), 5);

    sbl::Matrix<int> b(3, 3);
    b[0][0] = 2, b[0][1] = 6, b[0][2] = 3;
    b[1][0] = 1, b[1][1] = 0, b[1][2] = 2;
    b[2][0] = 5, b[2][1] = 8, b[2][2] = 4;
    EXPECT_EQ(determinant(b), 28);
}

TEST(algebra, gauss_main) {
    using std::vector;
    vector< vector<double> > a(2, vector<double>(2));
    vector< double > b(2);
    a[0][0] = 3, a[0][1] = 5;
    a[1][0] = 1, a[1][1] = 2;
    b[0] = 4, b[1] = 1;
    AUTO(ans, sbl::solve_system_of_linear_equations(a, b));
    EXPECT_DOUBLE_EQ(a[0][0] * ans[0] + a[0][1]*ans[1], b[0]);
    EXPECT_DOUBLE_EQ(a[1][0] * ans[0] + a[1][1]*ans[1], b[1]);

}
