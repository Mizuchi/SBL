#ifndef _sbl_bits
#define _sbl_bits
#include"../base.hpp"
#include<algorithm>
#include<limits>

namespace sbl {
// more information:
// http://graphics.stanford.edu/~seander/bithacks.html

template<class T>
void __is_integer() {
    STATIC_ASSERT(std::numeric_limits<T>::is_integer, must_be_a_integer);
}

/// Return a ** n, n must be a integer
template<class T, class U>
T power_integer(T a, U n) {
    __is_integer<T>();
    if (n == 0)
        return 1;
    if (n % 2 == 1) {
        return a * power_integer(a, n - 1);
    } else {
        T sqr = a * a;
        return power_integer(sqr, n / 2);
    }
}

/// Return 2 ** x
template<class T>
T power_of_two(T x) {
    __is_integer<T>();
    assert(x >= 0);
    return T(1) << x;
}

/// Returns whether u-th bit in t is set
template<class T>
bool contain(T t, T u) {
    __is_integer<T>();
    return (t bitand power_of_two(u)) != 0;
};

/// Return digit sum of the binary representation of a given number.
/// It is also called the population count, popcount or sideways sum.
/// \link http://en.wikipedia.org/wiki/Hamming_weight \endlink
template<class T>
size_t count_set_bits(T number) {
    // XXX: performance
    __is_integer<T>();
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
    // XXX: performance
    __is_integer<T>();
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
    // XXX: performance
    __is_integer<T>();
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
    __is_integer<T>();
    if (number == 0)
        return 0;
    return T(1) << (highest_set_bit_index(number) - 1);
}

/// Return minimum number bitand with given number is non-zero.
template<class T>
T lowest_set_bit(T number) {
    __is_integer<T>();
    if (number == 0)
        return 0;
    return T(1) << (lowest_set_bit_index(number) - 1);
}

/// Return random integer number less than a given number.
template<class T>
T random(T number = std::numeric_limits<int>::max()) {
    __is_integer<T>();

    // random last n bits
    struct {
        T operator()(size_t n) const {
            // XXX: performance
            T result = 0;
            for (size_t i = 0; i < n; i++) {
                result += rand() % 2;
                result *= 2;
            }
            return result;
        }
    } random_n_bits;

    AUTO(n, highest_set_bit_index(number));
    T result = random_n_bits(n);
    return result % number;
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
    // TODO: I don't understand this code?
    __is_integer<T>();
    assert(p != 0);
    T l = p bitand - p, r = p + l, i = r bitand compl p;
    return r bitor(((i / l) >> 1) - 1);
}

/// Return whether a + b will not overflow
template<class T> bool addition_is_safe(T a, T b) {
    __is_integer<T>();

    // Technically, signed integer overflow causes undefined behavior, while
    // unsigned integer overflow causes the number to be reduced modulo a power
    // of two, meaning that unsigned integers "wrap around" on overflow.
    // (ISO/IEC 14882:2003 3.9.1.4)

    T min = std::numeric_limits<T>::min();
    T max = std::numeric_limits<T>::max();

    if (a > 0 and b > 0) {
        // indicate max >= a + b
        return max - a >= b and max - b >= a;
    }
    if (a < 0 and b < 0) {
        // indicate min <= a + b
        return min - a <= b and min - b <= a;
    }

    // Otherwise, a and b have different sign will never overflow
    return true;
}

/// Return whether a * b will not overflow
template<class T>
bool multiplication_is_safe(T a, T b) {
    __is_integer<T>();
    // We use plus operator to emulate multiplies operator
    if (b == 0)
        return true;
    if (b % 2 == 1) {
        if (multiplication_is_safe(a, b - 1)) {
            // consider a + a * (b - 1) == a + b
            T c = a * (b - 1);
            return addition_is_safe(a, c);
        } else {
            return false;
        }
    } else {
        assert(b % 2 == 0 and b > 0);
        if (addition_is_safe(a, a)) {
            // consider (a + a) * b / 2 == a + b
            T c = a + a;
            return multiplication_is_safe(c, b / 2);
        } else {
            return false;
        }
    }
}

/// Return whether a ** b will not overflow
template<class T, class U>
bool exponentiation_is_safe(T a, U b) {
    __is_integer<T>();

    // We use multiplies operator to emulate power operator
    if (b == 0)
        return true;
    if (b % 2 == 1) {
        if (exponentiation_is_safe(a, b - 1)) {
            T c = power_integer(a, (b - 1));
            return multiplication_is_safe(a, c);
        } else {
            return false;
        }
    } else {
        assert(b % 2 == 0 and b > 0);
        if (multiplication_is_safe(a, a)) {
            T c = a * a;
            return exponentiation_is_safe(c, b / 2);
        } else {
            return false;
        }
    }
}

/// Return greatest integer less than or equal to the square root of given integer.
template<class T>
T integer_sqrt(T number) {
    // bisection method
    // XXX: Should rewrite with newton method for performance reason.
    // http://en.wikipedia.org/wiki/Integer_square_root
    // http://code.activestate.com/recipes/577821-integer-square-root-function/
    T left = 0;
    T right = std::max(number, 2);
    while (right - left > 1) {
        T middle = (left + right) / 2;
        if (middle <= number / middle)
            left = middle;
        else
            right = middle;
    }
    return left;
}

} // namespace sbl
#endif
