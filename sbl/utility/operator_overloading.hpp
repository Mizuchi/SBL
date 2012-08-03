#ifndef _sbl_operator_overloading
#define _sbl_operator_overloading
#include<iostream>

namespace sbl {

namespace operatorOverloading {

template<class Derived, class T> struct ForbiddenWrapperTypePolicy{};

template<class Derived, class T>
struct AnyTypePolicy {
        typedef Derived S;
        typedef Derived &R;
        typedef const Derived &C;
        template<class U>
        friend R operator+=(R a, U b) { return a += C(b); }
        template<class U>
        friend R operator-=(R a, U b) { return a -= C(b); }
        template<class U>
        friend R operator*=(R a, U b) { return a *= C(b); }
        template<class U>
        friend R operator/=(R a, U b) { return a /= C(b); }
        template<class U>
        friend R operator%=(R a, U b) { return a %= C(b); }
        template<class U>
        friend R operator&=(R a, U b) { return a &= C(b); }
        template<class U>
        friend R operator|=(R a, U b) { return a |= C(b); }
        template<class U>
        friend R operator^=(R a, U b) { return a ^= C(b); }

        template<class U>
        friend bool operator< (U a, C b) { return C(a) < C(b); }
        template<class U>
        friend bool operator< (C a, U b) { return C(a) < C(b); }
        template<class U>
        friend bool operator==(U a, C b) { return C(a) == C(b); }
        template<class U>
        friend bool operator==(C a, U b) { return C(a) == C(b); }
        template<class U>
        friend bool operator> (U a, C b) { return b < a; }
        template<class U>
        friend bool operator> (C a, U b) { return b < a; }
        template<class U>
        friend bool operator<=(U a, C b) { return not(a > b); }
        template<class U>
        friend bool operator<=(C a, U b) { return not(a > b); }
        template<class U>
        friend bool operator>=(U a, C b) { return not(a < b); }
        template<class U>
        friend bool operator>=(C a, U b) { return not(a < b); }
        template<class U>
        friend bool operator!=(U a, C b) { return not(a == b); }
        template<class U>
        friend bool operator!=(C a, U b) { return not(a == b); }

        template<class U>
        friend bool operator&&(U a, C b) { return C(a) && C(b); }
        template<class U>
        friend bool operator&&(C a, U b) { return C(a) && C(b); }
        template<class U>
        friend bool operator||(U a, C b) { return C(a) || C(b); }
        template<class U>
        friend bool operator||(C a, U b) { return C(a) || C(b); }

        template<class U>
        friend S operator+(U a, C b) { return C(a) + C(b); }
        template<class U>
        friend S operator+(C a, U b) { return C(a) + C(b); }
        template<class U>
        friend S operator-(U a, C b) { return C(a) - C(b); }
        template<class U>
        friend S operator-(C a, U b) { return C(a) - C(b); }
        template<class U>
        friend S operator*(U a, C b) { return C(a) * C(b); }
        template<class U>
        friend S operator*(C a, U b) { return C(a) * C(b); }
        template<class U>
        friend S operator/(U a, C b) { return C(a) / C(b); }
        template<class U>
        friend S operator/(C a, U b) { return C(a) / C(b); }
        template<class U>
        friend S operator%(U a, C b) { return C(a) % C(b); }
        template<class U>
        friend S operator%(C a, U b) { return C(a) % C(b); }
        template<class U>
        friend S operator&(U a, C b) { return C(a) & C(b); }
        template<class U>
        friend S operator&(C a, U b) { return C(a) & C(b); }
        template<class U>
        friend S operator|(U a, C b) { return C(a) | C(b); }
        template<class U>
        friend S operator|(C a, U b) { return C(a) | C(b); }
        template<class U>
        friend S operator^(U a, C b) { return C(a) ^ C(b); }
        template<class U>
        friend S operator^(C a, U b) { return C(a) ^ C(b); }

}; // struct AnyTypePolicy 

template<class Derived, class U>
struct ExactTypePolicy {
        typedef Derived S;
        typedef Derived &R;
        typedef const Derived &C;

