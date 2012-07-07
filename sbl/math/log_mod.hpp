#ifndef _sbl_mod_log
#define _sbl_mod_log
#include"modular.hpp"
#include"gcd.hpp"
#include"../utility/bits.hpp"
#include<map>

namespace sbl {
/// Compute discrete logarithm in O(sqrt(p))
/// \post x ** result == y (mod z)
/// \post result <= z
/// \pre z is a prime number
/// \link http://en.wikipedia.org/wiki/Discrete_logarithm \endlink
template<class T> T log_mod(T x, T y, T z) {

    // http://en.wikipedia.org/wiki/Baby-step_giant-step
    //
    //
    // The base idea is we can write result in this format:
    //
    // result = i * sqrt(z) + j (here i, j <= sqrt(z))
    //
    // So the first step (baby step), we enumerate j and store all (x ** j % z)
    // in a hash table. Later, the second step (giant step), we enumerate i and
    // compute (y * x ** (- i * sqrt(z)) % z) and check whether it is in the
    // hash table. If true, we find:
    //
    //     y * x **(-i * sqrt(z)) == x ** j (mod z)
    //
    // ==> y == (x ** j) * (x ** (i * sqrt(z))) (mod z) 
    //
    // ==> y == (x ** (i * sqrt(z) + j)) (mod z)
    //
    // Then (result = i * sqrt(z) + j) is what we are looking for.
    //
    
    // assert(isprime(z));
    x %= z;
    y %= z;
    T sqrtOfZ = integer_sqrt(z);

    // compute the hash table
    // table[x ** i % z] = i (0 <= i < sqrt(z))
    std::map<T, T> table;
    for (T i = 0, k = 1; i <= sqrtOfZ; i++) {
        table[k] = i;
        k = mul_mod(k, x, z);
    }

    // Later, we compute v = x ** (-sqrt(z))
    T v = modular_inverse(pow_mod(x, sqrtOfZ, z), z);
    for (T i = 0, k = y; i <= sqrtOfZ; i++) {
        // k = (y * x ** (- i * sqrt(z)) % z) 
        if (table.count(k))
            return i * sqrtOfZ + table[k];
        k = mul_mod(k, v, z);
    }
    return -1;
}
} // namespace sbl
#endif
