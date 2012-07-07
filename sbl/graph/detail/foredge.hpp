#ifndef _sbl_graph_foredge
#define _sbl_graph_foredge

#include"../../utility/macro.hpp"

/* -----------------------------------------------------------------------*/
/**
 * @brief travel a graph from a given head.
 *
 * @param GRAPH Input, the graph we want to travel.
 * @param HEAD Input, the head node of edge.
 * @param TAIL Output, the tail node of edge.
 * @param INDEX Output, the index of the edge we are visiting.
 */
/* -------------------------------------------------------------------------*/
#define foredge(GRAPH, HEAD, TAIL, INDEX)                                   \
    FOREACH_BEGIN()                                                         \
        for(AUTO(VAR(EDGE), (GRAPH).begin_edge(HEAD));                      \
            VAR(EDGE) != (GRAPH).end_edge(HEAD) and not BREAKED();          \
            VAR(EDGE) = (GRAPH).next(VAR(EDGE)))                            \
                ASSIGN_AUTO(TAIL, (GRAPH).tail(VAR(EDGE)))                  \
                ASSIGN_AUTO(INDEX, (GRAPH).index(VAR(EDGE)))                \
    FOREACH_END()

#endif
