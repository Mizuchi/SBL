#ifndef _sbl_count_inversion
#define _sbl_count_inversion
#include"../base.hpp"

namespace sbl {

/// @return inversion number of a sequence
template<class T1, class T2>
unsigned long long count_inversion(T1 beg, T2 end) {
    // http://en.wikipedia.org/wiki/Inversion_(discrete_mathematics)
    //     F[N] = O(N*Log[N]) + F[N/2]
    // ==> F[N] = O(N*Log[N]*Log[N])
    size_t n = end - beg;
    if (n == 1) return 0;
    AUTO(mid, beg + n / 2);
    AUTO(cnt, count_inversion(beg, mid) + count_inversion(mid, end));
    for (AUTO(i, beg); i != mid; ++i)
        cnt += std::lower_bound(mid, end, *i) - mid;
    std::sort(beg, end);
    return cnt;
}

} // namespace sbl
#endif
