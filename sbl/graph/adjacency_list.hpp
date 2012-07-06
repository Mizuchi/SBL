#ifndef _sbl_graph
#define _sbl_graph
#include"detail/base.hpp"
#include"../utility/type_traits.hpp"

namespace sbl {
class AdjacencyList: public GraphBase {
    public:
        typedef size_t Node;
    protected:
        typedef GraphBase::Edge Edge;
    private:

        struct LinkNode {
            int next;
            Node tail;
            LinkNode(int _next, Node _tail): next(_next), tail(_tail) {}
        };
        std::vector<LinkNode> link;
        mutable std::vector<int> info;
        void expand(size_t i) const {
            while (info.size() <= i) {
                int x = info.size();
                info.push_back(~x);
            }
        }
        struct EdgeImpl: GraphBase::EdgeImpl {
            EdgeImpl(size_t _): index(_) {}
            size_t index;
        };
        Edge make_edge(size_t index) const {
            return GraphBase::make_edge(new EdgeImpl(index));
        }
    public:
        Edge add_edge(Node head, Node tail) {
            expand(head);
            link.push_back(LinkNode(info[head], tail));
            info[head] = link.size() - 1;
            return make_edge(info[head]);
        }
        void erase(Edge edge) {
            if (to_prev(&edge)) {
                int nextIdx = link[index(edge)].next;
                link[index(edge)].next = link[nextIdx].next;
            } else {
                int headNode = head(edge);
                info[headNode] = ~headNode;
            }
        }
        void clear() {
            link.clear();
            info.clear();
        }
        size_t number_of_nodes() const {
            return info.size();
        }
        size_t number_of_edges() const {
            return link.size();
        }
        size_t index(Edge edge) const {
            AUTO(impl, GraphBase::get_edge_impl(edge));
            assert(dynamic_cast<EdgeImpl *>(impl) != NULL);
            EdgeImpl *derived = static_cast<EdgeImpl *>(impl);
            return derived->index;
        }
        Edge start_edge(Node node) const {
            expand(node);
            return make_edge(info[node]);
        }
        bool to_next(Edge *edge) const {
            size_t idx = index(*edge);
            int next = link[idx].next;
            if (next < 0) return false;
            *edge = make_edge(next);
            return true;
        }
        size_t next_index(Edge edge) const {
            to_next(&edge);
            return index(edge);
        }
        bool to_prev(Edge *edge) const {
            int headNode = head(*edge);
            if (info[headNode] == index(*edge))
                return false;
            Edge e = start_edge(headNode);
            while (index(*edge) != next_index(e))
                to_next(&e);
            *edge = e;
            return true;
        }
        Node head(Edge edge) const {
            while (to_next(&edge));
            size_t idx = index(edge);
            return ~link[idx].next;
        }
        Node tail(Edge edge) const {
            return link[index(edge)].tail;
        }

        std::vector<Edge>
        find_edges(Node head, Node tail, std::size_t limit = SIZE_MAX) const {
            std::vector<Edge> result;
            foredge(*this, head, newTail, index) {
                if (result.size() == limit)
                    break;
                if (newTail == tail)
                    result.push_back(make_edge(index));
            }
            return result;
        }
};

} // namespace sbl
#endif
