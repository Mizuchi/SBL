#ifndef _sbl_type_traits
#define _sbl_type_traits
#include"../base.hpp"

namespace sbl {

/// Empty class
class Empty {};

/// Empty base class
class EmptyBase {
    protected:
        ~EmptyBase() {}
};

/// Undefined class
class Null;

//////////////////////////////////////////////////////////////////////////////

/// Provides member typedef type, which is defined as T if B is true at compile
/// time, or as F if B is false. 
template<bool B, class T, class F> struct conditional { typedef T type; };

template<class T, class F>
struct conditional<false, T, F> {
    typedef F type;
};
//////////////////////////////////////////////////////////////////////////////
/// obtains the type of expression in unevaluated context 
template<class T> T declval();
//////////////////////////////////////////////////////////////////////////////

/// Deduces the return type of a function call expression at compile type.
template<class>
struct result_of;

template<class F>
struct result_of<F()> {
    typedef TYPEOF(declval<F>()()) type;
};
template<class F, class A1>
struct result_of<F(A1)> {
    typedef TYPEOF(declval<F>()(declval<A1>())) type;
};
template<class F, class A1, class A2>
struct result_of<F(A1, A2)> {
    typedef TYPEOF(declval<F>()(
                       declval<A1>(),
                       declval<A2>())) type;
};
template<class F, class A1, class A2, class A3>
struct result_of<F(A1, A2, A3)> {
    typedef TYPEOF(declval<F>()(
                       declval<A1>(),
                       declval<A2>(),
                       declval<A3>())) type;
};
//////////////////////////////////////////////////////////////////////////////

} // namespace sbl

#endif
