#ifndef _sbl_hash_permutation
#define _sbl_hash_permutation
#include "../structure/fenwick_tree.hpp"
#include<algorithm>

namespace sbl {
    using std::size_t;
/* -----------------------------------------------------------------------*/
/**
 * @brief innversion table
 *
 * @param a an all permutation in 0..n-1
 *
 * @return the index of this all permutation (0..n!)
 */
/* -------------------------------------------------------------------------*/
template<class T>
T permutation2hash(std::vector<size_t> a) {
    size_t n = a.size();
    std::vector<size_t> b(n);
    std::copy(a.begin(), a.end(), b.begin());
    std::sort(b.begin(), b.end());
    for (size_t i = 0; i < n; i++)
        a[i] = std::lower_bound(b.begin(), b.end(), a[i]) - b.begin();
    FenwickTree<size_t> d(n);
    T k = 1, ans = 0;
    for (long i = n - 1; i >= 0; i--) {
        size_t c = d.prefix_sum(a[i]);
        d.increase_nth_element(a[i], 1);
        ans += k * c;
        k *= (n - i);
    }
    return ans;
}

/* -----------------------------------------------------------------------*/
/**
 * @brief Lehmer code
 *
 * @param k index of all permutation
 * @param n size of all permutation
 *
 * @return an all permutation
 */
/* -------------------------------------------------------------------------*/
template<class T>
std::vector<size_t> hash2permutation(T k, size_t n) {
    std::vector<size_t> ret(n);
    if (n == 0) return ret;
    std::vector<T> f(n);
    f[0] = 1;
    for (size_t i = 1; i < n; i++) f[i] = f[i - 1] * i;
    for (size_t i = 0; i < n; i++) {
        ret[i] = k / f[n - i - 1];
        k %= f[n - i - 1];
    }
    FenwickTree<long> b(n);
    for (size_t i = 0; i < n; i++) b.increase_nth_element(i, 1);
    for (size_t i = 0; i < n; i++) {
        ret[i] = b.min_index_that_prefix_sum_greater_than(ret[i]);
        b.increase_nth_element(ret[i], -1);
    }
    return ret;
}

} // namespace sbl
#endif
