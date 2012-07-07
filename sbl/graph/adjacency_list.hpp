#ifndef _sbl_adjacency_list
#define _sbl_adjacency_list
#include<cstddef>
#include<climits>
#include"detail/common.hpp"
#include"../utility/type_traits.hpp"

namespace sbl {
class AdjacencyList:
    public GraphCommon<AdjacencyList, EmptyBase> {
    public:
        typedef size_t Edge;
        typedef size_t Node;

    private:

        static const size_t sentinel = INT_MAX;

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

        void remove(Edge edge) {
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

        std::size_t number_of_edges() const {
            return link.size();
        }

        Edge begin_edge(Node head) const {
            expand(head);
            return info[head];
        }

        Edge end_edge(Node node) const {
            return sentinel;
        }

        Edge next(Edge edge) const {
            return link[edge].next;
        }

        Node tail(Edge edge) const {
            return link[edge].tail;
        }
};

} // namespace sbl
#endif
