#ifndef _sbl_operator_overloading
#define _sbl_operator_overloading
#include<iostream>

namespace sbl {
/// @brief define a new type from a exists one that override operators
template<class Derived, class T>
class OperatorOverloadingBase {
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
        ~OperatorOverloadingBase() {}
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

    public:
        operator T() const { return value; }
        OperatorOverloadingBase(const T &a = 0): value(a) {}

        friend bool operator< (C a, C b) { return a.self().less(a, b); }
        friend bool operator==(C a, C b) { 
            return a.self().equal_to(a, b); 
        }

        friend R operator+=(R a, C b) { return a = a.self().plus(a, b); }
        friend R operator-=(R a, C b) { return a = a.self().minus(a, b); }
        friend R operator*=(R a, C b) { return a = a.self().multiplies(a, b); }
        friend R operator/=(R a, C b) { return a = a.self().divides(a, b); }
        friend R operator%=(R a, C b) { return a = a.self().modulus(a, b); }
        friend R operator&=(R a, C b) { return a = a.self().bit_and(a, b); }
        friend R operator|=(R a, C b) { return a = a.self().bit_or(a, b); }
        friend R operator^=(R a, C b) { return a = a.self().bit_xor(a, b); }

        friend bool operator&&(C a, C b) { return a.self().logical_and(a, b); }
        friend bool operator||(C a, C b) { return a.self().logical_or(a, b); }
        friend bool operator!(C a) { return a.self().logical_not(a); }
        friend S operator-(C a) { return a.self().negate(a); }

        friend S operator+(S a, C b) { return a += b; }
        friend S operator-(S a, C b) { return a -= b; }
        friend S operator*(S a, C b) { return a *= b; }
        friend S operator/(S a, C b) { return a /= b; }
        friend S operator%(S a, C b) { return a %= b; }
        friend S operator&(S a, C b) { return a &= b; }
        friend S operator|(S a, C b) { return a |= b; }
        friend S operator^(S a, C b) { return a ^= b; }

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

        friend R operator++(R a) { return a += 1; }
        friend R operator--(R a) { return a -= 1; }
        friend S operator++(R a, int) { S b = a; a += 1; return b; }
        friend S operator--(R a, int) { S b = a; a -= 1; return b; }

        friend std::istream &operator>>(std::istream &is, R a) {
            return is >> a.value;
        }
};

} // namespace sbl
#endif
