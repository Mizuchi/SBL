#ifndef _sbl_order_statistic_tree
#define _sbl_order_statistic_tree
#include<cstddef>
#include<cstdlib>
#include<cassert>
#include"detail/splay_tree.hpp"

/** \brief This is a intrusive data structure version of order statistic
 * tree.
 *
 * User must provide the node type, manage the memory, and guarantee:
 */

namespace sbl {

template<class NodePtr, class GetNode>
class OrderStatisticTree;

template<class NodePtr>
class OrderStatisticTreeNode {
        template<class, class> friend class OrderStatisticTree;
    public:
        ::sbl::detail::SplayTreeNode<NodePtr> node;
        size_t size;
        OrderStatisticTreeNode(): size(1) {}
};

/** @brief order statistic tree is a data structure described in Introduction
 * to Algorithm.
 *
 * This is an augmenting data structure, which add size attribute to every tree
 * nodes.  Size attribute represent how many nodes in current subtree (treat the
 * node we focus as root). For more information, read CLRS Chapter 14.
 *
 *
 * @tparam NodePtr a pointer to the node which defined by user.
 */

template < class NodePtr, class GetNode>
class OrderStatisticTree {
        /// This data structure implement by using Treap.
        /// Treap is a binary search tree.
    private:
        NodePtr root;
        typedef OrderStatisticTree<NodePtr, GetNode> Self;

        struct Update {
            void operator()(NodePtr parent, NodePtr left, NodePtr right) const {
                assert(parent != NULL);
                Self::set_size(parent, Self::get_size(left) + Self::get_size(right) + 1);
            }
        };

        struct Expand {
            void operator()(...) const {}
        };

        struct GetSplayNode {
            ::sbl::detail::SplayTreeNode<NodePtr>
            &operator()(NodePtr a) const {
                return Self::get_node(a).node;
            }
        };

        typedef ::sbl::detail::SplayTree <
            NodePtr,
            GetSplayNode,
            Expand,
            Update 
        > SplayTree;

        SplayTree st;

        static NodePtr get_left(NodePtr a) {
            return SplayTree::get_left(a);
        }
        static NodePtr get_right(NodePtr a) {
            return SplayTree::get_right(a);
        }

        /// get the node information from NodePtr
        static OrderStatisticTreeNode<NodePtr> &get_node(NodePtr a) {
            assert(a != NULL);
            GetNode getNode;
            return getNode(a);
        }

        /// @return number of nodes in subtree a.
        static size_t get_size(NodePtr a) {
            if (a == NULL) return 0;
            return get_node(a).size;
        }

        /// change size attribute.
        static void set_size(NodePtr a, size_t value) {
            if (a == NULL) return;
            get_node(a).size = value;
        }

        struct ThreeWay {
            NodePtr x;
            int operator()(NodePtr y) const {
                if (x->less_than(y)) return -1;
                if (y->less_than(x)) return +1;
                return 0;
            }
            ThreeWay(NodePtr _): x(_) {}
        };

    public:

        OrderStatisticTree(): root(NULL) {}

        /// @return number of all nodes.
        size_t size() {
            return get_size(root);
        }

        /// add a new node to root
        void insert(NodePtr x) {
            assert(x != NULL);
            root = st.add(root, x, ThreeWay(x));
        }

        /// @return the node has been removed.
        NodePtr erase(NodePtr x) {
            ThreeWay compare(x);
            root = st.find(root, compare);
            if (compare(root) == 0) {
                NodePtr delNode = root;
                root = st.del(root);
                return delNode;
            }
            return NULL;
        }

        /// @return number of nodes that smaller than NodePtr x.
        size_t smaller_count(NodePtr x) {
            assert(x != NULL);
            if (smaller(x) == NULL)
                return 0;
            NodePtr leftChild = get_left(root);
            return get_size(leftChild) + 1;
        }

        /// @return number of nodes that bigger than NodePtr x.
        size_t bigger_count(NodePtr x) {
            assert(x != NULL);
            if (bigger(x) == NULL)
                return 0;
            NodePtr rightChild = get_right(root);
            return get_size(rightChild) + 1;
        }

    private:
        struct Smaller3Way {
            NodePtr store;
            int operator()(NodePtr current) const {
                if (current->less_than(store)) return 1;
                return -1;
            }
            Smaller3Way(NodePtr _): store(_) {}
        };
    public:

        /// @return first NodePtr smaller than NodePtr x.
        NodePtr smaller(NodePtr x) {
            root = st.find(root, Smaller3Way(x));
            assert(x != NULL);
            assert(root != NULL);
            if (root->less_than(x))
                return root;
            else {
                // half change to splay the bigger one.
                root = st.find(root, Smaller3Way(x));
                assert(x != NULL);
                assert(root != NULL);
                if (root->less_than(x))
                    return root;
                else
                    return NULL;
            }
        }

    private:
        struct Bigger3Way {
            NodePtr store;
            int operator()(NodePtr current) const {
                if (store->less_than(current))
                    return -1;
                return 1;
            }
            Bigger3Way(NodePtr _): store(_) {}
        };
    public:

        /// @return first NodePtr bigger than NodePtr x.
        NodePtr bigger(NodePtr x) {
            root = st.find(root, Bigger3Way(x));
            assert(x != NULL);
            assert(root != NULL);
            if (x->less_than(root))
                return root;
            else {
                // half change to splay the smaller one.
                root = st.find(root, Bigger3Way(x));
                assert(x != NULL);
                assert(root != NULL);
                if (x->less_than(root))
                    return root;
                else
                    return NULL;
            }
        }

    private:
        template<int n>
        struct AlwaysReturn {
            int operator()(...) {
                return n;
            }
        };
    public:
        /// @return the minimum node.
        NodePtr smallest() {
            //root = st.find(root, AlwaysReturn < -1 > ());
            root = st.leftmost(root);
            assert(get_left(root) == NULL);
            return root;
        }
        /// @return the maximum node.
        NodePtr biggest() {
            //root = st.find(root, AlwaysReturn<1>());
            root = st.rightmost(root);
            assert(get_right(root) == NULL);
            return root;
        }

    private:
        struct FindPosition {
            mutable size_t idx;
            FindPosition(size_t _): idx(_) {}
            int operator()(NodePtr current) {
                NodePtr leftChild = Self::get_left(current);
                size_t size = Self::get_size(leftChild);
                if (size == idx)
                    return 0;
                else if (size + 1 > idx)
                    return -1;
                else {
                    idx -= size + 1;
                    return 1;
                }
            }

        };
    public:

        /// @return the n-th small node.
        NodePtr at(size_t n) {
            assert(n >= 0);
            assert(n < size());
            root = st.find(root, FindPosition(n));
            return root;
        }

        /// @return equivalence node of x.
        NodePtr find(NodePtr x) {
            root = st.find(root, ThreeWay(x));
            return root;
        }
        /// @return remove all node in OrderStatisticTree
        void clear() {
            root = NULL;
        }
};

} // namespace sbl
#endif
