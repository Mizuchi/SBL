#ifndef _sbl_fenwick_tree
#define _sbl_fenwick_tree
#include<vector>
#include"../algebra/element.hpp"

namespace sbl {
/* -----------------------------------------------------------------------*/
/** @brief Fenwich Tree
 *
 * Fenwich Tree is a data structure providing efficient methods for calculation
 * and manipulation of the prefix sums of a table of values.
 * for an array x[0..n-1], the time complexity of these operations is O(Log[n]):
 *
 * 1. given index idx，modify x[idx]
 * 2. given index idx，calculate the prefix sum x[0] + x[1] + .. + x[idx]
 * 3. given value sum，find minimum idx satisfy x[0] + x[1] + .. + x[idx] > sum
 *
 * operator + can be replaced by any operator has associative property.
 *
 */
/* -------------------------------------------------------------------------*/
template <class T, class Op = std::plus<T> > class FenwickTree {
        // http://www.algorithmist.com/index.php/Fenwick_tree
        // In this implementation, the tree is represented by a vector<T>.
        // Elements are numbered by 0, 1, ..., n-1.
        // (Note: this is a bit different from what is proposed in Fenwick's article.
        // To see why it makes sense, think about the trailing 1's in binary
        // representation of indexes.)
    private:
        /// sum of elements with indexes i&(i+1)..i, inclusive.
        std::vector<T> x;
        /// operator has associative property
        Op op;
    public:
        /// Creates a zero-initialized Fenwick tree for num elements.
        FenwickTree(size_t num,
                    Op _op = std::plus<T>()): x(num, identity(_op)), op(_op) {}

        /// Creates user-defined operation and identity element Fenwick tree.
        FenwickTree(size_t num, Op _op, T init): x(num, init), op(_op) {}

        /// Returns sum of elements with indexes 0..i, inclusive
        T prefix_sum(size_t i) const {
            T result = x[i];
            while (true) {
                i &= i + 1;
                if (i == 0) break;
                i -= 1;
                result = op(result, x[i]);
            }
            return result;
        }

        /// Returns number of element.
        size_t size() const {
            return x.size();
        }

        /// Increases value of n-th element by inc.
        void increase_nth_element(size_t n, T inc = 1) {
            for (size_t i = n; i < size(); i |= i + 1)
                x[i] = op(x[i], inc);
        }

        /// Returns index to the first element which prefix sum greater than a
        /// certain value.
        /// \post this->prefix_sum(result) > sum
        /// \post this->prefix_sum(result-1) <= sum
        size_t min_index_that_prefix_sum_greater_than(T sum) const {

            if (size() == 0) return 0;
            if (prefix_sum(size() - 1) <= sum) return size();

            size_t result = 0;

            /// always equal to the prefix_sum(result-1)
            T prefixSum = identity(op);

            for (size_t c = highest_set_bit(size()); c > 0; c >>= 1)
                // Determine every bit in the result from high to low
                if (result + c - 1 < size()
                    and op(prefixSum, x[result + c - 1]) <= sum) {
                    prefixSum = op(prefixSum, x[result + c - 1]);
                    result += c;
                }
            return result;
        }
};
} // namespace sbl
#endif
