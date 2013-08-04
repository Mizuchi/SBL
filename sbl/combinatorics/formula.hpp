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

// /** @brief 从一些数中选K个数，使得第i个数选j的数对必须出现在pattern中 TODO
// *
// * @param pattern 数组A，表示第A[i].first个数可以选A[i].second，除此之外都禁止。
// *
// * @return 数组S[k]，表示选k个数的方案数。
// */
// template<class T>
// std::vector<T> CountPermutationInPattern(const std::vector< pair<int, int> > &pattern);

// /** @brief 计算有禁区的排列 TODO
//  *
//  * @param n n个数
//  * @param k 选k个数的排列
//  * @param pattern 第first的数不能选second
//  *
//  * @return 满足条件的排列个数
//  */
// template<class T>
// T CountPermutationWithForbiddenPattern(int n, int k, const std::vector< pair<int, int> > &pattern);

} // namespace sbl
#endif
