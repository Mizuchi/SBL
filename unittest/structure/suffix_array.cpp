#include<gtest/gtest.h>
#include<cstring>
#include"../../sbl/structure/suffix_array.hpp"

TEST(structure, suffix_array_component) {
    using namespace sbl::suffixArray;
    /////////////////////////////////////////////////////////////////////////
    int origin[] = {1, 1, 2, 1, 1, 1, 1, 2, 1, 0};
    int suffix[] = {1, 2, 1, 1, 1, 1, 2, 1, 0, 2, 1, 1, 1, 1, 2, 1, 0, 0};
    int result[] = {4,       2,       5,       6,       3,       1};

    const int originLen = sizeof(origin)/sizeof(origin[0]);
    const int suffixLen = sizeof(suffix)/sizeof(suffix[0]);
    const int resultLen = sizeof(result)/sizeof(result[0]);

    std::vector<size_t> vOrigin(origin, origin + originLen);
    std::vector<size_t> vSuffix(suffix, suffix + suffixLen);
    std::vector<size_t> vResult(result, result + resultLen);

    EXPECT_EQ(DC3::merge_and_sort(vOrigin), vResult);
    /////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    int prevsa[] = {5, 1, 4, 0, 2, 3};
    int realsa[] = {8, 4, 5, 1, 7, 2};

    const int prevsaLen = sizeof(prevsa)/sizeof(prevsa[0]);
    const int realsaLen = sizeof(realsa)/sizeof(realsa[0]);

    std::vector<size_t> vPrevsa(prevsa, prevsa + prevsaLen);
    std::vector<size_t> vRealsa(realsa, realsa + realsaLen);

    EXPECT_EQ(DC3::get_real_sa(10, vPrevsa), vRealsa);
    /////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    int realsa3[] = {3, 0, 6};
    const int realsa3Len = sizeof(realsa3)/sizeof(realsa3[0]);
    std::vector<size_t> vRealsa3(realsa3, realsa3 + realsa3Len);
    EXPECT_EQ(DC3::calc_sa3(vOrigin, vRealsa), vRealsa3);
    /////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////
    int sa[] = {8, 3, 4, 5, 0, 6, 1, 7, 2};
    const int saLen = sizeof(sa)/sizeof(sa[0]);
    std::vector<size_t> vSa(sa, sa + saLen);
    EXPECT_EQ(DC3::merge_all(vOrigin, vRealsa, vRealsa3), vSa);
    /////////////////////////////////////////////////////////////////////////
    EXPECT_EQ(DC3::dc3(vResult), vPrevsa);
    /////////////////////////////////////////////////////////////////////////
    char str[] = "aabaaaaba";
    std::vector<size_t> vString(str, str+strlen(str));
    EXPECT_EQ(DC3::dc3(vString), vSa);
    /////////////////////////////////////////////////////////////////////////
};
TEST(structure, suffix_array_small_1) {
    using namespace sbl::suffixArray;
    std::vector<size_t> s;
    s.push_back(2);
    s.push_back(1);
    s.push_back(3);
    std::vector<size_t> g;
    g.push_back(1);
    g.push_back(0);
    g.push_back(2);
    EXPECT_EQ(DC3::dc3(s), g);
}
TEST(structure, suffix_array_small_2) {
    using namespace sbl::suffixArray;
    std::vector<size_t> s;
    s.push_back(2);
    s.push_back(3);
    s.push_back(4);
    s.push_back(1);
    std::vector<size_t> g;
    g.push_back(3);
    g.push_back(0);
    g.push_back(1);
    g.push_back(2);
    EXPECT_EQ(DC3::dc3(s), g);
}
TEST(structure, suffix_array_component_small) {
    using namespace sbl::suffixArray;
    std::vector<size_t> s;
    s.push_back(2);
    s.push_back(1);
    s.push_back(1);
    s.push_back(1);
    s.push_back(1);
    s.push_back(0);
    std::vector<size_t> g;
    g.push_back(3);
    g.push_back(2);
    g.push_back(3);
    g.push_back(1);
    EXPECT_EQ(DC3::merge_and_sort(s), g);
}

TEST(structure, suffix_array_small_3) {
    using namespace sbl::suffixArray;
    std::vector<size_t> s;
    s.push_back(2);
    s.push_back(1);
    s.push_back(1);
    s.push_back(1);
    s.push_back(1);
    std::vector<size_t> g;
    g.push_back(4);
    g.push_back(3);
    g.push_back(2);
    g.push_back(1);
    g.push_back(0);
    EXPECT_EQ(DC3::dc3(s), g);
}
