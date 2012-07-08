#ifndef _sbl_is_prime
#define _sbl_is_prime
#include"modular.hpp"

namespace sbl {
/// Return whether a integer number is a prime
template<class T>
bool isprime(T x) {
    // http://en.wikipedia.org/wiki/Primality_test
    // http://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test
    struct {
        bool operator()(T n, T a, T d, unsigned long s) const {
            d = pow_mod(a, d, n);
            if (d == 1) return true;
            while (s--)
                if (d + 1 == n)
                    return true;
                else
                    d = mul_mod(d, d, n);
            return false;
        }
    } test;
    if (x < 2 or (x > 2 and x % 2 == 0)) return false;
    T a[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 0};
    unsigned long s = 0;
    if (std::numeric_limits<T>::digits <= 32 or
        x <= static_cast<T>(0xFFFFFFFF))
        a[1] = 7, a[2] = 61, a[3] = 0;
    T d = x - 1;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }
    for (unsigned int i = 0; 0 < a[i] and a[i] < x; i++)
        if (not test(x, a[i], d, s))
            return false;
    return true;
}
} // namespace sbl
#endif
