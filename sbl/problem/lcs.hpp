#ifndef _sbl_lcs
#define _sbl_lcs

#include"../structure/suffix_array.hpp"

namespace sbl {
/* -----------------------------------------------------------------------*/
/**
 * @brief Longest common substring O(n+|alphabet|*log(n))
 *
 * @tparam Iter1 must be a input iterator
 * @tparam Iter2 must be a input iterator
 * @param beg1 start iterator of the first  string
 * @param end1 end   iterator of the first  string
 * @param beg2 start iterator of the second string
 * @param end2 end   iterator of the second string
 *
 * @return make_pair(length, make_pair(posInFirstString, posInSecondString))
 */
/* -------------------------------------------------------------------------*/
template<class Iter1, class Iter2>
pair<size_t, pair<size_t, size_t> > 
longest_common_substring(Iter1 beg1, Iter1 end1 Iter2 beg2, Iter2 end2) {
    using namespace suffixArray;
    AUTO(maxValue,max(*max_element(beg1, end1), *max_element(beg2, end2)));

    // Concat two string to S.
    vector<__typeof(maxValue)> s;
    s.reserve(distance(beg1, end1) + distance(beg2, end2) + 1);
    copy(beg1, end1, back_inserter(s));
    s.push_back(maxValue + 1); // sentinel
    copy(beg2, end2, back_inserter(s));

    // Generate index and height
    AUTO(index, make_sa(ALL(s)));
    AUTO(height, make_height(index, make_rank(index), ALL(s)));

    // Get answer
    size_t ans = 0, l1 = distance(beg1, end1), i1 = 0,  i2 = 0;
    for (size_t i = 1; i < s.size(); i++)
        if (height[i] >= ans) 
            if (size_t c = index[i - 1] < l1 && index[i] > l1 ? 1 :
                           index[i] < l1 && index[i - 1] > l1 ? 2 : 0) {
                ans = height[i];
                i1 = index[i - (c & 1)];
                i2 = index[i - (c / 2)] - l1 - 1;
            }
    return make_pair(ans, make_pair(i1, i2));
}
} // namespace sbl

#endif
