#ifndef _sbl_random
#define _sbl_random

#include<cstdlib>
namespace sbl {
unsigned long random() {
    static const unsigned long A = 48271;
    static const unsigned long Q = 44488;
    static const unsigned long R = 3399;
    static unsigned long x = rand();
    return x = A * (x % Q) - R * (x / Q);
}
} // namespace sbl 
#endif 
