#ifndef _sbl_bits
#define _sbl_bits
#include"../base.hpp"
#include<algorithm>
#include<limits>

namespace sbl {
// more information:
// http://graphics.stanford.edu/~seander/bithacks.html

/// Return 2 ** x
template<class T>
T power_of_two(T x) {
    assert(x >= 0);
    return T(1) << x;
}

/// Returns whether u-th bit in t is set
template<class T, class U>
bool contain(T t, U u) {
    return (t bitand power_of_two(u)) != 0;
};

/// Return digit sum of the binary representation of a given number.
/// It is also called the population count, popcount or sideways sum.
/// \link http://en.wikipedia.org/wiki/Hamming_weight \endlink
template<class T> size_t count_set_bits(T number) {
    size_t result = 0;
    while (number != 0) {
        if (number % 2 == 1) result += 1;
        number /= 2;
    }
    return
        result;
}

/// find first (least significant) bit set in a value of an integral type.
/// 1-based (like ffs()), 0 means no bits are set (number == 0)
template<class T>
size_t highest_set_bit_index(T number) {
    if (number == 0)
        return 0;
    size_t result = 0;
    while (number != 0) {
        result += 1;
        number /= 2;
    }
    return result;
}

/// find last (most significant) bit set in a value of an integral type.
/// 1-based (like ffs()), 0 means no bits are set (number == 0)
template<class T>
size_t lowest_set_bit_index(T number) {
    if (number == 0)
        return 0;
    size_t result = 1;
    while (number % 2 == 0) {
        result += 1;
        number /= 2;
    }
    return result;
}

/// Return next power of two greater than x.
template<class T>
T highest_set_bit(T number) {
    if (number == 0)
        return 0;
    return T(1) << (highest_set_bit_index(number) - 1);
}

/// Return minimum number bitand with given number is non-zero.
template<class T>
T lowest_set_bit(T number) {
    if (number == 0)
        return 0;
    return T(1) << (lowest_set_bit_index(number) - 1);
}

/// Enumerate every subset in a number
/// \post subset bitand number == subset
#define forsubset(subset, number) \
        for(AUTO(subset, number); subset > 0; subset = (subset - 1) bitand number)

/// Return next number has the same number of set bits with given number.
/// \post count_set_bits(result) == count_set_bits(p)
/// \post result > p
template<class T>
T next_combination(T p) {
    assert(p != 0);
    T l = p bitand -p, r = p + l, i = r bitand compl p;
    return r bitor (((i / l) >> 1) - 1);
}

/// Return whether a + b will not overflow
template<class T, class U>
bool addition_is_safe(T a, U b) {
    size_t highestBitIndex = std::max(std::numeric_limits<T>::digits,
                                      std::numeric_limits<T>::digits);
    size_t aBitIndex = highest_set_bit_index(a);
    size_t bBitIndex = highest_set_bit_index(b);
    return (aBitIndex < highestBitIndex - 1 and bBitIndex < highestBitIndex - 1);
}

/// Return whether a * b will not overflow
template<class T, class U>
bool multiplication_is_safe(T a, U b) {
    size_t highestBitIndex = std::max(std::numeric_limits<T>::digits,
                                      std::numeric_limits<T>::digits);
    size_t aBitIndex = highest_set_bit_index(a);
    size_t bBitIndex = highest_set_bit_index(b);
    return (aBitIndex + bBitIndex < highestBitIndex);
}

/// Return whether a ** b will not overflow
template<class T, class U>
bool exponentiation_is_safe(T a, U b) {
    size_t highestBitIndex = std::numeric_limits<T>::digits;
    size_t possibleBitIndex = highest_set_bit_index(a) * b;
    return (possibleBitIndex + 1 < highestBitIndex);
}

} // namespace sbl
#endif
