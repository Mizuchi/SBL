#ifndef _sbl_functional
#define _sbl_functional
#include<functional>
#include"type_traits.hpp"

namespace sbl {

/// simulate C++11's new functor according N3421
template<template<class> class Func>
struct Functor {
    template<class T>
    typename result_of<Func<T>(T)>::type
    operator()(const T &a) const {
        return Func<T>()(a);
    }

    template<class T>
    typename result_of<Func<T>(T, T)>::type
    operator()(const T &a, const T &b) const {
        return Func<T>()(a, b);
    }
};

typedef Functor<std::plus> Plus;
typedef Functor<std::minus> Minus;
typedef Functor<std::multiplies> Multiplies;
typedef Functor<std::divides> Divides;
typedef Functor<std::modulus> Modulus;
typedef Functor<std::negate> Negate;

typedef Functor<std::less> Less;
typedef Functor<std::less_equal> LessEqual;
typedef Functor<std::greater> Greater;
typedef Functor<std::greater_equal> GreaterEqual;
typedef Functor<std::equal_to> EqualTo;
typedef Functor<std::not_equal_to> NotEqualTo;

typedef Functor<std::logical_and> LogicalAnd;
typedef Functor<std::logical_or> LogicalOr;
typedef Functor<std::logical_not> LogicalNot;

typedef Functor<std::bit_and> BitAnd;
typedef Functor<std::bit_or> BitOr;
typedef Functor<std::bit_xor> BitXor;

struct First {
    template<class T, class U>
    const T &operator()(const T &a, const U &b) const {
        return a;
    }
};
struct Second {
    template<class T, class U>
    const U &operator()(const T &a, const U &b) const {
        return b;
    }
};
}
#endif
