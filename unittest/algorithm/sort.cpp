#include"../../sbl/algorithm/sort.hpp"

TEST(algorithm, sort) {
    using namespace std;
    for (int i = 0; i < 10; i++) {
        vector<int> a , b;
        for (int i = 0; i < 20; i++)
            a.push_back(rand() % 20 - 10);
        b = a;
        sort(b.begin(), b.end());
        sbl::radix_sort(a.begin(), a.end());
        EXPECT_EQ(a, b);
    }
    for (int i = 0; i < 10; i++) {
        vector<unsigned int> a , b;
        for (int i = 0; i < 20; i++)
            a.push_back(rand() % 20);
        b = a;
        sort(b.begin(), b.end());
        sbl::radix_sort(a.begin(), a.end());
        EXPECT_EQ(a, b);
    }
}

TEST(algorithm, sort_big) {
    using namespace std;
    for (int i = 0; i < 10; i++) {
        vector<int> a , b;
        for (int i = 0; i < 20; i++)
            a.push_back(INT_MAX - rand() % 20);
        b = a;
        sort(b.begin(), b.end());
        sbl::radix_sort(a.begin(), a.end());
        EXPECT_EQ(a, b);
    }
    for (int i = 0; i < 10; i++) {
        vector<unsigned int> a , b;
        for (int i = 0; i < 20; i++)
            a.push_back(UINT_MAX - rand() % 20);
        b = a;
        sort(b.begin(), b.end());
        sbl::radix_sort(a.begin(), a.end());
        EXPECT_EQ(a, b);
    }
}

TEST(algorithm, sort_ran) {
    using namespace std;
    for (int i = 0; i < 5; i++) {
        vector<int> a , b;
        for (int i = 0; i < 50; i++)
            a.push_back(rand() - RAND_MAX/2);
        b = a;
        sort(b.begin(), b.end());
        sbl::radix_sort(a.begin(), a.end());
        EXPECT_EQ(a, b);
    }
    for (int i = 0; i < 5; i++) {
        vector<unsigned int> a , b;
        for (int i = 0; i < 50; i++)
            a.push_back(rand());
        b = a;
        sort(b.begin(), b.end());
        sbl::radix_sort(a.begin(), a.end());
        EXPECT_EQ(a, b);
    }
}
