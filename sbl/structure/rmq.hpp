#ifndef _sbl_rmq_it
#define _sbl_rmq_it
#include<functional>
#include<algorithm>
#include<vector>
#include"../utility/bits.hpp"

namespace sbl {
using std::size_t;

template < class T, class Compare = std::less<T> >
class StaticRangeMinimunQuery {
    private:
        std::vector<T> f;
        size_t s;
        static size_t log2(size_t x) {
            assert(x > 0);
            return highest_set_bit_index(x) - 1;
        }
        static T max(T a, T b) {
            return Compare()(a, b) ? b : a;
        }
    public:
        template<class BeginIter, class EndIter>
        StaticRangeMinimunQuery(BeginIter a, EndIter b): f(a, b) {
            s = f.size();
            f.reserve(s * log2(s));
            for (size_t j = 0; j < log2(s); j++)
                for (size_t i = 0; i < s; i++) {
                    f.push_back(f[i + j * s]);
                    if (i + (1UL << j) < s)
                        f.back() = max(f.back(), f[i + (1UL << j) + j * s]);
                }
        }
        T top(size_t l, size_t r) const {
            size_t j = log2(r - l);
            return max(f[l + j * s], f[r - (1UL << j) + j * s]);
        }
};

template < class T, class Compare = std::less<T> >
class DynamicRangeMinimunQuery {
    private:
        Compare comp;
        std::vector<T> f;
        size_t s;
        const T *getmax(size_t x, size_t y, size_t n, size_t l, size_t r) const {
            size_t m = (l + r) / 2;
            if (y <= l || x >= r) return 0;
            if (x <= l && r <= y) return &f[n];
            const T *p = getmax(x, y, n * 2 + 1, l, m);
            const T *q = getmax(x, y, n * 2 + 2, m, r);
            return !p ? q : !q ? p : comp(*p, *q) ? q : p ;
        }
        T change(size_t x, T d, size_t n, size_t l, size_t r) {
            size_t m = (l + r) / 2;
            if (x < l || x >= r) return f[n];
            if (l + 1 == r) return f[n] = d;
            T p = change(x, d, n * 2 + 1, l, m);
            T q = change(x, d, n * 2 + 2, m, r);
            return f[n] = comp(p, q) ? q : p;
        }
    public:
        void replace(size_t x, T d) {
            change(x, d, 0, 0, s);
        }
        T top(size_t x, size_t y) const {
            return *getmax(x, y, 0, 0, s);
        }
        DynamicRangeMinimunQuery(size_t num, T init)
            : f(num * 4, init), s(num) {}
};

} // namespace sbl
#endif