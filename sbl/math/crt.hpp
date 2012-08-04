#ifndef _sbl_chinart
#define _sbl_chinart
#include<functional>
#include<numeric>
#include"gcd.hpp"
#include"modular.hpp"

namespace sbl {

/// \return a solution to a Chinese Remainder Theorem problem.
/// \pre gcd(m[i], m[j]) == 1
/// \post return % a[i] == m[i]
/// arg: [2, 3, 2]; [3, 5, 7]
/// ret: 23
template < 
    class Return,
    class IterBegA,
    class IterEndA,
    class IterBegM,
    class IterEndM 
> Return crt(
    IterBegA begA,
    IterEndA endA,
    IterBegM begM,
    IterEndM endM
) {
    assert(std::distance(begA, endA) == std::distance(begM, endM));
    Return result(0);
    Return p = 1;
    p = std::accumulate(begM, endM, p, std::multiplies<Return>());
    while (begA != endA) {
        assert(begM != endM);
        Return t = p / *begM;
        Return x, y;
        gcd<Return, Return>(t, *begM, &x, &y);
        
        // result += t * x * A[i]
        result = add_mod(result, mul_mod(t, mul_mod(x, *begA, p), p), p);

        ++begA;
        ++begM;
    }
    return result;
}
} // namespace sbl
#endif
