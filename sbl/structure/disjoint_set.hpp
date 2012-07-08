#ifndef _sbl_union_find_set
#define _sbl_union_find_set
#include"../base.hpp"
#include<vector>
#include<map>
#include<limits>
namespace sbl {

/// @brief base class of disjoint set
template<class Derived, class T>
class DisjointSetBase {
    // curiously recurring template pattern.
    private:
        /// find the root of a given element
        T find(T x) {
            return at(x) < 0 ? x : at(x) = find(at(x));
        }

        /** @brief get the father of element x or number of element in x.
         *
         * @param x element we asked
         *
         * @return hybrid coupling
         *
         * @return result < 0 indicate x is root and the number of element in.
         *
         * @return result > 0 indicate x's father element's index.
         */

        T &at(T x) {
            return static_cast<Derived &>(*this).at(x);
        }
    public:
        /// merge two set
        void merge(T x, T y) {
            x = find(x);
            y = find(y);
            if (x == y) 
                return;
            if (at(y) < at(x)) 
                std::swap(x, y);
            at(x) += at(y);
            at(y) = x;
        }
        /// @return whether to element from same set
        bool same(T x, T y) const {
            DisjointSetBase &self = const_cast<DisjointSetBase&>(*this);
            return self.find(x) == self.find(y);
        }

        /// @return number of element in set x
        T size(T x) {
            return -at(find(x));
        }
    protected:
        ~DisjointSetBase() {
            // Put static check in destruction function
            // because it is always instantiated.
            STATIC_ASSERT(std::numeric_limits<T>::is_signed, 
                    DisjointSet_Type_must_be_signed_integer);
        }
};

/// Disjoint Set normal implementation.
class DisjointSet: public DisjointSetBase<DisjointSet, long> {
        friend class DisjointSetBase<DisjointSet, long>;
        std::vector<long> pnt;
        long &at(long x) {
            if (x >= (long)pnt.size())
                pnt.resize(x + 1, -1);
            return pnt[x];
        }
};

/// Disjoint Set map version.
/// Has same API with normal one.
class DisjointSetDict:
    public DisjointSetBase<DisjointSetDict, long long> {
        friend class DisjointSetBase<DisjointSetDict, long long>;
        std::map<long long, long long> pnt;
        long long &at(long long x) {
            if(pnt.count(x) == 0)
                pnt[x] = -1;
            return pnt[x];
        }
};

} // namespace sbl
#endif
