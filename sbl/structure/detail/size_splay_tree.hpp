#ifndef _sbl_size_splay_tree_base
#define _sbl_size_splay_tree_base
#include"splay_tree.hpp"

namespace sbl {
namespace detail {

template<class NodePtr, class GetNode, class Expand, class Update>
class SizeSplayTreeBase;

template<class NodePtr>
class SizeSplayTreeNodeBase: public SplayTreeNodeBase<NodePtr> {
    private:
        template<class, class, class, class> friend class SizeSplayTreeBase;
        size_t size;
    public:
        SizeSplayTreeNodeBase(): size(1) {}
    protected:
        ~SizeSplayTreeNodeBase() {}
};

/** @brief Size Splay Tree
 *
 * Size splay tree an augmenting data structure, which add size attribute to every tree
 * nodes. Size attribute represent how many nodes in current subtree (treat the
 * node we focus as root). For more information, read CLRS Chapter 14.
 *
 * @tparam NodePtr a pointer to the node which defined by user.
 */

template<class NodePtr, class GetNode, class Expand, class Update>
class BaseOfSizeSplayTreeBase {
    private:

        typedef SizeSplayTreeBase<NodePtr, GetNode, Expand, Update> Self;

        struct SizeUpdate {
            void operator()(NodePtr parent, NodePtr left, NodePtr right) const {
                assert(parent != NULL);
                Update update;
                update(parent, left, right);
                Self::set_size(parent, Self::get_size(left) + Self::get_size(right) + 1);
            }
        };

        struct SizeExpand {
            void operator()(NodePtr parent, NodePtr left, NodePtr right) const {
                Expand expand;
                expand(parent, left, right);
            }
        };

    public:
        typedef SplayTreeBase<NodePtr, GetNode, SizeExpand, SizeUpdate> type;
};

template<class NodePtr, class GetNode, class Expand, class Update>
class SizeSplayTreeBase:
    public BaseOfSizeSplayTreeBase<NodePtr, GetNode, Expand, Update>::type {
    protected:
        ~SizeSplayTreeBase() {}
    public:
        typedef typename BaseOfSizeSplayTreeBase<NodePtr, GetNode, Expand, Update>::type Base;
        typedef SizeSplayTreeBase<NodePtr, GetNode, Expand, Update> Self;
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
        using Base::rotate;
        using Base::update;
        using Base::expand;

        using Base::add;
        using Base::del;
        using Base::find;

        static SizeSplayTreeNodeBase<NodePtr> &get_node(NodePtr a) {
            assert(a != NULL);
            return GetNode()(a);
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
        static NodePtr at(NodePtr root, size_t n) {
            assert(n >= 0);
            assert(n < get_size(root));
            return find(root, FindPosition(n));
        }
    private:
        struct InsertPosition {
            // almost like FindPosition, except return -1 when node found.
            mutable size_t idx;
            InsertPosition(size_t _): idx(_) {}
            int operator()(NodePtr current) {
                NodePtr leftChild = Self::get_left(current);
                size_t size = Self::get_size(leftChild);
                if (size == idx)
                    return -1;
                else if (size + 1 > idx)
                    return -1;
                else {
                    idx -= size + 1;
                    return 1;
                }
            }
        };
    public:
        /// @return insert a node to the n-th place
        static NodePtr insert(NodePtr root, size_t n, NodePtr newNode) {
            assert(n >= 0);
            assert(n <= get_size(root));
            return add(root, newNode, InsertPosition(n));
        }
};

} // namespace detail
} // namespace sbl
#endif