        friend R operator+=(R a, U b) { return a += C(b); }
        friend R operator-=(R a, U b) { return a -= C(b); }
        friend R operator*=(R a, U b) { return a *= C(b); }
        friend R operator/=(R a, U b) { return a /= C(b); }
        friend R operator%=(R a, U b) { return a %= C(b); }
        friend R operator&=(R a, U b) { return a &= C(b); }
        friend R operator|=(R a, U b) { return a |= C(b); }
        friend R operator^=(R a, U b) { return a ^= C(b); }

        friend bool operator< (U a, C b) { return C(a) < C(b); }
        friend bool operator< (C a, U b) { return C(a) < C(b); }
        friend bool operator==(U a, C b) { return C(a) == C(b); }
        friend bool operator==(C a, U b) { return C(a) == C(b); }
        friend bool operator> (U a, C b) { return b < a; }
        friend bool operator> (C a, U b) { return b < a; }
        friend bool operator<=(U a, C b) { return not(a > b); }
        friend bool operator<=(C a, U b) { return not(a > b); }
        friend bool operator>=(U a, C b) { return not(a < b); }
        friend bool operator>=(C a, U b) { return not(a < b); }
        friend bool operator!=(U a, C b) { return not(a == b); }
        friend bool operator!=(C a, U b) { return not(a == b); }

        friend bool operator&&(U a, C b) { return C(a) && C(b); }
        friend bool operator&&(C a, U b) { return C(a) && C(b); }
        friend bool operator||(U a, C b) { return C(a) || C(b); }
        friend bool operator||(C a, U b) { return C(a) || C(b); }

