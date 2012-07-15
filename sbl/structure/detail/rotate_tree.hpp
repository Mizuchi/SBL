#ifndef _sbl_rotate_tree_base
#define _sbl_rotate_tree_base
#include"binary_tree.hpp"

namespace sbl {
struct DoNothing { void operator()(...) {} };
namespace detail {

template<class NodePtr>
class RotateTreeNodeBase: public BinaryTreeNodeBase<NodePtr> {
    protected:
        ~RotateTreeNodeBase() {}
};

template<class NodePtr, class GetNode, class Expand, class Update>
class RotateTreeBase : public BinaryTreeBase<NodePtr, GetNode> {
    protected:
        ~RotateTreeBase() {}
    public:

        typedef BinaryTreeBase<NodePtr, GetNode> Base;
        typedef RotateTreeBase<NodePtr, GetNode, Expand, Update> Self;
        using Base::get_left;
        using Base::get_right;
        using Base::get_child;
        using Base::get_parent;
        using Base::link_left;
        using Base::link_right;
        using Base::link_child;
        using Base::set_parent;
        using Base::is_left;
        using Base::is_right;
        using Base::get_node;

        static void expand(NodePtr parent, NodePtr left, NodePtr right) {
            return Expand()(parent, left, right);
        }

        static void update(NodePtr parent, NodePtr left, NodePtr right) {
            return Update()(parent, left, right);
        }

        /// expand node x information to his children
        static void expand(NodePtr x) {
            expand(x, get_left(x), get_right(x));
        }

        /// update node x information from his children
        static void update(NodePtr x) {
            update(x, get_left(x), get_right(x));
        }

        /// swap x to her father
        static void rotate(NodePtr x) {
            // CLRS 3rd edition Page 313.
            NodePtr y = get_parent(x);
            if (get_parent(y) != NULL) {
                if (get_left(get_parent(y)) == y)
                    link_left(get_parent(y), x);
                else
                    link_right(get_parent(y), x);
            } else {
                set_parent(x, NULL);
            }
            size_t c = (get_left(y) == x) ? 0 : 1;
            link_child(y, c, get_child(x, 1 - c));
            link_child(x, 1 - c, y);

            update(y);
            update(x);
        }
}; // class RotateTreeBase

} // namespace detail
} // namespace sbl
#endif
