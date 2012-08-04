#ifndef _sbl_function
#define _sbl_function
#include<set>
#include<map>
#include<algorithm>
#include"../utility/foreach.hpp"
#include"integer_factorization.hpp"
#include"gcd.hpp"

namespace sbl {

/// Euler's totient function
/// Counts the number of positive integers less than or equal to n that are
/// relatively prime to n.
template<class T>
T euler(T n) {
    if (n == 1) return 1;
    std::vector<T>a;
    factorize_integer(n, &a);
    std::sort(a.begin(), a.end());
    a.erase(std::unique(a.begin(), a.end()), a.end());
    foreach(i, a) {
        n = n / i * (i - 1);
    }
    return n;
}

/// Generate Euler's totient function
static inline std::vector<size_t>
generate_euler(size_t n) {
    ++n;
    std::vector<size_t> a(n);
    a[1] = 1;
    for (size_t i = 2; i < n; i++)
        if (!a[i])
            for (size_t j = i; j < n; j += i) {
                if (a[j] == 0) 
                    a[j] = j;
                a[j] = a[j] / i * (i - 1);
            }
    return a;
}



/// Mobius function
/// return 1  if n is square-free with an even number of prime factors.
/// return -1 if n is square-free with an odd number of prime factors.
/// return 0  if n is not square-free.
/// \pre n > 0 (mobius(0) is undefined)
template<class T>
int mobius(T n) {
    // XXX: I don't know why, but return a signed char won't pass the unittest.
    if (n == 1) return 1;
    std::vector<T> a;
    factorize_integer(n, &a);
    std::sort(a.begin(), a.end());

    // check whether n is square-free or not
    if (std::unique(a.begin(), a.end()) == a.end())
        return a.size() % 2 == 0 ? 1 : -1;
    else
        return 0;
}

/// Generate Mobius Function
static inline std::vector<int> generate_mobius(size_t n) {
    ++n;
    std::vector<bool> b(n, true);
    std::vector<int> result(n, 1);
    for (size_t i = 2; i < n; i++)
        if (b[i]) {
            size_t j = i * i;
            result[i] = -1; // Prime
            for (size_t k = i * 2; k < n; k += i) {
                b[k] = 0;
                result[k] *= k % j ? -1 : 0;
            }
        }
    return result;
}

/// Carmichael function
/// The smallest positive integer m such that
/// a ** m % n == 1
/// for every integer a that is coprime to n.
///
/// \post a ** result % n == 1 (forall a satisfy gcd(a, n) == 1)
template<class T>
T carmichael(T n) {
    assert(n > 0);
    if (n == 1)
        return 1;
    if (n % 8 == 0)
        n /= 2;
    AUTO(b, factorize_integer(n));
    T result = 1;
    foreach(i, b) {
        T now = i.first - 1;
        for (size_t l = 1; l < i.second; l++) {
            assert(multiplication_is_safe(now, i.first));
            now *= i.first;
        }
        result = lcm(result, now);
        assert(result % now == 0);
    }
    return result;
}

/// @brief convert binary code to gray code
template<class T>
T binary2graycode(T a) {
    // http://en.wikipedia.org/wiki/Gray_code
    return a == 0 ? 0 : (a ^ (a >> 1));
}

} // namespace sbl
#endif
