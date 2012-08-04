#include"../../sbl/algorithm/sort.hpp"
#include<gtest/gtest.h>
#include<climits>

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

namespace LemonUnitTest {
using sbl::radix_sort;
static const int n = 10000;

struct Negate {
  typedef int argument_type;
  typedef int result_type;
  int operator()(int a) const { return - a; }
};

int negate(int a) { return - a; }


void generateIntSequence(int n, std::vector<int>& data) {
  int prime = 9973;
  int root = 136, value = 1;
  for (int i = 0; i < n; ++i) {
    data.push_back(value - prime / 2);
    value = (value * root) % prime;
  }
}

void generateCharSequence(int n, std::vector<unsigned char>& data) {
  int prime = 251;
  int root = 3, value = root;
  for (int i = 0; i < n; ++i) {
    data.push_back(static_cast<unsigned char>(value));
    value = (value * root) % prime;
  }
}

void checkRadixSort() {
  {
    std::vector<int> data1;
    generateIntSequence(n, data1);

    std::vector<int> data2(data1);
    std::sort(data1.begin(), data1.end());

    radix_sort(data2.begin(), data2.end());
    for (int i = 0; i < n; ++i) {
      EXPECT_EQ(data1[i], data2[i]);
    }

    radix_sort(data2.begin(), data2.end(), Negate());
    for (int i = 0; i < n; ++i) {
      EXPECT_EQ(data1[i], data2[n - 1 - i]);
    }

    radix_sort(data2.begin(), data2.end(), negate);
    for (int i = 0; i < n; ++i) {
      EXPECT_EQ(data1[i], data2[n - 1 - i]);
    }

  }

  {
    std::vector<unsigned char> data1(n);
    generateCharSequence(n, data1);

    std::vector<unsigned char> data2(data1);
    std::sort(data1.begin(), data1.end());

    radix_sort(data2.begin(), data2.end());
    for (int i = 0; i < n; ++i) {
      EXPECT_EQ(data1[i], data2[i]);
    }

  }
}


void checkStableRadixSort() {
  {
    std::vector<int> data1;
    generateIntSequence(n, data1);

    std::vector<int> data2(data1);
    std::sort(data1.begin(), data1.end());

    radix_sort(data2.begin(), data2.end());
    for (int i = 0; i < n; ++i) {
      EXPECT_EQ(data1[i], data2[i]);
    }

    radix_sort(data2.begin(), data2.end(), Negate());
    for (int i = 0; i < n; ++i) {
      EXPECT_EQ(data1[i], data2[n - 1 - i]);
    }

    radix_sort(data2.begin(), data2.end(), negate);
    for (int i = 0; i < n; ++i) {
      EXPECT_EQ(data1[i], data2[n - 1 - i]);
    }
  }

  {
    std::vector<unsigned char> data1(n);
    generateCharSequence(n, data1);

    std::vector<unsigned char> data2(data1);
    std::sort(data1.begin(), data1.end());

    radix_sort(data2.begin(), data2.end());
    for (int i = 0; i < n; ++i) {
      EXPECT_EQ(data1[i], data2[i]);
    }

  }
}

int main() {

  checkRadixSort();
  checkStableRadixSort();

  return 0;
}
} // namespace LemonUnitTest

TEST(algorithm, radix_sort_lemon) {
    LemonUnitTest::main();
}
