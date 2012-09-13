#ifndef _sbl_flow
#define _sbl_flow
#include<map>
#include<ostream>
#include"adjacency_list.hpp"
#include"shortest_path_tree.hpp"
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
        // XXX: std::map is not necessary, it could be calcuated directly
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

        size_t get_old_edge(size_t edge) const {
            assert(newToOldIndex.count(edge));
            return newToOldIndex.find(edge)->second;
        }

        static inline bool is_positive_direction_edge(size_t edge) {
            return edge % 2 == 0;
        }

        static inline bool is_negative_direction_edge(size_t edge) {
            return not is_positive_direction_edge(edge);
        }

        typedef typename result_of<GetCapacity(size_t)>::type ResultOfGetCapacity;
        typedef typename result_of<GetFlow(size_t)>::type ResultOfGetFlow;

        ResultOfGetCapacity get_capacity(size_t edge) const {
            return old_get_capacity(get_old_edge(edge));
        }

        ResultOfGetFlow get_flow(size_t edge) const {
            size_t oldEdge = get_old_edge(edge);
            if (is_positive_direction_edge(edge))
                return old_get_flow(oldEdge);
            else
                return old_get_capacity(oldEdge) - old_get_flow(oldEdge);
        }

        ResultOfGetFlow residual_capacity(size_t edge) const {
            return get_capacity(edge) - get_flow(edge);
        }
        void set_flow(size_t edge, ResultOfGetFlow newFlow) {
            size_t oldEdge = get_old_edge(edge);

            if (is_positive_direction_edge(edge))
                old_set_flow(oldEdge, newFlow);
            else
                old_set_flow(oldEdge, old_get_capacity(oldEdge) - newFlow);
            assert(get_flow(edge) == newFlow);
        }

        template<class Weight>
        struct Cost {
            Weight weight;
            bool isPositive;
            bool isFinite;

            Cost(): weight(), isPositive(true), isFinite(true) {}

            friend Cost operator+(Cost lhs, Cost rhs) {
                if (not lhs.isFinite) return lhs;
                if (not rhs.isFinite) return rhs;

                if (lhs.weight < rhs.weight)
                    std::swap(lhs, rhs);

                if (lhs.isPositive == rhs.isPositive)
                    lhs.weight += rhs.weight;
                else {
                    if (lhs.weight == rhs.weight)
                        lhs.isPositive = true;
                    lhs.weight -= rhs.weight;
                }

                return lhs;
            }

            friend bool operator<(Cost lhs, Cost rhs) {

                if (lhs.isPositive and not rhs.isPositive)
                    return false;

                if (not lhs.isPositive and rhs.isPositive)
                    return true;

                if (not lhs.isFinite)
                    return not lhs.isPositive;

                if (not rhs.isFinite)
                    return rhs.isPositive;

                if (lhs.isPositive)
                    return lhs.weight < rhs.weight;
                else
                    return rhs.weight < lhs.weight;

            }

            friend std::ostream& operator<<(std::ostream& os, Cost cost) {
                if(not cost.isPositive)
                    os << "-";
                if(cost.isFinite)
                    os << cost.weight;
                else
                    os << "infinity";
                return os;
            }

        };

        template<class Self, class GetWeight>
        class GetCost {
            private:
                const Self &self;
                const GetWeight &getWeight;
                typedef typename result_of<GetWeight(size_t)>::type Weight;
                typedef Cost<Weight> CostType;

            public:
                CostType operator()(size_t edge) const {
                    assert(self.get_capacity(edge) >= self.get_flow(edge));
                    CostType result;
                    result.isFinite = self.residual_capacity(edge) > 0;
                    if (result.isFinite) {
                        size_t oldEdge = self.get_old_edge(edge);
                        result.weight = getWeight(oldEdge);
                        result.isPositive = is_positive_direction_edge(edge);
                    }
                    return result;
                }
                GetCost(const Self &iSelf, const GetWeight &iGetWeight)
                    : self(iSelf), getWeight(iGetWeight) {}
        }; // struct GetCost

        struct AlwaysOne {
            size_t operator()(size_t)const {
                return 1;
            }
        };

        /// @brief change the flow by a augmenting path
        template<class ShortestPathTree>
        void change_flows(
            size_t source,
            size_t target,
            const ShortestPathTree &tree,
            ResultOfGetFlow *expandFlow
        ) {
            // backtrack to the source
            if (source == target)
                return;
            size_t last = tree.get_father(target);
            AUTO(edges, graph.find_edges(last, target));
            ResultOfGetFlow all = 0;
            foreach(edge, edges) {
                all += residual_capacity(edge);
            }
            *expandFlow = std::min(*expandFlow, all);

            change_flows(source, last, tree, expandFlow);

            // change the flow
            AUTO(k, *expandFlow);
            foreach(edge, edges) {
                AUTO(p, std::min(k, residual_capacity(edge)));
                set_flow(edge, p + get_flow(edge));
                assert(k >= p);
                k -= p;
            }
            assert(k == 0);
        }

    public:

        template<class GetWeight>
        ResultOfGetFlow run(
            size_t source,
            size_t target,
            const GetWeight &getWeight
        ) {
            // Edmonds-Karp algorithm
            AUTO(get_cost, MAKE2(GetCost, *this, getWeight));
            AUTO(weightedGraph, MAKE2(
                     WeightedGraphWrapper,
                     graph,
                     get_cost
                 ));
            AUTO(tree, MAKE1(ShortestPathTree, weightedGraph));

            ResultOfGetFlow result, expandFlow;
            do {
                expandFlow = std::numeric_limits<ResultOfGetFlow>::max();
                tree.run(source, target, true);
                change_flows(source, target, tree, &expandFlow);
                result += expandFlow;
            } while (expandFlow > 0);
            return result;
        }

        ResultOfGetFlow run(
            size_t source,
            size_t target
        ) {
            return run(source, target, AlwaysOne());
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

template<class Graph, class GetCapacity, class GetFlow, class SetFlow, class GetCost>
void minimum_cost_flow(
    Graph input_graph,              ///< any sbl's graph
    GetCapacity input_get_capacity, ///< a functor to get the capacity
    GetFlow input_get_flow,         ///< a functor to get the current flow
    SetFlow input_set_flow,         ///< a functor to change the flow
    GetCost input_get_cost,         ///< a functor to get the cost
    typename Graph::Node source,    ///< node represent source
    typename Graph::Node target     ///< node represent sink/target
) {
    MaxFlow<GetCapacity, GetFlow, SetFlow>
    main(input_graph, input_get_capacity, input_get_flow, input_set_flow);
    main.run(source, target, input_get_cost);
}

} // namespace sbl

#endif
