#ifndef _sbl_lower_bound_index
#define _sbl_lower_bound_index
#include"../structure/suffix_array.hpp"

namespace sbl {
template<class Iter1, class Iter2>
suffixArray::Index::const_iterator
lower_bound_index(suffixArray::Index const &index,
            Iter1 origin_beg,  Iter1 origin_end,
            Iter2 pattern_beg, Iter2 pattern_end) {
    long l = -1, r = index.size();
    while (r - l > 1) {
        long m = (l + r) / 2;
        lexicographical_compare(origin_beg + index[m], origin_end,
                                pattern_beg, pattern_end) ? l = m : r = m;
    }
    return index.begin() + r;
}
} // namespace sbl
#endif
