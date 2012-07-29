#ifndef _sbl_primitive_root
#define _sbl_primitive_root
#include"../utility/random.hpp"
#include"../utility/foreach.hpp"
#include"integer_factorization.hpp"
#include"function.hpp"
#include"modular.hpp"

namespace sbl {

/// \return whether a integer number has a primitive root
bool has_primitive_root(unsigned long n) {
    struct {
        bool operator()(unsigned long n) {
            if (n <= 1)
                return false;
            AUTO(a, factorize_integer(n));
            return a.size() == 1 and a.begin()->first % 2 == 1;
        }
    } only_prime_divisor;
    if (n == 2 or n == 4)
        return true;
    if (only_prime_divisor(n))
        return true;
    if (n % 2 == 0 and only_prime_divisor(n / 2))
        return true;
    return false;
}

class IsPrimitiveRoot {
    private:
        std::vector<unsigned long> a;
        const unsigned long n, phi;
    public:
        IsPrimitiveRoot(unsigned long n): n(n), phi(sbl::euler(n)) {
            AUTO(s, factorize_integer(phi));
            foreach(i, s) a.push_back(i.first);
        }
        bool operator()(unsigned long g) {
            if (gcd(n, g) != 1)
                return false;
            bool isRoot = true;
            foreach(i, a) {
                if (pow_mod(g, phi / i, n) == 1) {
                    isRoot = false;
                    break;
                }
            }
            return isRoot;
        }
}; // struct IsPrimitiveRoot

/// \return Primitive root modulo n
unsigned long primitive_root(unsigned long n) {
    assert(has_primitive_root(n));
    IsPrimitiveRoot is_root(n);
    while (true) {
        unsigned long g = random() % (n - 1) + 1;
        if (is_root(g))
            return g;
    }
}


} // namespace sbl
#endif
