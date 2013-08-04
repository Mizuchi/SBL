#ifndef _sbl_bigint
#define _sbl_bigint
#include<climits>
#include<istream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include"operator_overloading.hpp"
#include"foreach.hpp"
#include"../base.hpp"

namespace sbl {
namespace bigInteger {

static const long long kBase = 1e6;
static const int kBit = 6;

/// integer types that have infinite range and precision.
class Bigint:
    public operatorOverloading::Base<
        Bigint,
        std::vector<long long>,
        operatorOverloading::ForbiddenWrapperTypePolicy> {
    private:
        typedef std::vector<long long> T;
        typedef operatorOverloading::Base <
        Bigint,
        T,
        operatorOverloading::ForbiddenWrapperTypePolicy
        > Base;

        friend class operatorOverloading::Base <
            Bigint,
            T,
            operatorOverloading::ForbiddenWrapperTypePolicy
                >;

        bool less_than_zero(T a) const {
            return not a.empty() and a.back() < 0;
        }

        T zero() const {
            return T(0);
        }

        T abs(T a) const {
            return less_than_zero(a) ? negate(a) : a;
        }

        T plus(T a, T b) const {
            size_t m = std::max(a.size(), b.size());
            a.resize(m);
            for (size_t i = 0; i < b.size(); ++i)
                a[i] += b[i];
            return format(a);
        }
        T minus(T a, T b) const {
            return plus(a, negate(b));
        }
        T multiplies(T a, T b) const {
            T c(a.size() + b.size(), 0);
            for (size_t i = 0; i < a.size(); ++i)
                for (size_t j = 0; j < b.size(); ++j)
                    c[i + j] += a[i] * b[j];
            return format(c);
        }
        T divides(T x, T y) const {
            bool lhsIsNegative = less_than_zero(x);
            bool rhsIsNegative = less_than_zero(y);
            x = abs(x);
            y = abs(y);
            if (less(x, y))
                return zero();
            T z, t;
            size_t i = 1 + x.size() - y.size();
            while (i -- > 0) {
                t.assign(x.begin() + i, x.end());
                x.erase(x.begin() + i, x.end());
                long long l = 0, r = kBase;
                while (l + 1 < r) {
                    long long m = (l + r) / 2;
                    if (not less(t, multiplies(y, constructor(m))))
                        l = m;
                    else
                        r = m;
                }
                z.push_back(l);
                t = minus(t, multiplies(y, constructor(l)));
                x.insert(x.end(), t.begin(), t.end());
            }
            std::reverse(z.begin(), z.end());
            bool isNegative = (lhsIsNegative and not rhsIsNegative) or
                              (rhsIsNegative and not lhsIsNegative);
            return clean(isNegative ? negate(z) : z);
        }
        T modulus(T a, T b) const {
            return minus(a, multiplies(divides(a, b), b));
        }
        T negate(T a) const {
            foreach(&i, a) i = -i;
            return a;
        }
        bool equal_to(T a, T b) const {
            return normal(a) == normal(b);
        }
        bool less(T a, T b) const {
            a = normal(a);
            b = normal(b);
            size_t m = std::max(a.size(), b.size());
            a.resize(m);
            b.resize(m);
            while (m -- > 0)
                if (a[m] != b[m])
                    return a[m] < b[m];
            return false;
        }

        std::istream &input(std::istream &is, T &x) const {
            std::string s;
            is >> s;
            x = constructor(s);
            return is;
        }

        std::ostream &output(std::ostream &os, T x) const {
            if (x.empty())
                return os << 0;
            x = normal(x);
            os << x.back();
            x.pop_back();
            rforeach(i, x) {
                os << std::setw(kBit) << std::setfill('0') << std::abs(i);
            }
            return os;
        }

        T format(T num, long lastModified = LONG_MAX) const {
            long long c = 0;
            foreach(&i, num) {
                i += c;
                c = i / kBase;
                i %= kBase;
                if (--lastModified < 0 and c == 0)
                    return num;
            }
            for (; c; c /= kBase)
                num.push_back(c % kBase);
            return clean(num);
        }
        T clean(T num) const {
            while (not num.empty() and num.back() == 0)
                num.pop_back();
            return num;
        }
        T normal(T num) const {
            if (num.empty())
                return num;
            int r = num.back() < 0 ? -1 : 1;
            for (size_t i = 0; i < num.size(); i++)
                if (num[i] * r < 0) {
                    num[i] += r * kBase;
                    num[i + 1] -= r;
                }
            return clean(num);
        }

        T constructor(int x) const {
            return constructor((long long)(x));
        }
        T constructor(long x) const {
            return constructor((long long)(x));
        }
        T constructor(long long x) const {
            if (x == 0) return zero();
            return T(1, x);
        }
        T constructor(const char *s) const {
            return constructor(std::string(s));
        }
        T constructor(std::string s) const {
            T result;
            if (s.empty())
                s = "0";
            long long r = (s[0] == '-' ? -1 : 1);
            if (r == -1)
                s.erase(s.begin());
            while (s.size() % kBit)
                s = '0' + s;
            result.resize(s.size() / kBit);
            for (size_t i = 0, j = result.size() - 1; i < s.size(); ++i % kBit ? 0 : j--)
                result[j] = result[j] * 10 + r * (s[i] - '0');
            return result;
        }

    public:

        Bigint(): Base(zero()) {}
        Bigint(T a): Base(a) {}
        Bigint(int x): Base(constructor(x)) {}
        Bigint(long x): Base(constructor(x)) {}
        Bigint(long long x): Base(constructor(x)) {}
        Bigint(std::string x): Base(constructor(x)) {}
        Bigint(const char *x): Base(constructor(x)) {}
};

Bigint pow(const Bigint &a, size_t n) {
    if (n == 0)
        return 1;
    if (n % 2 == 0)
        return pow(a * a, n / 2);
    else
        return a * pow(a, n - 1);
}

Bigint sqrt(const Bigint &a, const long k = 2) {
    Bigint x = 1, y = a / k;
    while (x != y) {
        x = ((k - 1) * y + a / pow(y, k - 1)) / k;
        std::swap(x, y);
    }
    return x;
}
} // namespace bigInteger
using bigInteger::Bigint;
} // namespace sbl
#endif
