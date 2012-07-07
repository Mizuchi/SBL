#ifndef _sbl_strongly_connected_components
#define _sbl_strongly_connected_components
#include"detail/foredge.hpp"
#include<stack>

namespace sbl {
/// compute the strongly connected components of a graph.
/// @param graph given a graph
/// @return result[k] represent the color of node k
template<class Graph>
std::vector<std::size_t> strongly_connected_components(const Graph &graph) {
    using namespace std;
    struct DFS {
        const Graph &graph;
        size_t n, color, d;
        vector<size_t> b, c, dfn, low;
        stack<size_t> q;
        DFS(const Graph &_)
            : graph(_), n(_.number_of_nodes()), color(0), d(0),
              b(n, 0), c(n), dfn(n), low(n) {
            for (size_t i = 0; i < n; i++)
                if (b[i] == 0) dfs(i);
        }

        void dfs(size_t x) {
            dfn[x] = low[x] = ++d;
            q.push(x);
            b[x] = 1;
            foredge(graph, x, tail, edge) {
                if (b[tail] == 0) {
                    dfs(tail);
                    low[x] = min(low[x], low[tail]);
                } else {
                    if (b[tail] == 1)
                        low[x] = min(low[x], dfn[tail]);
                }
                // avoid warnning: unused variant "edge"
                static_cast<void>(edge);
            } if (low[x] == dfn[x]) { while (q.top() != x) {
                    c[q.top()] = color;
                    b[q.top()] = 2;
                    q.pop();
                }
                c[q.top()] = color++;
                b[q.top()] = 2;
                q.pop();
            }
        }
    } f(graph);
    return f.c;
}
} // namespace sbl
#endif
