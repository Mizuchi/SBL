#ifndef _sbl_leftist_tree
#define _sbl_leftist_tree
#include<algorithm>
namespace sbl {

/** \brief This is a intrusive data structure version of leftist tree.
 *
 * User must provide the node type, manage the memory, and guarantee:
 *
 * Member variant LeftistTreeNode<NodePtr> node record the information.
 *
 * Member function bool less_than(NodePtr other) to use for all comparisons
 * of keys
 */

template<class NodePtr> class LeftistTree;

template<class NodePtr>
class LeftistTreeNode {
        friend class LeftistTree<NodePtr>;
        NodePtr leftChild, rightChild;
        size_t nullPathLength;
};

template <class NodePtr>
class LeftistTree {
    private:
        LeftistTreeNode<NodePtr> &get_node(NodePtr s) {
            return s->node;
        }
        NodePtr &l(NodePtr a) {
            return get_node(a).leftChild;
        }
        NodePtr &r(NodePtr a) {
            return get_node(a).rightChild;
        }
        size_t &npl(NodePtr a) {
            static size_t zero = 0;
            if (a == NULL)
                return zero;
            else
                return get_node(a).nullPathLength;
        }

        NodePtr bind(NodePtr a, NodePtr b) {
            if (a == NULL) return b;
            if (b == NULL) return a;
            if (a->compare(b)) std::swap(a, b);

            r(a) = bind(r(a), b);

            if (npl(l(a)) < npl(r(a)))
                std::swap(l(a), r(a));
            npl(a) = npl(r(a)) + 1;
            return a;
        }
        NodePtr root;
    public:
        LeftistTree(): root(0) {}

        void push(NodePtr a) {
            l(a) = r(a) = NULL;
            npl(a) = 0;
            root = bind(root, a);
        }

        NodePtr pop() {
            NodePtr p = root;
            root = bind(l(root), r(root));
            return p;
        }

        void merge(LeftistTree &a) {
            root = bind(root, a.root);
            a.root = NULL;
        }

        const NodePtr &top() const {
            return root;
        }

        void clear() {
            root = NULL;
        }
};

} // namespace sbl
#endif
