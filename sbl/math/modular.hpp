#ifndef _sbl_modular
#define _sbl_modular
#include<algorithm>
#include"../utility/bits.hpp"

namespace sbl {


/// \return (x + y) % z
/// \pre x >= 0 and x < z
/// \pre y >= 0 and y < z
template<class T>
T add_mod_fast(T x, T y, T z) {
    assert(x >= 0 and x < z);
    assert(y >= 0 and y < z);
    if (addition_is_safe(x, y) and x + y < z)
        return x + y;

    // Either x + y is overflowed, or x + y < z if false,
    // we have x + y >= z anyway.
    return x - (z - y);
}

/// \return (x * y) % z
/// \pre x >= 0 and x < z
template<class T, class U>
T mul_mod_fast(T x, U y, T z) {
    assert(x >= 0 and x < z);
    if (y == 0)
        return 0;
    if (y % 2 == 1) {
        T n = mul_mod_fast(x, y - 1, z);
        return add_mod_fast(x, n, z);
    } else {
        T n = add_mod_fast(x, x, z);
        return mul_mod_fast(n, y / 2, z);
    }
}

/// \return (x ** y) % z
/// \pre x >= 0 and x < z
template<class T, class U>
T pow_mod_fast(T x, U y, T z) {
    assert(x >= 0 and x < z);
    if (y == 0)
        return 1;
    if (y % 2 == 1) {
        T n = pow_mod_fast(x, y - 1, z);
        return mul_mod_fast(x, n, z);
    } else {
        T n = mul_mod_fast(x, x, z);
        return pow_mod_fast(n, y / 2, z);
    }
}

/// \return a % b
/// \post 0 <= result and result < b
/// \post result = a (mod b)
template<class T>
T mod(T a, T b) {
    a %= b;
    if (a < 0) 
        a += b;
    return a;
}

/// \return (x + y) % z
template<class T>
T add_mod(T x, T y, T z) {
    return add_mod_fast(mod(x, z), mod(y, z), z);
}

/// \return (x * y) % z
template<class T>
T mul_mod(T x, T y, T z) {
    return mul_mod_fast(mod(x, z), y, z);
}

/// \return (x ** y) % z
template<class T>
T pow_mod(T x, T y, T z) {
    return pow_mod_fast(mod(x, z), y, z);
}

} // namespace sbl
#endif
