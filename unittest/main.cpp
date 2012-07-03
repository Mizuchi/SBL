#include<gtest/gtest.h>
#include"algebra/element.cpp"
#include"utility/bits.cpp"
#include"utility/foreach.cpp"
#include"utility/enum.cpp"
#include"math/module.cpp"

int main(int argv, char **argc) {
    testing::InitGoogleTest(&argv, argc);
    return RUN_ALL_TESTS();
}
