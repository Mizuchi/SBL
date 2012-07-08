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
    // http://en.wikipedia.org/wiki/Tarjan%27s_strongly_connected_components_algorithm
    using namespace std;
    struct DFS {
        const Graph &graph;
        size_t nodeCount, color, depth;
        vector<size_t> tag, colours;
        vector<size_t> dfn; ///< dfn[v] = Depth of node v in DFS tree
        vector<size_t> low; ///< low[v] = Highest place node v could visited.
        stack<size_t> st;
        DFS(const Graph &_)
            : graph(_), nodeCount(_.number_of_nodes()), color(0), depth(0),
              tag(nodeCount, 0), colours(nodeCount), dfn(nodeCount), low(nodeCount) {
            for (size_t i = 0; i < nodeCount; i++)
                if (tag[i] == 0) dfs(i);
        }

        void dfs(size_t x) {

            // Set the depth index for x
            dfn[x] = low[x] = ++depth;
            st.push(x);
            tag[x] = 1;
            // Consider successors of x
            foredge(graph, x, tail, edge) {
                if (tag[tail] == 0) {
                    // Successor w has not yet been visited; recurse on it
                    dfs(tail);
                    low[x] = min(low[x], low[tail]);
                } else {
                    if (tag[tail] == 1)
                        // Successor tail is in stack st and hence in the current SCC
                        low[x] = min(low[x], dfn[tail]);
                }
                // avoid warnning: unused variant "edge"
                static_cast<void>(edge);
            }

            // If x is a root node, pop the stack and generate an SCC
            if (low[x] == dfn[x]) {
                while (st.top() != x) {
                    colours[st.top()] = color;
                    tag[st.top()] = 2;
                    st.pop();
                }
                colours[st.top()] = color++;
                tag[st.top()] = 2;
                st.pop();
            }
        }
    } f(graph);
    return f.colours;
}
} // namespace sbl
#endif
