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

template<class NodePtr>
class OrderStatisticTreeNode {
        friend class OrderStatisticTree<NodePtr>;
        NodePtr child[2];
        size_t size;
        size_t priority;
        size_t random() {
            size_t c = rand() * rand() + 1;
            return c;
        }
    public:
        OrderStatisticTreeNode(): size(1), priority(random()) {
            child[0] = child[1] = NULL;
        }
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

        /// get the node information from NodePtr, const version
        const OrderStatisticTreeNode<NodePtr> &get_node(NodePtr a) const {
            return a->node;
        }

        /// @return number of nodes in subtree a.
        const size_t &size(NodePtr a) const {
            static const size_t zero = 0;
            if (a == NULL) return zero;
            return get_node(a).size;
        }

        /// change size attribute.
        void set_size(NodePtr a, size_t value) {
            if (a == NULL) return;
            get_node(a).size = value;
        }

        /// get priority from a NodePtr for treap
        const size_t &priority(NodePtr a) const {
            static const size_t zero = 0;
            if (a == NULL) return zero;
            return get_node(a).priority;
        }

        /// get the child according index.
        ///
        /// @param a father
        /// @param index 0 represent left child, 1 represent right child.
        ///
        /// @return const reference of child
        const NodePtr &child(NodePtr a, size_t idx) const {
            assert(idx == 0 or idx == 1);
            static const NodePtr kNullPtr = NULL;
            if (a == NULL) return kNullPtr;
            return get_node(a).child[idx];
        }

        /// get the reference of child according index.
        ///
        /// @param a father, must not be NULL
        /// @param index 0 represent left child, 1 represent right child.
        ///
        /// @return reference of child
        NodePtr &child_references(NodePtr a, size_t idx) {
            assert(a != NULL);
            assert(idx == 0 or idx == 1);
            return get_node(a).child[idx];
        }

        /// change child
        void set_child(NodePtr a, size_t idx, NodePtr b) {
            if (a == NULL) return;
            get_node(a).child[idx] = b;
        }

        /// get the left child from a NodePtr
        const NodePtr &l(NodePtr a) const {
            return child(a, 0);
        }

        /// get the right child from a NodePtr
        const NodePtr &r(NodePtr a) const {
            return child(a, 1);
        }
        /// get the left child from a NodePtr
        const NodePtr &get_left(NodePtr a) const {
            return l(a);
        }

        /// get the right child from a NodePtr
        const NodePtr &get_right(NodePtr a) const {
            return r(a);
        }

        void set_left(NodePtr a, NodePtr x) {
            set_child(a, 0, x);
        }

        void set_right(NodePtr a, NodePtr x) {
            set_child(a, 1, x);
        }

        /// update the size of current NodePtr
        void update_size(NodePtr a) {
            set_size(a, size(l(a)) + size(r(a)) + 1);
        }

        NodePtr left_rotate(NodePtr x) {
            // Introduction to Algorithm 2nd edition P276
            if(get_right(x) == NULL) return NULL;
            NodePtr y = get_right(x);
            NodePtr b = get_left(y);
            set_right(x, b);
            set_left(y, x);
            return y;
        }

        NodePtr right_rotate(NodePtr y) {
            // Introduction to Algorithm 2nd edition P276
            if(get_left(y) == NULL) return NULL;
            NodePtr x = get_left(y);
            NodePtr b = get_right(x);
            set_left(y, b);
            set_right(x, y);
            return x;
        }

        /// Swap a NodePtr with his daughter
        NodePtr rotate(NodePtr t, size_t idx) {
            assert(idx == 0 or idx == 1);
            NodePtr s;
            if(idx == 0)
                s = right_rotate(t);
            else
                s = left_rotate(t);
            update_size(t);
            update_size(s);
            return s;
        }

        /// Add NodePtr x to subtree a.
        void add(NodePtr x, NodePtr &a) {
            if (a == NULL) {
                a = x;
            } else {
                size_t idx = x->less_than(a) ? 0 : 1;
                add(x, child_references(a, idx));
                if (priority(child(a, idx)) <= priority(a))
                    update_size(a);
                else
                    a = rotate(a, idx);
            }

        }

