#include"../../sbl/algebra/qr.hpp"
#include<gtest/gtest.h>
#include<algorithm>

template<class T>
void matrix_almost_eq(sbl::Matrix<T> a, sbl::Matrix<T> b) {
    EXPECT_EQ(a.row_size(), b.row_size());
    EXPECT_EQ(a.col_size(), b.col_size());
    formatrix(a, k, i, j) {
        EXPECT_LE(std::abs(k - b[i][j]), 1e-9);
    }
}

TEST(algebra, qr1) {
    sbl::Matrix<double> a(3, 3), origin, q, r, ansQ, ansR;
    a[0][0] = 12, a[0][1] = -51, a[0][2] = 4;
    a[1][0] = 6, a[1][1] = 167, a[1][2] = -68;
    a[2][0] = -4, a[2][1] = 24, a[2][2] = -41;
    origin = a;
    sbl::qr_decomposition(origin, &q, &r);

    a[0][0] = 6 / 7.0, a[0][1] = -69 / 175.0, a[0][2] = -58 / 175.0;
    a[1][0] = 3 / 7.0, a[1][1] = 158 / 175.0, a[1][2] = 6 / 175.0;
    a[2][0] = -2 / 7.0, a[2][1] = 6 / 35.0, a[2][2] = -33 / 35.0;
    ansQ = a;

    a[0][0] = 14, a[0][1] = 21, a[0][2] = -14;
    a[1][0] = 0, a[1][1] = 175, a[1][2] = -70;
    a[2][0] = 0, a[2][1] = 0, a[2][2] = 35;
    ansR = a;

    //matrix_almost_eq(q, ansQ);
    //matrix_almost_eq(r, ansR);
    matrix_almost_eq(origin, q*r);

    // assert q is a unitary
    sbl::Matrix<double> p = q * sbl::adjoint(q);
    matrix_almost_eq(p, sbl::identity(std::multiplies<TYPEOF(p)>(), p));

    // assert r is a upper triangular
    formatrix(r, k, i, j) {
        if(i > j)
            EXPECT_EQ(k, sbl::identity(std::plus<TYPEOF(k)>(), k));
    }
}
