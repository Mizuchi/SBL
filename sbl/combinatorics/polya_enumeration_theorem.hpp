#ifndef _sbl_polya_enumeration_theorem
#define _sbl_polya_enumeration_theorem
#include"../utility/bits.hpp"
#include"permutation.hpp"
#include"../algebra/generate_closure.hpp"
namespace sbl {
template<class Result, class IterBeg, class IterEnd>
Result polya_enumeration_theorem(
    IterBeg beg,
    IterEnd end,
    size_t colorCount
) {
    AUTO(a, generate_closure(beg, end, sbl::Permutation::Composition()));
    Result result = 0;
    foreach(p, a) {
        result += power_integer<Result>(colorCount, p.cycle_notation_count());
    }
    result /= a.size();
    return result;
}
} // namespace sbl
#endif
