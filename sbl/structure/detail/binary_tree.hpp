#ifndef _sbl_binary_tree_base
#define _sbl_binary_tree_base
#include<cstddef>
#include<cassert>

namespace sbl {
namespace detail {

template<class NodePtr, class GetNode> class BinaryTreeBase;

template<class NodePtr>
class BinaryTreeNodeBase {
    private:
        template<class, class> friend class BinaryTreeBase;
        NodePtr left;   ///< left child
        NodePtr right;  ///< right child
        NodePtr parent; ///< parent node
    public:
        BinaryTreeNodeBase(): left(NULL), right(NULL), parent(NULL) {}
    protected:
        ~BinaryTreeNodeBase() {}
};

template<class NodePtr, class GetNode>
class BinaryTreeBase {
    protected:
        ~BinaryTreeBase() {}
    public:

        /// get the node information from NodePtr
        static BinaryTreeNodeBase<NodePtr> &get_node(NodePtr a) {
            assert(a != NULL);
            return GetNode()(a);
        }

        /// get the child according index {0: left, 1: right}
        static NodePtr get_child(NodePtr a, size_t idx) {
            assert(idx == 0 or idx == 1);
            if (idx == 0)
                return get_left(a);
            else
                return get_right(a);
        }

        /// get left child
        static NodePtr get_left(NodePtr a) {
            if (a == NULL) return NULL;
            return get_node(a).left;
        }

        /// get right child
        static NodePtr get_right(NodePtr a) {
            if (a == NULL) return NULL;
            return get_node(a).right;
        }

        /// get parent
        static NodePtr get_parent(NodePtr a) {
            if (a == NULL)return NULL;
            return get_node(a).parent;
        }
    private:

        /// set the child according index {0: left, 1: right}
        static void set_child(NodePtr a, size_t idx, NodePtr b) {
            assert(idx == 0 or idx == 1);
            if (idx == 0)
                set_left(a, b);
            else
                set_right(a, b);
        }

        /// set left child
        static void set_left(NodePtr a, NodePtr b) {
            if (a == NULL) return ;
            get_node(a).left = b;
        }

        /// set right child
        static void set_right(NodePtr a, NodePtr b) {
            if (a == NULL) return ;
            get_node(a).right = b;
        }

        /// set parent
    public:
        static void link_left(NodePtr a, NodePtr b) {
            set_left(a, b);
            set_parent(b, a);
        }
        static void link_right(NodePtr a, NodePtr b) {
            set_right(a, b);
            set_parent(b, a);
        }
        static void link_child(NodePtr a, size_t idx, NodePtr b) {
            set_child(a, idx, b);
            set_parent(b, a);
        }
        static void set_parent(NodePtr a, NodePtr b) {
            if (a == NULL) return ;
            get_node(a).parent = b;
        }

        /// check if x is a right child
        static bool is_right(NodePtr x) {
            assert(x != NULL);
            NodePtr y = get_parent(x);
            if (y == NULL) return false;
            return get_right(y) == x;
        }

        /// check if x is a left child
        static bool is_left(NodePtr x) {
            return not is_right(x);
        }
}; // class BinaryTreeBase

} // namespace detail
} // namespace sbl
#endif
