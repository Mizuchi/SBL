#ifndef _sbl_gauss
#define _sbl_gauss
#include"matrix.hpp"
#include<cmath>

namespace sbl {

/// @brief apply gaussian elimination to a matrix.
///
/// @tparam T Type of matrix element
/// @param A Matrix
/// @param swapCount Return count of row swap. Used to get determinant.
/// @param rank Return the rank of matrix.
template<class T>
void gaussian_elimination(Matrix<T> *A, size_t *swapCount, size_t *rank) {
    Matrix<T> &a = *A;

    const size_t n = a.row_size();
    const size_t m = a.col_size();
    (*swapCount) = 1;
    (*rank) = n;

    for (size_t i = 0, j = 0; i < n and j < m; i++, j++) {
        size_t pivot = i;
        for (size_t k = i + 1; k < n; k++)
            if (std::abs(a[pivot][j]) < std::abs(a[k][j]))
                pivot = k;
        if (i != pivot) {
            for (size_t l = j; l < m; l++)
                std::swap(a[pivot][l], a[i][l]);
            (*swapCount) ++;
        }
        if (iszero(a[i][j])) {
            (*rank) --;
            i--;
            continue;
        }
        for (size_t k = i + 1; k < n; k++)
            while (1) {
                T t = a[k][j] / a[i][j];
                for (size_t l = j; l < m; l++)
                    a[k][l] -= t * a[i][l];
                if (iszero(a[k][j]))
                    break;
                (*swapCount) ++;
                for (size_t l = j; l < m; l++)
                    std::swap(a[i][l], a[k][l]);
            }
    }
}

/// Get the determinant of matrix
template<class T>
T determinant(Matrix<T> a) {
    assert(a.row_size() == a.col_size());
    const size_t n = a.row_size();
    size_t swapCount, rank;
    gaussian_elimination(&a, &swapCount, &rank);
    T result = a[0][0];
    for (size_t i = 1; i < n; i++)
        result *= a[i][i];
    if (swapCount % 2 == 0)
        return -result;
    else
        return result;
}

/// Get the rank of matrix
template<class T>
size_t rank(Matrix<T> a) {
    size_t swapCount, rank;
    gaussian_elimination(&a, &swapCount, &rank);
    return rank;
}
 
/// @brief Solve system of linear equations
/// 
/// The vector equation is equivalent to a matrix equation of the form
/// AX = B
/// where A is an m×n matrix, x is a column vector with n entries, and b is a
/// column vector with m entries.
///
/// @param a the coefficients of the system
/// @param b the constant terms
///
/// @return vector X indicate the solution
template<class T>
std::vector<T>
solve_system_of_linear_equations(
    std::vector< std::vector<T> > a,
    std::vector<T> b
) {
    const size_t n = a.size();
    Matrix<T> c(n, n + 1);
    for (size_t i = 0; i < n; i++) {
        assert(a[i].size() == n);
        for (size_t j = 0; j < n; j++)
            c[i][j] = a[i][j];
    }
    for (size_t i = 0; i < n; i++)
        c[i][n] = b[i];
    size_t swapCount, rank;
    gaussian_elimination(&c, &swapCount, &rank);
    if (rank < n)
        return std::vector<T>();
    for (size_t i = 0; i < n; i++)
        if (iszero(c[i][i]))
            return std::vector<T>();
    std::vector<T> result(n);
    for (size_t i = 0; i < n; i++)
        result[i] = c[i][n];

    size_t i = n;
    while (i --> 0) {
        // You could call "-->" downto operator, means "for i: n-1 downto 0".
        //
        // This is a very complicated operator, so C++ Standard committee even
        // placed its description in two different parts of Standard. You could
        // read about it in 5.2.6/2 and 5.9 in C++03 Standard.
        for (size_t j = i + 1; j < n; j++)
            result[i] -= c[i][j] * result[j];
        result[i] /= c[i][i];
    }
    return result;
}
} // namespace sbl 
#endif

