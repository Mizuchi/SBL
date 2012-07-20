#ifndef _sbl_element
#define _sbl_element
#include<functional>

namespace sbl {

/** Return identity element with a operator and a element.
 *
 * Its argument is an operation, and its return value is the identity element
 * for that operation.  It is overloaded for addition and multiplication, and
 * you can overload it for your own nefarious operations. */
template<class T>
T identity(std::plus<T>, const T& = T(0)) {
    return T(0);
}

template<class T>
T identity(std::multiplies<T>, const T& = T(1)) {
    return T(1);
}

/** Return inverse element with a operator and a element.
 *
 * Its argument is an operation, and its return value is the inverse element of
 * that element for that operation.  It is overloaded for addition and
 * multiplication, and you can overload it for your own nefarious operations.
 * */
template<class T>
T inverse(std::plus<T>, const T &a) {
    return -a;
}

template<class T> T inverse(std::multiplies<T>, const T &a);

/// @return conjugate of the number 
template<class Number> 
Number conj(Number n)  {
    return n;
}

} // namespace sbl
#endif
