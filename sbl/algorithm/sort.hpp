#ifndef _sbl_sort
#define _sbl_sort
#include"../base.hpp"
#include<limits>
#include<iterator>
#include<vector>
#include<algorithm>
#include"../utility/foreach.hpp"
#include<iostream>
using namespace std;

namespace sbl {
template<class Iterator, size_t digits = 8>
class RadixSort {
    private:
        template<bool v> struct Bool {
            static const bool value = v;
        };

        typedef typename std::iterator_traits<Iterator>::value_type value_type;
        static const size_t maxDigits = std::numeric_limits<value_type>::digits;
        Iterator beg, end;

        std::vector<value_type> data, newData;
        value_type maxElement;

        template<size_t current>
        void counting_sort(Bool<false>) {}

        template<size_t current>
        void counting_sort(Bool<true>) {

            class {
                public:
                    size_t operator()(value_type v) {
                        STATIC_ASSERT(current < maxDigits, 
                                RadixSortError_current_digit_is_too_large);
                        v /= 1 << current;
                        v %= 1 << digits;
                        return v < 0 ? -v : v;
                    }
            } get_index;

            std::vector<size_t> count(1 << digits, 0);
            foreach(v, data) {
                size_t idx = get_index(v);
                assert(idx < (1 << digits));
                count[idx] ++;
            }

            for (size_t idx = 1; idx < count.size(); idx++)
                count[idx] += count[idx - 1];

            rforeach(v, data) {
                size_t idx = get_index(v);
                assert(idx < (1 << digits));
                count[idx]--;
                assert(count[idx] < newData.size());
                newData[count[idx]] = v;
            }
            data.swap(newData);
            counting_sort < current + digits > (
                Bool < current + digits < maxDigits>());
        }

        void sort() {
            counting_sort<0>(Bool<true>());
            if (std::numeric_limits<value_type>::is_signed) {
                newData.clear();
                rforeach(v, data) {
                    if (v < 0)
                        newData.push_back(v);
                }
                foreach(v, data) {
                    if (v >= 0)
                        newData.push_back(v);
                }
                assert(data.size() == newData.size());
                data.swap(newData);
            }
        }

    public:
        RadixSort(Iterator beg, Iterator end)
            : beg(beg), end(end),
              data(beg, end), newData(data),
              maxElement(*max_element(beg, end)) {
            sort();
        }


        ~RadixSort() {
            size_t idx = 0;
            for (Iterator iter = beg; iter != end; ++iter) {
                *iter = data[idx];
                idx++;
            }
        }
};

template<class BegIter, class EndIter>
void radix_sort(BegIter beg, EndIter end) {
    RadixSort<EndIter>(beg, end);
}
template<size_t digits, class BegIter, class EndIter>
void radix_sort_digits(BegIter beg, EndIter end) {
    RadixSort<EndIter, digits>(beg, end);
}

} // namespace sbl
#endif