        friend S operator+(U a, C b) { return C(a) + C(b); }
        friend S operator+(C a, U b) { return C(a) + C(b); }
        friend S operator-(U a, C b) { return C(a) - C(b); }
        friend S operator-(C a, U b) { return C(a) - C(b); }
        friend S operator*(U a, C b) { return C(a) * C(b); }
        friend S operator*(C a, U b) { return C(a) * C(b); }
        friend S operator/(U a, C b) { return C(a) / C(b); }
        friend S operator/(C a, U b) { return C(a) / C(b); }
        friend S operator%(U a, C b) { return C(a) % C(b); }
        friend S operator%(C a, U b) { return C(a) % C(b); }
        friend S operator&(U a, C b) { return C(a) & C(b); }
        friend S operator&(C a, U b) { return C(a) & C(b); }
        friend S operator|(U a, C b) { return C(a) | C(b); }
        friend S operator|(C a, U b) { return C(a) | C(b); }
        friend S operator^(U a, C b) { return C(a) ^ C(b); }
        friend S operator^(C a, U b) { return C(a) ^ C(b); }

}; // struct ExactTypePolicy 

/// @brief define a new type from a exists one that override operators
template<
    class Derived, 
    class T,
    template <class, class> class OPolicy = ExactTypePolicy
> class Base
    :public OPolicy<Derived, T>{
    private:
        typedef Derived S;
        typedef Derived &R;
        typedef const Derived &C;

        C self() const {
            return static_cast<C>(*this);
        }
        R self() {
            return static_cast<R>(*this);
        }

    protected:
        ~Base() {}
        T value;

        T    plus(T a, T b)        const { return a + b;      } 
        T    minus(T a, T b)       const { return a - b;      } 
        T    multiplies(T a, T b)  const { return a * b;      } 
        T    divides(T a, T b)     const { return a / b;      } 
        T    modulus(T a, T b)     const { return a % b;      } 
        T    negate(T a)           const { return -a;         } 

        bool equal_to(T a, T b)    const { return a == b;     } 
        bool less(T a, T b)        const { return a < b;      } 

        bool logical_and(T a, T b) const { return a and b;    } 
        bool logical_or(T a, T b)  const { return a or b;     } 
        bool logical_not(T a)      const { return not a;      } 

        T    bit_and(T a, T b)     const { return a bitand b; } 
        T    bit_or(T a, T b)      const { return a bitor b;  } 
        T    bit_xor(T a, T b)     const { return a xor b;    } 

        std::istream& input (std::istream &is, T &a) const { return is >> a; }
        std::ostream& output(std::ostream &os, T  a) const { return os << a; }

        T    do_plus(T a, T b)        const { return self().plus(a, b);      } 
        T    do_minus(T a, T b)       const { return self().minus(a, b);      } 
        T    do_multiplies(T a, T b)  const { return self().multiplies(a, b); } 
        T    do_divides(T a, T b)     const { return self().divides(a,b);     } 
        T    do_modulus(T a, T b)     const { return self().modulus(a,b);     } 
        T    do_negate(T a)           const { return self().negate(a);        } 

        bool do_equal_to(T a, T b)    const { return self().equal_to(a,b);    } 
        bool do_less(T a, T b)        const { return self().less(a,b);        } 

        bool do_logical_and(T a, T b) const { return self().logical_and(a,b); } 
        bool do_logical_or(T a, T b)  const { return self().logical_or(a,b);  } 
        bool do_logical_not(T a)      const { return self().logical_not(a);   } 

        T    do_bit_and(T a, T b)     const { return self().bit_and(a,b);     } 
        T    do_bit_or(T a, T b)      const { return self().bit_or(a,b);      } 
        T    do_bit_xor(T a, T b)     const { return self().bit_xor(a,b);     } 

        std::istream& do_input (std::istream &is, T &a) const { 
            return self().input(is, a);
        }
        std::ostream& do_output(std::ostream &os, T  a) const { 
            return self().output(os, a);
        }
    public:
        operator T() const { return value; }
        Base(const T &a): value(a) {}

        friend bool operator< (C a, C b) { return a.do_less(a, b); }
        friend bool operator==(C a, C b) { return a.do_equal_to(a, b); }
        friend bool operator> (C a, C b) { return b < a; }
        friend bool operator<=(C a, C b) { return not(a > b); }
        friend bool operator>=(C a, C b) { return not(a < b); }
        friend bool operator!=(C a, C b) { return not(a == b); }

        friend R operator+=(R a, C b) { return a = a.do_plus(a, b); }
        friend R operator-=(R a, C b) { return a = a.do_minus(a, b); }
        friend R operator*=(R a, C b) { return a = a.do_multiplies(a, b); }
        friend R operator/=(R a, C b) { return a = a.do_divides(a, b); }
        friend R operator%=(R a, C b) { return a = a.do_modulus(a, b); }
        friend R operator&=(R a, C b) { return a = a.do_bit_and(a, b); }
        friend R operator|=(R a, C b) { return a = a.do_bit_or(a, b); }
        friend R operator^=(R a, C b) { return a = a.do_bit_xor(a, b); }

        friend bool operator&&(C a, C b) { return a.do_logical_and(a, b); }
        friend bool operator||(C a, C b) { return a.do_logical_or(a, b); }
        friend bool operator!(C a)       { return a.do_logical_not(a); }
        friend S operator-(C a) { return a.do_negate(a); }

        friend S operator+(S a, C b) { return a += b; }
        friend S operator-(S a, C b) { return a -= b; }
        friend S operator*(S a, C b) { return a *= b; }
        friend S operator/(S a, C b) { return a /= b; }
        friend S operator%(S a, C b) { return a %= b; }
        friend S operator&(S a, C b) { return a &= b; }
        friend S operator|(S a, C b) { return a |= b; }
        friend S operator^(S a, C b) { return a ^= b; }

        friend R operator++(R a) { return a += 1; }
        friend R operator--(R a) { return a -= 1; }
        friend S operator++(R a, int) { S b = a; a += 1; return b; }
        friend S operator--(R a, int) { S b = a; a -= 1; return b; }

        friend std::istream &operator>>(std::istream &is, R a) {
            return a.do_input(is, a.value);
        }

        friend std::ostream &operator<<(std::ostream &os, C a) {
            return a.do_output(os, a.value);
        }
};
} // namespace operatorOverloading
} // namespace sbl
#endif
