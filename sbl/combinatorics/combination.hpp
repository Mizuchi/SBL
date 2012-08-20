#ifndef _sbl_combination
#define _sbl_combination
#include"../base.hpp"

namespace sbl {
using std::size_t;

/// choose k-combinations from a given set S of n elements,
/// given a combination, return the next
/// \pre assert(is_sorted(beg, end));
template<class IterBeg, class IterEnd>
bool next_combination(
    IterBeg beg,
    IterEnd end,
    size_t n
) {
    AUTO(iter, end);
    size_t m = n;
    while (iter != beg and size_t(*(iter - 1)) == m - 1) {
        --iter;
        --m;
    }
    if (iter == beg) return false;
    ++(*(iter - 1));
    for (; iter < end; ++iter)
        *iter = *(iter - 1) + 1;
    return true;
}

} // namespace sbl
#endif
