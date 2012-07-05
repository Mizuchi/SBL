#ifndef _sbl_leftist_tree_intrusive
#define _sbl_leftist_tree_intrusive
#include<algorithm>
namespace sbl {
namespace intrusive {

/** \brief This is a intrusive data structure version of leftist tree.
 *
 * User must provide the node type, manage the memory, and guarantee:
 *
 * Member variant NodePtr leftChild record left child
 *
 * Member variant NodePtr rightChild record right child
 *
 * Member variant size_t npl record the null path length
 *
 * Member function compare two NodePtr
 */
template <class NodePtr>
class LeftistTree {
    private:

        std::size_t get_length(NodePtr a) {
            if (a == NULL) return 0;
            return a->npl;
        }

        NodePtr bind(NodePtr a, NodePtr b) {
            if (a == NULL) return b;
            if (b == NULL) return a;
            if (a->compare(b)) std::swap(a, b);
            a->rightChild = bind(a->rightChild, b);
            if (get_length(a->leftChild) < get_length(a->rightChild))
                std::swap(a->leftChild, a->rightChild);
            a->npl = get_length(a->rightChild) + 1;
            return a;
        }
        NodePtr root;
    public:
        LeftistTree(): root(0) {}

        void push(NodePtr a) {
            a->leftChild = a->rightChild = NULL;
            a->npl = 0;
            root = bind(root, a);
        }

        NodePtr pop() {
            NodePtr p = root;
            root = bind(root->leftChild, root->rightChild);
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
} // namespace intrusive
} // namespace sbl
#endif
