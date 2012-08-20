#ifndef _sbl_formula
#define _sbl_formula
#include<vector>

namespace sbl {
/// \return number of permutations of n distinct objects
/// \code{.cpp}
/// assert(count_permutation<int>(7,3) == 7 * 6 * 5);
/// \endcode
template<class T>
T count_permutation(std::size_t n, std::size_t k) {
    T ans = 1;
    for (std::size_t i = 1; i <= k; ++i) {
        ans *= n - k + i;
    }
    return ans;
}

/// Binomial coefficient
/// \return number of k-combinations from a given set S of n elements
/// \code{.cpp}
/// assert(count_combination<int>(7,3) == 7 * 6 * 5 / (3 * 2));
/// \endcode
template<class T>
T count_combination(std::size_t n, std::size_t k) {
    T ans = 1;
    for (std::size_t i = 1; i <= k; ++i) {
        ans *= n - k + i;
        ans /= i;
    }
    return ans;
}

/// \return n * (n-1) * (n-2) * ... * 1
template<class T>
T factorial(std::size_t n) {
    T ret = 1;
    for (std::size_t i = 1; i <= n; ++i)
        ret *= i;
    return ret;
}

} // namespace sbl
#endif
