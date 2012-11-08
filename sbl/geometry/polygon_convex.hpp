#ifndef _sbl_polygon_convex
#define _sbl_polygon_convex
#include<algorithm>
#include"polygon.hpp"
#include"../utility/macro.hpp"

namespace sbl {
template<class Point>
struct PolygonConvex: Polygon<Point> {
    SBL_CONSTRUCTOR_TO_BASE(Polygon<Point>, PolygonConvex);
};

template<class Container>
PolygonConvex<typename Container::value_type>
convex_hull(Container ps) {
    typedef typename Container::value_type Point;
    struct AddToResult {
        PolygonConvex<Point> result;
        void operator()(Point p0) {
            while (result.size() >= 2) {
                Point p1 = *result.rbegin();
                Point p2 = *(result.rbegin() + 1);
                if (position(p2, p1, p0) != state::right) 
                    break;
                result.pop_back();
            }
            result.push_back(p0);
        }
    } add_to_result; //     struct
    std::sort(ps.begin(), ps.end(), PointLess<Point>());
    FOR(i, ps) add_to_result(*i); // lower hull
    add_to_result.result.pop_back();
    RFOR(i, ps) add_to_result(*i); // upper hull
    add_to_result.result.pop_back();
    return add_to_result.result;
}
} // namespace sbl
#endif
