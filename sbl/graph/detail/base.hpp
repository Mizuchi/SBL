#ifndef _sbl_graph_base
#define _sbl_graph_base
#include<algorithm>
#include<limits>
#include<cstddef>
#include<vector>
#define SIZE_MAX (std::numeric_limits<std::size_t>::max())



namespace sbl {

/** @brief GraphBase (Deprecated)
 *
 * Design a graph class is not a easy job. 
 *
 * Just like CLRS point out that "There is no one best way to store and access
 * vertex and edge attributes." (page 592, 3rd edition). So SBL Graph will not
 * contain any attribute for node and edge. In SBL Graph, nodes and edges could
 * be represented as a unsigned integer. User could map the integer to the
 * attribute they are interested in.
 *
 * We mapped a edge to its appended ordinal. The first edge added to the graph
 * is numbered 0, the second edge is numbered 1, the third is numbered 2, etc.
 * Remove any edge would not effect index.  It always automatically increase
 * after add a new edge.
 *
 * User could use macro foredge to travel graph.
 *
 * Deprecated. (was less tested, no users, no maintainer)
 */
class GraphBase {
    public:

        /// NodeType.
        /// For the sake of convenient, node is a unsigned integer in SBL
        /// Graph. You store any attribute about node yourself.
        typedef std::size_t Node;

        /// EdgeType.
        /// For the sake of convenient, edge is a unsigned integer in SBL
        /// Graph. Represented as it added order.
        typedef std::size_t Edge;

        /// 
        virtual ~GraphBase() {}

        /// Add a edge from head to tail
        /// @return the edge just we added
        virtual Edge add_edge(Node head, Node tail) = 0;

        /// Remove a exist edge.
        /// @return whether edge in the graph.
        virtual bool remove_edge(Edge edge) = 0;

        /// Remove all node and edge.
        virtual void clear() = 0;

        /// @return number of nodes in graph.
        virtual std::size_t number_of_nodes() const = 0;

        /// @return number of edges in graph.
        virtual std::size_t number_of_edges() const = 0;

        /// @return first edge of the graph's node.
        virtual Edge begin_edge(Node node) const = 0;

        /// @return edge that following the last edge of the graph's node.
        virtual Edge end_edge(Node node) const = 0;

        /// Move to next edge.
        /// @return false if there is next edge.
        virtual Edge next(Edge edge) const = 0;

        /// Move to previous edge.
        /// @return whether there is previous edge.
        virtual Edge prev(Edge edge) const = 0;

        /// @return head of a edge
        virtual Node head(Edge edge) const = 0;

        /// @return tail of a edge
        virtual Node tail(Edge edge) const = 0;

        /// @brief Find edges connect head and tail,
        ///
        /// @param head source of a edge
        /// @param tail target of a edge
        /// @param limit return at most limit edges
        ///
        /// @return All edges we find.
        virtual std::vector<Edge>
        find_edges(
            Node head,
            Node tail,
            std::size_t limit = SIZE_MAX
        ) const = 0;

}; // class GraphBase

} // namespace sbl
#endif
