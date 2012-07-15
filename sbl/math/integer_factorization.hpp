#ifndef _sbl_integer_factorization
#define _sbl_integer_factorization
#include<map>
#include<vector>
#include<algorithm>
#include<cassert>
#include"gcd.hpp"
#include"isprime.hpp"
#include"../utility/foreach.hpp"
#include"../utility/bits.hpp"

namespace sbl {
/// @brief factorize a given integer
/// \post \prod{k^{result[k]}} = n

template<class T>
std::map<T, size_t> factorize_integer(T n) {
    // http://en.wikipedia.org/wiki/Trial_division
    // CLRS 3rd edition P975
    std::map<T, size_t> result;
    for (T i = 2; i <= integer_sqrt(n); i++)
        while (n % i == 0) {
            n /= i;
            ++result[i];
        }
    if (n > 1)
        result[n] = 1;
    return result;
}

/// Get one divisor of a number.
/// \pre n is not a prime number.
/// \pre n > 1
/// \post result > 1
/// \post result < n
/// \post n % result == 0
template<class T> T get_divisor(T n) {
    // use pollard rho algorithm
    assert(n > 1);
    if (n % 2 == 0) return 2;
    assert(!isprime(n));
    for (T c(1); true; ++c) {
        assert(c < n);
        T x(2), y(2), d(1);
        do {
            x = add_mod(mul_mod(x, x, n), c, n);
            y = add_mod(mul_mod(y, y, n), c, n);
            y = add_mod(mul_mod(y, y, n), c, n);
            d = gcd(std::max(x - y, y - x), n);
        } while (d == 1);
        if (d != n) return d;
    }
}

/// @brief factorize a given integer
///
/// @param n number we want to factorize.
/// @param a Output, a[0] * a[1] * ... * a.back() == n
///
/// \pre a must be empty
/// \post \prod{a[k]} = n
template<class T, class Container>
void factorize_integer(T n, Container *a) {
    if (isprime(n)) {
        a->push_back(n);
    } else {
        T x = get_divisor(n);
        factorize_integer(x, a);
        factorize_integer(n / x, a);
    }
}

/// Get all the divisors of a number.
/// @return list of all divisors.
template<class T>
std::vector<T> get_all_divisor(T n) {
    std::vector<T> result(1, 1);
    AUTO(a, factorize_integer(n));
    foreach(i, a) {
        size_t total = result.size();
        for (size_t j = 0; j < total; j++) {
            T value = result[j];
            for (size_t k = 0; k < (size_t)i.second; k++) {
                value *= i.first;
                result.push_back(value);
            }
        }
    }
    return result;
}
} // namespace sbl
#endif
