#ifndef _sbl_fix_float
#define _sbl_fix_float
#include<cmath>
#include<limits>
#include"../utility/constant.hpp"
#include"state.hpp"
#include"../base.hpp"

namespace sbl {

inline static bool almost_equal(double a, double b, int maxUlps = 4) {
    // TODO: ulps support
    STATIC_ASSERT(std::numeric_limits<double>::is_iec559, 
            SBL_Requires_IEEE_754_floating_point_currently);
    return a - b < 1e-6 and b - a < 1e-6;
}

namespace fix {

inline static state::Compare cmp(double a, double b) {
    if (almost_equal(a, b)) return state::equal_to;
    return a < b ? state::less : state::greater;

}

inline static double asin(double a) {
    if (almost_equal(a, +1)) return +pi / 2;
    if (almost_equal(a, -1)) return -pi / 2;
    return ::std::asin(a);
}

inline static double acos(double a) {
    if (almost_equal(a, +1)) return 0;
    if (almost_equal(a, -1)) return -pi;
    return ::std::acos(a);
}

inline static double sqrt(double a) {
    return almost_equal(a, 0) ? 0 : ::std::sqrt(a);
}

template<class T> T abs(T a) { return a > 0 ? a : -a; }

} // namespace fix

inline static long long round(double a) {
    return a + (a > 0 ? 0.5 : -0.5);
}

} // namespace sbl
#endif
