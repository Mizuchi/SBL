#ifndef _sbl_order_statistic_tree_intrusive
#define _sbl_order_statistic_tree_intrusive
#include<cstddef>
#include<cstdlib>
#include<cassert>

/** \brief This is a intrusive data structure version of order statistic
 * tree.
 *
 * User must provide the node type, manage the memory, and guarantee:
 *
 * Member variant OrderStatisticTreeNode<NodePtr> node record the
 * information.
 *
 * Member function bool less_than(NodePtr other) to use for all comparisons
 * of keys
 */

namespace sbl {
namespace intrusive {

template < class NodePtr >
class OrderStatisticTree;

size_t random() {
    size_t c = rand() * rand();
    return c ? c : 1;
}

template<class NodePtr>
class OrderStatisticTreeNode {
        friend class OrderStatisticTree<NodePtr>;
        NodePtr child[2];
        size_t size;
        size_t priority;
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

template < class NodePtr >
class OrderStatisticTree {
    /// This data structure implement by using Treap.
    /// Treap is a binary search tree.
    private:

        /// get the node information from NodePtr
        OrderStatisticTreeNode<NodePtr> &get_node(NodePtr a) {
            return a->node;
        }

        /// get the left child from a NodePtr
        NodePtr &l(NodePtr a) {
            return get_node(a).child[0];
        }

        /// get the right child from a NodePtr
        NodePtr &r(NodePtr a) {
            return get_node(a).child[1];
        }

        /// get the child according index.
        /// 
        /// @param index 0 represent left child, 1 represent right child.
        ///
        NodePtr &child(NodePtr a, size_t idx) {
            if (idx == 0) return l(a);
            if (idx == 1) return r(a);
            assert(false && "OrderStatisticTree:: subscript range error");
        }

        /// get priority from a NodePtr for treap
        size_t &priority(NodePtr a) {
            return get_node(a).priority;
        }

        /// update the size of current NodePtr
        void update_size(NodePtr a) {
            size(a) = size(l(a)) + size(r(a)) + 1;
        }

        /// Swap a NodePtr with her father.
        NodePtr rotate(NodePtr t, size_t idx) {
            assert(idx == 0 or idx == 1);
            NodePtr s = child(t, idx);
            child(t, idx) = child(s, 1 - idx);
            child(s, 1 - idx) = t;
            update_size(t);
            update_size(s);
            return s;
        }

        /// Add NodePtr a to subtree x.
        void add(NodePtr x, NodePtr &a) {
            if (a == nullPtr) {
                a = x;
                l(a) = r(a) = nullPtr;
                size(a) = 1;
                priority(a) = random();
            } else {
                int c = x->compare(a) ? 0 : 1;
                add(x, child(a, c));
                if (priority(child(a, c)) <= priority(a))
                    size(a)++;
                else
                    a = rotate(a, c);
            }

        }

        /// Delete NodePtr a from subtree x.
        NodePtr del(NodePtr x, NodePtr &a) {
            if (a == nullPtr) return 0;
            int c = x->compare(a) ? 0 : a->compare(x) ? 1 : 2;
            if (c == 2) {
                if (l(a) == r(a) and  r(a) == nullPtr) {
                    NodePtr ret = a;
                    a = nullPtr;
                    return ret;
                }
                c = priority(l(a)) > priority(r(a)) ? 1 : 0;
                a = rotate(a, 1 - c);
            }
            NodePtr ret = del(x, child(a, c));
            if (ret != 0)
                size(a)--;
            return ret;
        }

        /// @return number of nodes in subtree a.
        size_t &size(NodePtr a) {
            return get_node(a).size;
        }

        NodePtr root;    
        NodePtr nullPtr; ///< a sentinel denote the empty pointer
    public:
        /** Since OrderStatisticTree could not be allocated memory for a NodePtr,
         * the user must given a useless NodePtr as a sentinel.
         */
        OrderStatisticTree(NodePtr a): root(a), nullPtr(a) {
            l(a) = r(a) = a;
            size(a) = 0;
            priority(a) = 0;
        }

        /// @return number of all nodes.
        size_t size() const{
            return root->node.size;
        }

        /// add NodePtr x to root.
        void insert(NodePtr x) {
            add(x, root);
        }

        /// remove NodePtr from root.
        NodePtr erase(NodePtr x) {
            return del(x, root);
        }

        /// @param x the NodePtr for comparing.
        /// @param a which subtree we are focused.
        ///
        /// @return number of nodes that (key) smaller than NodePtr x.
        size_t smaller_count(NodePtr x, NodePtr a = 0) {
            if (a == 0) a = root;
            if (a == nullPtr) return 0;
            if (!a->compare(x)) return smaller_count(x, l(a));
            return smaller_count(x, r(a)) + size(l(a)) + 1;
        }

        /// @param x the NodePtr for comparing.
        /// @param a which subtree we are focused.
        ///
        /// @return number of nodes that (key) bigger than NodePtr x.
        size_t bigger_count(NodePtr x, NodePtr a = 0) {
            if (a == 0) a = root;
            if (a == nullPtr) return 0;
            if (!x->compare(a)) return bigger_count(x, r(a));
            return bigger_count(x, l(a)) + size(r(a)) + 1;
        }
        /// @param x the NodePtr for comparing.
        /// @param a which subtree we are focused.
        ///
        /// @return first NodePtr smaller than NodePtr x.
        NodePtr smaller(NodePtr x, NodePtr a = 0) {
            if (a == 0) a = root;
            if (a == nullPtr) return 0;
            if (!a->compare(x)) return smaller(x, l(a));
            else {
                NodePtr b = smaller(x, r(a));
                return b == 0 ? a : b;
            }
        }
        /// @param x the NodePtr for comparing.
        /// @param a which subtree we are focused.
        ///
        /// @return first NodePtr bigger than NodePtr x.
        NodePtr bigger(NodePtr x, NodePtr a = 0) {
            if (a == 0) a = root;
            if (a == nullPtr) return 0;
            if (!x->compare(a)) return bigger(x, r(a));
            else {
                NodePtr b = bigger(x, l(a));
                return b == 0 ? a : b;
            }
        }
        /// @return the minimum node
        NodePtr smallest(NodePtr a = 0) {
            if (a == 0) a = root;
            if (a == nullPtr || l(a) == nullPtr) return a;
            return smallest(l(a));
        }
        /// @return the maximum node
        NodePtr biggest(NodePtr a = 0) {
            if (a == 0) a = root;
            if (a == nullPtr || r(a) == nullPtr) return a;
            return biggest(r(a));
        }
        /// @return the n-th small node.
        NodePtr at(size_t n, NodePtr a = 0) {
            if (a == 0) a = root;
            size_t ls = size(l(a));
            return ls == n ? a :
                   ls >  n ? at(n, l(a)) :
                   at(n - ls - 1, r(a));
        }
        /// @return the node equal to x.
        NodePtr find(NodePtr x, NodePtr a = 0) {
            if (a == 0) a = root;
            return a == nullPtr  ? 0 :
                   x->compare(a) ? find(x, l(a)) :
                   a->compare(x) ? find(x, r(a)) : a;
        }
};

} // namespace intrusive
} // namespace sbl
#endif
