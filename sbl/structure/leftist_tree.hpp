#ifndef _sbl_leftist_tree
#define _sbl_leftist_tree
#include<cassert>
#include<cstddef>
namespace sbl {

/** \brief This is a intrusive data structure version of leftist tree.
 *
 * User must provide the node type that contain LeftistTreeNode as a member
 * variant. Provide two functor, one for compare two LeftistTreeNode, return if
 * the lhs < rhs, another for get the LeftistTreeNode for your node type.
 *
 */

template <class NodePtr, class GetNode, class Compare>
class LeftistTree;

template<class NodePtr>
class LeftistTreeNode {
    private:
        template<class, class, class> friend class LeftistTree;
        NodePtr leftChild, rightChild;
        std::size_t nullPathLength;
    public:
        LeftistTreeNode()
            : leftChild(NULL), rightChild(NULL), nullPathLength(0) {}
};

template <class NodePtr, class GetNode, class Compare>
class LeftistTree {
    private:
        Compare compare;
        static LeftistTreeNode<NodePtr> &get_node(NodePtr s) {
            assert(s != NULL);
            GetNode getNode;
            return getNode(s);
        }
        static NodePtr get_left(NodePtr a) {
            return get_node(a).leftChild;
        }
        static void set_left(NodePtr a, NodePtr b) {
            if (a == NULL) return;
            get_node(a).leftChild = b;
        }
        static NodePtr get_right(NodePtr a) {
            return get_node(a).rightChild;
        }
        static void set_right(NodePtr a, NodePtr b) {
            if (a == NULL) return;
            get_node(a).rightChild = b;
        }

        static std::size_t get_npl(NodePtr a) {
            if (a == NULL)return 0;
            return get_node(a).nullPathLength;
        }
        static void set_npl(NodePtr a, std::size_t value) {
            if (a == NULL)return ;
            get_node(a).nullPathLength = value;
        }

        NodePtr bind(NodePtr a, NodePtr b) {
            if (a == NULL) return b;
            if (b == NULL) return a;
            if (compare(a, b)) {
                NodePtr swapTmp = a;
                a = b;
                b = swapTmp;
            }

            set_right(a, bind(get_right(a), b));

            if (get_npl(get_left(a)) < get_npl(get_right(a))) {
                NodePtr swapTmp = get_left(a);
                set_left(a, get_right(a));
                set_right(a, swapTmp);
            }
            set_npl(a, get_npl(get_right(a)) + 1);
            return a;
        }
        NodePtr root;
    public:
        LeftistTree(): root(0) {}

        void push(NodePtr a) {
            root = bind(root, a);
        }

        NodePtr pop() {
            NodePtr p = root;
            root = bind(get_left(root), get_right(root));
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
