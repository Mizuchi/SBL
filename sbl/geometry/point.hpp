#ifndef _sbl_point
#define _sbl_point
#include"../base.hpp"
#include"state.hpp"
#include"../utility/complex.hpp"
#include"../utility/float.hpp"

namespace sbl {

typedef Complex<Float> Point;

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
state::Position position(Point b, Point c) {
    if (cross(b, c) < 0)   return state::right;
    if (cross(b, c) > 0)   return state::left;
    if (dot(b, c) < 0)     return state::reverse;
    if (norm(b) > norm(c)) return state::back;
    if (norm(b) < norm(c)) return state::front;
    return state::same;
}

template<class Point>
state::Position position(Point a, Point b, Point c) {
    return position(b - a, c - a);
}

template<class Point>
bool on_same_line(Point a, Point b, Point c = 0) {
    AUTO(p, position(a, b, c));
    return p != state::left and p != state::right;
}

template<class Point>
typename Point::value_type
dist_square(Point a, Point b) {
    return norm(a - b);
}

template<class Point>
typename Point::value_type
dist(Point a, Point b) {
    return sqrt(norm(a - b));
}

template<class Point>
typename Point::value_type
angle(Point a, Point b) {
    return acos(dot(a, b) / abs(a) / abs(b));
}

}

#endif
