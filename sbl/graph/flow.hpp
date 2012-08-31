#ifndef _sbl_flow
#define _sbl_flow
#include<map>
#include"adjacency_list.hpp"
#include"shortest_path.hpp"
#include"../utility/type_traits.hpp"
#include"../utility/foreach.hpp"
#include"../base.hpp"

namespace sbl {

template<class GetCapacity, class GetFlow, class SetFlow>
class MaxFlow {
    private:
        GetCapacity old_get_capacity;
        GetFlow     old_get_flow;
        SetFlow     old_set_flow;

        // a new graph represent the residual network
        // we will split every directed edge to
        // two new edge with opposite direction.
        AdjacencyList graph;

        // mapping residual network's edge to origin edge
        std::map<size_t, size_t> newToOldIndex;

    public:
        template<class Graph>
        MaxFlow(
            Graph input_graph,
            GetCapacity input_get_capacity,
            GetFlow input_get_flow,
            SetFlow input_set_flow
        ):
            old_get_capacity(input_get_capacity),
            old_get_flow(input_get_flow),
            old_set_flow(input_set_flow) {

            // build residual network
            size_t nodeCount = input_graph.number_of_nodes();
            for (size_t head = 0; head < nodeCount; head++) {
                foredge(input_graph, head, tail, oldEdge) {
                    // split oldEdge to two edges with opposite direction
                    // (edge) and (edge^1), should be paired.
                    
                    // we call this "positive direction edge", PDE
                    newToOldIndex[graph.add_edge(head, tail)] = oldEdge;

                    // we call this "negaitive direction edge", NDE
                    newToOldIndex[graph.add_edge(tail, head)] = oldEdge;
                }
            }

            //PDE and NDE should have same capacity. flow in PDE plus NDE
            //should always equal to the capacity.
            //
            //for example, in the origin graph (old graph), we have 0 --> 1
            //with 9 capacity, then if flow in 0 --> 1 is 0, for convenience we
            //let flow in 1 --> 0 be 9. if flow in 0 --> 1 is 2 then flow in
            //0 --> 1 is 9-2=7. Now any path without zero residual capacity in
            //residual network, we could find a augmenting path in origin flow
            //network to match it. Then it is possible to reuse shortest_path.
        
            }
    private:

        typedef typename result_of<GetCapacity(size_t)>::type ResultOfGetCapacity;
        typedef typename result_of<GetFlow(size_t)>::type ResultOfGetFlow;

        ResultOfGetCapacity get_capacity(size_t edge) const {
            assert(newToOldIndex.count(edge));
            size_t oldEdge = newToOldIndex.find(edge)->second;
            return old_get_capacity(oldEdge);
        }

        ResultOfGetFlow get_flow(size_t edge) const {
            assert(newToOldIndex.count(edge));
            size_t oldEdge = newToOldIndex.find(edge)->second;
            if (edge % 2 == 0)
                // for positive direction edge
                return old_get_flow(oldEdge);
            else
                // for negative direction edge
                return old_get_capacity(oldEdge) - old_get_flow(oldEdge);
        }

        ResultOfGetFlow residual_capacity(size_t edge) const {
            return get_capacity(edge) - get_flow(edge);
        }

        void set_flow(size_t edge, ResultOfGetFlow newFlow) {
            assert(newToOldIndex.count(edge));
            size_t oldEdge = newToOldIndex[edge];
            if (edge % 2 == 0)
                // for positive direction edge
                old_set_flow(oldEdge, newFlow);
            else
                // for negative direction edge
                old_set_flow(oldEdge, old_get_capacity(oldEdge) - newFlow);
            assert(get_flow(edge) == newFlow);
        }

        template<class Self>
        struct GetCost {
            const Self &self;
            size_t operator()(size_t edge) const {
                assert(self.get_capacity(edge) >= self.get_flow(edge));
                if (self.residual_capacity(edge) > 0)
                    // if edge has non zero residual capacity
                    return 1;
                else
                    //otherwise, this edge does not exist.
                    //we must give a big enough cost.
                    return sentinel;
            }
            const size_t sentinel;
            GetCost(const Self &_, size_t infinity)
                : self(_), sentinel(infinity) {}
        }; // struct GetCost

        ResultOfGetFlow expandFlow;

        /// @brief change the flow by a augmenting path
        template<class Father>
        void change_flows(
            size_t source,
            size_t target,
            const Father &father
        ) {
            // backtrack to the source
            if (source == target)
                return;
            size_t last = father[target];
            AUTO(edges, graph.find_edges(last, target));
            ResultOfGetFlow all = 0;
            foreach(edge, edges) {
                all += residual_capacity(edge);
            }
            expandFlow = std::min(expandFlow, all);

            change_flows(source, last, father);

            // change the flow
            AUTO(k, expandFlow);
            foreach(edge, edges) {
                AUTO(p, std::min(k, residual_capacity(edge)));
                set_flow(edge, p + get_flow(edge));
                assert(k >= p);
                k -= p;
            }
            assert(k == 0);
        }

    public:

        ResultOfGetFlow run(size_t source, size_t target) {
            // Edmonds-Karp algorithm
            size_t infinity = graph.number_of_nodes();
            ResultOfGetFlow result;
            do {
                GetCost<MaxFlow> getCost(*this, infinity);

                // XXX: shortest path algorithm is not necessary, bfs is enough.
                AUTO(ans, shortest_path(graph, getCost, true, source, target));

                expandFlow = std::numeric_limits<ResultOfGetFlow>::max();
                change_flows(source, target, ans.father);

                result += expandFlow;
            } while (expandFlow > 0);
            return result;
        }

}; // struct MaxFlow


/// @brief calculate the max flow of current flow network
///
/// Actually, this is just a wrapper for MaxFlow.
template<class Graph, class GetCapacity, class GetFlow, class SetFlow>
void max_flow(
    Graph input_graph,              ///< any sbl's graph
    GetCapacity input_get_capacity, ///< a functor to get the capacity
    GetFlow input_get_flow,         ///< a functor to get the current flow
    SetFlow input_set_flow,         ///< a functor to change the flow
    typename Graph::Node source,    ///< node represent source
    typename Graph::Node target     ///< node represent sink/target
) {
    MaxFlow<GetCapacity, GetFlow, SetFlow>
    main(input_graph, input_get_capacity, input_get_flow, input_set_flow);
    main.run(source, target);
}

} // namespace sbl

#endif
