#ifndef _sbl_order_statistic_tree
#define _sbl_order_statistic_tree
#include<cstddef>
#include<cstdlib>
#include<cassert>
#include"detail/order_statistic_splay_tree.hpp"

/** \brief This is a intrusive data structure version of order statistic
 * tree.
 *
 * User must provide the node type, manage the memory, and guarantee:
 */

namespace sbl {

template<class NodePtr, class GetNode, class Compare>
class OrderStatisticTree;

template<class NodePtr>
class OrderStatisticTreeNode:
    public ::sbl::detail::OrderStatisticSplayTreeNodeBase<NodePtr> {};

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

template < class NodePtr, class GetNode, class Compare>
class OrderStatisticTree
        :private ::sbl::detail::OrderStatisticSplayTreeBase<NodePtr, GetNode, DoNothing, DoNothing> {
        /// This data structure implement by using Splay Tree.
        /// Splay Tree is a binary search tree.
    private:
        Compare compare;

        typedef OrderStatisticTree<NodePtr, GetNode, Compare> Self;
        typedef ::sbl::detail::OrderStatisticSplayTreeBase<NodePtr, GetNode, DoNothing, DoNothing> Base;

        struct ThreeWay {
            NodePtr x;
            int operator()(NodePtr y) const {
                if (compare(x, y)) return -1;
                if (compare(y, x)) return +1;
                return 0;
            }
            Compare compare;
            ThreeWay(NodePtr _): x(_) {}
        };

        NodePtr root;
        using Base::get_left;
        using Base::get_right;
        using Base::get_size;
        using Base::add;
        using Base::find;
        using Base::del;
        using Base::leftmost;
        using Base::rightmost;
        using Base::at;
    public:

        OrderStatisticTree(): root(NULL) {}

        /// @return number of all nodes.
        size_t size() {
            return get_size(root);
        }

        /// add a new node to root
        void insert(NodePtr x) {
            assert(x != NULL);
            root = add(root, x, ThreeWay(x));
        }

        /// @return the node has been removed.
        NodePtr erase(NodePtr x) {
            ThreeWay compare(x);
            root = find(root, compare);
            if (compare(root) == 0) {
                NodePtr delNode = root;
                root = del(root);
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
                if (compare(current, store)) return 1;
                return -1;
            }
            Compare compare;
            Smaller3Way(NodePtr _): store(_) {}
        };
    public:

        /// @return first NodePtr smaller than NodePtr x.
        NodePtr smaller(NodePtr x) {
            root = find(root, Smaller3Way(x));
            assert(x != NULL);
            assert(root != NULL);
            if (compare(root, x)) {
                return root;
            } else {
                // half change to splay the bigger one.
                root = find(root, Smaller3Way(x));
                assert(x != NULL);
                assert(root != NULL);
                if (compare(root, x))
                    return root;
                else
                    return NULL;
            }
            assert(false);
        }

    private:
        struct Bigger3Way {
            NodePtr store;
            int operator()(NodePtr current) const {
                if (compare(store, current))
                    return -1;
                return 1;
            }
            Compare compare;
            Bigger3Way(NodePtr _): store(_) {}
        };
    public:

        /// @return first NodePtr bigger than NodePtr x.
        NodePtr bigger(NodePtr x) {
            root = find(root, Bigger3Way(x));
            assert(x != NULL);
            assert(root != NULL);
            if (compare(x, root)) {
                return root;
            } else {
                // half change to splay the smaller one.
                root = find(root, Bigger3Way(x));
                assert(x != NULL);
                assert(root != NULL);
                if (compare(x, root))
                    return root;
                else
                    return NULL;
            }
            assert(false);
        }

        /// @return the minimum node.
        NodePtr smallest() {
            root = leftmost(root);
            assert(get_left(root) == NULL);
            return root;
        }
        /// @return the maximum node.
        NodePtr biggest() {
            root = rightmost(root);
            assert(get_right(root) == NULL);
            return root;
        }

        /// @return n-th node
        NodePtr at(size_t n) {
            root = at(root, n);
            return root;
        }

        /// @return equivalence node of x.
        NodePtr find(NodePtr x) {
            root = find(root, ThreeWay(x));
            return root;
        }
        /// @return remove all node in OrderStatisticTree
        void clear() {
            root = NULL;
        }
};

} // namespace sbl
#endif
