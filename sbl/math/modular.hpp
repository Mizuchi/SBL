#ifndef _sbl_modular
#define _sbl_modular
#include<algorithm>
#include"../utility/bits.hpp"

namespace sbl {
// (x + y) % z
template<class T>
T add_mod(T x, T y, T z) {
    assert(x >= 0 and x < z);
    assert(y >= 0 and y < z);
    if (addition_is_safe(x, y) and x + y < z)
        return x + y;

    // Either x + y is overflowed, or x + y < z if false,
    // we have x + y > z anyway.
    return x - (z - y);
}

// (x * y) % z
template<class T>
T mul_mod(T x, T y, T z) {
    if (y == 0)
        return 0;
    if (y % 2 == 1) {
        T n = mul_mod(x, y - 1, z);
        return add_mod(x, n, z);
    } else {
        T n = add_mod(x, x, z);
        return mul_mod(n, y / 2, z);
    }
}

// (x ** y) % z
template<class T>
T pow_mod(T x, T y, T z) {
    if (y == 0)
        return 1;
    if (y % 2 == 1) {
        T n = pow_mod(x, y - 1, z);
        return mul_mod(x, n, z);
    } else {
        T n = mul_mod(x, x, z);
        return pow_mod(n, y / 2, z);
    }
}
} // namespace sbl
#endif
