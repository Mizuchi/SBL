#ifndef _sbl_permutation
#define _sbl_permutation
#include"../utility/foreach.hpp"
#include<algorithm>
#include<iostream>

namespace sbl {
using std::size_t;
/// Store a permutation
class Permutation {
        // http://en.wikipedia.org/wiki/Permutation
    private:
        typedef std::vector<size_t> value_type;
        value_type oneLineNotation;
    public:

        // identity construction
        explicit Permutation(size_t n): oneLineNotation(n) {
            for (size_t i = 0; i < n; i++)
                oneLineNotation[i] = i;
            assert(__validity_test());
        }

        Permutation(value_type _): oneLineNotation(_) {
            assert(__validity_test());
        }

        template<class IterBeg, class IterEnd>
        Permutation(IterBeg beg, IterEnd end) {
            oneLineNotation.reserve(std::distance(beg, end));
            for (; beg != end; ++beg)
                oneLineNotation.push_back(*beg);
            assert(__validity_test());
        }

        bool __validity_test() const {
            value_type a(oneLineNotation);

            // This should make a = {0, 1, ..., a.size() - 1}
            std::sort(a.begin(), a.end());

            if (a.front() != 0 or a.back() != a.size() - 1)
                return false;

            if (std::unique(a.begin(), a.end()) != a.end())
                return false;

            return true;
        }

        // public member function
        size_t operator[](size_t i) const {
            return oneLineNotation[i];
        }
        size_t get_image(size_t i) const {
            return oneLineNotation[i];
        }
        size_t get_origin(size_t i) const {
            return std::find(
                       oneLineNotation.begin(),
                       oneLineNotation.end(),
                       i
                   ) - oneLineNotation.begin();
        }

        std::vector< value_type >
        cycle_notation() const {
            typedef value_type Cycle;
            const value_type &p = oneLineNotation;
            const size_t n = p.size();
            std::vector<bool> v(n, false);
            std::vector<Cycle> ret;
            for (size_t i = 0; i < n; ++i)
                if (v[i] == false) {
                    Cycle cycle;
                    size_t j = i;
                    do {
                        cycle.push_back(j);
                        v[j] = true;
                        j = p[j];
                    } while (j != i);
                    ret.push_back(cycle);
                }
            return ret;
        }

        size_t cycle_notation_count() const {
            // used for Polya enumeration theorem (PET)
            return cycle_notation().size();
        }
        size_t size() const {
            return oneLineNotation.size();
        }
        struct Composition {
            Permutation operator()(Permutation lhs, Permutation rhs) const {
                assert(lhs.size() == rhs.size());
                value_type result(lhs.size());
                for (size_t i = 0; i < lhs.size(); ++i)
                    result[i] = rhs[lhs[i]];
                return result;
            }
        }; // struct Composition

        bool operator==(Permutation b) const {
            return oneLineNotation == b.oneLineNotation;
        }
        bool operator<(Permutation b) const {
            return oneLineNotation < b.oneLineNotation;
        }
}; //     class Permutation

static inline
std::ostream &operator<<(std::ostream &os, Permutation a) {
    os << '(';
    for (size_t i = 0; i < a.size(); i++)
        os << a[i] << (i + 1 == a.size() ? ')' : ' ');
    return os;
}

static inline
Permutation identity(Permutation::Composition, Permutation a) {
    return Permutation(a.size());
}

} // namespace sbl
#endif
