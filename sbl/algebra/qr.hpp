#ifndef _sbl_qr_decomposition
#define _sbl_qr_decomposition
#include"matrix.hpp"
#include<cmath>

namespace sbl {

template <class T>
void qr_decomposition(const Matrix<T> &a, Matrix<T> *oQ, Matrix<T> *oR) {
    // modified Gram-Schmidt iteration
    
    Matrix<T> &q = *oQ;
    Matrix<T> &r = *oR;
    const size_t m = a.row_size();
    const size_t n = a.col_size();
    assert(m > 0);
    assert(n > 0);

    q.resize(m, n);
    r.resize(n, n);
    r.fill(identity(std::plus<T>(), a[0][0]));

    std::vector< Matrix<T> > v(n);

    for (size_t i = 0; i < n; i++)
        v[i] = get_col(a, i);

    assert(v[0].row_size() == m);
    assert(v[0].col_size() == 1);

    for (size_t i = 0; i < n; i++) {
        r[i][i] = std::sqrt(dot_product(v[i], v[i]));

        // q[i] = v[i] / r[i][i]
        for (size_t j = 0; j < m; j++)
            q[j][i] = v[i][j][0] / r[i][i];

        for (size_t j = i + 1; j < n; j++) {
            r[i][j] = dot_product(get_col(q, i), v[j]);

            //  v[j] = v[j] - r[i][j] * q[i]
            for (size_t k = 0; k < m; k ++)
                v[j][k][0] -= r[i][j] * q[k][i];

        }
    }
} // function qr_decomposition

} // namespace sbl
#endif
