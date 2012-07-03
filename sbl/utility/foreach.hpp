#ifndef _sbl_foreach
#define _sbl_foreach
#include"macro.hpp"

#define FOREACH_ITERATOR(CONTAINER)                                        \
    if (bool VAR(go) = false) {} else                                      \
        for (AUTO(VAR(i), (CONTAINER).begin());                            \
                VAR(go) == false and VAR(i) != (CONTAINER).end(); ++VAR(i))

#define FOREACH_ITERATOR_REVERSE(CONTAINER)                                \
    if (bool VAR(go) = false) {} else                                      \
        for (AUTO(VAR(i), (CONTAINER).end());                              \
                VAR(go) == false and VAR(i)-- != (CONTAINER).begin();)

#define FOREACH_VALUE(VALUE)                                               \
    if (not(VAR(go) = true)) {} else                                       \
        for (VALUE = *VAR(i); VAR(go) == true; VAR(go) = false)    

#define FOREACH_VALUE_AUTO(VALUE)                                          \
    if (not(VAR(go) = true)) {} else                                       \
        for (AUTO(VALUE, *VAR(i)); VAR(go) == true; VAR(go) = false) 

#define foreach(VALUE, CONTAINER)                                          \
    FOREACH_ITERATOR(CONTAINER)                                            \
    FOREACH_VALUE_AUTO(VALUE)

#define rforeach(VALUE, CONTAINER)                                         \
    FOREACH_ITERATOR_REVERSE(CONTAINER)                                    \
    FOREACH_VALUE_AUTO(VALUE)

#define foreach_def(VALUE, CONTAINER)                                      \
    FOREACH_ITERATOR(CONTAINER)                                            \
    FOREACH_VALUE(VALUE)

#define rforeach_def(VALUE, CONTAINER)                                     \
    FOREACH_ITERATOR_REVERSE(CONTAINER)                                    \
    FOREACH_VALUE(VALUE)

#endif
