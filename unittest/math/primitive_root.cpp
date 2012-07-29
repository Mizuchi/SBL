#include"../../sbl/math/primitive_root.hpp"

#include"../../sbl/math/modular.hpp"
#include"../../sbl/math/function.hpp"
#include"../../sbl/math/prime.hpp"
#include"../../sbl/utility/foreach.hpp"
#include"../../sbl/utility/random.hpp"

TEST(math, primitive_root_prime) {
    using namespace sbl;
    AUTO(s, generate_prime(200));
    foreach(n, s) {
        EXPECT_TRUE(has_primitive_root(n));
        int x = primitive_root(n);
        int phi = euler(n);
        EXPECT_EQ(pow_mod(x, phi, (int)n), 1)
                << "x: " << x << ", n: " << n << ", phi(n): " << euler(n) ;
        for (int i = 1; i < phi; i++)
            EXPECT_NE(pow_mod(x, i, (int)n), 1)
                    << "x: " << x << ", n: " << n << ", i: " << i ;
    }
}

TEST(math, primitive_root) {
    using namespace sbl;
    std::vector<unsigned long> s;
    for (int i = 0; i < 50; i++)
        s.push_back(sbl::random() % 500);
    foreach(n, s) {
        if(not has_primitive_root(n)) 
            continue;
        int x = primitive_root(n);
        int phi = euler(n);
        EXPECT_EQ(pow_mod(x, phi, (int)n), 1)
                << "x: " << x << ", n: " << n << ", phi(n): " << euler(n) ;
        for (int i = 1; i < phi; i++)
            EXPECT_NE(pow_mod(x, i, (int)n), 1)
                    << "x: " << x << ", n: " << n << ", i: " << i ;
    }
}
