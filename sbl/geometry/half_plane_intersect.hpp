#ifndef _sbl_half_plane_intersect
#define _sbl_half_plane_intersect
#include"polygon_convex.hpp"
#include<deque>
#include<algorithm>

namespace sbl {
template<class Point>
class HalfPlaneIntersect {
    private:
        typedef const Line<Point> ConstLine;
        static double slope(ConstLine &a) {
            return arg(a[1] - a[0]);
        }
        static bool less(ConstLine &a, ConstLine &b) {
            if (not slope_equal(a, b))
                return slope(a) < slope(b);
            return position(b[0], a[0], b[1]) == state::right;
        }
        static bool slope_equal(ConstLine &a, ConstLine &b) {
            AUTO(s, position(a[1] - a[0], b[1] - b[0]));
            return s == state::front or s == state::back or s == state::same;
        }
        static bool over(ConstLine &a, ConstLine &b, ConstLine &c) {
            AUTO(res, intersect(a, b));
            // We already remove all lines that has the same slope.
            // So any two lines should always intersect each other.
            assert(res.size() == 1);
            return position(c[0], res[0], c[1]) == state::left;
        }
        void pop_last(ConstLine &a) {
            while (dq.size() > 1 and over(*(dq.rbegin() + 1), dq.back(), a))
                dq.pop_back();
        }
        void pop_first(ConstLine &a) {
            while (dq.size() > 1 and over(dq[1], dq[0], a))
                dq.pop_front();
        }
        template<class Lines>
        void half_plane_intersect(Lines &lines) {
            // http://www.csie.ntnu.edu.tw/~u91029/Half-planeIntersection.html
            FOR(i, lines) {
                pop_last(*i);
                pop_first(*i);
                dq.push_back(*i);
            }
            pop_last(dq[0]);
            pop_first(dq.back());
        }
        template<class Lines>
        static void sort_and_remove_duplicate(Lines &lines) {
            std::sort(lines.begin(), lines.end(), less);
            AUTO(i, std::unique(lines.begin(), lines.end(), slope_equal));
            lines.erase(i, lines.end());
        }
        std::deque< Line<Point> > dq;
    public:
        const std::deque< Line<Point> > &result;
        HalfPlaneIntersect(std::vector< Line<Point> > lines)
            : dq(), result(dq) {
            sort_and_remove_duplicate(lines);
            half_plane_intersect(lines);
        }
};

/// @brief given half planes, calculate intersection of all half planes.
///
/// @param a Half plane list. Each line represent a half plane as its left side.
///
/// @return a convex polygon repersent the intersection of all half planes.
template<class Point>
PolygonConvex<Point> half_plane_intersect(const std::vector< Line<Point> > &a) {
    HalfPlaneIntersect<Point> h(a);
    PolygonConvex<Point> result;
    if (h.result.size() <= 1)
        return result;
    FOR(i, h.result) {
        AUTO(j, i + 1);
        if (j == h.result.end())
            j = h.result.begin();
        AUTO(e, intersect(*i, *j));

        // XXX: Runtime error here indicate that the result convex polygon has
        // infinity area. It can not be represented due to the limitation of
        // SBL.
        assert(e.size() == 1);

        result.push_back(e[0]);
    }
    return result;
}

template<class Container, class Point>
void generate_half_plane_from_polygon(
    Container &s,
    const Polygon<Point> &a
) {
    FOR(i, a) {
        AUTO(j, i + 1);
        if (j == a.end()) j = a.begin();
        s.push_back(line(*i, *j));
    }
}

template<class Point>
PolygonConvex<Point> intersect(
    const PolygonConvex<Point> &a,
    const PolygonConvex<Point> &b
) {
    std::vector< Line<Point> > s;
    generate_half_plane_from_polygon(s, a);
    generate_half_plane_from_polygon(s, b);
    return half_plane_intersect(s);
}

template<class Point>
PolygonConvex<Point> kernel(const Polygon<Point> &a) {
    std::vector< Line<Point> > s;
    generate_half_plane_from_polygon(s, a);
    return half_plane_intersect(s);
}
} // namespace sbl
#endif
