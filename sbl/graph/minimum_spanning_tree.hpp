#ifndef _sbl_minimum_spanning_tree
#define _sbl_minimum_spanning_tree
#include"detail/greedy.hpp"
#include"../utility/functional.hpp"

namespace sbl {

template<class Graph, class GetCost>
detail::GreedyExpand<GetCost> minimum_spanning_tree(
    const Graph &graph,
    const GetCost &getCost,
    const bool recordFather = false,
    const size_t start = 0,
    const size_t endpoint = -1) {
    return detail::GreedyExpand<GetCost>(
               graph, getCost, start, endpoint,
               recordFather, Second());
}

} // namespace sbl
#endif 
