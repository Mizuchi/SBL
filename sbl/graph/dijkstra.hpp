#ifndef _sbl_graph_dijkstra_algorithm
#define _sbl_graph_dijkstra_algorithm
#include<vector>
#include<queue>
#include<utility>
#include<functional>
#include"foredge.hpp"
#include"../utility/type_traits.hpp"

namespace sbl {

template<class Value>
struct Dijkstra {
    private:
        struct PriorityValue {
            Value value;
            size_t node;
            friend bool operator<(PriorityValue lhs, PriorityValue rhs) {
                return lhs.value > rhs.value;
            }
            PriorityValue(const Value &_value, const size_t _node)
                : value(_value), node(_node) {}
        };
        size_t n;
    public:
        std::vector<Value> value;
        std::vector<bool> vaild;
        std::vector<size_t> father;
        std::vector<size_t> index;

        template<class Graph, class GetCost, class Plus, class Less>
        Dijkstra(
            const Graph &graph,
            const GetCost &getCost,
            const bool recordFather,
            const size_t start,
            const size_t endpoint,
            const Plus &plus,
            const Less &less
        ) : n(graph.number_of_nodes()),
            value(n),
            vaild(n),
            father(recordFather ? n : 0),
            index(recordFather ? n : 0) {

            std::priority_queue<PriorityValue> q;
            std::vector<bool> visited(n);

            value[start] = 0;
            vaild[start] = true;

            q.push(PriorityValue(0, start));
            while (not q.empty()) {
                Value tvalue = q.top().value;
                size_t head = q.top().node;
                q.pop();
                if (value[head] != tvalue) continue;
                if (head == endpoint) break;
                visited[head] = true;
                foredge(graph, head, tail, edge) {
                    if (visited[tail]) continue;
                    AUTO(now, plus(value[head], getCost(edge)));
                    if (not vaild[tail] or less(now, value[tail])) {
                        vaild[tail] = true;
                        value[tail] = now;
                        if (recordFather) {
                            father[tail] = head;
                            index[tail] = edge;
                        }
                        q.push(PriorityValue(value[tail], tail));
                    }
                }
            }
        } // Constructor
}; // struct Dijkstra


/// apply dijkstra algorithm and return a struct contain member variant:
///
/// 1. value[x]: value of shortest path from start point to x
/// 2. valid[x]: beingness of shortest path from start point to x
/// 3. father[x]: last node of shortest path from start point to x
/// 4. index[x]: last edge of shortest path from start point to x
///
template<class Graph, class GetCost, class Plus, class Less>
Dijkstra< typename result_of<GetCost(size_t)>::type >
make_dijkstra(
    // Since C++03 does not support Default Template Arguments for Function Templates.
    // We have to write the code multiples just like SGI STL did.
    // In C++11, we just need to write one time.
    const Graph &graph,       ///< input graph
    const GetCost &getCost,   ///< functor to get cost
    const bool recordFather,  ///< record father or not, false by default
    const size_t start,       ///< start node, 0 by default
    const size_t endpoint,    ///< end point, -1 by default
    const Plus &plus,         ///< plus functor, std::plus by default
    const Less &less          ///< less functor, std::less by default
) {
    typedef typename result_of<GetCost(size_t)>::type Value;
    return Dijkstra<Value>(graph, getCost, recordFather, start, endpoint, plus, less);
}

template<class Graph, class GetCost, class Plus>
Dijkstra< typename result_of<GetCost(size_t)>::type >
make_dijkstra(
    const Graph &graph,
    const GetCost &getCost,
    const bool recordFather,
    const size_t start,
    const size_t endpoint,
    const Plus &plus
) {
    typedef typename result_of<GetCost(size_t)>::type Value;
    AUTO(less, (std::less<Value>()));
    return Dijkstra<Value>(graph, getCost, recordFather, start, endpoint, plus, less);
}

template<class Graph, class GetCost>
Dijkstra< typename result_of<GetCost(size_t)>::type >
make_dijkstra(
    const Graph &graph,
    const GetCost &getCost,
    const bool recordFather = false,
    const size_t start = 0,
    const size_t endpoint = -1
) {
    typedef typename result_of<GetCost(size_t)>::type Value;
    AUTO(plus, (std::plus<Value>()));
    AUTO(less, (std::less<Value>()));
    return Dijkstra<Value>(graph, getCost, recordFather, start, endpoint, plus, less);
}

} // namespace sbl
#endif
