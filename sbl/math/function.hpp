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
template<class T> T euler(T n) {
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



/// Mobius function
/// return 1  if n is square-free with an even number of prime factors.
/// return -1 if n is square-free with an odd number of prime factors.
/// return 0  if n is not square-free.
/// \pre n > 0 (mobius(0) is undefined)
template<class T>
signed char mobius(T n) {
    if (n == 1) return 1;
    std::vector<T> a;
    factorize_integer(n, &a);
    std::sort(a.begin(), a.end());

    // check whether n is square-free or not
    if(std::unique(a.begin(), a.end()) == a.end())
        return a.size() % 2 ? 1 : -1;
    else
        return 0;
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
} // namespace sbl
#endif
