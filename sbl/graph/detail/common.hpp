#ifndef _sbl_graph_common
#define _sbl_graph_common
#include<cassert>
#include<vector>
#include<cstddef>
#include"foredge.hpp"
#include"../../utility/type_traits.hpp"

namespace sbl {

template<class Derived, class Base>
class GraphCommon: public Base {
        const Derived &self() const {
            return static_cast<const Derived &>(*this);
        }
        Derived &self() {
            return static_cast<Derived &>(*this);
        }
    public:
        typedef std::size_t Node;
        typedef std::size_t Edge;

        // O(|E|)
        std::size_t number_of_edges() const {
            std::size_t result = 0;
            for (std::size_t node = 0;
                 node < self().number_of_nodes(); node++) {
                foredge(self(), node, tail, edge) {
                    result++;
                    static_cast<void>(tail);
                    static_cast<void>(edge);
                }
            }
            return result;
        }

        // O(|E|)
        std::size_t prev(Edge edge) const {
            std::size_t head = self().head(edge);
            if (self().begin_edge(head) == edge)
                return self().end_edge(head);
            for (Edge iter = self().begin_edge(head);
                 iter != self().end_edge(head);
                 iter = self().next(iter)) {
                if (self().next(iter) == edge)
                    return iter;
            }
            assert(false and "GraphCommon::prev: edge is not in this graph");
        }

        // O(|E|)
        std::size_t head(Edge edge) const {
            for (std::size_t node = 0;
                 node < self().number_of_nodes(); node++) {
                foredge(self(), node, tail, index) {
                    if (index == edge)
                        return node;
                    static_cast<void>(tail);
                }
            }
            assert(false and "GraphCommon::head: edge is not in this graph");
        }

        // O(|E|)
        std::vector<Edge>
        find_edges(Node head, Node tail, std::size_t limit) const {
            std::vector<Edge> result;
            for (Edge edge = self().begin_edge(head);
                 edge != self().end_edge(head);
                 edge = self().next(head)) {
                if (result.size() == limit)
                    break;
                if (self().tail(edge) == tail)
                    result.push_back(edge);
            }
            return result;
        }

    protected:
        ~GraphCommon() {}

}; // class GraphBase

} // namespace sbl
#endif
