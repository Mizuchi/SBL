#ifndef _sbl_line
#define _sbl_line
#include<typeinfo>
#include<stdexcept>
#include<vector>
#include<iostream>
#include"point.hpp"

namespace sbl {
template<class Point>
class BaseLine {
    public:
        Point operator[](int i) const {
            if (i == 0) return a.first;
            if (i == 1) return a.second;
            throw std::out_of_range("Line: range check");
        }
        Point &operator[](int i) {
            if (i == 0) return a.first;
            if (i == 1) return a.second;
            throw std::out_of_range("Line: range check");
        }
    protected:
        BaseLine(Point x, Point y): a(x, y) {}
        BaseLine() {}
    private:
        std::pair<Point, Point> a;
};

template<class Point>
std::ostream& operator<<(std::ostream &os, const BaseLine<Point> &b) {
    return os << "{" << b[0] << ", " << b[1] << "}";
}


template<class Point>
struct Line : BaseLine<Point> {
    Line() {}
    Line(Point a, Point b): BaseLine<Point>(a, b) {}
};

template<class Point>
struct Segment : BaseLine<Point> {
    Segment() {}
    Segment(Point a, Point b): BaseLine<Point>(a, b) {}
};

template<class Point>
Segment<Point> segment(Point a, Point b) {
    return Segment<Point>(a, b);
}

template<class Point>
Line<Point> line(Point a, Point b) {
    return Line<Point>(a, b);
}

template<class Point>
bool contain(Line<Point> l, Point p) {
    return almost_equal(cross(l[1] - p, l[0] - p), 0);
}

template<class Point>
bool contain(Segment<Point> s, Point p) {
    AUTO(st, position(s[0] - p, s[1] - p));
    return st == state::same or st == state::reverse;
}

template<template<class>class T1, template<class>class T2, class Point>
std::vector<Point> intersect(
    const T1<Point> &a,
    const T2<Point> &b
) {
    std::vector<Point> result;
    typedef typename Point::value_type value_type;
    AUTO(s0, cross(b[0] - a[0], b[1] - a[0]));
    AUTO(s1, cross(b[1] - a[1], b[0] - a[1]));
    if (almost_equal(s0 + s1, 0))
        return result;
    Point e = (a[1] * s0 + a[0] * s1) / (s0 + s1);
    if ((typeid(T1<Point>) == typeid(Line<Point>) or contain(a, e)) and 
        (typeid(T2<Point>) == typeid(Line<Point>) or contain(b, e)))
        result.push_back(e);
    return result;
}

template<class Point>
Point projection(const BaseLine<Point> &l, const Point &p) {
    AUTO(t, dot(p - l[0], l[0] - l[1]) / dist_square(l[0], l[1]));
    return l[0] + t * (l[0] - l[1]);
}

template<class Point>
Point reflection(const BaseLine<Point> &l, const Point &p) {
    return p + 2 * (projection(l, p) - p);
}

template<class Point>
typename Point::value_type
dist_square(const Line<Point> &l, Point p) {
    return dist_square(projection(l, p), p);
}

template<class Point>
typename Point::value_type
dist_square(Point p, const Line<Point> &l) {
    return dist_square(l, p);
}

template<class Point>
typename Point::value_type
dist(const Line<Point> &l, Point p) {
    return fix::sqrt(dist_square(l, p));
}

template<class Point>
typename Point::value_type
dist(Point p, const Line<Point> &l) {
    return dist(l, p);
}

} // namespace sbl
#endif
