#ifndef _sbl_algorithm_string
#define _sbl_algorithm_string
#include"../base.hpp"
#include<string>
#include<vector>

namespace sbl {

/// @return a list of the words in the string, using sep as the delimiter.
std::vector<std::string> 
split(const std::string &str, const std::string &delim = " \t\r\n") {
    typedef std::vector<std::string> Return;
    Return res;
    size_t current = 0, found;
    while ((found = str.find_first_of(delim, current)) != std::string::npos) {
        if (current != found)
            res.push_back(str.substr(current, found - current));
        current = found + 1;
    }
    if (current != found)
        res.push_back(str.substr(current));
    return res;
}

/// @return satisfy (rotate(beg, ret, end) <= rotate(beg, iter, end) for any iter)
template<class Iter>
Iter min_rotate(Iter beg, Iter end) {
    // arg: "dontcallmebfu"
    // ret:  .....^
    std::size_t i = 0, j = 1, k = 0, l = std::distance(beg, end);
    while (i < l and j < l and k < l) {
        AUTO(p, *(beg + (i + k) % l));
        AUTO(q, *(beg + (j + k) % l));
        if (p == q) ++k;
        else {
            if (p > q)
                i += k + 1;
            else
                j += k + 1;
            if (i == j)
                ++j;
            k = 0;
        }
    }
    return beg + (i < j ? i : j);
}

} // namespace sbl
#endif
