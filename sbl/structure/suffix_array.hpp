#ifndef _sbl_suffix_array
#define _sbl_suffix_array
#include<vector>
#include<algorithm>
#include<cassert>
#include"../algorithm/sort.hpp"
#include"../base.hpp"

namespace sbl {
namespace suffixArray {

using std::vector;
using std::size_t;

class DC3 {
        // DC3 algorithm
        // http://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.137.7871
        //
        // This implementation is much slow than the one on the paper.
    public:
        struct CompressThree {
            size_t index;
            size_t data[3];
            bool operator==(CompressThree other) {
                return data[0] == other.data[0] and
                       data[1] == other.data[1] and
                       data[2] == other.data[2];
            }
            bool operator!=(CompressThree other) {
                return not operator==(other);
            }
        };

        template<size_t idx>
        struct Choose {
            size_t operator()(CompressThree x) const {
                return x.data[idx];
            }
        };

        static vector<size_t> merge_and_sort(vector<size_t> origin) {
            vector<size_t> suffix1 = origin;
            suffix1.erase(suffix1.begin());

            vector<size_t> suffix2 = suffix1;
            suffix2.erase(suffix2.begin());

            while (suffix1.size() % 3 != 0) suffix1.push_back(0);
            while (suffix2.size() % 3 != 0) suffix2.push_back(0);

            vector<CompressThree> record;
            size_t idx = 0;
            for (size_t i = 0; i < suffix1.size(); i += 3) {
                CompressThree x = {idx, {suffix1[i], suffix1[i + 1], suffix1[i + 2]}};
                record.push_back(x);
                idx++;
            }
            for (size_t i = 0; i < suffix2.size(); i += 3) {
                CompressThree x = {idx, {suffix2[i], suffix2[i + 1], suffix2[i + 2]}};
                record.push_back(x);
                idx++;
            }
            radix_sort(record.begin(), record.end(), Choose<2>());
            radix_sort(record.begin(), record.end(), Choose<1>());
            radix_sort(record.begin(), record.end(), Choose<0>());

            vector<size_t> result(idx);
            size_t rank = 1;
            result[record[0].index] = rank;
            for (size_t i = 1; i < record.size(); i++) {
                if (record[i] != record[i - 1])
                    rank++;
                result[record[i].index] = rank;
            }
            return result;
        }

        static vector<size_t> get_real_sa(size_t length, vector<size_t> sa12) {
            vector<size_t> result;
            size_t firstPart = (length - 1) / 3;
            if ((length - 1) % 3 != 0)
                firstPart ++;
            foreach(idx, sa12) {
                if (idx < firstPart)
                    result.push_back(idx * 3 + 1);
                else
                    result.push_back((idx - firstPart) * 3 + 2);
            }
            return result;
        }

        struct ReturnFirst {
            size_t operator()(std::pair<size_t, size_t> a) const {
                return a.first;
            }
        };

        static vector<size_t> calc_sa3(vector<size_t> origin, vector<size_t> realsa12) {
            vector<size_t> result;
            vector< std::pair<size_t, size_t> > realsa1;
            foreach(idx, realsa12) {
                if (idx % 3 == 1)
                    realsa1.push_back(std::make_pair(origin[idx - 1], idx - 1));
            }
            radix_sort(realsa1.begin(), realsa1.end(), ReturnFirst());
            foreach(u, realsa1) {
                result.push_back(u.second);
            }
            return result;
        }

