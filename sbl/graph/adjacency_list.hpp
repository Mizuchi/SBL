#ifndef _sbl_adjacency_list
#define _sbl_adjacency_list
#include<vector>
#include<cstddef>
#include<climits>
#include<limits>
#include"foredge.hpp"

namespace sbl {

using std::size_t;

/// read GraphBase for the interface.
class AdjacencyList {
    public:
        typedef size_t Edge;
        typedef size_t Node;

    private:
        static const size_t sentinel = -1;

        struct LinkNode {
            size_t next;
            size_t tail;
            LinkNode(size_t _next, size_t _tail)
                : next(_next), tail(_tail) {}
        };

        std::vector<LinkNode> link;
        mutable std::vector<size_t> info;

        void expand(size_t node) const {
            if (info.size() <= node)
                info.resize(node + 1, sentinel);
        }

    public:
        Edge add_edge(Node head, Node tail) {
            expand(head);
            link.push_back(LinkNode(info[head], tail));
            info[head] = link.size() - 1;
            return info[head];
        }

        void remove_edge(Edge edge) {
            size_t headNode = head(edge);
            size_t nextEdge = link[edge].next;
            if (prev(edge) == end_edge(headNode)) {
                info[headNode] = nextEdge;
            } else {
                link[prev(edge)].next = nextEdge;
            }
        }

        void clear() {
            link.clear();
            info.clear();
        }

        std::size_t number_of_nodes() const {
            return info.size();
        }

        Edge begin_edge(Node head) const {
            expand(head);
            return info[head];
        }

        Edge end_edge(Node /*node*/) const {
            return sentinel;
        }

        Edge next(Edge edge) const {
            return link[edge].next;
        }

        Node tail(Edge edge) const {
            return link[edge].tail;
        }

        // O(|E|)
        std::size_t number_of_edges() const {
            std::size_t result = 0;
            for (std::size_t node = 0; node < number_of_nodes(); node++) {
                foredge(*this, node, tail, edge) {
                    result++;
                    static_cast<void>(tail);
                    static_cast<void>(edge);
                }
            }
            return result;
        }

        // O(|E|)
        std::size_t prev(Edge edge) const {
            std::size_t head = this->head(edge);
            if (begin_edge(head) == edge)
                return end_edge(head);
            for (Edge iter = begin_edge(head);
                 iter != end_edge(head);
                 iter = next(iter)) {
                if (next(iter) == edge)
                    return iter;
            }
            assert(false and "GraphCommon::prev: edge is not in this graph");
            return 0;
        }

        // O(|E|)
        std::size_t head(Edge edge) const {
            for (std::size_t node = 0;
                 node < number_of_nodes(); node++) {
                foredge(*this, node, tail, index) {
                    if (index == edge)
                        return node;
                    static_cast<void>(tail);
                }
            }
            assert(false and "GraphCommon::head: edge is not in this graph");
            return 0;
        }

        // O(|E|)
        std::vector<Edge>
        find_edges(Node head, Node iTail, std::size_t limit = -1) const {
            std::vector<Edge> result;
            foredge(*this, head, tail, index) {
                if (result.size() == limit)
                    break;
                if (tail == iTail)
                    result.push_back(index);
            }
            return result;
        }

};

} // namespace sbl
#endif
