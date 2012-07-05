#ifndef _sbl_kmp
#define _sbl_kmp
#include<vector>

namespace sbl {

/// Type store the result.
typedef std::vector<std::size_t> PrefixLength;

/// Compute the suffix function, in common use.
/// \pre substr(beg2 + i + 1, table[i]) == substr(beg2, table[i])
/// \pre substr(beg2 + i + 1, table[i]+1) != substr(beg2, table[i]+1)
/// \post substr(beg1 + i, len[i]) == substr(beg2, len[i])
/// \post substr(beg1 + i, len[i]+1) != substr(beg2, len[i]+1)
template<class Iter1, class Iter2>
void __compute_suffix_function(Iter1 beg1, Iter1 end1,
                               Iter2 beg2, Iter2 end2,
                               PrefixLength const &table,
                               PrefixLength &len) {

    // Z algorithm. Present by Dan Gusfield, in his book *Algorithms on
    // Strings, Trees and Sequences* Second Chapter
    //
    // The idea is very similar with Knuth-Morris-Pratt algorithm. However, Z
    // algorithm could provide more information, not just exact matching
    // position, but also matching length about the prefix string for every
    // suffix string in pattern string.
    //
    // http://binfalse.de/2010/09/advanced-searching-via-z-algorithm/

    len.resize(end1 - beg1);
    if (len.empty()) return;
    for (len[0] = 0;
         beg1 + len[0] != end1 and
         beg2 + len[0] != end2 and
         beg1[len[0]] == beg2[len[0]]; len[0]++);
    for (std::size_t i = 1, k = 0; i < len.size(); i++) {
        len[i] = table.empty() ? 0 : table[i - k - 1];
        if (len[i] + i >= len[k] + k) {
            for (len[i] = len[k] + k > i ? len[k] + k - i : 0;
                 beg1 + len[i] != end1 - i &&
                 beg2 + len[i] != end2 &&
                 beg1[len[i] + i] == beg2[len[i]]; len[i]++);
            k = i;
        }
    }
}

/// Compute the suffix function for the string itself.
/// \post substr(beg1 + i + 1, result[i]) == substr(beg1, result[i])
/// \post substr(beg1 + i + 1, result[i]+1) != substr(beg1, result[i]+1)
template<class Iter1>
PrefixLength compute_suffix_function(Iter1 beg1, Iter1 end1) {
    PrefixLength len;
    __compute_suffix_function(beg1 + 1, end1, beg1, end1, len, len);
    return len;
}

/// Compute the suffix function, the length of the longest substring of beg1 to
/// end1 that starts at i > 1 and matches a prefix of beg2 to end2.
/// \post substr(beg1 + i, result[i]) == substr(beg2, result[i])
/// \post substr(beg1 + i, result[i]+1) != substr(beg2, result[i]+1)
template<class Iter1, class Iter2>
PrefixLength compute_suffix_function(Iter1 beg1, Iter1 end1,
                                     Iter2 beg2, Iter2 end2) {
    /// to satisfy the precondition.
    PrefixLength table = compute_suffix_function(beg2 , end2);
    PrefixLength len;
    __compute_suffix_function(beg1, end1, beg2, end2, table, len);
    return len;
}
} // namespace sbl
#endif