        static vector<size_t> merge_all(
            vector<size_t> origin,
            vector<size_t> realsa12,
            vector<size_t> realsa3
        ) {
            struct Compare {
                vector<size_t> origin;
                size_t n;
                vector<size_t> rank12;

                bool operator()(size_t idx12, size_t idx3) {
                    assert(idx12 % 3 == 1 or idx12 % 3 == 2);
                    assert(idx3 % 3 == 0);
                    if (origin[idx12] != origin[idx3])
                        return origin[idx12] < origin[idx3];

                    if (origin[idx12 + 1] != origin[idx3 + 1])
                        return origin[idx12 + 1] < origin[idx3 + 1];

                    if (idx12 % 3 == 1) {
                        return rank12[idx12 + 1] < rank12[idx3 + 1];
                    } else {
                        return rank12[idx12 + 2] < rank12[idx3 + 2];
                    }
                }

                Compare(vector<size_t> origin, vector<size_t> realsa12)
                    : origin(origin), n(origin.size() + 3), rank12(n, 0) {
                    for (size_t i = 0; i < realsa12.size(); i++)
                        rank12[realsa12[i]] = i;
                }
            } less_than(origin, realsa12);
            vector<size_t> result;
            size_t sa12idx = 0;
            size_t sa3idx = 0;
            while (sa12idx < realsa12.size() and sa3idx < realsa3.size()) {
                size_t sa12 = realsa12[sa12idx];
                size_t sa3 = realsa3[sa3idx];
                if (less_than(sa12, sa3)) {
                    result.push_back(sa12);
                    sa12idx++;
                } else {
                    result.push_back(sa3);
                    sa3idx++;
                }
            }
            result.insert(result.end(), realsa12.begin() + sa12idx, realsa12.end());
            result.insert(result.end(), realsa3.begin() + sa3idx, realsa3.end());
            return result;
        }

        static vector<size_t> dc3(vector<size_t> origin) {
            assert(*std::min_element(origin.begin(), origin.end()) > 0);
            origin.push_back(0);
            if (origin.size() == 2) {
                vector<size_t> result;
                result.push_back(0);
                return result;
            } else if (origin.size() == 3) {
                vector<size_t> result;
                result.push_back(0);
                result.push_back(1);
                if (origin[0] > origin[1])
                    std::swap(result[0], result[1]);
                return result;
            } else {
                vector<size_t> merge = merge_and_sort(origin);
                vector<size_t> sa12 = dc3(merge);
                vector<size_t> realsa12 = get_real_sa(origin.size(), sa12);
                vector<size_t> realsa3 = calc_sa3(origin, realsa12);
                vector<size_t> result = merge_all(origin, realsa12, realsa3);

                if (origin.size() % 3 != 1)
                    result.erase(result.begin());
                return result;
            }
        }
}; // class DC3

typedef vector<size_t> Index;

/// Index array of suffix array.
/// We name the result as sa.
/// \post str[result[i]:] < str[result[i+1]:]
template<class BegIter, class EndIter>
vector<size_t> make_index(BegIter beg, EndIter end) {
    vector<size_t> origin(beg, end);
    AUTO(minElement, *std::min_element(beg, end));
    foreach(&v, origin) {
        v -= minElement;
        v ++;
    }
    return DC3::dc3(origin);
}

/// rank of suffix array
/// Whe name the result as rank
/// \post result[sa[i]] == i
/// \post result[i] < result[j] iff str[i:] < str[j:]
vector<size_t> make_rank(vector<size_t> const &index) {
    vector<size_t> rank(index.size());
    for (size_t i = 0; i < index.size(); ++i) rank[index[i]] = i;
    return rank;
}

/// height of suffix array
/// Whe name the result as height
/// \post str[sa[i]:sa[i]+height[i]] == str[sa[i+1]:sa[i+1]+height[i]]
template<class Iter>
vector<size_t> make_height(
    vector<size_t> const &index,
    vector<size_t> const &rank,
    Iter beg, Iter
) {
    vector<size_t> height(index.size());
    for (size_t i = 0, h = 0; i < index.size(); ++i)
        if (rank[i] > 0) {
            size_t j = index[rank[i] - 1];
            while (std::max(i, j) + h < index.size() and
                   beg[i + h] == beg[j + h]) ++h;
            height[rank[i]] = h > 0 ? h-- : h;
        }
    return height;
}
} // namespace suffixArray

/// @brief calc sa, rank and height for suffix array.
///
/// TODO: add interface to get the result.
class SuffixArray {
    private:
        std::vector<size_t> sa;
        std::vector<size_t> rank;
        std::vector<size_t> height;
    public:
        template<class Iterator>
        SuffixArray(Iterator beg, Iterator end)
            : sa(suffixArray::make_index(beg, end)),
              rank(suffixArray::make_rank(sa)),
              height(suffixArray::make_height(sa, rank, beg, end)) {}
};

} // namespace sbl

#endif
