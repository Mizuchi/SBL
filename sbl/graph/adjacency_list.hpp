#ifndef _sbl_adjacency_list
#define _sbl_adjacency_list
#include<cstddef>
#include<climits>
#include"detail/common.hpp"
#include"../utility/type_traits.hpp"

namespace sbl {
class AdjacencyList:
    public GraphCommon<AdjacencyList, EmptyBase, size_t> {
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

        static Edge make_edge(size_t index) {
            return index;
        }

        void expand(size_t node) const {
            if (info.size() <= node)
                info.resize(node + 1, sentinel);
        }

    public:

        Edge add_edge(Node head, Node tail) {
            expand(head);
            link.push_back(LinkNode(info[head], tail));
            info[head] = link.size() - 1;
            return make_edge(info[head]);
        }

        void remove(Edge edge) {
            size_t headNode = head(edge);
            size_t nextIndex = link[index(edge)].next;
            if (prev(edge) == end_edge(headNode)) {
                info[headNode] = nextIndex;
            } else {
                link[prev(edge)].next = nextIndex;
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

        std::size_t index(Edge edge) const {
            return edge;
        }

        Edge begin_edge(Node head) const {
            expand(head);
            return make_edge(info[head]);
        }

        Edge end_edge(Node node) const {
            return make_edge(sentinel);
        }

        Edge next(Edge edge) const {
            size_t idx = index(edge);
            size_t nextIdx = link[idx].next;
            return make_edge(nextIdx);
        }

        Node tail(Edge edge) const {
            size_t idx = index(edge);
            return link[idx].tail;
        }
};

} // namespace sbl
#endif
