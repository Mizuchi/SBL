#include"../../sbl/utility/type_traits.hpp"
#include<gtest/gtest.h>
#include<typeinfo>

struct S {
    double operator()(char, int &);
};

TEST(type_traits, result_of) {
    EXPECT_EQ(typeid(sbl::result_of<S(char, int &)>::type), typeid(double));
}

TEST(type_traits, conditional) {
    typedef sbl::conditional<true, int, double>::type Type1;
    typedef sbl::conditional<false, int, double>::type Type2;
    typedef sbl::conditional < sizeof(float) <= sizeof(double), char, long>::type Type3;
    EXPECT_EQ(typeid(Type1), typeid(int));
    EXPECT_EQ(typeid(Type2), typeid(double));
    EXPECT_EQ(typeid(Type3), typeid(char));
}
