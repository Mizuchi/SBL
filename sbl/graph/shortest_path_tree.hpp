#ifndef _sbl_graph_dijkstra_algorithm
#define _sbl_graph_dijkstra_algorithm
#include<vector>
#include<queue>
#include<utility>
#include<functional>
#include"weighted_graph.hpp"
#include"foredge.hpp"
#include"../utility/type_traits.hpp"

namespace sbl {

/// @brief get the shortest path of graph by bellman ford algorithm.
template <class WeightedGraph>
class ShortestPathTree: private WeightedGraph {
    private:

        using WeightedGraph::graph;
        using WeightedGraph::getWeight;
        using WeightedGraph::plus;
        using WeightedGraph::less;

        typedef typename WeightedGraph::Weight Weight;

        std::vector<Weight> value;
        std::vector<bool> vaild;
        std::vector<size_t> father;
        std::vector<size_t> edgeToFather;

        void init_result() {
            size_t n = graph.number_of_nodes();
            value.assign(n, Weight());
            vaild.assign(n, false);
            father.assign(n, 0);
            edgeToFather.assign(n, 0);
        }

        bool relax(size_t head, size_t tail, size_t edge) {
            Weight now = plus(value[head], getWeight(edge));
            if (not vaild[tail] or less(now, value[tail])) {
                vaild[tail] = true;
                value[tail] = now;
                father[tail] = head;
                edgeToFather[tail] = edge;
                return true;
            }
            return false;
        }

        void dijkstra(size_t source) {
            init_result();
            vaild[source] = true;
            size_t n = graph.number_of_nodes();
            std::vector<bool> visited(n);
            size_t head = source;
            while (head < n) {
                visited[head] = true;
                foredge(graph, head, tail, edge) {
                    if (not visited[tail])
                        relax(head, tail, edge);
                }
                head = n;
                for (size_t k = 0; k < n; k++)
                    if (not visited[k] and vaild[k])
                        if (head == n or less(value[k], value[head]))
                            head = k;
            }
        }

        bool bellman_ford_iterate() {
            bool changed = false;
            size_t n = graph.number_of_nodes();
            for (size_t head = 0; head < n; head++)
                if (vaild[head]) {
                    foredge(graph, head, tail, edge) {
                        bool modified = relax(head, tail, edge);
                        if (modified)
                            changed = true;
                    }
                }
            return changed;
        }

        void bellman_ford(size_t source) {
            init_result();
            vaild[source] = true;
            size_t n = graph.number_of_nodes();
            for (size_t repeat = 0; repeat < n; repeat++)
                bellman_ford_iterate();
            assert(not bellman_ford_iterate());
        }

    public:
        Weight get_sum_of_weights(size_t node) const {
            return value[node];
        }
        bool in_tree(size_t node) const {
            return vaild[node];
        }
        size_t get_father(size_t node) const {
            return father[node];
        }
        size_t get_edge_to_father(size_t node) const {
            return edgeToFather[node];
        }

        size_t size() const {
            return value.size();
        }

        ShortestPathTree(WeightedGraph _)
            : WeightedGraph(_) {}

        void run(
            size_t source = 0,
            size_t /*target*/ = -1,
            bool hasNegativeEdgeWeights = false
        ) {
            if (hasNegativeEdgeWeights)
                bellman_ford(source);
            else
                dijkstra(source);
        }

}; // struct ShortestPathTree

} // namespace sbl
#endif
