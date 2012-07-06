#ifndef _sbl_graph_base
#define _sbl_graph_base
#include<algorithm>
#include"../../utility/macro.hpp"

namespace sbl {

/// @brief GraphBase
///
/// Design a graph class is not a easy job.
///
/// Just like CLRS point out that there is no generic way to store a attribute
/// to a edge or node. So SBL Graph will not contain any attribute for node and
/// edge. In SBL Graph, nodes and edges could be represented as a unsigned
/// integer. User could map the integer to the attribute they are interested in.
///
/// However, the edge type is not a integer. You have to use member function
/// index() to get the index of a edge. The index is the edge appended ordinal.
/// The first edge added to the graph has index 0, the second edge has index 1,
/// the third has index 2, etc. Remove any edge would not effect index.  It
/// always automatically increase after add a new edge.
///
/// User could use macro foredge to travel graph.
class GraphBase {
    private:

        struct EdgeImpl {
            virtual ~EdgeImpl() {}
        };

        /// Edge type.
        class Edge {

                // You can consider edge is a iterator, which will travel all
                // edge from the head.  User can not control edge directly.

            public:
                /// User could copy a exist Edge.
                /// But they can not create a new one.
                Edge(const Edge &other)
                    : impl(other.impl), refCount(other.refCount) {
                    ++refCount;
                }

                /// User could assign one edge to another.
                Edge &operator=(const Edge &other) {
                    Edge newEdge(other);
                    swap(newEdge);
                    return *this;
                }

                ~Edge() {
                    --refCount;
                    if (refCount == 0) {
                        delete refCount;
                        delete impl;
                    }
                }
            private:
                // It's not wise to open the API to the user.

                friend class GraphBase;

                /// pimpl
                EdgeImpl *impl;

                /// Reference counting
                size_t *refCount;

                /// Only GraphBase can construct a Edge.
                Edge(EdgeImpl *_): impl(_), refCount(new size_t(1)) {}

                /// In order to keep it simple and compatible,
                /// user must use std::swap instead of this member function.
                void swap(Edge &other) {
                    std::swap(impl, other.impl);
                    std::swap(refCount, other.refCount);
                }
        };

    protected:
        
        /// Derived use this function to get a EdgeImpl from edge
        EdgeImpl *get_edge_impl(Edge edge) {
            // Do not delete, don't break reference counting. Use it careful.
            return edge.impl;
        }

        /// Derived use this function to create a Edge
        Edge make_edge(EdgeImpl *pimpl) {
            return Edge(pimpl);
        }

    public:

        /// NodeType.
        /// For the sake of convenient, node is a unsigned integer in SBL
        /// Graph. You store any attribute about node yourself.
        typedef std::size_t Node;

        ///
        virtual ~GraphBase() {}

        /// Add a edge from head to tail
        /// @return the edge we added
        virtual Edge add_edge(Node head, Node tail) = 0;

        /// Remove a exist edge.
        /// @return whether edge in the graph.
        virtual bool erase(Edge edge) const = 0;

        /// Remove all node and edge.
        virtual void clear() = 0;

        // get information

        ///
        virtual size_t number_of_nodes() const = 0;

        ///
        virtual size_t number_of_edges() const = 0;

        /// @return index of a edge.
        virtual size_t edge_to_index(Edge edge) const = 0;

        /// @return edge which index connected.
        virtual Edge index_to_edge(size_t index) const = 0;

        ///
        virtual Edge first_edge_of_node(Node node) const = 0;

        /// Move to next edge.
        /// @return false if there is next edge.
        virtual bool move_to_next(Edge *edge) const = 0;

        /// Move to previous edge.
        /// @return whether there is previous edge.
        virtual bool move_to_prev(Edge *edge) const = 0;

        /// @return head of a edge
        virtual Node head(Edge edge) const = 0;

        /// @return tail of a edge
        virtual Node tail(Edge edge) const = 0;

        /// @return first edge connect head and tail
        virtual Edge find_first_edge(Node head, Node tail) const = 0;

        /// @return last edge connect head and tail
        virtual Edge find_last_edge(Node head, Node tail) const = 0;

}; // class GraphBase


/* -----------------------------------------------------------------------*/
/**
 * @brief travel a graph from a given head.
 *
 * @param GRAPH Input, the graph we want to travel.
 * @param HEAD Input, the head node of edge.
 * @param TAIL Output, the tail node of edge.
 * @param INDEX Output, the index of the edge we are visiting.
 */
/* -------------------------------------------------------------------------*/
#define foredge(GRAPH, HEAD, TAIL, INDEX)                                     \
    if(bool VAR(go) = false) {} else                                          \
        for(AUTO(VAR(EDGE), GRAPH.first(HEAD)), VAR(NEXT) = VAR(EDGE);        \
            GRAPH.next(VAR(NEXT)) and not VAR(go); VAR(EDGE) = VAR(NEXT))     \
            ASSIGN(INDEX, GRAPH.index(VAR(EDGE)))                         \
            if(not (VAR(go) = true)) {} else                          \
                for(AUTO(TAIL, GRAPH.tail(VAR(EDGE)));                    \
                    VAR(go) == true; VAR(go) = false)


} // namespace sbl
#endif
