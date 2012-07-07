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
 * @param EDGE Output, the edge we are visiting.
 */
/* -------------------------------------------------------------------------*/
#define foredge(GRAPH, HEAD, TAIL, EDGE)                                    \
    FOREACH_BEGIN()                                                         \
        for(AUTO(EDGE, (GRAPH).begin_edge(HEAD));                           \
            EDGE != (GRAPH).end_edge(HEAD) and not BREAKED();               \
            EDGE = (GRAPH).next(EDGE))                                      \
                ASSIGN_AUTO(TAIL, (GRAPH).tail(EDGE))                       \
    FOREACH_END()

#endif