        /// Delete NodePtr a from subtree x.
        NodePtr del(NodePtr x, NodePtr &a) {
            if (a == NULL) return 0;
            size_t idx = x->less_than(a) ? 0 : a->less_than(x) ? 1 : 2;
            if (idx == 2) {
                // x and a are equivalence
                if (l(a) == r(a) and r(a) == NULL) {
                    NodePtr ret = a;
                    a = NULL;
                    return ret;
                }
                idx = priority(l(a)) > priority(r(a)) ? 1 : 0;
                a = rotate(a, 1 - idx);
            }
            NodePtr ret = del(x, child_references(a, idx));
            if (ret != 0)
                update_size(a);
            return ret;
        }

        /// @return number of nodes in subtree a smaller than x.
        size_t smaller_count(NodePtr x, NodePtr a) const {
            if (a == NULL)
                return 0;
            else if (not a->less_than(x))
                return smaller_count(x, l(a));
            else
                return smaller_count(x, r(a)) + size(l(a)) + 1;
        }

        /// @return number of nodes in subtree a bigger than x.
        size_t bigger_count(NodePtr x, NodePtr a) const {
            if (a == NULL)
                return 0;
            else if (not x->less_than(a))
                return bigger_count(x, r(a));
            else
                return bigger_count(x, l(a)) + size(r(a)) + 1;
        }

        /// @return node in subtree a smaller than x.
        NodePtr smaller(NodePtr x, NodePtr a) const {
            if (a == NULL)
                return 0;
            else if (not a->less_than(x)) {
                return smaller(x, l(a));
            } else {
                NodePtr b = smaller(x, r(a));
                return b == NULL ? a : b;
            }
        }

        /// @return node in subtree a bigger than x.
        NodePtr bigger(NodePtr x, NodePtr a) const {
            if (a == NULL)
                return 0;
            else if (not x->less_than(a)) {
                return bigger(x, r(a));
            } else {
                NodePtr b = bigger(x, l(a));
                return b == NULL ? a : b;
            }
        }

        /// @return smallest node in subtree a
        NodePtr smallest(NodePtr a) const {
            if (a == NULL || l(a) == NULL) return a;
            return smallest(l(a));
        }
        /// @return biggest node in subtree a
        NodePtr biggest(NodePtr a) const {
            if (a == NULL || r(a) == NULL) return a;
            return biggest(r(a));
        }

        /// @return n-th small node in subtree a.
        NodePtr at(size_t n, NodePtr a) const {
            if (a == 0) a = root;
            size_t ls = size(l(a));
            return ls == n ? a :
                   ls >  n ? at(n, l(a)) :
                   at(n - ls - 1, r(a));
        }

        /// @return equivalence of x in subtree a.
        NodePtr find(NodePtr x, NodePtr a) const {
            if (a == 0) a = root;
            return a == NULL  ? 0 :
                   x->less_than(a) ? find(x, l(a)) :
                   a->less_than(x) ? find(x, r(a)) : a;
        }

        NodePtr root;
    public:
        
        /// construct an empty OrderStatisticTree
        OrderStatisticTree(): root(NULL) {}

        /// @return number of all nodes.
        size_t size() const {
            return size(root);
        }

        /// add NodePtr x to root.
        void insert(NodePtr x) {
            add(x, root);
        }

        /// remove NodePtr from root.
        NodePtr erase(NodePtr x) {
            return del(x, root);
        }

        /// @return number of nodes that smaller than NodePtr x.
        size_t smaller_count(NodePtr x) const {
            return smaller_count(x, root);
        }

        /// @return number of nodes that bigger than NodePtr x.
        size_t bigger_count(NodePtr x) const {
            return bigger_count(x, root);
        }
        /// @return first NodePtr smaller than NodePtr x.
        NodePtr smaller(NodePtr x) const {
            return smaller(x, root);
        }
        /// @return first NodePtr bigger than NodePtr x.
        NodePtr bigger(NodePtr x) const {
            return bigger(x, root);
        }
        /// @return the minimum node.
        NodePtr smallest() const {
            return smallest(root);
        }
        /// @return the maximum node.
        NodePtr biggest() const {
            return biggest(root);
        }
        /// @return the n-th small node.
        NodePtr at(size_t n) const {
            return at(n, root);
        }
        /// @return equivalence node of x.
        NodePtr find(NodePtr x) const {
            return find(x, root);
        }
        /// @return remove all node in OrderStatisticTree
        void clear() {
            root = NULL;
        }
};

} // namespace intrusive
} // namespace sbl
#endif
