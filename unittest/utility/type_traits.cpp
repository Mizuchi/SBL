#include"../../sbl/utility/type_traits.hpp"
#include<gtest/gtest.h>
#include<typeinfo>

template<int> struct Sfinae {
    enum { value = true };
};

struct Eval {
    template <typename U>
    typename sbl::enable_if<Sfinae<sizeof(&U::one)>::value, int>::type
    operator()(U u) {
        return u.one;
    }
    template <typename U>
    typename sbl::enable_if<Sfinae<sizeof(&U::two)>::value, unsigned>::type
    operator()(U u) {
        return u.two;
    }
};
struct One {
    int one;
    One(): one(1) {}
};
struct Two {
    unsigned two;
    Two(): two(2) {}
};

TEST(type_traits, enable_if) {
    Eval eval;
    One one;
    EXPECT_EQ(eval(one), 1);
    Two two;
    EXPECT_EQ(eval(two), 2);
}

struct S {
    double operator()(char, int &);
};

TEST(type_traits, result_of) {
    EXPECT_EQ(typeid(sbl::result_of<S(char, int &)>::type), typeid(double));
    EXPECT_EQ(typeid(sbl::result_of<Eval(One)>::type), typeid(int));
    EXPECT_NE(typeid(sbl::result_of<Eval(Two)>::type), typeid(int));
    EXPECT_EQ(typeid(sbl::result_of<Eval(Two)>::type), typeid(unsigned));
}

TEST(type_traits, conditional) {
    typedef sbl::conditional<true, int, double>::type Type1;
    typedef sbl::conditional<false, int, double>::type Type2;
    typedef sbl::conditional < sizeof(float) <= sizeof(double), char, long>::type Type3;
    EXPECT_EQ(typeid(Type1), typeid(int));
    EXPECT_EQ(typeid(Type2), typeid(double));
    EXPECT_EQ(typeid(Type3), typeid(char));
}
