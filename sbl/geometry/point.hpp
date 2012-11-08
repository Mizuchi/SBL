#ifndef _sbl_point
#define _sbl_point
#include<complex>
#include"fix.hpp"
#include"../base.hpp"
#include"state.hpp"

namespace sbl {

typedef std::complex<double> Point;

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
    if (fix::cmp(cross(a, b), 0) == state::less) return state::right;
    if (fix::cmp(cross(a, b), 0) == state::greater) return state::left;
    if (fix::cmp(dot(a, b), 0) == state::less) return state::reverse;
    if (fix::cmp(norm(a), norm(b)) == state::greater) return state::back;
    if (fix::cmp(norm(a), norm(b)) == state::less) return state::front;
    return state::same;
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

template<class Point>
typename Point::value_type
angle(Point a, Point b) {
    return fix::acos(dot(a, b) / abs(a) / abs(b));
}

} // namespace sbl
#endif
