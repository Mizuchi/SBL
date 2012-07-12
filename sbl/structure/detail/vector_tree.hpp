#ifndef _sbl_vector_tree_base
#define _sbl_vector_tree_base
#include"size_splay_tree.hpp"

namespace sbl {
namespace detail {

template<class NodePtr>
class VectorTreeNodeBase: public SizeSplayTreeNodeBase<NodePtr> {
    protected:
        ~VectorTreeNodeBase() {}
};

template<class NodePtr, class GetNode, class Update, class Expand>
class VectorTreeBase: public SizeSplayTreeBase<NodePtr, GetNode, Update, Expand> {
    protected:
        ~VectorTreeBase() {}
    public:
        typedef SizeSplayTreeBase<NodePtr, GetNode, Update, Expand> Base;
        typedef VectorTreeBase<NodePtr, GetNode, Update, Expand> Self;
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
        using Base::get_size;
        using Base::at;

        template<class Call>
        static NodePtr call_segment(NodePtr root, size_t l, size_t r, Call func) {
            assert(root != NULL);
            assert(get_parent(root) == NULL);
            assert(l <= r);
            assert(r <= get_size(root));
            if (l == r) {
                func(NULL);
                return root;
            }
            if (l == 0 and r == get_size(root)) {
                func(root);
            } else if (l == 0) {
                root = at(root, r);
                func(get_left(root));
                update(root);
            } else if (r == get_size(root)) {
                root = at(root, l - 1);
                func(get_right(root));
                update(root);
            } else {
                root = at(root, r);
                expand(root);
                NodePtr newRoot = get_left(root);

                link_left(root, NULL);
                set_parent(newRoot, NULL);

                newRoot = at(newRoot, l - 1);
                expand(newRoot);

                func(get_right(newRoot));

                update(newRoot);
                link_left(root, newRoot);
                update(root);
            }
            return root;
        }

        struct ReplaceSegment {
            // We want to afference a reference argument.
            // That's why we use point.
            NodePtr newNode;
            NodePtr *oldNodeSave;
            ReplaceSegment(NodePtr current, NodePtr *old)
                : newNode(current), oldNodeSave(old) {}
            void operator()(NodePtr oldNode) {
                NodePtr parent = Self::get_parent(oldNode);
                assert(parent != NULL);
                if (Self::is_left(oldNode))
                    Self::link_left(parent, newNode);
                else
                    Self::link_right(parent, newNode);
                *oldNodeSave = oldNode;
            }
        };

        NodePtr replace_segment(
            NodePtr root,
            size_t l,
            size_t r,
            NodePtr newNode,
            NodePtr *oldNode
        ) {
            assert(l < r);
            assert(r <= get_size(root));
            assert(l > 0 or r < get_size(root));
            return call_segment(root, l, r, ReplaceSegment(newNode, oldNode));
        }
}; // class VectorTree
} // namespace detail
} // namespace sbl
#endif
