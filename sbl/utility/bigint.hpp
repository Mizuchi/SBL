#ifndef _sbl_bigint
#define _sbl_bigint
#include<climits>
#include<istream>
#include<iomanip>
#include<vector>
#include<string>
#include<algorithm>
#include"../base.hpp"

namespace sbl {
const long long kBase = 1e6;
const long kBit = 6;

struct Bigint: std::vector<long long> {
    // XXX: This is just a prototype. 
    // Derived from a STL Container is not a good idea.
    typedef std::vector<long long> Base;
    Bigint(long long x = 0): Base(1, x) {}
    Bigint(std::string s) {
        if (s.empty()) s = "0";
        long long r = s[0] == '-' ? -1 : 1;
        if (r == -1) s.erase(s.begin());
        while (s.size() % kBit) s = '0' + s;
        resize(s.size() / kBit);
        for (size_t i = 0, j = size() - 1; i < s.size(); ++i % kBit ? 0 : j--)
            operator[](j) = operator[](j) * 10 + r * (s[i] - '0');
    }
    Bigint &format(long lastModified = LONG_MAX) {
        long long c = 0;
        FOR(i, *this) {
            *i += c;
            c = *i / kBase;
            *i %= kBase;
            if (--lastModified < 0 && !c)
                return *this;
        }
        for (; c; c /= kBase) push_back(c % kBase);
        return clean();
    }
    Bigint &clean() {
        while (size() > 1 && !back()) pop_back();
        return *this;
    }
    Bigint &normal() {
        int r = back() < 0 ? -1 : 1;
        FOR(i, *this) if (*i * r < 0)
            *i += r * kBase, *(i + 1) -= r;
        return clean();
    }
};

Bigint operator-(Bigint x) {
    FOR(i, x) *i = -*i;
    return x;
}

Bigint abs(Bigint x) {
    return x.back() < 0 ? -x : x;
}

bool operator < (Bigint x, Bigint y) {
    x.normal(), y.normal();
    x.resize(std::max(x.size(), y.size()));
    y.resize(x.size());
    for (int i = x.size() - 1; i >= 0; --i)
        if (x[i] != y[i])
            return x[i] < y[i];
    return false;
}

bool operator==(Bigint x, Bigint y) {
    x.normal(), y.normal();
    return Bigint::Base(x) == Bigint::Base(y);
}

std::istream &operator>>(std::istream &is, Bigint &x) {
    std::string s;
    if(is >> s) x = s;
    return is;
}

std::ostream &operator<<(std::ostream &os, Bigint x) {
    os << x.normal().back();
    for (AUTO(i, x.rbegin() + 1); i != x.rend(); ++i)
        os << std::setw(kBit) << std::setfill('0') << abs(*i);
    return os;
}

Bigint &operator+=(Bigint &x, long long y) {
    x[0] += y;
    return x.format(0);
}
Bigint operator+(Bigint x, long long y) {
    return x += y;
}
Bigint operator+(long long y, Bigint x) {
    return x += y;
}

Bigint &operator+=(Bigint &x, const Bigint &y) {
    x.resize(std::max(x.size(), y.size()));
    for (size_t i = 0; i < y.size(); ++i)
        x[i] += y[i];
    return x.format();
}
Bigint operator+(Bigint x, const Bigint &y) {
    return x += y;
}

Bigint &operator-=(Bigint &x, long long y) {
    x[0] -= y;
    return x.format(0);
}
Bigint operator-(Bigint x, long long y) {
    return x -= y;
}
Bigint operator-(long long y, Bigint x) {
    return y + (-x);
}

Bigint &operator-=(Bigint &x, const Bigint &y) {
    x.resize(std::max(x.size(), y.size()));
    for (size_t i = 0; i < y.size(); ++i)
        x[i] -= y[i];
    return x.format();
}

Bigint operator-(Bigint x, const Bigint &y) {
    return x -= y;
}

Bigint &operator*=(Bigint &x, long y) {
    FOR(i, x) *i *= y;
    return x.format();
}
Bigint operator*(Bigint x, long y) {
    return x *= y;
}
Bigint operator*(long y, Bigint x) {
    return x *= y;
}

Bigint operator*(const Bigint &x, const Bigint &y) {
    Bigint z;
    z.resize(x.size() + y.size());
    for (size_t i = 0; i < x.size(); ++i)
        for (size_t j = 0; j < y.size(); ++j)
            z[i + j] += x[i] * y[j];
    return z.format();
}
Bigint &operator*=(Bigint &x, const Bigint &y) {
    return x = x * y;
}

Bigint &operator/=(Bigint &x, long y) {
    long long c = 0;
    for (long i = x.size() - 1; i >= 0; --i) {
        c = c * kBase + x[i];
        x[i] = c / y;
        c = c % y;
    }
    return x.format();
}

Bigint operator/(Bigint x, long y) {
    return x /= y;
}

Bigint operator%(Bigint x, long y) {
    return x - x / y * y;
}

Bigint operator/(Bigint x, Bigint y) {
    bool r = x.back() * y.back() < 0;
    x = abs(x), y = abs(y);
    if (x < y) return 0;
    Bigint z, t;
    for (long i = x.size() - y.size(); i >= 0; i--) {
        t.assign(x.begin() + i, x.end());
        x.erase(x.begin() + i, x.end());
        long l = 0, r = kBase;
        while (l + 1 < r) {
            long m = (l + r) / 2;
            if (y * m <= t) l = m;
            else r = m;
        }
        z.push_back(l);
        t -= y * l;
        x.insert(x.end(), t.begin(), t.end());
    }
    std::reverse(z.begin(), z.end());
    return r ? -z : z;
}

Bigint operator%(const Bigint &x, const Bigint &y) {
    return x - (x / y) * y;
}

Bigint pow(const Bigint &a, unsigned long n) {
    return n % 2 ? a * pow(a, n - 1) :
           n > 0 ? pow(a * a, n / 2) : 1;
}

Bigint sqrt(const Bigint &a, const long k = 2) {
    Bigint x = 1, y = a / k;
    while (x != y) {
        x = ((k - 1) * y + a / pow(y, k - 1)) / k;
        x.swap(y);
    }
    return x;
}
} // namespace sbl
#endif
