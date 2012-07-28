#ifndef _sbl_sort
#define _sbl_sort
#include"../base.hpp"
#include<limits>
#include<iterator>
#include<vector>
#include<algorithm>
#include<cmath>
#include"../utility/foreach.hpp"
#include"../utility/type_traits.hpp"

// http://lemon.cs.elte.hu/pub/doc/latest-svn/a00854.html

namespace sbl {

struct Unchange {
    template<class T> T operator()(T a) const {
        return a;
    }
};

template<class Iterator, class Functor, size_t digits = 8>
class RadixSort {
    private:
        template<bool v> struct Bool {
            static const bool value = v;
        };
        const Functor &functor;
        Iterator beg, end;

        typedef typename std::iterator_traits<Iterator>::value_type OriginData;
        typedef typename result_of<Functor(OriginData)>::type value_type;
        static const size_t maxDigits = std::numeric_limits<value_type>::digits;
        static const bool is_signed = std::numeric_limits<value_type>::is_signed;
        std::vector<OriginData> data, newData;
        value_type maxElement;

        template<size_t current>
        size_t get_index(OriginData v) {
            STATIC_ASSERT(current < maxDigits,
                          RadixSortError_current_digit_is_too_large);
            value_type x = functor(v);
            x /= value_type(1) << current;
            x %= 1 << digits;
            return std::abs(x);
        }

        template<size_t current>
        void counting_sort(Bool<false>) {}

        template<size_t current>
        void counting_sort(Bool<true>) {
            if ((maxElement >> current) == 0)
                return;

            std::vector<size_t> count(1 << digits, 0);
            foreach(v, data) {
                size_t idx = get_index<current>(v);
                assert(idx < (1 << digits));
                count[idx] ++;
            }

            for (size_t idx = 1; idx < count.size(); idx++)
                count[idx] += count[idx - 1];

            rforeach(v, data) {
                size_t idx = get_index<current>(v);
                assert(idx < (1 << digits));
                count[idx]--;
                assert(count[idx] < newData.size());
                newData[count[idx]] = v;
            }

            data.swap(newData);
            counting_sort < current + digits > (
                Bool < current + digits < maxDigits>());
        }

        template<bool is_signed> struct LessThanZero;

        bool less_than_zero(const value_type &a, Bool<true> is_signed) {
            static_cast<void>(is_signed);
            return a < 0;
        }
        bool less_than_zero(const value_type &a, Bool<false> is_signed) {
            static_cast<void>(is_signed);
            return false;
        }

        void treat_negative_number() {
            newData.clear();
            rforeach(v, data) {
                if (less_than_zero(functor(v), Bool<is_signed>()))
                    newData.push_back(v);
            }
            foreach(v, data) {
                if (not less_than_zero(functor(v), Bool<is_signed>()))
                    newData.push_back(v);
            }
            data.swap(newData);
        }

        void sort() {
            counting_sort<0>(Bool<true>());
            treat_negative_number();
        }

    public:
        RadixSort(Iterator beg, Iterator end, Functor const &functor)
            : functor(functor),
              beg(beg), end(end),
              data(beg, end), newData(data) {
            if (beg != end) {
                maxElement = std::abs(functor(data[0]));
                foreach(v, data) {
                    value_type x = functor(v);
                    if (maxElement < std::abs(x))
                        maxElement = std::abs(x);
                }
                sort();
            }
        }


        ~RadixSort() {
            // write back
            size_t idx = 0;
            for (Iterator iter = beg; iter != end; ++iter) {
                *iter = data[idx];
                idx++;
            }
        }
};

/// \ingroup auxalg
///
/// \brief Sorts the STL compatible range into ascending order.
///
/// The radix_sort sorts an STL compatible range into ascending
/// order.  The radix sort algorithm can sort items which are mapped
/// to integers with an adaptable unary function functor and the
/// order will be ascending according to these mapped values.
///
/// It is also possible to use a normal function instead
/// of the functor object. If the functor is not given it will use
/// the identity function instead.
///
/// This is a special quick sort algorithm where the pivot
/// values to split the items are choosen to be 2<sup>k</sup>
/// for each k.
/// Therefore, the time complexity of the algorithm is O(log(c)*n) and
/// it uses O(n) additional space, where c is the maximal value
/// and n is the number of the items in the container.
///
/// \param beg The begin of the given range.
/// \param ned The end of the given range.
/// \param functor An adaptible unary function or a normal function
/// which maps the items to any integer type which can be either
/// signed or unsigned.
template<class BegIter, class EndIter, class Functor>
void radix_sort(BegIter beg, EndIter end, Functor functor) {
    RadixSort<EndIter, Functor>(beg, end, functor);
}

template<size_t digits, class BegIter, class EndIter, class Functor>
void radix_sort_digits(BegIter beg, EndIter end, Functor functor) {
    RadixSort<EndIter, Functor, digits>(beg, end, functor);
}

template<class BegIter, class EndIter>
void radix_sort(BegIter beg, EndIter end) {
    radix_sort(beg, end, Unchange());
}

template<size_t digits, class BegIter, class EndIter>
void radix_sort_digits(BegIter beg, EndIter end) {
    radix_sort<digits>(beg, end, Unchange());
}

} // namespace sbl
#endif
