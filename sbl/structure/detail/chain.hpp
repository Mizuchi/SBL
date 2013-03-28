#include"../vector_tree.hpp"
#include"../../utility/type_traits.hpp"

namespace sbl {
namespace chainFeatures {
const int replace  = 0b1;
const int reverse  = 0b10;
const int sum      = 0b1000;
const int top      = 0b10000;
const int maxsum   = 0b100000;
const int lcp      = 0b1000000;
} // namespace chainFeatures

namespace detail {
template<class T>
struct ReplaceBase {
    public:
        static const int feature = chainFeatures::replace;
        bool isReplaced;
        T replaceValue;
    protected:
        ReplaceBase(T value): replaceValue(value) {}
        ~ReplaceBase() {}
};

struct ReverseBase {
    public:
        static const int feature = chainFeatures::reverse;
        bool isReversed;
    protected:
        template<class T>
        ReverseBase(T value) {}
        ~ReverseBase() {}
};
template<class T>
struct SumBase {
    public:
        static const int feature = chainFeatures::sum;
        T allSum;
    protected:
        SumBase(T value): allSum(value) {}
        ~SumBase() {}
};
template<class T>
struct TopBase {
    public:
        static const int feature = chainFeatures::top;
        T topValue;
    protected:
        TopBase(T value): topValue(value) {}
        ~TopBase() {}
};
template<class T>
struct MaxSumBase {
    public:
        static const int feature = chainFeatures::maxsum;
        T leftMaxSum;
        T rightMaxSum;
        T maxSum;
    protected:
        MaxSumBase(T value):
            leftMaxSum(value),
            rightMaxSum(value),
            maxSum(value) {}
        ~MaxSumBase() {}
};
template<class HashReturn>
struct LCPBase {
    public:
        static const int feature = chainFeatures::lcp;
        HashReturn hashValue;
    protected:
        ~LCPBase() {}
};
} // namespace detail
} // namespace sbl
