#ifndef _sbl_math_solve
#define _sbl_math_solve
#include"gcd.hpp"
#include"modular.hpp"
namespace sbl {

/// \Return {x | a * x % n == b and 0 <= x and x < n}
template<class T> std::vector<T> 
solve_modular_linear_equations(T a, T b, T n) {
    // CLRS 2nd Edition Page. 868
    T x, y;
    T d = gcd(a, n, &x, &y);
    std::vector<T> result;
    result.reserve(d);
    if (b % d == 0) {
        result.push_back(mul_mod(x, b / d, n / d));
        for (size_t i = 1; i < (size_t)d; ++i)
            result.push_back(add_mod(result.back(), n / d,  n));
    }
    return result;
}
} // namespace sbl
#endif
