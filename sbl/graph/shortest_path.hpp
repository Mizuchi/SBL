#ifndef _sbl_shortest_path
#define _sbl_shortest_path
#include"detail/greedy.hpp"
#include"../utility/functional.hpp"

namespace sbl {
template<class Graph, class GetCost>
detail::GreedyExpand<GetCost> shortest_path(
    const Graph &graph,
    const GetCost &getCost,
    const bool recordFather = false,
    const size_t start = 0,
    const size_t endpoint = -1) {
    return detail::GreedyExpand<GetCost>(
               graph, getCost, start, endpoint,
               recordFather, Plus());
}
} // namespace sbl
#endif 
