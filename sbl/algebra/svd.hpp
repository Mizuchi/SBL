#ifndef _sbl_svd_decomposition
#define _sbl_svd_decomposition
#include"../base.hpp"

namespace sbl {
template <class T>
void svd_decomposition(
    const Matrix<T> &a,
    Matrix<T> *oS,
    Matrix<T> *oV,
    Matrix<T> *oD
) {
    STATIC_ASSERT(sizeof(T) == 0, "Not Implemented");
}
} // namespace sbl
#endif
