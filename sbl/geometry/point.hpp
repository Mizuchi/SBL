#ifndef _sbl_point
#define _sbl_point
#include<complex>
#include"fix.hpp"
#include"../base.hpp"
#include"state.hpp"

namespace sbl {

typedef std::complex<double> Point;

template<class Point>
bool almost_equal(Point a, Point b) {
    return almost_equal(real(a), real(b)) and
           almost_equal(imag(a), imag(b));
}

template<class Point>
typename Point::value_type
cross(Point a, Point b) {
    return imag(conj(a) * b);
}

template<class Point>
typename Point::value_type
dot(Point a, Point b) {
    return real(conj(a) * b);
}

template<class Point>
struct PointLess { // '_'!
    bool operator()(Point a, Point b) const {
        return real(a) != real(b) ? real(a) < real(b) : imag(a) < imag(b);
    }
}; // struct PointLess

// stand in 0, face to a, which position is b on.
template<class Point>
state::Position position(Point a, Point b) {
    // XXX: need better way to check if two float is almost equal.
    if (almost_equal(a, b)) return state::same;
    typename Point::value_type scale = abs(a) * abs(b);
    if (scale < 1) scale = 1;
    if (not almost_equal(cross(a, b) / scale, 0))
        return cross(a, b) < 0 ? state::right : state::left;
    if (not almost_equal(dot(a, b) / scale, 0) and dot(a, b) < 0)
        return state::reverse;
    return norm(a) < norm(b) ?  state::front : state::back;

}

// stand in a, face to b, which position is c on.
template<class Point>
state::Position position(Point a, Point b, Point c) {
    return position(b - a, c - a);
}

template<class Point>
typename Point::value_type
dist_square(Point a, Point b) {
    return norm(a - b);
}

template<class Point>
typename Point::value_type
dist(Point a, Point b) {
    return fix::sqrt(norm(a - b));
}

} // namespace sbl
#endif
