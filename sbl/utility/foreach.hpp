#ifndef _sbl_foreach
#define _sbl_foreach
#include"macro.hpp"

#define FOREACH_ITERATOR(CONTAINER)                                        \
    FOREACH_BEGIN()                                                        \
        for (AUTO(VAR(i), (CONTAINER).begin());                            \
                VAR(i) != (CONTAINER).end() and not BREAKED(); ++VAR(i))

#define FOREACH_ITERATOR_REVERSE(CONTAINER)                                \
    FOREACH_BEGIN()                                                        \
        for (AUTO(VAR(i), (CONTAINER).end());                              \
                VAR(i)-- != (CONTAINER).begin() and not BREAKED();)

#define FOREACH_VALUE(VALUE)                                               \
    ASSIGN(VALUE, *VAR(i))                                                 \
        FOREACH_END()                                                  

#define FOREACH_VALUE_AUTO(VALUE)                                          \
    ASSIGN_AUTO(VALUE, *VAR(i))                                            \
        FOREACH_END()                                                  

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
