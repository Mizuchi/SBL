#ifndef _sbl_generate_closure
#define _sbl_generate_closure
#include"../combinatorics/permutation.hpp"
#include<iterator>
#include<set>

namespace sbl {
/// @brief Generate the closure.
///
/// @param beg begin iterator
/// @param end end iterator
/// @param op operator
template<class IterBeg, class IterEnd, class OperatorFunctor>
std::set< typename std::iterator_traits<IterBeg>::value_type >
generate_closure(
    IterBeg beg,
    IterEnd end,
    OperatorFunctor op
) {
    typedef typename std::iterator_traits<IterBeg>::value_type value_type;
    std::set<value_type> now, others;
    if (beg == end)
        return now;
    now.insert(identity(op, *beg));
    for (IterBeg iter = beg; iter != end; ++iter) {
        value_type current = *iter;
        others.clear();
        foreach_def(sbl::Permutation x, now) {
            while (true) {
                x = op(x, current);
                if (others.count(x) > 0)
                    break;
                else
                    others.insert(x);
            }
        }
        foreach(x, others) {
            now.insert(x);
        }
    }
    return now;
}
} // namespace sbl
#endif
