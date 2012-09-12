#ifndef _sbl_macro
#define _sbl_macro
#include"../base.hpp"

#define VAR(a) _SBL_VAR(a, __LINE__)
#define _SBL_VAR(a, b) __SBL_VAR(a, b)
#define __SBL_VAR(s, B) _sBl ## s ## B ## l

#define SBL_CONSTRUCTOR_TO_BASE(base, derived)                             \
    derived() {}                                                           \
    template<class VAR(1)>                                                 \
    derived(VAR(1) const &t1) : base(t1) {}                                \
    template<class VAR(1), class VAR(2)>                                   \
    derived(VAR(1) const &t1, VAR(2) const &t2) : base(t1, t2) {}          \
    template<class VAR(1), class VAR(2), class VAR(3)>                     \
    derived(VAR(1) const &t1, VAR(2) const &t2, VAR(3) const &t3)          \
        :base(t1, t2, t3) {}

#define ASSIGN(LHS, RHS)                                                   \
    if (bool VAR(stop) = false) {} else                                    \
        for (LHS = RHS; VAR(stop) == false; VAR(stop) = true)

#define ASSIGN_AUTO(LHS, RHS) ASSIGN(TYPEOF(RHS) LHS, RHS)

#define BREAKED() VAR(breaked)
#define FOREACH_BEGIN() if (bool BREAKED() = false) {} else
#define FOREACH_END()   for (BREAKED() = true; BREAKED(); BREAKED() = false)

#define MAKE1(CLASS, ARG) (CLASS<TYPEOF((ARG))>(ARG))

#define MAKE2(C, A1, A2) \
    (C<TYPEOF((A1)), TYPEOF((A2))>((A1), (A2)))

#define MAKE3(C, A1, A2, A3) \
    (C<TYPEOF((A1)), TYPEOF((A2)), TYPEOF((A3))>((A1), (A2), (A3)))

#define MAKE4(C, A1, A2, A3, A4) \
    (C<TYPEOF((A1)), TYPEOF((A2)), TYPEOF((A3)), TYPEOF((A4))> \
        ((A1), (A2), (A3), (A4)))

#define MAKE5(C, A1, A2, A3, A4, A5) \
    (C<TYPEOF((A1)), TYPEOF((A2)), TYPEOF((A3)), TYPEOF((A4)), TYPEOF((A5))> \
        ((A1), (A2), (A3), (A4), (A5))

#endif
