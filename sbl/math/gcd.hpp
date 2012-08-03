#ifndef _sbl_gcd
#define _sbl_gcd
#include<limits>
#include<cassert>

namespace sbl {

/// Return greatest common divisor of a and b.
/// \link http://en.wikipedia.org/wiki/Greatest_common_divisor \endlink
template<class T> T gcd(T a, T b) {
    // http://en.wikipedia.org/wiki/Euclidean_algorithm
    if (b != 0)
        return gcd(b, a % b);
    else
        return a;
}

/// Return least common multiple of a and b
/// \link http://en.wikipedia.org/wiki/Least_common_multiple \endlink
template<class T> T lcm(T a, T b) {
    return a / gcd(a, b) * b;
}

/// finds integers x and y that satisfy Bezout's identity
/// Return gcd of a and b
/// \post a*x + b*y == gcd(a, b)
template<class T, class U>
T gcd(T a, T b, U *x, U *y) {
    // http://en.wikipedia.org/wiki/Extended_Euclidean_algorithm
    // http://en.wikipedia.org/wiki/B%C3%A9zout%27s_identity
    assert(std::numeric_limits<U>::is_signed);
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    } else {
        T result = gcd(b, a % b, y, x);
        *y -= *x * (a / b);
        return result;
    }
}

/// Return a modular inverse for a modulo b
/// \pre gcd(a, b) == 1
/// \pre a % b != 0
/// \post a * result % b == 1
/// \post 0 <= result and result < b
template<class T>
T modular_inverse(T a, T b) {
    // http://en.wikipedia.org/wiki/Modular_multiplicative_inverse
    assert(gcd(a, b) == 1);

    // find x, y satisfy a * x + b * y = gcd(a, b)
    long long x, y;
    gcd(a, b, &x, &y);

    // this indicate a * x = 1 (mod b)
    // so x is what we looking for
    return (x % b + b) % b;
}
} // namespace sbl
#endif
