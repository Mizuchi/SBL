#ifndef _sbl_complex
#define _sbl_complex
#include<iostream>
#include<math.h>

namespace sbl {

/// @brief sbl::Complex is a alternative of std::complex
///
/// So why do I re-inventing the wheel?
/// Yes, C++ Standard given as a good complex class,
/// unfortunately, "The effect of instantiating the template complex 
/// for any type other than float, double, or long double is unspecified."
/// (ISO/IEC 14882:2011, 26.4)
template<class T>
class Complex {
    private:
        T x, y;
    public:
        typedef T value_type;
        Complex(T x = 0, T y = 0): x(x), y(y) {}
        T real() const {
            return x;
        }
        T imag() const {
            return y;
        }
        void real(T v) {
            x = v;
        }
        void imag(T v) {
            y = v;
        }

        Complex &operator=(T b) {
            real(b);
            imag(0);
            return *this;
        }

        friend Complex operator+(Complex a, Complex b) {
            return Complex(a.real() + b.real(), a.imag() + b.imag());
        }
        friend Complex operator-(Complex a, Complex b) {
            return Complex(a.real() - b.real(), a.imag() - b.imag());
        }
        friend Complex operator*(Complex a, Complex b) {
            return Complex(a.real() * b.real() - a.imag() * b.imag(),
                           a.imag() * b.real() + a.real() * b.imag());
        }
        friend Complex operator/(Complex a, Complex b) {
            T p = b.real() * b.real() + b.imag() * b.imag();
            return Complex((a.real() * b.real() + a.imag() * b.imag()) / p,
                           (a.imag() * b.real() - a.real() * b.imag()) / p);
        }

        friend Complex operator+(T a, Complex b) {
            return Complex(a + b.real(), b.imag());
        }
        friend Complex operator+(Complex a, T b) {
            return Complex(a.real() + b, a.imag());
        }
        friend Complex operator-(T a, Complex b) {
            return Complex(b.real() - a, b.imag());
        }
        friend Complex operator-(Complex a, T b) {
            return Complex(a.real() - a, a.imag());
        }
        friend Complex operator*(T a, Complex b) {
            return Complex(a * b.real(), a * b.imag());
        }
        friend Complex operator*(Complex a, T b) {
            return Complex(a.real() * b, a.imag() * b);
        }
        friend Complex operator/(T a, Complex b) {
            return Complex(a) / b;
        }
        friend Complex operator/(Complex a, T b) {
            return Complex(a.real() / b, a.imag() / b);
        }

        friend Complex &operator+=(Complex &a, Complex b) {
            return a = a + b;
        }
        friend Complex &operator+=(Complex &a, T b) {
            return a = a + b;
        }
        friend Complex &operator-=(Complex &a, Complex b) {
            return a = a - b;
        }
        friend Complex &operator-=(Complex &a, T b) {
            return a = a - b;
        }
        friend Complex &operator*=(Complex &a, Complex b) {
            return a = a * b;
        }
        friend Complex &operator*=(Complex &a, T b) {
            return a = a * b;
        }
        friend Complex &operator/=(Complex &a, Complex b) {
            return a = a / b;
        }
        friend Complex &operator/=(Complex &a, T b) {
            return a = a / b;
        }
        friend bool operator==(Complex a, Complex b) {
            return a.real() == b.real() and a.imag() == b.imag();
        }
}; // class Complex

template<class T> T sqr(T a) {
    return a * a;
}
template<class T> T real(Complex<T> a) {
    return a.real();
}
template<class T> T imag(Complex<T> a) {
    return a.imag();
}
template<class T> T norm(Complex<T> a) {
    return real(a) * real(a) + imag(a) * imag(a);
}
template<class T> T arg(Complex<T> a) {
    return atan2(imag(a), real(a));
}
template<class T> T abs(Complex<T> a) {
    return sqrt(norm(a));
}
template<class T> Complex<T> conj(Complex<T> a) {
    return Complex<T>(real(a), -imag(a));
}
template<class T> Complex<T> polar(T rho, T theta) {
    T real = rho * cos(theta);
    T imag = rho * sin(theta);
    return Complex<T>(real, imag);
}

template<class T>
std::istream &operator>>(std::istream &is, Complex<T> a) {
    T x, y;
    is >> x >> y;
    a.real(x);
    a.imag(y);
    return is;
}

template<class T>
std::ostream &operator<<(std::ostream &os, Complex<T> a) {
    return os << '(' << a.real() << ", " << a.imag() << ')';
}

} // namespace sbl

#endif
