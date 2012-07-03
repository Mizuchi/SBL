#ifndef _sbl_macro
#define _sbl_macro
#include"../base.hpp"

#define SBL_CONSTRUCTOR_TO_BASE(base, derived)                                \
    derived() {}                                                              \
    template<class _T1>                                                       \
    derived(_T1 const &t1) : base(t1) {}                                      \
    template<class _T1, class _T2>                                            \
    derived(_T1 const &t1, _T2 const &t2) : base(t1, t2) {}                   \
    template<class _T1, class _T2, class _T3>                                 \
    derived(_T1 const &t1, _T2 const &t2, _T3 const &t3) : base(t1, t2, t3) {}

#define SBL_VAR(a) _SBL_VAR(a, __LINE__)
#define _SBL_VAR(a, b) __SBL_VAR(a, b)
#define __SBL_VAR(s, B) _sBl ## s ## B ## l

#define VAR SBL_VAR

#define ASSIGN(LHS, RHS)                                                   \
    if (bool VAR(stop) = false) {} else                                    \
        for (AUTO(LHS, (RHS)); VAR(stop) == false; VAR(stop) = true)

#endif 
