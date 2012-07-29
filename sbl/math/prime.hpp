#ifndef _sbl_prime
#define _sbl_prime
#include"modular.hpp"

namespace sbl {
/// Return whether a integer number is a prime
template<class T>
bool isprime(T x) {
    // http://en.wikipedia.org/wiki/Primality_test
    // http://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test
    // CLRS 3rd edition P968
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

// arg: 20
// ret: 2 3 5 7 11 13 17 19
static std::vector<size_t> generate_prime(size_t n) {
    std::vector<bool> a(++n);
    std::vector<size_t> p;
    for (size_t i = 2; i < n; i++) {
        if (a[i] == 0) p.push_back(i);
        for (size_t j = 0; j < p.size() and i * p[j] < n; j++) {
            a[i * p[j]] = 1;
            if (i % p[j] == 0) break;
        }
    }
    return p;
}

// Port from http://en.wikipedia.org/wiki/Sieve_of_atkin
// arg: 10
// ret: 00110101000
static std::vector<bool> generate_prime_fast(size_t limit) {
    std::vector<bool> isPrime(limit + 1);
    for (size_t x = 1, xx = 1; xx <= limit; xx += 2 * x ++ + 1)
        for (size_t y = 1, yy = 1; yy <= limit; yy += 2 * y ++ + 1) {
            size_t n = 4 * xx + yy;
            if (n <= limit and (n % 12 == 1 or n % 12 == 5))
                isPrime[n] = !isPrime[n];
            n = 3 * xx + yy;
            if (n <= limit and n % 12 == 7)
                isPrime[n] = !isPrime[n];
            n = 3 * xx - yy;
            if (x > y and n <= limit and n % 12 == 11)
                isPrime[n] = !isPrime[n];
        }
    for (size_t n = 5, nn = 25; nn <= limit; nn += 2 * n ++ + 1)
        if (isPrime[n])
            for (size_t k = nn; k <= limit; k += nn)
                isPrime[k] = false;
    isPrime[2] = isPrime[3] = true;
    return isPrime;
}

} // namespace sbl
#endif
