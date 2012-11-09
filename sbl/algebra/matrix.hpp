#ifndef _sbl_matrix
#define _sbl_matrix
#include<iostream>
#include<vector>
#include<numeric>
#include"element.hpp"
#include"../utility/macro.hpp"

namespace sbl {

using std::size_t;

#define formatrix(MATRIX, ELEMENT, ROW, COL)                                   \
    FOREACH_BEGIN()                                                            \
    for(size_t ROW = 0; ROW < (MATRIX).row_size() and not BREAKED(); ++ROW)    \
        for(size_t COL = 0; COL < (MATRIX).col_size() and not BREAKED(); ++COL)\
            ASSIGN_AUTO(ELEMENT, (MATRIX)[ROW][COL])                           \
            FOREACH_END()

template<class T>
class Matrix {
    protected:
        std::vector<T> a;
        size_t rowSize, colSize;

    public:
        typedef T value_type;
        Matrix(): rowSize(0), colSize(0) {}
        Matrix(size_t n, size_t m)
            : a(n * m), rowSize(n), colSize(m) {}
        Matrix(const std::vector<T> &v)
            : a(v), rowSize(a.size()), colSize(1) {}

        operator std::vector<T> () const {
            assert(colSize == 1);
            return a;
        }

        void resize(size_t n, size_t m) {
            rowSize = n;
            colSize = m;
            a.resize(n * m);
        }

        T *operator[](size_t index) {
            assert(index < rowSize);
            return a.data() + index * colSize;
        }

        const T *operator[](size_t index) const {
            assert(index < rowSize);
            return a.data() + index * colSize;
        }

        size_t row_size() const {
            return rowSize;
        }

        size_t col_size() const {
            return colSize;
        }

        void swap(Matrix &b) {
            swap(rowSize, b.rowSize);
            swap(colSize, b.colSize);
            a.swap(b.a);
        }

        void fill(T x) {
            a.assign(a.size(), x);
        }

}; // class Matrix

template<class T>
bool operator==(const Matrix<T> &a, const Matrix<T> &b) {
    if(not __same_size(a, b))
        return false;
    formatrix(a, k, i, j) {
        if(k != b[i][j])
            return false;
    }
    return true;
}


template<class T>
std::ostream &operator<<(std::ostream &os, const Matrix<T> &a) {
    for (size_t i = 0; i < a.row_size(); i++) {
        if (i == 0)
            os << '[';
        else
            os << ' ';

        for (size_t j = 0; j < a.col_size(); j++) {
            os << a[i][j];
            if (j + 1 < a.col_size()) 
                os << ' ';
        }

        if (i + 1 == a.row_size())
            os << "]\n";
        else
            os << "\n";
    }
    return os;
}

template<class T>
bool __same_size(const Matrix<T> &lhs, const Matrix<T> &rhs) {
    return lhs.row_size() == rhs.row_size() and
           lhs.col_size() == rhs.col_size();

}

template<class T>
Matrix<T> &operator+=(Matrix<T> &a, const Matrix<T> &b) {
    assert(__same_size(a, b));
    formatrix(a, &k, i, j) {
        k += b[i][j];
    }
    return a;
}

template<class T>
Matrix<T> operator+(Matrix<T> a, const Matrix<T> &b) {
    return a += b;
}

template<class T>
Matrix<T> &operator-=(Matrix<T> &a, const Matrix<T> &b) {
    assert(__same_size(a, b));
    formatrix(a, &k, i, j) {
        k -= b[i][j];
    }
    return a;
}

template<class T>
Matrix<T> operator-(Matrix<T> a, const Matrix<T> &b) {
    return a -= b;
}

template<class T>
Matrix<T> operator*(const Matrix<T> &a, const Matrix<T> &b) {
    assert(a.col_size() == b.row_size());
    Matrix<T> c(a.row_size(), b.col_size());
    formatrix(c, &x, i, j) {
        x = a[i][0] * b[0][j];
        for (size_t k = 1; k < a.col_size(); k++)
            x += a[i][k] * b[k][j];
    }
    return c;
}
template<class T>
Matrix<T> &operator*=(Matrix<T> &a, const Matrix<T> &b) {
    return a = a * b;
}

template<class T>
Matrix<T> identity(std::multiplies< Matrix<T> >, const Matrix<T> &x) {
    assert(x.row_size() == x.col_size());
    Matrix<T> a(x.row_size(), x.col_size());
    formatrix(a, &k, i, j) {
        if (i == j)
            k = identity(std::multiplies<T>());
        else
            k = identity(std::plus<T>());
    }
    return a;
}

template<class T>
Matrix<T> identity(std::plus< Matrix<T> >, Matrix<T> x) {
    x.fill(identity(std::plus<T>()));
    return x;
}

template<class T, class U>
T pow(T a, U n) {
    return n % 2 ? a * pow(a, n - 1) :
           n > 0 ? pow(a * a, n - 1) :
           identity(std::multiplies<T>(), a);
}

template<class T>
Matrix<T> transpose(const Matrix<T> &a) {
    Matrix<T> b(a.col_size(), a.row_size());
    formatrix(b, &k, i, j) {
        k = a[j][i];
    }
    return b;
}

template<class T>
Matrix<T> get_row(const Matrix<T>& a, size_t rowIndex) {
    assert(rowIndex >= 0);
    assert(rowIndex < a.row_size());
    Matrix<T> result(1, a.col_size());
    for(size_t colIndex = 0; colIndex < a.col_size(); colIndex++) 
        result[0][colIndex] = a[rowIndex][colIndex];
    return result;
}

template<class T>
Matrix<T> get_col(const Matrix<T>& a, size_t colIndex) {
    assert(colIndex >= 0);
    assert(colIndex < a.col_size());
    Matrix<T> result(a.row_size(), 1);
    for(size_t rowIndex = 0; rowIndex < a.row_size(); rowIndex++) 
        result[rowIndex][0] = a[rowIndex][colIndex];
    return result;
}

/// @brief Hermite conjugate
template<class T>
Matrix<T> adjoint(const Matrix<T> &a) {
    return conj(transpose(a));
}

template<class T>
Matrix<T> conj(const Matrix<T> &a) {
    Matrix<T> result = a;
    formatrix(result, &k, i, j) {
        k = conj(k);
    }
    return result;
}

template<class T>
T dot_product(const Matrix<T> &a, const Matrix<T> &b) {
    assert(a.col_size() == 1);
    assert(b.col_size() == 1);
    assert(a.row_size() == b.row_size());
    Matrix<T> c = adjoint(a) * b;
    assert(c.row_size() == 1);
    assert(c.col_size() == 1);
    return c[0][0];
}

template<class T>
bool is_hermitian_matrix(const Matrix<T> &a) {
    return a == adjoint(a);
}

/// @return whether a matrix is orthogonal (正交矩阵)
template<class T>
bool is_orthogonal(const Matrix<T> &a, const Matrix<T> &b) {
    return a * b == identity(std::plus<T>());
}

/// @return whether a matrix is unitary (酉矩阵)
template<class T>
bool is_unitary(const Matrix<T> &a) {
    Matrix<T> p = a * adjoint(a);
    return p == identity(std::multiplies< Matrix<T> >(), p);
}

} // namespace sbl
#endif
