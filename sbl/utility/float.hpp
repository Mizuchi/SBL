#ifndef _sbl_float
#define _sbl_float
#include"operator_overloading.hpp"
#include"constant.hpp"
#include<cmath>

namespace sbl {
namespace almostEqualFloat {

/// @brief overried the less than operator for built-in float 
///
/// known issue: 
/// since c++ does not support implicit conversion twice, 
/// it does not accept a float when use it as a argument
/// of a construct of a class. (see the unittest)
class Float: public OperatorOverloadingBase<Float, double> {
    private:
        typedef OperatorOverloadingBase<Float, double> Base;
        friend class OperatorOverloadingBase<Float, double>;
    public:
        bool less(double a, double b) const {
            return (b - a) > zero;
        }
        bool equal_to(double a, double b) const {
            return not(less(a, b) or less(b, a));
        }
        double divides(double a, double b) const {
            assert((b < -zero or zero < b) and "SBL::Float: Division by zero");
            return a / b;
        }
    public:
        Float(double a = 0): Base(a) {}
        operator double() const {
            return Base::operator double();
        }
};

static inline Float asin(Float a) {
    if (a == -1) return -pi / 2;
    if (a == 1)  return pi / 2;
    return std::asin(a);
}

static inline Float acos(Float a) {
    if (a == -1) return pi;
    if (a == 1)  return 0;
    return std::acos(a);
}

static inline Float sqrt(Float a) {
    return (a == 0) ? 0 : std::sqrt(a);
}


static inline Float atan2(Float x, Float y) {
    return std::atan2(x, y);
}
static inline Float pow(Float x, Float y)   {
    return std::pow(x, y);
}

#define FLOATMAP(func) static inline Float func(Float x) {return std::func(x);}
FLOATMAP(fabs);
FLOATMAP(abs);
FLOATMAP(atan);
FLOATMAP(sin);
FLOATMAP(cos);
FLOATMAP(tan);
FLOATMAP(sinh);
FLOATMAP(cosh);
FLOATMAP(tanh);
FLOATMAP(log);
FLOATMAP(exp);
FLOATMAP(log10);
FLOATMAP(ceil);
FLOATMAP(floor);
#undef FLOATMAP

} // namespace floatAlmostEqual
using almostEqualFloat::Float;
} // namespace sbl
#endif
