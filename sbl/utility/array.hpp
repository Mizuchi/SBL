#ifndef _sbl_array
#define _sbl_array
#include<vector>
#include<deque>
#include<cstddef>
#include"macro.hpp"

// TODO: Need unittest
namespace sbl {

/// STL compliant container wrapper for arrays of constant size
template<class T, size_t n>
class Array {
    private:
        T data[n];
    public:
        typedef T *iterator;
        typedef T const *iterator;
        iterator begin() const {
            return data;
        }
        iterator end() const {
            return data + n;
        }
        T &operator[](size_t i) {
            assert(i < n);
            return data[i];
        }
        T operator[](size_t i) const {
            assert(i < n);
            return data[i];
        }
        size_t size() {
            return n;
        }
};

/// Accept int subscript and auto expand when needed
template<class T>
class RangeArray {
        mutable int s, t;
        mutable std::deque<T>a;
        void expand(int i) const {
            if (a.empty()) {
                s = i, t = i + 1;
                a.push_back(T());
            }
            while (s > i) {
                --s;
                a.push_front(T());
            }
            while (t <= i) {
                ++t;
                a.push_back(T());
            }
        }
    public:
        T &operator[](int i) {
            expand(i);
            return a[i - s];
        }
        T operator[](int i) const {
            expand(i);
            return a[i - s];
        }
        RangeArray(int l = 0, int r = 0) :
            s(l), t(r), a(r - l) {}
};

/* -----------------------------------------------------------------------*/
/** @brief std::vector like container with fixed max_size
 *
 * @tparam T value_type
 * @tparam maxSize max_size */
/* -------------------------------------------------------------------------*/
template<typename T, size_t maxSize>
class FixedArray {
    public:
        typedef T value_type;
        typedef T *iterator;
        typedef const T *const_iterator;
        explicit FixedArray(size_t count, const T &value = T()) {
            assign(count, value);
        }
        template< class InputIterator >
        FixedArray(InputIterator first, InputIterator last) {
            assign(first, last);
        }
        void assign(size_t count, const T &value) {
            assert(count < max_size());
            top = count;
            fill_n(a, count, value);
        }
        template< class InputIterator >
        void assign(InputIterator first, InputIterator last) {
            top = std::distance(first, last);
            assert(top < max_size());
            copy(first, last, a);
        }
        T &operator[](int i) {
            assert(i >= 0 and i < size());
            return a[i];
        }
        T operator[](int i) const {
            assert(i >= 0 and i < size());
            return a[i];
        }
        T front() const {
            assert(not empty());
            return a[0];
        }
        T back() const {
            assert(not empty());
            return a[top - 1];
        }
        T &front() {
            assert(not empty());
            return a[0];
        }
        T &back() {
            assert(not empty());
            return a[top - 1];
        }
        T *data() {
            return a;
        }
        iterator begin() {
            return a;
        }
        iterator end() {
            return a + size();
        }
        const_iterator begin() const {
            return a;
        }
        const_iterator end() const {
            return a + size();
        }

        bool empty() const {
            return size() == 0;
        }
        size_t size() const {
            return top;
        }
        size_t max_size() const {
            return maxSize;
        }
        void clear() {
            top = 0;
        }
        void push_back(const T &value) {
            assert(size() < max_size());
            a[top++] = value;
        }
        void pop_back() {
            assert(not empty());
            top--;
        }
        void resize(size_t count, T value = T()) {
            assert(count < max_size());
            while (size() < count) push_back(value);
            top = count;
        }
        template<size_t s>
        void swap(FixedArray<T, s> &other) {
            assert(max_size() >= other.size());
            assert(other.max_size() >= size());
            for (size_t i = 0; i < max(size(), other.size()); i++)
                if (i > size()) a[i] = other.a[i];
                else if (i > other.size()) other.a[i] = a[i];
                else swap(a[i], other.a[i]);
            swap(top, other.top);
        }
    private:
        T a[maxSize];
        size_t top;
};

template<class T, size_t s1, size_t s2>
bool operator<(FixedArray<T, s1> a, FixedArray<T, s2> b) {
    return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
}

template<class T, size_t s1, size_t s2>
bool operator==(FixedArray<T, s1> a, FixedArray<T, s2> b) {
    return not((a < b) or (b < a));
}

} // namespace sbl
#endif
