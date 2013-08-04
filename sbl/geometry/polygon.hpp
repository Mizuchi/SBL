#ifndef _sbl_polygon
#define _sbl_polygon
#include"line.hpp"
#include"../utility/macro.hpp"
namespace sbl {
template<class Point>
struct Polygon: std::vector<Point> {
    SBL_CONSTRUCTOR_TO_BASE(std::vector<Point>, Polygon);
};
template<class Point>
Point next(const Polygon<Point> &a, size_t i) {
    return i + 1 == a.size() ? a[0] : a[i + 1];
}
template<class Point>
state::Contain contain(const Polygon<Point> &poly, const Point &p) {
    size_t inside = false;
    for (size_t i = 0; i < poly.size(); i++) {
        Point a = poly[i], b = next(poly, i);
        if (contain(segment(a, b), p)) return state::touch;
        if (imag(a) > imag(b)) std::swap(a, b);
        if (imag(a) <= imag(p) and imag(p) < imag(b))
            if (cross(a - p, b - p) < 0)
                inside = not inside;
    }
    return inside ? state::inside : state::outside;
}

template<class Point>
typename Point::value_type
area_double(const Polygon<Point> &p) {
    if (p.empty()) return 0;
    typename Point::value_type result = 0;
    for (size_t i = 0; i < p.size(); ++i)
        result += cross(p[i], next(p, i));
    return result;
}

template<class Point>
typename Point::value_type
area(const Polygon<Point> &p) {
    return area_double(p) / 2.0;
}

/// @return centroid of a polygon 
template<class Point>
Point centroid(const Polygon<Point> &p) {
    Point result;
    if (almost_equal(area_double(p), 0)) {
        FOR(i, p) result += *i;
        result /= p.size();
    } else {
        for (size_t i = 0; i < p.size(); ++i)
            result += cross(p[i], next(p, i)) * (p[i] + next(p, i));
        result /= area_double(p) * 3;
    }
    return result;
}

} // namespace sbl
#endif
