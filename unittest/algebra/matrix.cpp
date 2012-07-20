#include"../../sbl/algebra/matrix.hpp"
#include<gtest/gtest.h>
#include<complex>

TEST(algebra, matrix1) {
    sbl::Matrix<int> a(2, 2);
    sbl::Matrix<int> b(2, 2);
    a[0][0] = 1, a[0][1] = 1;
    a[1][0] = 1, a[1][1] = 0;

    b[0][0] = 0, b[0][1] = 1;
    b[1][0] = 1, b[1][1] = -1;
    AUTO(c, a * b);
    EXPECT_EQ(c[0][0], 1);
    EXPECT_EQ(c[0][1], 0);
    EXPECT_EQ(c[1][0], 0);
    EXPECT_EQ(c[1][1], 1);
    EXPECT_EQ(c, sbl::identity(std::multiplies<TYPEOF(a)>(), a));
}
TEST(algebra, matrix2) {
    // Introduction to Algorithm P 749 2nd edition
    sbl::Matrix<int> a(4, 4);
    sbl::Matrix<int> b(4, 4);
    sbl::Matrix<int> c(4, 4);
    a[0][0] = 2, a[0][1] =  3, a[0][2] =  1, a[0][3] =  5;
    a[1][0] = 6, a[1][1] = 13, a[1][2] =  5, a[1][3] = 19;
    a[2][0] = 2, a[2][1] = 19, a[2][2] = 10, a[2][3] = 23;
    a[3][0] = 4, a[3][1] = 10, a[3][2] = 11, a[3][3] = 31;

    b[0][0] = 1, b[0][1] = 0, b[0][2] = 0, b[0][3] = 0;
    b[1][0] = 3, b[1][1] = 1, b[1][2] = 0, b[1][3] = 0;
    b[2][0] = 1, b[2][1] = 4, b[2][2] = 1, b[2][3] = 0;
    b[3][0] = 2, b[3][1] = 1, b[3][2] = 7, b[3][3] = 1;

    c[0][0] = 2, c[0][1] = 3, c[0][2] = 1, c[0][3] = 5;
    c[1][0] = 0, c[1][1] = 4, c[1][2] = 2, c[1][3] = 4;
    c[2][0] = 0, c[2][1] = 0, c[2][2] = 1, c[2][3] = 2;
    c[3][0] = 0, c[3][1] = 0, c[3][2] = 0, c[3][3] = 3;

    EXPECT_EQ(a, b * c);
    EXPECT_EQ(a, conj(a));
    EXPECT_EQ(b, conj(b));
    EXPECT_EQ(a, conj(b * c));
    EXPECT_EQ(conj(a), b * c);

}

TEST(algebra, matrix_dot_product) {
    sbl::Matrix<int> a(3, 1);
    a[0][0] = 1, a[1][0] = 3, a[2][0] = -5;
    sbl::Matrix<int> b(a);
    b[0][0] = 4, b[1][0] = -2, b[2][0] = -1;
    EXPECT_EQ(dot_product(a, b), 3);
    EXPECT_EQ(dot_product(a, a), 1 * 1 + 3 * 3 + 5 * 5);
    EXPECT_EQ(dot_product(b, b), 4 * 4 + 2 * 2 + 1 * 1);
}

TEST(algebra, matrix_dot_product2) {
    sbl::Matrix< std::complex<float> > a(3, 1);
    a[0][0] = 1, a[1][0] = 3, a[2][0] = -5;
    sbl::Matrix< std::complex<float> > b(a);
    b[0][0] = 4, b[1][0] = -2, b[2][0] = -1;
    EXPECT_EQ(dot_product(a, b), std::complex<float>(3));
    EXPECT_EQ(dot_product(a, a), std::complex<float>(1 * 1 + 3 * 3 + 5 * 5));
    EXPECT_EQ(dot_product(b, b), std::complex<float>(4 * 4 + 2 * 2 + 1 * 1));
}

TEST(algebra, matrix_hermitian) {
    sbl::Matrix< std::complex<double> > a(2, 2);
    a[0][0] = 3, a[0][1] = 2;
    a[1][0] = 2, a[1][1] = 1;
    a[0][1].imag(1);
    a[1][0].imag(-1);
    EXPECT_TRUE(is_hermitian_matrix(a));
}
