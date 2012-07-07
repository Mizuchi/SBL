#ifndef _sbl_greedy_graph
#define _sbl_greedy_graph
#include<vector>
#include<queue>
#include<utility>
#include"foredge.hpp"
#include"../../utility/type_traits.hpp"


namespace sbl {
namespace detail {
using std::vector;

template<class GetCost>
struct GreedyExpand {
    private:
        typedef typename result_of<GetCost(size_t)>::type Value;
        size_t n;
    public:
        vector<Value> value;
        vector<bool> vaild;
        vector<size_t> father;
        vector<size_t> index;

        struct PriorityValue {
            Value value;
            size_t node;
            friend bool operator<(PriorityValue lhs, PriorityValue rhs) {
                return lhs.value > rhs.value;
            }
            PriorityValue(const Value &_value, const size_t _node)
                : value(_value), node(_node) {}
        };

        template<class Graph, class Evaluate>
        GreedyExpand(
            const Graph &graph,
            const GetCost &getCost,
            const size_t start,
            const size_t endpoint,
            const bool recordFather,
            const Evaluate &eval)
            : n(graph.number_of_nodes()),
              value(n),
              vaild(n),
              father(recordFather ? n : 0),
              index(recordFather ? n : 0) {

            std::priority_queue<PriorityValue> q;
            vector<bool> visited(n);

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
                    AUTO(now, eval(value[head], getCost(edge)));
                    if (not vaild[tail] or now < value[tail]) {
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
        }
};
} // namespace detail
} // namespace sbl
#endif
