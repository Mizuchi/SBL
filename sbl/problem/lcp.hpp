#ifndef _sbl_lcp
#define _sbl_lcp

#include"../structure/rmq.hpp"
#include"../structure/suffix_array.hpp"

namespace sbl{
/* -----------------------------------------------------------------------*/
/** @brief 保存计算最长公共前缀的信息 */
/* -------------------------------------------------------------------------*/
class LongestCommonPrefix {
    private:
        typedef suffixArray::Index Index;
        Index rank;
        StaticRangeMinimunQuery<size_t, std::greater<size_t> > p;
    public:
        /* -----------------------------------------------------------------------*/
        /**
         * @brief 构造最长公共前缀 
         *
         * @param rank suffix array 中的 rank
         * @param height suffix array 中的 height
         */
        /* -------------------------------------------------------------------------*/
        LongestCommonPrefix(Index const &rank, 
                            Index const &height)
            :rank(rank), p(height.begin(), height.end()) {}
        /* -----------------------------------------------------------------------*/
        /**
         * @brief 询问最长公共前缀
         *
         * @param i 字符串的第 i 个字符开始
         * @param j 字符串的第 j 个字符开始
         *
         * @return 最长公共前缀的长度
         */
        /* -------------------------------------------------------------------------*/
        size_t operator()(size_t i, size_t j) const {
            if (i == j) return rank.size() - i;
            i = rank[i], j = rank[j];
            if (i > j) std::swap(i, j);
            return p.top(i + 1, j + 1);
        }
};
} // namespace sbl

#endif
