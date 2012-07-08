#ifndef _sbl_carrier_intrusive
#define _sbl_carrier_intrusive
#include<algorithm>

namespace sbl {
namespace intrusive {

template<class NodePtr>
class Carrier {
    // base on splay tree
    // just a prototype
    // still not stable
    // partial useable
    private:
        NodePtr &f(NodePtr a) { return a->father; }
        NodePtr &l(NodePtr a) { return a->child[0]; }
        NodePtr &r(NodePtr a) { return a->child[1]; }
        void update(NodePtr a) {
            if (a != nullNode) {
                a->size = l(a)->size + r(a)->size + 1;
                a->update();
            }
        }

        void init_node(NodePtr a) {
            f(a) = l(a) = r(a) = nullNode;
            update(a);
        }
    public:

        Carrier(NodePtr z, NodePtr x, NodePtr y) {
            nullNode = z;
            init_node(x);
            init_node(y);
            init_node(z);
            root = x;
            r(x) = y;
            f(y) = x;
            update(x);
        }

        NodePtr at(long n, NodePtr a = 0) {
            if (a == 0) a = root, ++n;
            a->expand();
            long ls = l(a)->size;
            return ls == n ? splay(a) :
                   ls > n  ? at(n, l(a)) :
                   at(n - ls - 1, r(a));
        }

        void insert(long k, NodePtr t) {
            init_node(t);
            replace(k, k, t);
        }

        void insert(long k, NodePtr beg, NodePtr end) {
            if (beg == end)return;
            NodePtr t = beg, q = t;
            init_node(t);
            for (NodePtr x = beg; ++x != end;) {
                init_node(x);
                r(q) = x;
                f(r(q)) = q;
                q = r(q);
            }
            replace(k, k, t);
            splay(q);
        }
        NodePtr erase(long x, long y) {
            return replace(x, y, nullNode);
        }
        long size() {
            return root->size - 2;
        }

        NodePtr replace(long x, long y, NodePtr z) {
            segment(x, y);
            f(z) = r(root);
            std::swap(z, l(r(root)));
            update(r(root));
            update(root);
            return z;
        }
        template<class Callable>
        void segment_call(long x, long y, Callable f) {
            f(segment(x, y));
            update(r(root));
            update(root);
        }
    private:
        void rotate(NodePtr x);
        NodePtr segment(long x, long y);
        NodePtr splay(NodePtr t);
        NodePtr nullNode;
        NodePtr root;
};


template<class NodePtr>  void Carrier<NodePtr>::rotate(NodePtr x) {
    NodePtr y = x->father;
    if (f(y) != nullNode) {
        if (l(f(y)) == y) l(f(y)) = x;
        else r(f(y)) = x;
    }
    f(x) = f(y);
    long c = (l(y) == x) ? 0 : 1;
    y->child[c] = x->child[1 - c];
    x->child[1 - c] = f(y->child[c]) = y;
    f(y) = x;
    update(y);
    update(x);
}
template<class NodePtr>  NodePtr Carrier<NodePtr>::splay(NodePtr t) {
    while (f(t) != nullNode) {
        NodePtr y = f(t);
        if (f(y) == nullNode) rotate(t);
        else if ((r(f(y)) == y && r(y) == t) ||
                 (l(f(y)) == y && l(y) == t)) {
            rotate(y);
            rotate(t);
        } else {
            rotate(t);
            rotate(t);
        }
    }
    return root = t;
}
template<class NodePtr> NodePtr 
Carrier<NodePtr>::segment(long beg, long end) {
    at(beg - 1);
    root->expand();
    NodePtr t = root, k = r(t);
    f(k) = nullNode;
    at(end);
    k = root;
    root = t;
    r(root) = k;
    f(k) = root;
    update(root);
    root->expand();
    r(root)->expand();
    return l(r(root));
}

} // namespace intrusive
} // namespace sbl

#endif
