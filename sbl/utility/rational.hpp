#ifndef _sbl_rational
#define _sbl_rational
#include"../math/gcd.hpp"

namespace sbl {

template<typename I>
class Rational {

    public:
        typedef I int_type;
        I n, d;

        // Constructors
        Rational(): n(0), d(1) {}
        Rational(I n): n(n), d(1) {}
        Rational(I n, I d) : n(n), d(d) {
            format();
        }

        // Representation
        I numerator() const {
            return n;
        }
        I denominator() const {
            return d;
        }

        // assignment operators
        Rational &assign(I _n, I _d) {
            return *this = Rational(_n, _d);
        }

        // Arithmetic operators
        friend Rational operator+ (Rational a, Rational b) {
            return Rational(a.n * b.d + b.n * a.d, a.d * b.d);
        }
        friend Rational operator- (Rational a, Rational b) {
            return Rational(a.n * b.d - b.n * a.d, a.d * b.d);
        }
        friend Rational operator* (Rational a, Rational b) {
            return Rational(a.n * b.n, a.d * b.d);
        }
        friend Rational operator/ (Rational a, Rational b) {
            return Rational(a.n * b.d, a.d * b.n);
        }

        friend Rational &operator+=(Rational &a, Rational b) {
            return a = a + b;
        }
        friend Rational &operator-=(Rational &a, Rational b) {
            return a = a - b;
        }
        friend Rational &operator*=(Rational &a, Rational b) {
            return a = a * b;
        }
        friend Rational &operator/=(Rational &a, Rational b) {
            return a = a / b;
        }

        // Comparison operators
        friend bool operator< (Rational a, Rational b) {
            return (a - b).numerator() < 0;
        }
        friend bool operator== (Rational a, Rational b) {
            return (a - b).numerator() == 0;
        }

        // Unary operators
        Rational operator+ () {
            return Rational(+n, d);
        }
        Rational operator- () {
            return Rational(-n, d);
        }
    private:
        void format() {
            I m = gcd(n, d);
            if (m != 0) {
                n /= m;
                d /= m;
            }
            if (d < 0) {
                n = -n;
                d = -d;
            }
        }
};
} // namespace sbl
#endif
