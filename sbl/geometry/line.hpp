#ifndef _sbl_line
#define _sbl_line
#include<typeinfo>
#include<stdexcept>
#include<vector>
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

template<class Point>
std::vector<Point> intersect(
    const BaseLine<Point> &a,
    const BaseLine<Point> &b
) {
    std::vector<Point> result;
    typedef typename Point::value_type value_type;
    AUTO(s1, cross(b[0] - a[0], b[1] - a[0]));
    AUTO(s2, cross(b[1] - a[1], b[0] - a[1]));
    if (almost_equal(s1 + s2, 0))
        return result;
    e = (a[1] - a[0]) * (s1 / (s1 + s2)) + a[0];
    bool aIsLine = typeid(a) == typeid(Line<Point>);
    bool bIsLine = typeid(b) == typeid(Line<Point>);
    if ((aIsLine or contain(static_cast<Segment<Point>&>(a), e)) and
        (bIsLine or contain(static_cast<Segment<Point>&>(b), e)))
        result.push_back(e);
    return result;
}

} // namespace sbl 
#endif
