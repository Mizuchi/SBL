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
    private:
        friend class DisjointSetBase<DisjointSet, long>;
        std::vector<long> pnt;
        long &at(long x) {
            if (x >= (long)pnt.size())
                pnt.resize(x + 1, -1);
            return pnt[x];
        }
};

/// Disjoint Set map version.
template<class T>
class DisjointMap {
    private:
        // http://www.gotw.ca/gotw/057.htm
        // Recursive Declarations
        // map T to a iterator of itself.
        // Works like std::map<T, typename Map::iterator> Map;
        class MapIterWrapper;
        typedef std::map<T, MapIterWrapper> Map;
        typedef typename Map::iterator MapIter;

        class MapIterWrapper {
            public:
                MapIterWrapper() {}
                MapIterWrapper(MapIter p) : m(p) {}
                MapIter find_root() {
                    if (m != m->second.m) 
                        // This is not root, look back upon father.
                        m = m->second.find_root();
                    return m;
                }
            private:
                MapIter m;
        }; // class MapIterWrapper

        Map pnt;
        MapIter find(T x) {
            if (pnt.count(x) == 0) {
                pnt[x] = pnt.begin();
                pnt[x] = pnt.find(x);
            }
            return pnt[x].find_root();
        }
    public:
        void merge(T x, T y) {
            MapIter u = find(x), v = find(y);
            if (u == v)
                return;
            u->second = v;
        }
        bool same(T x, T y) {
            return find(x) == find(y);
        }
};

} // namespace sbl
#endif

